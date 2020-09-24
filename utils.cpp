#include <fstream>
#include <codecvt>
#include <iostream>
#include <regex>
#include <forward_list>
#include <algorithm>
#include <cxxopts.hpp>
#include <fmt/format.h>
#include "utils.h"
#include "reverse.h"
#include "universal_iterator.h"
#include "rang.hpp"
#include "calmsize.h"
#include "ksy_helper.h"

void
say_what_again(const std::exception& e,
               const std::string& info)
{
    std::cout
    << rang::fgB::red
    << e.what()
    << (info.empty() ? info : "\n"s + info)
    << rang::fg::reset
    << '\n';
}

config
parse_options(int argc, char *argv[])
{
    cxxopts::Options options("mkv", "description");
    auto result = config{};
    options.add_options()
        ("h,help",           "help")
        ("p,path",           "path",
          cxxopts::value<std::string>()->default_value(fs::current_path().string()))
        ("t,top",            "top",
          cxxopts::value<std::uint64_t>()->default_value("10"))
        ("f,flat",           "flat");
    auto opt = options.parse(argc, argv);
    if (opt["help"].as<bool>())
    {
        result.help = true;
    }
    else
    {
        result.path = opt["path"].as<std::string>();
        result.flat = opt["flat"].as<bool>();
        result.top  = opt["top" ].as<std::uint64_t>();
    }
    return result;
}

std::vector<pair>
search(const std::string& path,
       bool flag)
{
    auto fist = std::forward_list<pair>{};
    auto size = std::uint64_t{0};
    for(const auto& p: universal_iterator(path, flag))
        if (fs::is_regular_file(p))
            if (const auto [fit, code] = encode_extension(p); fit)
            {
                fist.push_front({code, p.path()});
                ++size;
            }
    auto result = std::vector<pair>{};
    result.reserve(size);
    std::generate_n(std::back_inserter(result),
                    size,
                    [iter = std::begin(fist)]() mutable
                    {return std::move(*iter++); });
    return result;
}

std::map<std::string, Same>
process(const std::vector<pair>& names)
{
    auto data = std::map<std::string, Same>{};
    for (const auto& [code, p] : names)
    {
        try
        {
            const auto milli = duration(p, code);
            const auto key = format(milli);
            const auto [it, ok] = data.try_emplace(key, Same{p});
            if (!ok) data[key].push_back(p);
        }
        catch (const std::exception& e)
        {
            say_what_again(e, p.string());
        }

    }
    return data;
}

void
padded_filename(const auto p,
                const auto time,
                const auto max)
{
    std::cout
        << "    "
        << rang::fgB::blue
        // << std::left << std::setw(max)  << name  -- no code point awareness
        << pad(p.filename().string(), max)
        << rang::fg::reset
        << " -- "
        << rang::fgB::green
        << time
        << rang::fg::reset
        << " -- ";
}

void
padded_filesize(const auto p)
{
    auto s = format(fs::file_size(p));
    if (s.ends_with("Gb"))
    {
        std::cout
        << rang::fgB::red
        << std::right << std::setw(9)
        << s
        << rang::fg::reset;
    }
    else
    {
        std::cout
        << std::right << std::setw(9)
        << s;
    }
}


void
print_sorted_top(Map& m,
                 const std::uint64_t atop)
{
    auto cur = atop;
    const auto max = get_max(m, atop);
    std::cout << "\n\n";
    for (auto& [time, vec] : reverse(m))
    {
        std::sort(std::begin(vec), std::end(vec));
        for (const auto& p : vec)
        {
            cur -= 1;
            padded_filename(p, time, max);
            padded_filesize(p);
            std::cout << '\n';
            if (0 == cur) break;
        }
        if (0 == cur) break;
    }
    std::cout << "\n\n";

}

int
print_help()
{
    std::cout << rang::fg::green
              << strip_margin(R"HELP(
              |Usage: mkv [options]
              |Longest movies (in current directory)
              |
              |Options:
              |  -h, --help            Displays this help.
              |  -p, --path Videos     Path to movies.
              |  -t, --top 30          Number of lines to show.
              |                        Default is 10, 0 is inf.
              |  -f, --flat            No recursion.)HELP")
              << rang::fg::reset
              << "\n\n";
    return 0;
}


std::size_t
get_max(const Map& m,
        const std::uint64_t copy)
{
    auto max = std::size_t{0};
    auto cur = std::size_t{copy};
    for (const auto& [key, vec] : reverse(m))
    {
        for (const auto& p : vec)
        {
            cur -= 1;
            auto name = p.filename().string();
            auto cp = code_points(name);
            if (cp > max) max = cp;
            if (0 == cur) return max;
        }
    }
    return max;

}

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
        case ext::webm:
        case ext::mkv:  return mkv_duration(&ks) / 1000;
        case ext::mp4:  return mp4_duration(&ks, fs::file_size(path));
    }
    return 3.1415926;
}


std::string
format(const std::uintmax_t bytes)
{
    return human_filesize(bytes);
}

std::string
format(const double seconds)
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
    switch (code) // hex(int.from_bytes(b"webm", byteorder="little", signed=False))
    {
        case 0x6d626577: return {true, ext::webm};
        case 0x766b6d2e: return {true, ext::mkv};
        case 0x34706d2e: return {true, ext::mp4};
    }
    return {false, ext::unknown};
}

std::string
strip_margin(const std::string &s)
{
    auto r = std::regex{R"(\n([ ]*)\|)"};
    return   std::regex_replace(s, r, "\n");
}
