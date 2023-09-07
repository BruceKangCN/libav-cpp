#pragma once

#include <cstdint>
#include <exception>

extern "C" {
#include <libavutil/common.h>
}

namespace av {

class Exception : public std::exception {
public:
    Exception() noexcept = default;
    Exception(const Exception&) = default;
    Exception(Exception&&) noexcept = default;
    ~Exception() override = default;
    Exception& operator=(const Exception&) = default;
    Exception& operator=(Exception&&) noexcept = default;

    explicit Exception(int no) noexcept;

    const char* what() const noexcept override;

    [[nodiscard]] int errorCode() const noexcept
    {
        return m_no;
    }

private:
    int m_no = 0;
};

} // namespace av
