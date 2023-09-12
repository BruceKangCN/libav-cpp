#pragma once

#include <string>
#include <string_view>
#include <vector>
extern "C" {
#include <libavutil/dict.h>
}

#include <av-cpp/def.h>

/// incomplete, DO NOT USE!!!

namespace av {

struct DictionaryEntry {
    std::string key;
    std::string value;
};

class LIBAV_CPP_PUBLIC Dictionary {
public:
    // TODO: Ctor and Dtor?

    [[nodiscard]] int count() const noexcept
    {
        return static_cast<int>(m_elems.size());
    }

    [[nodiscard]] int size() const noexcept
    {
        return static_cast<int>(m_elems.size());
    }

    // TODO: other functions

private:
    std::vector<DictionaryEntry> m_elems;
};

} // namespace av
