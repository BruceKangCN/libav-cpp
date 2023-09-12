#include <new>

#include <av-cpp/avutil/frame.hpp>

namespace av {

Frame::Frame()
    : m_v(av_frame_alloc())
{
    if (!m_v) {
        throw std::bad_alloc();
    }
}

Frame::Frame(const Frame& other)
    : m_v(av_frame_clone(other.m_v))
{
    if (!m_v) {
        throw std::bad_alloc();
    }
}

Frame::Frame(Frame&& other) noexcept
    : m_v(nullptr)
{
    av_frame_move_ref(m_v, other.m_v);
}

Frame::~Frame()
{
    av_frame_free(&m_v);
}

Frame& Frame::operator=(const Frame& other)
{
    if (&other == this) {
        return *this;
    }

    m_v = av_frame_clone(other.m_v);
    if (!m_v) {
        throw std::bad_alloc();
    }
    return *this;
}

Frame& Frame::operator=(Frame&& other) noexcept
{
    if (&other == this) {
        return *this;
    }

    av_frame_unref(m_v);
    av_frame_move_ref(m_v, other.m_v);
    return *this;
}

Frame::Frame(AVFrame* frame) noexcept
    : m_v(frame)
{
    // nothing
}

} // namespace av
