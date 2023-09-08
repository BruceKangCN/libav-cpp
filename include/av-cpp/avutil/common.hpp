#pragma once

#include <cstdint>
#include <exception>

extern "C" {
#include <libavutil/common.h>
}

#include <av-cpp/def.h>

namespace av {

/// throw if return code represents an error. do nothing if \a ret equals 0.
LIBAV_CPP_PUBLIC void throwOnError(int ret);

} // namespace av
