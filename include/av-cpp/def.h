#pragma once

#if defined _WIN32 || defined __CYGWIN__
  #ifdef BUILDING_LIBAV_CPP
    #define LIBAV_CPP_PUBLIC __declspec(dllexport)
  #else
    #define LIBAV_CPP_PUBLIC __declspec(dllimport)
  #endif
#else
  #ifdef BUILDING_LIBAV_CPP
      #define LIBAV_CPP_PUBLIC __attribute__ ((visibility ("default")))
  #else
      #define LIBAV_CPP_PUBLIC
  #endif
#endif
