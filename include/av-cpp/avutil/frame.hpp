#pragma once

extern "C" {
#include <libavutil/frame.h>
}

#include <av-cpp/avutil.hpp>
#include <av-cpp/avutil/buffer.hpp>
#include <av-cpp/avutil/error.hpp>
#include <av-cpp/avutil/rational.hpp>

namespace av {

class LIBAV_CPP_PUBLIC Frame {
public:
    Frame();
    Frame(const Frame& other);
    Frame(Frame&& other) noexcept;
    ~Frame();
    Frame& operator=(const Frame& other);
    Frame& operator=(Frame&& other) noexcept;

    Frame(AVFrame* frame) noexcept;

    [[nodiscard]] operator AVFrame*() noexcept
    {
        return m_v;
    }

    [[nodiscard]] operator const AVFrame*() const noexcept
    {
        return m_v;
    }

    void ref(const Frame& src)
    {
        throwOnError(av_frame_ref(m_v, src.m_v));
    }

    void unref()
    {
        av_frame_unref(m_v);
    }

    [[nodiscard]] Frame clone() const
    {
        return av_frame_clone(m_v);
    }

    // TODO: getBuffer?

    [[nodiscard]] bool writable() const noexcept
    {
        return static_cast<bool>(av_frame_is_writable(m_v));
    }

    void makeWritable()
    {
        throwOnError(av_frame_make_writable(m_v));
    }

    void copy(Frame& dst) const
    {
        throwOnError(av_frame_copy(dst.m_v, m_v));
    }

    void copyProps(Frame& dst) const
    {
        throwOnError(av_frame_copy_props(dst.m_v, m_v));
    }

    BufferRef planeBuffer(int plane)
    {
        return av_frame_get_plane_buffer(m_v, plane);
    }

    // TODO: newSideData, newSideDataFromBuf, sideData, removeSideData, sideDataName

    void applyCropping(int flags)
    {
        throwOnError(av_frame_apply_cropping(m_v, flags));
    }

private:
    AVFrame* m_v;
};

} // namespace av
