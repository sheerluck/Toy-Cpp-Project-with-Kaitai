#include <map>
#include <filesystem>
#include <cstdlib>
#include <cxxopts.hpp>
#include "utils.h"
#include "rang.hpp"
#include "reverse.h"

using namespace std::string_literals;
namespace fs = std::filesystem;
using Same = std::vector<fs::path>;

void say_what_again(const std::exception& e,
                    const std::string& info = ""s)
{
    std::cout
    << rang::fgB::red
    << e.what()
    << (info.empty() ? info : "\n"s + info)
    << rang::fg::reset
    << '\n';
}

std::size_t
get_max(const std::map<std::string, Same>& data,
        long long copy)
{
    auto max = std::size_t{0};
    for (auto& [key, vec] : reverse(data))
    {
        for (const auto& p : vec)
        {
            copy -= 1;
            auto name = p.filename().string();
            auto cp = code_points(name);
            if (cp > max) max = cp;
            if (0 == copy) return max;
        }
    }
    return max;
}

extern char **environ;

int main (int argc, char *argv[])
{
    //print_argv(*argv, *environ);
    cxxopts::Options options("mkv", "description");
    options.add_options()
        ("h,help",           "help")
        ("p,path",           "path",
          cxxopts::value<std::string>()->default_value(fs::current_path().string()))
        ("t,top",            "top",
          cxxopts::value<long long>()->default_value("10"))
        ("f,flat",           "flat");
    try
    {
        auto opt = options.parse(argc, argv);
        if (opt["help"].as<bool>())
        {
            std::cout << rang::fg::green << strip_margin(R"HELP(
            |Usage: mkv [options]
            |Longest movies (in current directory)
            |
            |Options:
            |  -h, --help            Displays this help.
            |  -p, --path Videos     Path to movies.
            |  -t, --top 30          Number of lines to show.
            |                        Default is 10, 0 is inf.
            |  -f, --flat            No recursion.)HELP")
            << rang::fg::reset << "\n\n";
            return 0;
        }
        const auto path = fs::path{opt["path"].as<std::string>()};
        auto data = std::map<std::string, Same>{};
        const auto collect = [&data] (const fs::path& p)
        {
            if (const auto [fit, code] = encode_extension(p); fit)
            {
                try
                {
                    const auto milli = duration(p, code);
                    const auto key = format(milli);
                    const auto [it, ok] = data.try_emplace(key, Same{p});
                    if (!ok) data[key].push_back(p);
                }
                catch (const std::exception& e)
                {
                    say_what_again(e, p.string());
                }
            }
        };
        auto doptions = fs::directory_options::skip_permission_denied;
        if (opt["flat"].as<bool>())
        {
            for(const auto& p: fs::directory_iterator(path, doptions))
                if (fs::is_regular_file(p)) collect(p.path());
        }
        else
        {
            for(const auto& p: fs::recursive_directory_iterator(path, doptions))
                if (fs::is_regular_file(p)) collect(p.path());
        }

        auto top = opt["top" ].as<long long>();
        auto max = get_max(data, top);
        std::cout << "\n\n";
        for (auto& [key, vec] : reverse(data))
        {
            std::sort(std::begin(vec), std::end(vec));
            for (const auto& p : vec)
            {
                top -= 1;
                std::cout
                << "    "
                << rang::fgB::blue
                // << std::left << std::setw(max)  << name  -- no code point awareness
                << pad(p.filename().string(), max)
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
                if (0 == top) break;
            }
            if (0 == top) break;
        }
        std::cout << "\n\n";
    }
    catch (const std::exception& e)
    {
        say_what_again(e);
        return 19;
    }
}
