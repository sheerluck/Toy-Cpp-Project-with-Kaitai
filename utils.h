#pragma once

#include <filesystem>

namespace fs = std::filesystem;

enum class ext: unsigned
{
    unknown = 0,
    webm = 0x10,
    mkv  = 0x20,
    mp4  = 0x30,
};

std::size_t
code_points(const std::string& utf8);

double
duration(const fs::path& path, ext ftype);

std::string
format(const std::uintmax_t bytes);

std::string
format(const double seconds);

std::string
format(const fs::path& path);

std::string
pad(const std::string& s, std::size_t max);

void
print_argv(char *argv, char *environ);

std::pair<bool, ext>
encode_extension(const fs::path& path);

std::string
strip_margin(const std::string &s);
