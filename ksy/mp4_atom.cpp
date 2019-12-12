// This is a generated file! Please edit source .ksy file and use kaitai-struct-compiler to rebuild

#include <memory>
#include "mp4_atom.h"



mp4_atom_t::mp4_atom_t(kaitai::kstream* p__io, kaitai::kstruct* p__parent, mp4_atom_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = this;
}

void mp4_atom_t::_read() {
    m_size = m__io->read_u4be();
    m_type = m__io->read_u4be();
}

mp4_atom_t::~mp4_atom_t() {
}
