#pragma once

#include <cstdint>
#include <functional>
#include <vector>

extern "C" {
#include <libavutil/buffer.h>
}

#include <av-cpp/def.h>

namespace av {

class LIBAV_CPP_PUBLIC BufferRef {
public:
    enum class Flag {
        ReadOnly = AV_BUFFER_FLAG_READONLY,
    };

    BufferRef() = delete;
    BufferRef(const BufferRef& ref);
    BufferRef(BufferRef&&) = delete;
    ~BufferRef();

    /// Note: this function does nothing on self-copy
    BufferRef& operator=(const BufferRef& ref);
    BufferRef& operator=(BufferRef&&) = delete;

    BufferRef(std::size_t size, bool init = true);

    BufferRef(AVBufferRef* ref);

    [[nodiscard]] operator const AVBufferRef*() const noexcept
    {
        return m_v;
    }

    [[nodiscard]] operator AVBufferRef*() noexcept
    {
        return m_v;
    }

    void replace(const BufferRef& other);

    static BufferRef create(std::vector<std::uint8_t>& data,
        void (*free)(void*, std::uint8_t*), void* opaque, int flags);

    [[nodiscard]] bool writable() const noexcept
    {
        return static_cast<bool>(av_buffer_is_writable(m_v));
    }

    [[nodiscard]] void* opaque(bool pool = false) const noexcept
    {
        if (pool) {
            return av_buffer_get_opaque(m_v);
        } else {
            return av_buffer_pool_buffer_get_opaque(m_v);
        }
    }

    [[nodiscard]] int refCount() const noexcept
    {
        return av_buffer_get_ref_count(m_v);
    }

    void makeWritable();

    void realloc(std::size_t size);

private:
    AVBufferRef* m_v;
};

class LIBAV_CPP_PUBLIC BufferPool {
public:
    BufferPool(std::size_t size, AVBufferRef* (*alloc)(std::size_t size));
    BufferPool(std::size_t size, void* opaque, AVBufferRef* (*alloc)(void*, std::size_t size),
        void (*free)(void*));
    BufferPool() = delete;
    BufferPool(const BufferPool&) = delete;
    BufferPool(BufferPool&&) = delete;
    ~BufferPool();

    BufferPool& operator=(const BufferPool&) = delete;
    BufferPool& operator=(BufferPool&&) = delete;

    BufferPool(AVBufferPool* pool);

    [[nodiscard]] operator AVBufferPool*() noexcept
    {
        return m_v;
    }

    [[nodiscard]] BufferRef get();

private:
    AVBufferPool* m_v;
};

} // namespace av
