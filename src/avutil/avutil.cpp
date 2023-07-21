#include <array>

#include <av-cpp/avutil.hpp>

namespace av {

std::string fourcc2str(std::uint32_t fourcc)
{
    std::array<char, FOURCC_MAX_STRING_SIZE + 1> buf {};
    return av_fourcc_make_string(buf.data(), fourcc);
}

} // namespace av
