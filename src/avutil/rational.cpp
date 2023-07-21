#include <av-cpp/avutil/rational.hpp>

namespace av {

Rational::Rational(double v, int max) noexcept
    : m_v(av_d2q(v, max))
{
    // nothing
}

} // namespace av
