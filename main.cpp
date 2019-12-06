#include <map>
#include <filesystem>
#include <fmt/format.h>
#include "utils.h"

namespace fs = std::filesystem;
using Same = std::vector<fs::directory_entry>;

int main() {
    using namespace std::string_literals;
    using namespace fmt::literals;
    const auto extension = ".mkv"s;
    auto data = std::map<std::uint16_t, Same>{};
    auto max = 1u;
    for(const auto& p: fs::recursive_directory_iterator(fs::current_path()))
    {
        if (p.path().string().ends_with(extension))
        {
            auto name = p.path().filename().string();
            if (name.length() > max) max = name.length();
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
            fmt::print("{mkv:} goes on '{dur}' and occupies '{size}'\n",
                       "mkv"_a  = pad(p.path().filename().string(), max),
                       "size"_a = format(fs::file_size(p)),
                       "dur"_a  = format(key));
        }
    }
}