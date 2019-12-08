#include <fstream>
#include <codecvt>
#include <fmt/format.h>
#include "utils.h"
#include "calmsize.h"

#include <kaitai/kaitaistream.h>
#include "generated.h"

float
code_points(const std::string& utf8)
{
    std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t> utf16conv;
    std::u16string utf16 = utf16conv.from_bytes(utf8);
    return utf16.length();
}


double
duration(fs::path path)
{
    std::ifstream ifs(path, std::ifstream::binary);
    kaitai::kstream ks(&ifs);
    generated_t g = generated_t(&ks);

    uint64_t offset = 0;
    uint8_t a, b, c;
    while (true)
    {
        a = g._io()->read_u1();
        offset++;
        if (0x44 != a) continue;
        b = g._io()->read_u1();
        if (0x89 != b)
        {
            g._io()->seek(offset);
            continue;
        }
        c = g._io()->read_u1();
        if (0x84 == c || 0x88 == c) break;
        g._io()->seek(offset);
    }
    g._io()->seek(offset - 1);
    g._read();
    return (generated_t::size_type_t::SIZE_TYPE_FLOAT == g.protocol()) ? g.value4() : g.value8();
}

std::string
format(std::uintmax_t bytes)
{
    return human_filesize(bytes);
}

std::string
format(double milliseconds)
{
    return human_duration(milliseconds / 1000);
}

std::string
pad(const std::string& s, int max)
{
    // "Hello", 10 -> "Hello    "
    using namespace std::string_literals;
    auto cp = code_points(s);
    if (cp < max) {
        auto spaces = ""s;
        spaces.resize(max - cp, ' ');
        return s + spaces;
    }
    return s;
}

