#include <algorithm>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <tuple>

using namespace std;

namespace ns1{
    class A {};
}
namespace ns2{
    class A {};
}

enum class e1 {
    a, b
};
enum class e2 {
    a, c, d
};

enum class entry_kind
{
    error,
    warning,
    info,
    unknown
};

bool starts_with(string s, string prefix)
{
    return s.compare(0, prefix.length(), prefix) == 0;
}

entry_kind get_entry_kind(string s)
{
    static auto m =
    {
        make_tuple("ERROR", entry_kind::error),
        make_tuple("WARNING", entry_kind::warning),
        make_tuple("INFO", entry_kind::info),
    };

    for (auto t : m)
        if (starts_with(s, get<0>(t)))
            return get<1>(t);

    return entry_kind::unknown;

    //if (starts_with(s, "ERROR"))
    //    return entry_kind::error;
    //if (starts_with(s, "WARNING"))
    //    return entry_kind::warning;
    //if (starts_with(s, "INFO"))
    //    return entry_kind::info;
    //
    //return entry_kind::unknown;
}

bool is_error_entry(string s)
{
    return starts_with(s, "ERROR");
}

bool is_info_entry(string s)
{
    return starts_with(s, "INFO");
}

bool f(int &r)
{
    r = 42;
    return true;
}

void print(int x)
{
    printf("%d\n", x);
}

void print(char x)
{
    printf("%c\n", x);
}

void print(int *p)
{
    printf("%d\n", *p);
}

class entry
{
public:
    entry_kind kind_;
    string date_;
    string message_;

    entry(entry_kind kind, string date, string message)
        : kind_(kind), date_(date), message_(message)
    {
    }
};

class ee
{
public:
    entry e;

    ee()
        : e(entry_kind::error, "", "")
    {
        e.date_;
    }
};

entry parse_entry(string line)
{
    auto pos = line.find(' ');
    auto kind = get_entry_kind(line.substr(0, pos));
    auto pos2 = line.find(' ', pos + 1);
    auto date = line.substr(pos + 1, pos2 - pos - 1);
    auto message = line.substr(pos2 + 1);

    return { kind, date, message };
}

int main()
{
    int x{ 10 };
    int y{ 10 };
    //my_struct_t ms { 1, 2, 3 };

    entry e{ entry_kind::error, "2014-07-12", "mesaj" };
    int yy{ 4.2 };

    vector<int> v { 1, 2, 3 };

    //entry e(entry_kind::error, "2014-07-12", "mesaj");
    //return 0;

    //int x = 14, *p = nullptr;
    //print(&x);
    ////print(nullptr);
    //print(42);
    //print('c');
    //return 0;
    //int x;
    //f(x);
    //cout << x << endl;
    //return 0;
    //int x = 42;
    //int &r = x;
    //r = 17;
    //int v[2];
    //int &q = v[1];
    //q = 34;
    //q = x;

    ifstream file("input.txt");
    string s;
    vector<string> lines;
    ns1::A a;
    vector<entry> entries;

    while (getline(file, s))
        lines.push_back(s);

    for (auto &line : lines)
    {
        entries.push_back(parse_entry(line));
    }

    for (auto &e : entries)
        if (e.kind_ == entry_kind::error)
            cout << e.message_ << endl;

    //line = "am modificat linia";

    //for (string line : lines)
    //    cout << line << endl;

    return 0;
    cout
        << count_if(lines.begin(), lines.end(), is_error_entry)
        << endl;


    lines.erase(
        remove_if(lines.begin(), lines.end(),
        [](string s) {
        return starts_with(s, "INFO");
    }),
        lines.end());

    for (string line : lines)
        cout << line << endl;

    return 0;

    printf("%s %d\n", "abc", 42);
    cout << "safsdf" << sizeof(int) << ' ' << 42 << endl;
}

