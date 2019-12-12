#include "ksy_helper.h"

#include "ksy/avi.h"
#include "ksy/mkv.h"
#include "ksy/mp4.h"
#include "ksy/mp4_atom.h"

double
avi_duration(kaitai::kstream* pks)
{
    return 111111;
}

double
mkv_duration(kaitai::kstream* pks)
{
    mkv_t o = mkv_t(pks);

    uint64_t offset = 0;
    uint8_t a, b, c;
    while (true)
    {
        a = o._io()->read_u1();
        offset++;
        if (0x44 not_eq a) continue;
        if (b = o._io()->read_u1(); 0x89 not_eq b)
        {
            o._io()->seek(offset);
            continue;
        }
        if (c = o._io()->read_u1(); 0x84 == c or 0x88 == c) break;
        o._io()->seek(offset);
    }
    o._io()->seek(offset - 1);
    o._read();
    auto is_float = mkv_t::size_type_t::SIZE_TYPE_FLOAT == o.protocol();
    return is_float ? static_cast<double>(o.value4()) : o.value8();

}

uint64_t
find_moov(kaitai::kstream* pks)
{
    constexpr auto moov = 0x6d6f6f76;
    uint64_t offset = 0;
    uint64_t prev   = 0;
    mp4_atom_t o = mp4_atom_t(pks);
    do
    {
        o._read();
        prev = offset;
        offset += o.size();
        o._io()->seek(offset);
    } while (moov not_eq o.type());
    return prev;
}

uint64_t
find_mvhd(kaitai::kstream* pks, uint64_t start)
{
    constexpr auto mvhd = 0x6d766864;
    uint64_t offset = start + 4 + 4;  // size + type
    uint64_t prev   = 0;
    mp4_atom_t o = mp4_atom_t(pks);
    o._io()->seek(offset);
    do
    {
        o._read();
        prev = offset;
        offset += o.size();
        o._io()->seek(offset);
    } while (mvhd not_eq o.type());
    return prev;
}


double
mp4_duration(kaitai::kstream* pks)
{
    auto offset = find_mvhd(pks, find_moov(pks));
    mp4_t o = mp4_t(pks);
    o._io()->seek(offset + 4);
    o._read();
    return o.duration() / o.scale();
}
