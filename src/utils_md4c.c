#include "../include/utils_md4c.h"
#include "../memsafe-boii/memsafe_boii.h"
#include "../SDL2/include/SDL.h"
#include "../include/callbacks.h"

const char* utils_blocktype_to_string(MD_BLOCKTYPE block_type) {
  switch (block_type) {
    case MD_BLOCK_DOC: return "BLOCK_DOC: <body>";
    case MD_BLOCK_QUOTE: return "BLOCK_QUOTE: <blockquote>";
    case MD_BLOCK_UL: return "BLOCK_UL: <ul>";
    case MD_BLOCK_OL: return "BLOCK_OL: <ol>";
    case MD_BLOCK_LI: return "BLOCK_LI: <li>";
    case MD_BLOCK_HR: return "BLOCK_HR: <hr>";
    case MD_BLOCK_H: return "BLOCK_H: <h1>";
    case MD_BLOCK_CODE: return "BLOCK_CODE: <pre><code>";
    case MD_BLOCK_HTML: return "Raw HTML";
    case MD_BLOCK_P: return "BLOCK_P: <p>";
    default: break;
  }
  return "Table blocks";
}

const char* utils_spantype_to_string(MD_SPANTYPE span_type) {
  switch (span_type) {
    case MD_SPAN_EM: return "SPAN_EM: <em>";
    case MD_SPAN_STRONG: return "SPAN_STRONG: <strong>";
    case MD_SPAN_A: return "SPAN_A: <a>";
    case MD_SPAN_IMG: return "SPAN_IMG: <img>";
    case MD_SPAN_CODE: return "SPAN_CODE: <code>";
    case MD_SPAN_DEL: return "SPAN_DEL | SPAN_STRIKETHROUGH: <del>";
    case MD_SPAN_U: return "SPAN_U: <u>";
    default: break;
  }
  return "LatexMath, WikiLink spans";
}

const char* utils_texttype_to_string(MD_TEXTTYPE text_type) {
  switch (text_type) {
    case MD_TEXT_NORMAL: return "TEXT_NORMAL";
    case MD_TEXT_NULLCHAR: return "TEXT_NULLCHAR";
    case MD_TEXT_SOFTBR: return "TEXT_SOFTBR";
    case MD_TEXT_BR: return "TEXT_BR";
    case MD_TEXT_ENTITY: return "TEXT_ENTITY";
    case MD_TEXT_CODE: return "TEXT_CODE";
    case MD_TEXT_HTML: return "TEXT_HTML";
    default: break;
  }
  return "LatexMath text";
}

MD_PARSER* utils_parser_new() {
  MD_PARSER* parser = (MD_PARSER*)memsafe_boii_api__allocate(sizeof(MD_PARSER));
  if (!parser) {
    #ifdef DEBUG
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Unable to allocate memory for MD_PARSER");
    #endif
    return NULL;
  }

  parser->abi_version = 0;
  parser->flags = MD_FLAG_NOHTML;
  parser->syntax = NULL;
  parser->enter_block = &enter_block_callback;
  parser->leave_block = &leave_block_callback;
  parser->enter_span = &enter_span_callback;
  parser->leave_span = &leave_span_callback;
  parser->text = &text_callback;
  parser->debug_log = &debug_callback;

  return parser;
}

parser_func_params* parser_func_param__new(const MD_CHAR *text, MD_SIZE size, const MD_PARSER *parser, void *userdata) {
  parser_func_params* params = (parser_func_params*)memsafe_boii_api__allocate(sizeof(parser_func_params));
  if (!params) {
    #ifdef DEBUG
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Unable to allocate memory for parser_func_params!");
    #endif
    return NULL;
  }

  params->text = text;
  params->size = size;
  params->parser = parser;
  params->userdata = userdata;

  return params;
}