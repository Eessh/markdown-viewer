#include <string.h>
#include "../include/utils_select_file_prompt.h"
// #ifndef SDL_MAIN_HANDLED
// #define SDL_MAIN_HANDLED
// #endif
#include "../SDL2/include/SDL.h"
#include "../memsafe-boii/memsafe_boii.h"
#include "../tinyfiledialogs/tinyfiledialogs.h"

prompt_result select_file_prompt(TTF_Font* font) {
  // creating window
  SDL_WindowFlags prompt_window_flags = SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_MOUSE_FOCUS | SDL_WINDOW_SHOWN;
  SDL_Window* prompt_window = SDL_CreateWindow("Markdown Viewer - Open markdown file", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, prompt_window_flags);
  if (!prompt_window) {
    SDL_LogCritical(SDL_LOG_CATEGORY_ERROR, "Unable to create window for select file prompt: %s", SDL_GetError());
    return (prompt_result){
      .ok = false,
      .data = {.error_message = "Unable to create window for select file prompt."}
    };
  }

  bool quit = false, closed_without_file_selection = true;
  SDL_Event event;
  char* markdown_file_path = NULL;

  // intial render
  SDL_Surface* prompt_window_surface = SDL_GetWindowSurface(prompt_window);
  SDL_FillRect(prompt_window_surface, &(SDL_Rect){.x=230, .y=400, .w=180, .h=30}, SDL_MapRGBA(prompt_window_surface->format, 50, 50, 50, 255));

  int font_height = TTF_FontHeight(font);

  SDL_Surface* text_surface = TTF_RenderText_Blended(font, "Open markdown file", (SDL_Color){.r=255, .g=255, .b=255, .a=255});
  if (!text_surface) {
    #ifdef DEBUG
    SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Error while rendering text surface: %s", TTF_GetError());
    #endif
  }
  SDL_BlitSurface(text_surface, NULL, prompt_window_surface, &(SDL_Rect){.x=238, .y=400, .w=200, .h=20});
  SDL_UpdateWindowSurface(prompt_window);
  SDL_FreeSurface(text_surface);

  // event loop
  // just an event loop, which waits for click event on button `Open markdown file`
  while (!quit) {
    if (SDL_WaitEvent(&event)) {
      if (event.type == SDL_QUIT) {
        quit = true;
      }
      else if (event.type == SDL_MOUSEBUTTONUP) {
        if (event.button.button == SDL_BUTTON_LEFT) {
          // left click
          int mouse_xcoord = 0, mouse_ycoord = 0;
          SDL_GetMouseState(&mouse_xcoord, &mouse_ycoord);
          #ifdef DEBUG
          SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Mouse click: (%d, %d)", mouse_xcoord, mouse_ycoord);
          #endif
          if (230<=mouse_xcoord&&mouse_xcoord<=410 && 400<=mouse_ycoord&&mouse_ycoord<=430) {
            const char* file_selection_filters[1] = { "*.md" };
            markdown_file_path = tinyfd_openFileDialog("Select markdown file", "", 1, file_selection_filters, "Markdown", 0);
            if (markdown_file_path) {
              SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Selected file path: %s", markdown_file_path);
              closed_without_file_selection = false;
              quit = true;
            }
            else {
              // cancelled
              #ifdef DEBUG
              SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Cancelled select markdown file dialog.");
              #endif
            }
          }
        }
      }
    }
  }

  SDL_DestroyWindow(prompt_window);

  if (closed_without_file_selection) {
    return (prompt_result){
      .ok = false,
      .data = {.error_message = "Prompt closed without file selection."}
    };
  }

  return (prompt_result){
    .ok = true,
    .data = {.file_path = markdown_file_path}
  };
}