#ifndef MARKDOWN_VIEWER__LOADERS
#define MARKDOWN_VIEWER__LOADERS

#pragma once

#include <stdio.h>

typedef struct file_details
{
  char* content;
  unsigned long long length;
} file_details;

file_details* load_file(const char* file_path);

#endif