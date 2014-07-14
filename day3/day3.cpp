#include <algorithm>
#include <chrono>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <tuple>

#include "timemanip.h"

using namespace std;
using namespace std::chrono;

enum class entry_kind
{
    error,
    warning,
    info,
    unknown
};

class entry
{
public:
    entry_kind kind_;
    system_clock::time_point date_;
    string message_;

    entry(entry_kind kind, system_clock::time_point date, string message)
        : kind_(kind), date_(date), message_(message)
    {
    }

    entry()
    {
    }
};

entry_kind get_entry_kind(const string &s)
{
    static auto m =
    {
        make_tuple("ERROR", entry_kind::error),
        make_tuple("WARNING", entry_kind::warning),
        make_tuple("INFO", entry_kind::info),
    };

    for (const auto &t : m)
        if (s == get<0>(t))
            return get<1>(t);

    return entry_kind::unknown;
}

istream & operator>>(istream &stream, entry &e)
{
    string kind;
    system_clock::time_point date;
    string message;

    stream >> kind >> get_system_time(date, "%Y-%m-%d");
    stream.ignore();
    getline(stream, message);

    e = { get_entry_kind(kind), date, message };

    return stream;
}

int main()
{
    ifstream file("input.txt");
    vector<entry> entries;
    entry e;
     
    while (file >> e)
        entries.push_back(e);

    sort(entries.begin(), entries.end(),
        [](const entry &e1, const entry &e2) { return e1.date_ < e2.date_; });

    for (auto &e : entries)
        if (e.kind_ == entry_kind::error)
            cout << put_system_time(e.date_, "%Y-%m-%d") << ' ' << e.message_ << endl;
}
