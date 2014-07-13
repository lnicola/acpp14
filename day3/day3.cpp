#include <algorithm>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <tuple>

using namespace std;

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
    string date_;
    string message_;

    entry(entry_kind kind, string date, string message)
        : kind_(kind), date_(date), message_(message)
    {
    }
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
}

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
    ifstream file("input.txt");
    string s;
    vector<string> lines;
    vector<entry> entries;

    while (getline(file, s))
        lines.push_back(s);

    for (auto &line : lines)
        entries.push_back(parse_entry(line));

    for (auto &e : entries)
        if (e.kind_ == entry_kind::error)
            cout << e.message_ << endl;
}
