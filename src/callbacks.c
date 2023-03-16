#include "../include/callbacks.h"
#include "../include/utils_md4c.h"
#include "../SDL2-2.26.4/include/SDL.h"

int enter_block_callback(MD_BLOCKTYPE block_type, void* block_detail, void* user_data) {
  SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Entering block: %s", utils_blocktype_to_string(block_type));

  switch (block_type) {
    case MD_BLOCK_DOC: {
      // TODO: handle doc block details
      return 0;
    };
    case MD_BLOCK_QUOTE: {
      // TODO: handle quote block details
      return 0;
    };
    case MD_BLOCK_UL: {
      MD_BLOCK_UL_DETAIL* ul_block_detail = (MD_BLOCK_UL_DETAIL*)block_detail;
      SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "<ul> details: { is_tight: %d, mark: %c }", ul_block_detail->is_tight, ul_block_detail->mark);
      return 0;
    };
    case MD_BLOCK_OL: {
      MD_BLOCK_OL_DETAIL* ol_block_detail = (MD_BLOCK_OL_DETAIL*)block_detail;
      SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "<ol> details: { start_index: %d, is_tight: %d, mark_delimiter: %c }", ol_block_detail->start, ol_block_detail->is_tight, ol_block_detail->mark_delimiter);
      return 0;
    };
    case MD_BLOCK_LI: {
      MD_BLOCK_LI_DETAIL* li_block_detail = (MD_BLOCK_LI_DETAIL*)block_detail;
      SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "<li> details: { is_task: %d, task_mark: %c, task_mark_offset: %d }", li_block_detail->is_task, li_block_detail->task_mark, li_block_detail->task_mark_offset);
      return 0;
    };
    case MD_BLOCK_HR: {
      // TODO: handle <hr> block details
      return 0;
    };
    case MD_BLOCK_H: {
      MD_BLOCK_H_DETAIL* h_block_detail = (MD_BLOCK_H_DETAIL*)block_detail;
      SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "<h1> details: { level: %d }", h_block_detail->level);
      return 0;
    };
    case MD_BLOCK_CODE: {
      MD_BLOCK_CODE_DETAIL* code_block_detail = (MD_BLOCK_CODE_DETAIL*)block_detail;
      SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "<code> details: { lang: %s, fence_char: %c }", code_block_detail->lang.text, code_block_detail->fence_char);
      return 0;
    };
    case MD_BLOCK_HTML: return 0;
    case MD_BLOCK_P: return 0;
    default: break;
  }

  return 0;
}

int leave_block_callback(MD_BLOCKTYPE block_type, void* block_detail, void* user_data) {
  SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Leaving block: %s", utils_blocktype_to_string(block_type));
  return 0;
}

int enter_span_callback(MD_SPANTYPE span_type, void* span_detail, void* user_data) {
  SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Entering span: %s", utils_spantype_to_string(span_type));

  switch (span_type) {
    case MD_SPAN_A: {
      MD_SPAN_A_DETAIL* a_span_detail = (MD_SPAN_A_DETAIL*)span_detail;
      SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "<a> details: { href: %s, title: %s }", a_span_detail->href.text, a_span_detail->title.text);
      return 0;
    };
    case MD_SPAN_IMG: {
      MD_SPAN_IMG_DETAIL* image_span_detail = (MD_SPAN_IMG_DETAIL*)span_detail;
      SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "<img> details: { src: %s, title: %s }", image_span_detail->src.text, image_span_detail->title.text);
      return 0;
    };
    case MD_SPAN_WIKILINK: {
      MD_SPAN_WIKILINK_DETAIL* wikilink_span_detail = (MD_SPAN_WIKILINK_DETAIL*)span_detail;
      SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "wikilink details: { target: %s }", wikilink_span_detail->target.text);
      return 0;
    };
    default: break;
  }

  return 0;
}

int leave_span_callback(MD_SPANTYPE span_type, void* span_detail, void* user_data) {
  SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Leaving span: %s", utils_spantype_to_string(span_type));
  return 0;
}

int text_callback(MD_TEXTTYPE text_type, const MD_CHAR* text, MD_SIZE length, void* user_data) {
  SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Text callback: %s", utils_texttype_to_string(text_type));
  return 0;
}

void debug_callback(const char* message, void* user_data) {
  // SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "%s", message);
}