#include "../include/loaders.h"
#include "../memsafe-boii/memsafe_boii.h"
#include "../SDL2-2.26.4/include/SDL.h"

file_details* load_file(const char* file_path) {
  if (!file_path) {
    #ifdef DEBUG
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Passed NULL pointer to load_file()");
    #endif
    return NULL;
  }
  FILE* fp = fopen(file_path, "r");
  if (!fp) {
    #ifdef DEBUG
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Unable to open file: %s", file_path);
    #endif
    return NULL;
  }
  fseek(fp, 0, SEEK_END);
  unsigned long long length = ftell(fp);
  fseek(fp, 0, SEEK_SET);
  char* buffer = (char*)memsafe_boii_api__allocate(sizeof(char)*length);
  if (!buffer) {
    #ifdef DEBUG
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Unable to allocate memory for text in file: %s", file_path);
    #endif
    fclose(fp);
    return NULL;
  }
  fread(buffer, sizeof(char), length, fp);
  fclose(fp);
  file_details* details = (file_details*)memsafe_boii_api__allocate(sizeof(file_details));
  if (!details) {
    #ifdef DEBUG
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Unable to allocate memory for file_details for file: %s", file_path);
    #endif
    memsafe_boii_api__deallocate(buffer);
    return NULL;
  }
  details->content = buffer;
  details->length = length;
  return details;
}