#ifndef MARKDOWN_VIEWER__THREADS
#define MARKDOWN_VIEWER__THREADS

#pragma once

#if defined(_WIN32) || defined(__WIN32__) || defined(_WIN64) ||                \
  defined(__WIN64__) || defined(__WINDOWS__)
#  include <windows.h>
#else
#  include <pthread.h>
#endif

#endif