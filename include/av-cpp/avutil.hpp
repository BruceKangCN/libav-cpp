#pragma once

#include <cstdint>
#include <string>

extern "C" {
#include <libavutil/avutil.h>
}

#include <av-cpp/avutil/rational.hpp>

namespace av {

[[nodiscard]] inline unsigned utilVersion() noexcept
{
    return avutil_version();
}

[[nodiscard]] inline const char* versionInfo() noexcept
{
    return av_version_info();
}

[[nodiscard]] inline const char* utilConfiguration() noexcept
{
    return avutil_configuration();
}

[[nodiscard]] inline const char* utilLicense() noexcept
{
    return avutil_license();
}

enum class MediaType {
    Unknown = AVMEDIA_TYPE_UNKNOWN,
    Video = AVMEDIA_TYPE_VIDEO,
    Audio = AVMEDIA_TYPE_AUDIO,
    Data = AVMEDIA_TYPE_DATA,
    Subtitle = AVMEDIA_TYPE_SUBTITLE,
    Attachment = AVMEDIA_TYPE_ATTACHMENT,
    Nb = AVMEDIA_TYPE_NB,
};

[[nodiscard]] inline const char* getMediaTypeString(MediaType mediaType) noexcept
{
    return av_get_media_type_string(static_cast<AVMediaType>(mediaType));
}

enum class PictureType {
    None = AV_PICTURE_TYPE_NONE,
    I = AV_PICTURE_TYPE_I,
    P = AV_PICTURE_TYPE_P,
    B = AV_PICTURE_TYPE_B,
    S = AV_PICTURE_TYPE_S,
    SI = AV_PICTURE_TYPE_SI,
    SP = AV_PICTURE_TYPE_SP,
    BI = AV_PICTURE_TYPE_BI,
};

[[nodiscard]] inline char getPictureTypeChar(PictureType pictureType) noexcept
{
    return av_get_picture_type_char(static_cast<AVPictureType>(pictureType));
}

constexpr std::size_t LAMBDA_SHIFT = FF_LAMBDA_SHIFT;
constexpr std::size_t LAMBDA_SCALE = std::size_t(1) << LAMBDA_SHIFT;
constexpr std::size_t QP2LAMBDA = FF_QP2LAMBDA;
constexpr std::size_t LAMBDA_MAX = FF_LAMBDA_MAX;

constexpr std::size_t QUALITY_SCALE = FF_QUALITY_SCALE;

constexpr auto NOPTS_VALUE = AV_NOPTS_VALUE;
constexpr std::size_t TIME_BASE = AV_TIME_BASE;
constexpr auto TIME_BASE_Q = Rational(AV_TIME_BASE_Q);

// TODO:
//     error (exception)
//     mathemmatics
//     log
//     pixfmt

// TODO: is this useful?
[[nodiscard]] inline void* xIfNull(const void* p, const void* x) noexcept
{
    return av_x_if_null(p, x);
}

// TODO: is this useful?
[[nodiscard]] inline std::size_t intListLengthForSize(std::size_t elSize,
    const void* list, std::uint64_t term) noexcept
{
    return av_int_list_length_for_size(static_cast<unsigned>(elSize), list, term);
}

// TODO: is this useful?
template <typename T>
[[nodiscard]] inline std::size_t intListLength(T* list, std::uint64_t term) noexcept
{
    return av_int_list_length(list, term);
}

[[nodiscard]] inline Rational getTimeBaseQ() noexcept
{
    return av_get_time_base_q();
}

constexpr std::size_t FOURCC_MAX_STRING_SIZE = AV_FOURCC_MAX_STRING_SIZE;

LIBAV_CPP_PUBLIC [[nodiscard]] std::string fourcc2str(std::uint32_t fourcc);

} // namespace av
