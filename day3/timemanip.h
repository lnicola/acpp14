#pragma once

#include <chrono>
#include <ctime>
#include <iomanip>
#include <istream>
#include <ostream>

template<typename T>
class get_system_time_helper
{
public:
    std::chrono::system_clock::time_point &time_;
    const T *format_;

    get_system_time_helper(std::chrono::system_clock::time_point &time, const T *format)
        : time_(time), format_(format)
    {
    }
};

template<typename T>
std::istream & operator>>(std::istream &stream, const get_system_time_helper<T> &helper)
{
    tm tm{};

    stream >> get_time(&tm, helper.format_);
    helper.time_ = system_clock::from_time_t(mktime(&tm));

    return stream;
}

template<typename T>
get_system_time_helper<T> get_system_time(std::chrono::system_clock::time_point &time, const T *format)
{
    return { time, format };
}

template<typename T>
class put_system_time_helper
{
public:
    std::chrono::system_clock::time_point &time_;
    const T *format_;

    put_system_time_helper(std::chrono::system_clock::time_point &time, const T *format)
        : time_(time), format_(format)
    {
    }
};

template<typename T>
std::ostream & operator<<(std::ostream &stream, const put_system_time_helper<T> &helper)
{
    time_t t = std::chrono::system_clock::to_time_t(helper.time_);
    return stream << std::put_time(std::localtime(&t), helper.format_);
}

template<typename T>
put_system_time_helper<T> put_system_time(std::chrono::system_clock::time_point &time, const T *format)
{
    return{ time, format };
}
