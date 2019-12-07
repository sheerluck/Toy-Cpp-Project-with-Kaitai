#pragma once

#include <filesystem>

namespace fs = std::filesystem;

float
code_points(const std::string& utf8);

double
duration(fs::path path);

std::string
format(std::uintmax_t bytes);

std::string
format(double milliseconds);


std::string
pad(const std::string& s, int max);
