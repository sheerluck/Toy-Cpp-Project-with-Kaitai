#include "utils.h"

std::uint16_t
duration(fs::directory_entry path)
{
    return 42;
}

std::string
format(std::uintmax_t bytes)
{
    return "3 Gb 2 Mb 3 Kb";
}

std::string
format(std::uint16_t seconds)
{
    return "00:00:42";
}

std::string
pad(const std::string s, int max)
{
    // "Hello", 10 -> "Hello    "
    using namespace std::string_literals;
    auto len = s.length();
    if (len < max) {
        auto spaces = ""s;
        spaces.resize(max - len, ' ');
        return s + spaces;
    }
    return s;
}

