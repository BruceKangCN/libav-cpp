FROM mcr.microsoft.com/devcontainers/cpp:1-debian-12

RUN apt-get update && export DEBIAN_FRONTEND=noninteractive \
    && apt-get -y install --no-install-recommends meson clang-format clang-tidy \
    libavcodec-dev libavdevice-dev libavfilter-dev libavformat-dev libavutil-dev \
    libpostproc-dev libswresample-dev libswscale-dev man-db git pkgconf
