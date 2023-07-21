project('libav-cpp', 'cpp',
  license: ['MIT', 'Apache-2.0'],
  meson_version: '>= 0.60',
  version: '0.1.0',
  default_options : [
    'warning_level=3',
    'strip=true',
    'cpp_std=c++20',
    'b_ndebuf=if-release',
  ],
)

lib_args = ['-DBUILDING_LIBAV_CPP']

libav_dep = [
  dependency('libavcodec', include_type: 'system'),
  dependency('libavdevice', include_type: 'system'),
  dependency('libavfilter', include_type: 'system'),
  dependency('libavformat', include_type: 'system'),
  dependency('libavutil', include_type: 'system'),
  dependency('libpostproc', include_type: 'system'),
  dependency('libswresample', include_type: 'system'),
  dependency('libswscale', include_type: 'system'),
]

inc = include_directories('include')
src = []

subdir('src')

lib = library(
  meson.project_name(),
  src,
  install: true,
  cpp_args: lib_args,
  include_directories: inc,
  dependencies: libav_dep,
  gnu_symbol_visibility: 'hidden',
)

libav_cpp_dep = declare_dependency(
  include_directories: include_directories('.'),
  link_with: lib,
)

install_subdir('include/av', install_dir: get_option('includedir'))

pkg = import('pkgconfig')
pkg.generate(
  name: meson.project_name(),
  description: 'C++ wrapper for libav',
  libraries: lib,
)
