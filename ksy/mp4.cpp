// This is a generated file! Please edit source .ksy file and use kaitai-struct-compiler to rebuild

#include <memory>
#include "mp4.h"

#include <kaitai/exceptions.h>

mp4_t::mp4_t(kaitai::kstream* p__io, kaitai::kstruct* p__parent, mp4_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = this;
}

void mp4_t::_read() {
    m_magic = m__io->read_bytes(4);
    if (!(magic() == std::string("\x6D\x76\x68\x64", 4))) {
        throw kaitai::validation_not_equal_error<std::string>(std::string("\x6D\x76\x68\x64", 4), magic(), _io(), std::string("/seq/0"));
    }
    m_version = m__io->read_u1();
    m_flags = m__io->read_bytes(3);
    m_ctime = m__io->read_u4be();
    m_mtime = m__io->read_u4be();
    m_scale = m__io->read_u4be();
    m_duration = m__io->read_u4be();
}

mp4_t::~mp4_t() {
}
