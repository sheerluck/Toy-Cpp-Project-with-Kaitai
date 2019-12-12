#pragma once

#include <kaitai/kaitaistream.h>

double
avi_duration(kaitai::kstream* pks);

double
mkv_duration(kaitai::kstream* pks);

double
mp4_duration(kaitai::kstream* pks);
