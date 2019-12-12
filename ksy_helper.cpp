#include "ksy_helper.h"

#include "ksy/avi.h"
#include "ksy/mkv.h"
#include "ksy/mp4.h"


double
avi_duration(kaitai::kstream* pks)
{
    return 111111;
}

double
mkv_duration(kaitai::kstream* pks)
{
    mkv_t g = mkv_t(pks);

    uint64_t offset = 0;
    uint8_t a, b, c;
    while (true)
    {
        a = g._io()->read_u1();
        offset++;
        if (0x44 not_eq a) continue;
        b = g._io()->read_u1();
        if (0x89 not_eq b)
        {
            g._io()->seek(offset);
            continue;
        }
        c = g._io()->read_u1();
        if (0x84 == c or 0x88 == c) break;
        g._io()->seek(offset);
    }
    g._io()->seek(offset - 1);
    g._read();
    auto is_float = mkv_t::size_type_t::SIZE_TYPE_FLOAT == g.protocol();
    return is_float ? static_cast<double>(g.value4()) : g.value8();

}

double
mp4_duration(kaitai::kstream* pks)
{
    return 333333;
}
