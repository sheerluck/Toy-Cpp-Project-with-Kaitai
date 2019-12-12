#pragma once

// This is a generated file! Please edit source .ksy file and use kaitai-struct-compiler to rebuild

#include "kaitai/kaitaistruct.h"

#include <stdint.h>
#include <memory>

#if KAITAI_STRUCT_VERSION < 9000L
#error "Incompatible Kaitai Struct C++/STL API: version 0.9 or later is required"
#endif

class mp4_atom_t : public kaitai::kstruct {

public:

    mp4_atom_t(kaitai::kstream* p__io, kaitai::kstruct* p__parent = nullptr, mp4_atom_t* p__root = nullptr);
    void _read();
    ~mp4_atom_t();

private:
    uint32_t m_size;
    uint32_t m_type;
    mp4_atom_t* m__root;
    kaitai::kstruct* m__parent;

public:
    uint32_t size() const { return m_size; }
    uint32_t type() const { return m_type; }
    mp4_atom_t* _root() const { return m__root; }
    kaitai::kstruct* _parent() const { return m__parent; }
};
