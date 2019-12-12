#include <fstream>
#include <codecvt>
#include <iostream>
#include <fmt/format.h>
#include "utils.h"
#include "calmsize.h"
#include "ksy_helper.h"

std::size_t
code_points(const std::string& utf8)
{
    std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t> utf16conv;
    std::u16string utf16 = utf16conv.from_bytes(utf8);
    return utf16.length();
}

double
duration(const fs::path& path, ext ftype)
{
    std::ifstream ifs(path, std::ifstream::binary);
    kaitai::kstream ks(&ifs);
    switch(ftype)
    {
        case ext::unknown:    throw std::runtime_error("y u do dis to me");
        case ext::avi: return avi_duration(&ks);
        case ext::mkv: return mkv_duration(&ks) / 1000;
        case ext::mp4: return mp4_duration(&ks);
    }
}

std::string
format(std::uintmax_t bytes)
{
    return human_filesize(bytes);
}

std::string
format(double seconds)
{
    return human_duration(seconds);
}

std::string
pad(const std::string& s, std::size_t max)
{
    // "Hello", 10 -> "Hello    "
    using namespace std::string_literals;
    if (auto cp = code_points(s); cp < max) {
        auto spaces = ""s;
        spaces.resize(max - cp, ' ');
        return s + spaces;
    }
    return s;
}

void
print_argv(char *argv, char *environ)
{
    while (argv < environ)
    {
        std::cout << ((0 == *argv) ? ' ' : *argv);
        argv ++;
    }
    std::cout << '\n';
}

std::pair<bool, ext>
encode_extension(const fs::path& path)
{
    auto code = uint32_t{};
    auto tail = std::array<unsigned char, 4>{};
    auto name = path.filename().string();
    if (name.length() < tail.size())
        return {false, ext::unknown};
    std::transform(std::end(name) - tail.size(),
                   std::end(name),
                   std::begin(tail),
                   [](unsigned char c){ return std::tolower(c);});
    std::memcpy(&code, tail.data(), tail.size());
    switch (code)
    {
        case 0x6976612e: return {true, ext::avi};
        case 0x766b6d2e: return {true, ext::mkv};
        case 0x34706d2e: return {true, ext::mp4};
    }
    return {false, ext::unknown};
}

