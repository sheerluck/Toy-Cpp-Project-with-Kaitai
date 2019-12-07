#pragma once

#include <string>

std::string
human_filesize(const std::uintmax_t size);

std::string
human_duration(const double seconds);
