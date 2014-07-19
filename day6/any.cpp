#include <iostream>
#include <memory>
#include <utility>

#ifndef _MSC_VER
namespace std
{
    template<class _Ty,
    class... _Types> inline
        typename enable_if<!is_array<_Ty>::value,
        unique_ptr<_Ty> >::type make_unique(_Types&&... _Args)
    {	// make a unique_ptr
        return (unique_ptr<_Ty>(new _Ty(std::forward<_Types>(_Args)...)));
    }
}
#endif

struct trace
{
    trace()
    {
        std::cout << "trace()" << std::endl;
    }

    trace(const trace &)
    {
        std::cout << "trace(const trace &)" << std::endl;
    }

    trace(trace &&)
    {
        std::cout << "trace(trace &&)" << std::endl;
    }

    trace & operator=(const trace &)
    {
        std::cout << "operator=(const trace &)" << std::endl;
        return *this;
    }

    trace & operator=(trace &&)
    {
        std::cout << "operator=(trace &&)" << std::endl;
        return *this;
    }

    ~trace()
    {
        std::cout << "~trace()" << std::endl;
    }
};

class any
{
    class any_holder_base
    {
    public:
        virtual std::unique_ptr<any_holder_base> clone() const = 0;
        virtual ~any_holder_base() { }
    };

    template<typename T>
    class any_holder : public any_holder_base
    {
    public:
        T value;

        any_holder(const T &value)
            : value(value) { }

        any_holder(T &&value)
            : value(std::move(value)) { }

        std::unique_ptr<any_holder_base> clone() const override
        {
            return std::make_unique<any_holder>(value);
        }
    };

    std::unique_ptr<any_holder_base> holder;

    template<typename T>
    friend const T * any_cast(const any &any);

    template<typename T>
    friend T * any_cast(any &any);

    template<typename T>
    friend T * any_cast(any &&any);

public:
    template<typename T>
    any(const T &value)
        : holder(std::make_unique<any_holder<T>>(value)) { }

    template<typename T, typename std::enable_if<
        !std::is_lvalue_reference<T>::value,
        int>::type = 0>
    any(T &&value)
        : holder(std::make_unique<any_holder<T>>(std::forward<T>(value))) { }

    any(const any &other)
        : holder(other.holder->clone()) { }

    any(any &&other)
        : holder(move(other.holder))
    {
    }

    template<typename T>
    any & operator=(const T &value)
    {
        holder = std::make_unique<any_holder<T>>(value);
        return *this;
    }

    template<typename T>
    any & operator=(T &&value)
    {
        holder = std::make_unique<any_holder<T>>(std::forward<T>(value));
        return *this;
    }

    any & operator=(const any &other)
    {
        holder = other.holder->clone();
        return *this;
    }

    any & operator=(any &&other)
    {
        holder = move(other.holder);
        return *this;
    }

    void swap(any &second)
    {
        using std::swap;
        swap(holder, second.holder);
    }

    void reset()
    {
        holder.reset();
    }

    operator bool() const
    {
        return static_cast<bool>(holder);

    }
};

void swap(any &first, any &second)
{
    first.swap(second);
}

template<typename T>
const T * any_cast(const any &any)
{
    if (auto holder_typed = dynamic_cast<const any::any_holder<T> *>(any.holder.get()))
        return &holder_typed->value;

    return nullptr;
}

template<typename T>
T * any_cast(any &any)
{
    if (auto holder_typed = dynamic_cast<any::any_holder<T> *>(any.holder.get()))
        return &holder_typed->value;

    return nullptr;
}

template<typename T>
T * any_cast(any &&any)
{
    if (auto holder_typed = dynamic_cast<any::any_holder<T> *>(any.holder.get()))
        return &holder_typed->value;

    return nullptr;
}

int main()
{
    any foo(42);
    const any bar(11);

    std::cout << *any_cast<int>(foo) << std::endl;
    std::cout << *any_cast<int>(any(10)) << std::endl;
    std::cout << any_cast<long>(foo) << std::endl;
    std::cout << *any_cast<int>(bar) << std::endl;

    foo = 3;
    foo = nullptr;
    foo = 4;

    any t1 = trace();
    t1 = trace();
}
