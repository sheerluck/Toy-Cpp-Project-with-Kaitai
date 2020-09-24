#include "utils.h"

int main (int argc, char *argv[])
{
    auto o = parse_options(argc, argv);
    try
    {
        if (o.help) return print_help();
        const auto names = search(o.path, o.flat);
        auto data = process(names);
        print_sorted_top(data, o.top);
    }
    catch (const std::exception& e)
    {
        say_what_again(e);
        return 19;
    }
}
