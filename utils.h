#pragma once

#include <filesystem>

namespace fs = std::filesystem;

std::size_t
code_points(const std::string& utf8);

double
duration(const fs::path& path);

std::string
format(std::uintmax_t bytes);

std::string
format(double milliseconds);


std::string
pad(const std::string& s, std::size_t max);
