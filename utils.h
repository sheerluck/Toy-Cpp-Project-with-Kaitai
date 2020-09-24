#pragma once

#include <map>
#include <filesystem>
#include <vector>

enum class ext: unsigned
{
    unknown = 0,
    webm = 0x10,
    mkv  = 0x20,
    mp4  = 0x30,
};

struct config
{
    std::string path = ".";
    std::uint64_t top = 10;
    bool help = false;
    bool flat = false;
};

namespace fs = std::filesystem;
using pair = std::tuple<ext, fs::path>;
using Same = std::vector<fs::path>;
using Map = std::map<std::string, Same>;
using namespace std::string_literals;

void
say_what_again(const std::exception& e,
               const std::string& info = ""s);

config
parse_options(int argc, char *argv[]);

std::vector<pair>
search(const std::string& path,
       bool flag);

Map
process(const std::vector<pair>& names);

void
print_sorted_top(Map& m,
                 const std::uint64_t atop);

int
print_help();

std::size_t
get_max(const Map& m,
        const std::uint64_t copy);

std::size_t
code_points(const std::string& utf8);

double
duration(const fs::path& path, ext ftype);

std::string
format(const std::uintmax_t bytes);

std::string
format(const double seconds);

std::string
pad(const std::string& s, std::size_t max);

void
print_argv(char *argv, char *environ);

std::pair<bool, ext>
encode_extension(const fs::path& path);

std::string
strip_margin(const std::string &s);
