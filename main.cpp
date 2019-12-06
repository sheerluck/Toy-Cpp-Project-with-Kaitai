#include <map>
#include <filesystem>
#include "utils.h"
#include "rang.hpp"

namespace fs = std::filesystem;
using Same = std::vector<fs::directory_entry>;

int main() {
    using namespace std::string_literals;
    const auto extension = ".mkv"s;
    auto data = std::map<std::uint16_t, Same>{};
    auto max = 1u;
    for(const auto& p: fs::recursive_directory_iterator(fs::current_path()))
    {
        if (p.path().string().ends_with(extension))
        {
            auto name = p.path().filename().string();
            auto cp = code_points(name);
            if (cp > max) max = cp;
            auto key = duration(p.path());
            auto [it, ok] = data.try_emplace(key, Same{p});
            if (!ok) data[key].push_back(p);
        }
    }

    for (auto& [key, vec] : data)
    {
        std::sort(std::begin(vec), std::end(vec));
        for (const auto& p : vec)
        {
            std::cout
            << rang::fgB::blue
            << pad(p.path().filename().string(), max)
            << rang::fg::reset

            << " goes on "

            << rang::fgB::green
            << format(key)
            << rang::fg::reset

            << ", " << format(fs::file_size(p)) << '\n';
        }
    }
}
