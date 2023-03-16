#ifndef MARKDOWN_VIEWER__UTILS_MD4C
#define MARKDOWN_VIEWER__UTILS_MD4C

#pragma once

#include "../md4c/md4c.h"

const char* utils_blocktype_to_string(MD_BLOCKTYPE block_type);

const char* utils_spantype_to_string(MD_SPANTYPE span_type);

const char* utils_texttype_to_string(MD_TEXTTYPE text_type);

MD_PARSER* utils_parser_new();

typedef struct parser_func_params {
  const MD_CHAR *text;
  MD_SIZE size;
  const MD_PARSER *parser;
  void *userdata;
} parser_func_params;

parser_func_params* parser_func_param__new(const MD_CHAR *text, MD_SIZE size, const MD_PARSER *parser, void *userdata);

#endif