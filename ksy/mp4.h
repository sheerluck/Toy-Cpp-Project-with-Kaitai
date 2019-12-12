#pragma once

// This is a generated file! Please edit source .ksy file and use kaitai-struct-compiler to rebuild

#include "kaitai/kaitaistruct.h"

#include <stdint.h>
#include <memory>

#if KAITAI_STRUCT_VERSION < 9000L
#error "Incompatible Kaitai Struct C++/STL API: version 0.9 or later is required"
#endif

class mp4_t : public kaitai::kstruct {

public:

    mp4_t(kaitai::kstream* p__io, kaitai::kstruct* p__parent = nullptr, mp4_t* p__root = nullptr);
    void _read();
    ~mp4_t();

private:
    std::string m_magic;
    uint8_t m_version;
    std::string m_flags;
    uint32_t m_ctime;
    uint32_t m_mtime;
    uint32_t m_scale;
    uint32_t m_duration;
    mp4_t* m__root;
    kaitai::kstruct* m__parent;

public:
    std::string magic() const { return m_magic; }
    uint8_t version() const { return m_version; }
    std::string flags() const { return m_flags; }
    uint32_t ctime() const { return m_ctime; }
    uint32_t mtime() const { return m_mtime; }
    uint32_t scale() const { return m_scale; }
    uint32_t duration() const { return m_duration; }
    mp4_t* _root() const { return m__root; }
    kaitai::kstruct* _parent() const { return m__parent; }
};
