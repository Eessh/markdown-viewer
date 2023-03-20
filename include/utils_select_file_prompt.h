#ifndef MARKDOWN_VIEWER__SELECT_FILE_PROMPT
#define MARKDOWN_VIEWER__SELECT_FILE_PROMPT

#pragma once

#include <stdbool.h>
#include "../SDL2_ttf/include/SDL_ttf.h"

typedef struct prompt_result {
  bool ok;
  union {
    char* file_path;
    const char* error_message;
  } data;
} prompt_result;

prompt_result select_file_prompt(TTF_Font* font);

#endif