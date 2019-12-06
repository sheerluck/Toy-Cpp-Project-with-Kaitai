#include <fstream>
#include <codecvt>
#include <fmt/format.h>
#include "utils.h"
#include "calmsize.h"

float
code_points(const std::string& utf8)
{
    std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t> utf16conv;
    std::u16string utf16 = utf16conv.from_bytes(utf8);
    return utf16.length();
}


std::uint16_t
duration(fs::path path)
{
    std::ifstream file(path);

    //auto storage = blob::input_storage(file);
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
pad(const std::string& s, int max)
{
    // "Hello", 10 -> "Hello    "
    using namespace std::string_literals;
    auto cp = code_points(s);
    if (cp < max) {
        auto spaces = ""s;
        spaces.resize(max - cp, ' ');
        return s + spaces;
    }
    return s;
}

