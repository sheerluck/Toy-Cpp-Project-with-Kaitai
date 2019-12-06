#pragma once

#include <filesystem>

namespace fs = std::filesystem;

float
code_points(const std::string& utf8);

std::uint16_t
duration(fs::path path);

std::string
format(std::uintmax_t bytes);

std::string
format(std::uint16_t seconds);

std::string
pad(const std::string& s, int max);
