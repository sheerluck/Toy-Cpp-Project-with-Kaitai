#include "calmsize.h"
#include <fmt/format.h>
#include <fmt/printf.h>

std::string
human_filesize(const std::uintmax_t size)
{
    // ported from hachoir.core.tools
    using namespace std::string_literals;
    using namespace fmt::literals;
    if (size < 10000)
    {
        return fmt::format("{size} bytes",
                            "size"_a = size);
    }
    auto units = {"Kb", "Mb", "Gb", "Tb"};
    auto fsize = static_cast<float>(size);
    auto divsr = 1024;
    auto xunit = "BUG"s;
    for (const auto& unit : units)
    {
        xunit = unit;
        fsize /= divsr;
        if (fsize < divsr)
            return fmt::sprintf("%.1f %s", fsize, unit);
    }
    return fmt::sprintf("%u %s", fsize, xunit);
}

std::string
human_duration(const double seconds)
{
    auto s = std::llround(seconds);
    auto H = s / (60 * 60);
    auto m = s % (60 * 60); 
    auto M = m / 60;
    auto S = m % 60;
    return fmt::sprintf("%.2d:%.2d:%.2d", H, M, S);
}
