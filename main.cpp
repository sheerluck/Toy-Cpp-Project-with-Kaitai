#include <map>
#include <filesystem>
#include <cstdlib>
#include <cxxopts.hpp>
#include "utils.h"
#include "rang.hpp"
#include "reverse.h"

namespace fs = std::filesystem;
using Same = std::vector<fs::directory_entry>;

std::string expand_user(std::string path)
{
    if (not path.empty() and path[0] == '~')
    {
        auto home = std::getenv("HOME");
        path.replace(0, 1, home);
    }
    return path;
}

void say_what_again(const std::exception& e)
{
    std::cout
    << rang::fgB::red
    << e.what()
    << rang::fg::reset
    << '\n';
};

int main (int argc, char *argv[])
{
    using namespace std::string_literals;
    cxxopts::Options options("mkv", "description");
    options.add_options()
        ("h,help",           "help")
        ("p,path",           "path",
          cxxopts::value<std::string>()->default_value(fs::current_path().string()))
        ("t,top",            "top",
          cxxopts::value<long long>()->default_value("10"))
        ("f,flat",           "flat");
    auto opt_help = false;
    auto opt_path = ""s;
    auto opt_top  = 10LL;
    auto opt_flat = false;
    try
    {
        auto opt = options.parse(argc, argv);
        opt_help = opt["help"].as<bool>();
        opt_path = opt["path"].as<std::string>();
        opt_top  = opt["top" ].as<long long>();
        opt_flat = opt["flat"].as<bool>();
    }
    catch (const cxxopts::option_not_exists_exception& e)
    {
        say_what_again(e);
        return 19;
    }
    catch (const cxxopts::option_requires_argument_exception& e)
    {
        say_what_again(e);
        return 17;
    }
    if (opt_help)
    {
        std::cout
        << rang::fg::green
        << R"HELP(
Usage: mkv [options]
Longest movies in color (in current directory or whatever)

Options:
  -h, --help                  Displays this help.
  -p, --path "Videos/Mkv"     Path to movies.
  -t, --top 30                Number of lines to show.
                              Default is 10, 0 is inf.
  -f, --flat                  No recursion.
)HELP"
        << rang::fg::reset
        << '\n';
        return 0;
    }
    const auto path = fs::path{expand_user(opt_path)};
    const auto extension = ".mkv"s;
    auto data = std::map<std::string, Same>{};
    auto max  = std::size_t{1};
    try
    {
        auto collect = [&] (auto p)
        {
            if (p.path().string().ends_with(extension))
            {
                auto name = p.path().filename().string();
                auto cp = code_points(name);
                if (cp > max) max = cp;
                auto milli = duration(p.path());
                auto key = format(milli);
                auto [it, ok] = data.try_emplace(key, Same{p});
                if (!ok) data[key].push_back(p);
            }
        };
        if (opt_flat)
        {
            for(const auto& p: fs::directory_iterator(path))
                collect(p);
        }
        else
        {
            for(const auto& p: fs::recursive_directory_iterator(path))
                collect(p);
        }
    }
    catch (const fs::filesystem_error& e)
    {
        say_what_again(e);
        return 23;
    }

    for (auto& [key, vec] : reverse(data))
    {
        std::sort(std::begin(vec), std::end(vec));
        for (const auto& p : vec)
        {
            opt_top -= 1;
            std::cout
            << rang::fgB::blue
            // << std::left << std::setw(max)  << name  -- no code point awareness
            << pad(p.path().filename().string(), max)
            << rang::fg::reset
            << " -- "
            << rang::fgB::green
            << key
            << rang::fg::reset
            << " -- ";

            auto s = format(fs::file_size(p));
            if (s.ends_with("Gb"))
            {
                std::cout
                << rang::fgB::red
                << std::right << std::setw(9)
                << s
                << rang::fg::reset;
            }
            else
            {
                std::cout
                << std::right << std::setw(9)
                << s;
            }
            std::cout << '\n';
            if (0 == opt_top) break;
        }
        if (0 == opt_top) break;
    }
}
