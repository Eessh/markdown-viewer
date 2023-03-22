#include <stdbool.h>
#include "include/loaders.h"
#include "include/utils_md4c.h"
#include "include/utils_select_file_prompt.h"
#include "memsafe-boii/memsafe_boii.h"
#ifndef SDL_MAIN_HANDLED
#  define SDL_MAIN_HANDLED
#endif
#include "SDL2/include/SDL.h"
#include "SDL2_ttf/include/SDL_ttf.h"
#if defined(_WIN32) || defined(_WIN64) || defined(__WIN32__) ||                \
  defined(__WIN64__) || defined(__WINDOWS__)
#  include <Windows.h>
#endif
#include "tinyfiledialogs/tinyfiledialogs.h"

DWORD WINAPI threaded_parsing(LPVOID lp_param)
{
  parser_func_params* params = (parser_func_params*)lp_param;

  int parser_return_value =
    md_parse(params->text, params->size, params->parser, params->userdata);
#ifdef DEBUG
  SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION,
              "Parser return value: %d",
              parser_return_value);
#endif

  return parser_return_value;
}

int main(int argc, char** argv)
{

  // Initialize SDL2
  if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) != 0)
  {
    SDL_LogCritical(
      SDL_LOG_CATEGORY_ERROR, "Unable to initialize video: %s", SDL_GetError());
    return 1;
  }
  SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Initialized Video Subsystem.");

  // Initialize SDL2 TTF extension
  if(TTF_Init() != 0)
  {
    SDL_LogCritical(SDL_LOG_CATEGORY_ERROR,
                    "Unable to initialize ttf extension: %s",
                    TTF_GetError());
    SDL_Quit();
    return 1;
  }
  SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Initialized TTF extension.");

  // Loading font
  // const char* roboto_font_file_path = "assets/fonts/roboto/Roboto-Regular.ttf";
  // TTF_Font* roboto_font = TTF_OpenFont(roboto_font_file_path, 18);
  // if (!roboto_font) {
  //   SDL_LogCritical(SDL_LOG_CATEGORY_ERROR, "Unable to load font: %s", roboto_font_file_path);
  //   TTF_Quit();
  //   SDL_Quit();
  //   return 1;
  // }
  // SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Loaded font: %s", roboto_font_file_path);

  // Loading system font
  const char* segoeui_font_file_path = "C:/Windows/Fonts/segoeui.ttf";
  TTF_Font* segoeui_font = TTF_OpenFont(segoeui_font_file_path, 18);
  if(!segoeui_font)
  {
    SDL_LogCritical(SDL_LOG_CATEGORY_ERROR,
                    "Unable to load font: %s",
                    segoeui_font_file_path);
    TTF_Quit();
    SDL_Quit();
    return 1;
  }
  SDL_LogInfo(
    SDL_LOG_CATEGORY_APPLICATION, "Loaded font: %s", segoeui_font_file_path);

  char* markdown_file_path = NULL;
  if(argc < 2)
  {
    prompt_result result = select_file_prompt(segoeui_font);

    if(result.ok)
    {
      markdown_file_path = result.data.file_path;
      SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION,
                      "Markdown file path: %s",
                      markdown_file_path);
#ifdef DEBUG
      SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION,
                  "Markdown file path: %s",
                  markdown_file_path);
#endif
    }
    else
    {
      // closed without selecting file
      // unable to create window or renderer for prompt window
      TTF_Quit();
      SDL_Quit();
      return 0;
    }
  }
  else
  {
    unsigned int markdown_file_path_length = strlen(argv[1]);
    markdown_file_path = argv[1];
#ifdef DEBUG
    SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION,
                "Markdown file path: %s",
                markdown_file_path);
#endif
  }

  file_details* markdown_file_details = load_file(markdown_file_path);
  if(!markdown_file_details)
  {
#ifdef DEBUG
    SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION,
                    "Unable to open file: %s",
                    markdown_file_path);
#endif
    memsafe_boii_api__clean();
    return 1;
  }
#ifdef DEBUG
  SDL_LogCritical(
    SDL_LOG_CATEGORY_APPLICATION, "Blob: %s", markdown_file_details->content);
#endif

  MD_PARSER* parser = utils_parser_new();
  if(!parser)
  {
#ifdef DEBUG
    SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, "Unable to create parser.");
#endif
    memsafe_boii_api__clean();
    return 1;
  }

  parser_func_params* params =
    parser_func_param__new(markdown_file_details->content,
                           sizeof(char) * markdown_file_details->length,
                           parser,
                           NULL);
  if(!params)
  {
#ifdef DEBUG
    SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION,
                    "Unable to allocate memory for params struct.");
#endif
    memsafe_boii_api__clean();
    return 1;
  }

  // int parser_return_value = md_parse(markdown_file_details->content, sizeof(char)*markdown_file_details->length, parser, NULL);
  // SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "Parser return value: %d", parser_return_value);

  // Creating window
  Uint32 window_flags = SDL_WINDOW_INPUT_FOCUS | SDL_WINDOW_MOUSE_FOCUS |
                        SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN |
                        SDL_WINDOW_ALLOW_HIGHDPI;
  SDL_Window* window = SDL_CreateWindow("Markdown Viewer",
                                        SDL_WINDOWPOS_CENTERED,
                                        SDL_WINDOWPOS_CENTERED,
                                        1080,
                                        720,
                                        window_flags);
  if(!window)
  {
    SDL_LogCritical(
      SDL_LOG_CATEGORY_RENDER, "Unable to create window: %s", SDL_GetError());
    TTF_CloseFont(segoeui_font);
    TTF_Quit();
    SDL_Quit();
    memsafe_boii_api__clean();
    return 1;
  }
  SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Created window.");

  // Creating renderer
  Uint32 renderer_flags = SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_SOFTWARE;
  SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, renderer_flags);
  if(!renderer)
  {
    SDL_LogCritical(
      SDL_LOG_CATEGORY_RENDER, "Unable to create renderer: %s", SDL_GetError());
    SDL_DestroyWindow(window);
    TTF_CloseFont(segoeui_font);
    TTF_Quit();
    SDL_Quit();
    memsafe_boii_api__clean();
    return 1;
  }
  SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Created renderer.");

  HANDLE parsing_thread_handle =
    CreateThread(NULL, 0, &threaded_parsing, params, 0, NULL);
  if(!parsing_thread_handle)
  {
#ifdef DEBUG
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
                 "Unable to create thread for parsing!");
#endif
    memsafe_boii_api__clean();
    return 1;
  }
  SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION,
              "Lauched parsing in a seperate thread.");

  SDL_Event event;
  bool quit = false;
  bool parsing_complete = false;

  // loop to check for completion of parsing, then immediately rendering parsed markdown
  // this is not the main app loop
  // this loop exits when parsing is completed
  while(!parsing_complete && !quit)
  {
    while(SDL_PollEvent(&event))
    {
      if(event.type == SDL_QUIT)
      {
        quit = true;
      }
      else if(event.type == SDL_WINDOWEVENT_RESIZED)
      {}
      else if(event.type == SDL_WINDOWEVENT_RESTORED)
      {}
      else if(event.type == SDL_WINDOWEVENT_MAXIMIZED)
      {}
    }

    SDL_RenderClear(renderer);

    // checking for parsing thread completion
    DWORD result = WaitForSingleObject(parsing_thread_handle, 0);
    if(result == WAIT_OBJECT_0)
    {
      // parsing complete
      parsing_complete = true;
      SDL_Surface* text_surface = TTF_RenderText_Blended(
        segoeui_font,
        "* Parsing Complete :)",
        (SDL_Color){.r = 255, .g = 255, .b = 255, .a = 255});
      if(!text_surface)
      {
#ifdef DEBUG
        SDL_LogError(SDL_LOG_CATEGORY_ERROR,
                     "Error while rendering text surface: %s",
                     TTF_GetError());
#endif
        continue;
      }

      SDL_Texture* text_texture =
        SDL_CreateTextureFromSurface(renderer, text_surface);
      if(!text_texture)
      {
#ifdef DEBUG
        SDL_LogError(SDL_LOG_CATEGORY_ERROR,
                     "Error while creating texture from text surface: %s",
                     SDL_GetError());
#endif
        continue;
      }

      SDL_Rect destination_rect = {
        .x = 10, .y = 10, .w = text_surface->w, .h = text_surface->h};
      SDL_RenderCopy(renderer, text_texture, NULL, &destination_rect);

      SDL_DestroyTexture(text_texture);
      SDL_FreeSurface(text_surface);
      SDL_RenderPresent(renderer);
      continue;
    }
    else
    {
      // still parsing
      SDL_Surface* text_surface = TTF_RenderText_Blended(
        segoeui_font,
        "Parsing ...",
        (SDL_Color){.r = 255, .g = 255, .b = 255, .a = 255});
      if(!text_surface)
      {
#ifdef DEBUG
        SDL_LogError(SDL_LOG_CATEGORY_ERROR,
                     "Error while rendering text surface: %s",
                     TTF_GetError());
#endif
        continue;
      }

      SDL_Texture* text_texture =
        SDL_CreateTextureFromSurface(renderer, text_surface);
      if(!text_texture)
      {
#ifdef DEBUG
        SDL_LogError(SDL_LOG_CATEGORY_ERROR,
                     "Error while creating texture from text surface: %s",
                     SDL_GetError());
#endif
        continue;
      }

      SDL_Rect destination_rect = {
        .x = 10, .y = 10, .w = text_surface->w, .h = text_surface->h};
      SDL_RenderCopy(renderer, text_texture, NULL, &destination_rect);

      SDL_DestroyTexture(text_texture);
      SDL_FreeSurface(text_surface);

      SDL_RenderPresent(renderer);
    }
  }

  // app loop
  while(!quit)
  {
    if(SDL_WaitEvent(&event))
    {
      if(event.type == SDL_QUIT)
      {
        quit = true;
      }
      if(event.type == SDL_MOUSEBUTTONUP)
      {
        if(event.button.button == SDL_BUTTON_LEFT)
        {
          // left click
        }
        else if(event.button.button == SDL_BUTTON_RIGHT)
        {
          // right click
        }
      }
      else if(event.type == SDL_WINDOWEVENT_RESIZED)
      {}
      else if(event.type == SDL_WINDOWEVENT_RESTORED)
      {}
      else if(event.type == SDL_WINDOWEVENT_MAXIMIZED)
      {}
    }

    SDL_RenderClear(renderer);

    SDL_Surface* text_surface = TTF_RenderText_Blended(
      segoeui_font,
      "* Parsing Complete :)",
      (SDL_Color){.r = 255, .g = 255, .b = 255, .a = 255});
    if(!text_surface)
    {
#ifdef DEBUG
      SDL_LogError(SDL_LOG_CATEGORY_ERROR,
                   "Error while rendering text surface: %s",
                   TTF_GetError());
#endif
      continue;
    }

    SDL_Texture* text_texture =
      SDL_CreateTextureFromSurface(renderer, text_surface);
    if(!text_texture)
    {
#ifdef DEBUG
      SDL_LogError(SDL_LOG_CATEGORY_ERROR,
                   "Error while creating texture from text surface: %s",
                   SDL_GetError());
#endif
      continue;
    }

    SDL_Rect destination_rect = {
      .x = 10, .y = 10, .w = text_surface->w, .h = text_surface->h};
    SDL_RenderCopy(renderer, text_texture, NULL, &destination_rect);

    SDL_DestroyTexture(text_texture);
    SDL_FreeSurface(text_surface);

    SDL_RenderPresent(renderer);
  }

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);

  SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Cleaned up all resources.");
  SDL_Quit();

  memsafe_boii_api__clean();

  return 0;
}
