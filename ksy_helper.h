#pragma once

#include <kaitai/kaitaistream.h>

double
mkv_duration(kaitai::kstream* pks);

double
mp4_duration(kaitai::kstream* pks, bool maybe_mpeg2);
