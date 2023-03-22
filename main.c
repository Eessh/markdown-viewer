#include <corecrt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "md4c/md4c.h"

int enter_block_callback_func(MD_BLOCKTYPE, void*, void*);
int leave_block_callback_func(MD_BLOCKTYPE, void*, void*);
int enter_span_callback_func(MD_SPANTYPE, void*, void*);
int leave_span_callback_func(MD_SPANTYPE, void*, void*);
int text_callback_func(MD_TEXTTYPE, const MD_CHAR*, MD_SIZE, void*);
void debug_callback_func(const char*, void*);

typedef struct file_details
{
  char* content;
  unsigned long long length;
} file_details;

file_details* read_file(const char* file_path);

int main(int argc, char** argv)
{

  if(argc < 2)
  {
    printf("Usage: mdv.exe <markdown file path>");
    return 0;
  }
  unsigned int markdown_file_path_length = strlen(argv[1]);
  char* markdown_file_path =
    (char*)malloc(sizeof(char) * (markdown_file_path_length + 1));
  strcpy_s(markdown_file_path,
           sizeof(char) * (markdown_file_path_length + 1),
           argv[1]);
  printf("Markdown file path: %s\n", markdown_file_path);

  MD_PARSER* parser = (MD_PARSER*)malloc(sizeof(MD_PARSER));
  parser->abi_version = 0;
  parser->flags = MD_FLAG_NOHTML;
  parser->syntax = NULL;
  parser->enter_block = &enter_block_callback_func;
  parser->leave_block = &leave_block_callback_func;
  parser->enter_span = &enter_span_callback_func;
  parser->leave_span = &leave_span_callback_func;
  parser->text = &text_callback_func;
  parser->debug_log = &debug_callback_func;

  file_details* details = read_file(markdown_file_path);
  if(!details)
  {
    // some error occurred while opening file
    free(parser);
    free(details);
    return 0;
  }

  int ret_value =
    md_parse(details->content, sizeof(char) * details->length, parser, NULL);
  printf("Return Value: %d", ret_value);

  free(parser);
  free(details);

  return 0;
}

int enter_block_callback_func(MD_BLOCKTYPE a, void* b, void* c)
{
  printf("entering block\n");
  return 0;
}

int leave_block_callback_func(MD_BLOCKTYPE a, void* b, void* c)
{
  printf("leaving block\n");
  return 0;
}

int enter_span_callback_func(MD_SPANTYPE a, void* b, void* c)
{
  printf("entering span\n");
  return 0;
}

int leave_span_callback_func(MD_SPANTYPE a, void* b, void* c)
{
  printf("leaving span\n");
  return 0;
}

int text_callback_func(MD_TEXTTYPE a, const MD_CHAR* b, MD_SIZE c, void* d)
{
  printf("text\n");
  return 0;
}

void debug_callback_func(const char* message, void* user_data)
{
  printf("%s", message);
}

file_details* read_file(const char* file_path)
{
  char* buffer = NULL;
  unsigned long long length = 0;
  FILE* fp = NULL;
  errno_t error_code = fopen_s(&fp, file_path, "r");
  if(error_code != 0)
  {
    printf("Unable to open file: %s\n", file_path);
    return NULL;
  }
  fseek(fp, 0, SEEK_END);
  length = ftell(fp);
  fseek(fp, 0, SEEK_SET);
  buffer = (char*)malloc(sizeof(char) * length);
  if(!buffer)
  {
    // returning NULL, if cannot allocate memory for buffer
    printf("Unable to allocate memory for reading characters in file: %s",
           file_path);
    fclose(fp);
    return NULL;
  }
  fread(buffer, sizeof(char), length, fp);
  fclose(fp);
  file_details* details = (file_details*)malloc(sizeof(file_details));
  details->content = buffer;
  details->length = length;
  return details;
}
