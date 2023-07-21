#pragma once

#include <bit>
#include <compare>
#include <cstdint>
#include <type_traits>
#include <vector>

extern "C" {
#include <libavutil/rational.h>
}

#include <av-cpp/def.h>

namespace av {

class LIBAV_CPP_PUBLIC Rational {
public:
    friend inline int cmpQ(const Rational& a, const Rational& b);
    friend inline Rational operator+(const Rational& a, const Rational& b);
    friend inline Rational operator-(const Rational& a, const Rational& b);
    friend inline Rational operator*(const Rational& a, const Rational& b);
    friend inline Rational operator/(const Rational& a, const Rational& b);

    constexpr Rational() = default;
    constexpr Rational(const Rational&) = default;
    constexpr Rational(Rational&&) = default;
    constexpr ~Rational() = default;
    constexpr Rational& operator=(const Rational&) = default;
    constexpr Rational& operator=(Rational&&) = default;

    constexpr Rational(int num, int den) noexcept
        : m_v(AVRational { num, den })
    {
        // nothing
    }

    constexpr Rational(AVRational r) noexcept
        : m_v(r)
    {
        // nothing
    }

    Rational(double v, int max) noexcept;

    [[nodiscard]] operator double() const noexcept
    {
        return av_q2d(m_v);
    }

    [[nodiscard]] Rational inv() const noexcept
    {
        return av_inv_q(m_v);
    }

    [[nodiscard]] int nearer(const Rational& a, const Rational& b) const noexcept
    {
        return av_nearer_q(m_v, a.m_v, b.m_v);
    }

    [[nodiscard]] int findNearestQIndex(const std::vector<Rational>& list) const noexcept
    {
        return av_find_nearest_q_idx(m_v, std::bit_cast<AVRational*>(list.data()));
    }

    [[nodiscard]] std::uint32_t toIntFloat() const noexcept
    {
        return av_q2intfloat(m_v);
    }

    [[nodiscard]] static Rational gcd(const Rational& a, const Rational& b,
        int maxDen, const Rational& def) noexcept
    {
        return av_gcd_q(a.m_v, b.m_v, maxDen, def.m_v);
    }

private:
    AVRational m_v;
};

static_assert(std::is_standard_layout_v<Rational>);
static_assert(sizeof(Rational) == sizeof(AVRational));

[[nodiscard]] inline int cmpQ(const Rational& a, const Rational& b)
{
    return av_cmp_q(a.m_v, b.m_v);
}

#if __cplusplus >= 202002L

[[nodiscard]] inline int operator<=>(const Rational& a, const Rational& b)
{
    return cmpQ(a, b);
}

#endif /* C++20 */

inline bool reduce(int& dstNum, int& dstDen, std::int64_t num, std::int64_t den, int64_t max)
{
    return static_cast<bool>(av_reduce(&dstNum, &dstDen, num, den, max));
}

inline Rational operator+(const Rational& a, const Rational& b)
{
    return av_add_q(a.m_v, b.m_v);
}

inline Rational operator-(const Rational& a, const Rational& b)
{
    return av_sub_q(a.m_v, b.m_v);
}

inline Rational operator*(const Rational& a, const Rational& b)
{
    return av_mul_q(a.m_v, b.m_v);
}

inline Rational operator/(const Rational& a, const Rational& b)
{
    return av_div_q(a.m_v, b.m_v);
}

} // namespace av
