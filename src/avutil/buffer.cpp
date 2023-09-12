#include <new>

#include <av-cpp/avutil/buffer.hpp>

namespace av {

BufferRef::BufferRef(const BufferRef& ref)
    : m_v(av_buffer_ref(ref.m_v))
{
    if (!m_v) {
        throw std::bad_alloc();
    }
}

BufferRef::BufferRef(std::size_t size, bool init)
    : m_v(init ? av_buffer_allocz(size) : av_buffer_alloc(size))
{
    if (!m_v) {
        throw std::bad_alloc();
    }
}

BufferRef::BufferRef(AVBufferRef* ref)
    : m_v(ref)
{
    // nothing
}

BufferRef::~BufferRef()
{
    av_buffer_unref(&m_v);
}

BufferRef& BufferRef::operator=(const BufferRef& ref)
{
    if (&ref == this) {
        return *this;
    }

    m_v = av_buffer_ref(ref.m_v);
    if (!m_v) {
        throw std::bad_alloc();
    }

    return *this;
}

BufferPool::BufferPool(std::size_t size, AVBufferRef* (*alloc)(std::size_t size))
    : m_v(av_buffer_pool_init(size, alloc))
{
    if (!m_v) {
        throw std::bad_alloc();
    }
}

BufferPool::BufferPool(std::size_t size, void* opaque,
    AVBufferRef* (*alloc)(void*, std::size_t size), void (*free)(void*))
    : m_v(av_buffer_pool_init2(size, opaque, alloc, free))
{
    if (!m_v) {
        throw std::bad_alloc();
    }
}

BufferPool::~BufferPool()
{
    av_buffer_pool_uninit(&m_v);
}

BufferPool::BufferPool(AVBufferPool* pool)
    : m_v(pool)
{
    // nothing
}

} // namespace av
