#pragma once

#include <array>
#include <cstdint>
extern "C" {
#include <libavutil/display.h>
}

namespace av {

constexpr std::size_t TRANSFORMATION_MATRIX_SIZE = 9;

using TransformationMatrix = std::array<std::int32_t, TRANSFORMATION_MATRIX_SIZE>;

[[nodiscard]] inline double getDisplayRotation(const TransformationMatrix& matrix)
{
    return av_display_rotation_get(&matrix[0]);
}

[[nodiscard]] inline TransformationMatrix setDisplayRotation(double angle)
{
    TransformationMatrix matrix {};
    av_display_rotation_set(&matrix[0], angle);
    return matrix;
}

inline void flipDisplayMatrix(TransformationMatrix& matrix, bool hFlip, bool vFlip)
{
    av_display_matrix_flip(&matrix[0], static_cast<int>(hFlip), static_cast<int>(vFlip));
}

} // namespace av
