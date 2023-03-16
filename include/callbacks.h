#ifndef MARKDOWN_VIEWER__CALLBACKS
#define MARKDOWN_VIEWER__CALLBACKS

#pragma once

#include "../md4c/md4c.h"

int enter_block_callback(MD_BLOCKTYPE block_type, void* block_detail, void* user_data);
int leave_block_callback(MD_BLOCKTYPE block_type, void* block_detail, void* user_data);

int enter_span_callback(MD_SPANTYPE span_type, void* span_detail, void* user_data);
int leave_span_callback(MD_SPANTYPE span_type, void* span_detail, void* user_data);

int text_callback(MD_TEXTTYPE text_type, const MD_CHAR* text, MD_SIZE length, void* user_data);

void debug_callback(const char* message, void* user_data);

#endif