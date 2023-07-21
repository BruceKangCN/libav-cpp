# LIBAV-CPP

C++ wrapper for libAV. Still under early development.

## Features

- libAV functions under `av` namespace
- throw exceptions instead of returning error codes
- resource management using RAII
- Object oriented and operator overloading, for example:
    ```cpp
    auto r = av::Rational(1, 2); // same as `av_make_q(1, 2)`
    auto d = static_cast<double>(r); // same as `av_q2d(r)`
    auto i = r.inv(); // same as `av_iv_q(r)`
    ```

## Requirements

- C++ compiler supporting C++17
- libAV