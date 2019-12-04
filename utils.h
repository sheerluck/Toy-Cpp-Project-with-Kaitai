#pragma once

#include <filesystem>

namespace fs = std::filesystem;

std::uint16_t
duration(fs::directory_entry path);

std::string
format(std::uintmax_t bytes);

std::string
format(std::uint16_t seconds);

std::string
pad(std::string s, int max);
