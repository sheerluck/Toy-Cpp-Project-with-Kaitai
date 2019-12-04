#include <iostream>
#include <filesystem>
#include <fmt/format.h>

namespace fs = std::filesystem;

int main() {
    using namespace std::string_literals;
    using namespace fmt::literals;
    auto extension = ".mkv"s;
    for(const auto& p: fs::recursive_directory_iterator(fs::current_path()))
    {
        if (p.path().string().ends_with(extension))
        {
            fmt::print("{mkv} has {size} bytes\n",
                        "mkv"_a  = p.path().filename().string(),
                        "size"_a = 42);
        }
    }
    return 0;
}