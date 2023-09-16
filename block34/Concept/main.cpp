#include <iostream>
#include <concepts>
#include <type_traits>
#include <string>

template <typename T>
concept ComplexConcept = !std::has_virtual_destructor<T>::value && requires(const T v)
{
    {v.hash()} -> std::convertible_to<long>;
    {v.toString()} -> std::same_as<std::string>;
};

template <typename T>
struct Value
{
    T value;
    Value(T outer) : value(outer)
    {

    }

    ~Value()
    {

    }

    long hash() const
    {
        return static_cast<long>(value);
    }

    std::string toString() const
    {
        return std::to_string(value);
    }
};

template <typename T>
bool checkLong(T value) 
{
    return typeid(value) == typeid(long);
}

template <typename T>
bool checkString(T value) 
{
    return typeid(value) == typeid(std::string);
}

void print(ComplexConcept auto& obj) 
{   
    std::cout << "Whether the value is \'long\'? " << (checkLong(obj.hash()) ? " Yes!" : " No.") << std::endl;
    std::cout << "Whether the value is \'string\'? " << (checkString(obj.toString()) ? "Yes!" : "No.") << std::endl;
}

int main()
{
    Value<float> x(5.5);
    print(x);

    return 0;
}
