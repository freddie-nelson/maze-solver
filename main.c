#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdbool.h>
#include <sys/time.h>
#include <stdlib.h>
#include "globals.h"

TTF_Font *FONT;

// SDL_Texture *numTextures[10];

// void setupNumbers(SDL_Renderer *renderer)
// {
//   SDL_Surface *surface;
//   SDL_Color textColor = {255, 255, 255, 0};

//   for (uint8_t i = 0; i < 10; i++)
//   {
//     char text[1];
//     sprintf(text, "%u", i);

//     surface = TTF_RenderText_Solid(FONT, text, textColor);
//     if (surface == NULL)
//     {
//       printf(" %s ", SDL_GetError());
//     }

//     numTextures[i] = SDL_CreateTextureFromSurface(renderer, surface);
//     if (numTextures[i] == NULL)
//     {
//       printf(" %s ", SDL_GetError());
//     }
//   }

//   SDL_FreeSurface(surface);
// }

int main()
{
  SDL_Window *window = NULL;
  SDL_Renderer *renderer = NULL;
  SDL_Surface *screenSurface = NULL;

  // init png loading
  IMG_Init(IMG_INIT_PNG);

  // load font
  TTF_Init();
  FONT = TTF_OpenFont("font.ttf", 16);
  if (FONT == NULL)
  {
    printf(" could not find font %s ", stderr);
    exit(EXIT_FAILURE);
  }

  bool quit = true;

  if (SDL_Init(SDL_INIT_VIDEO) < 0)
  {
    printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
  }
  else
  {
    // create window
    window = SDL_CreateWindow("Snake", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_SIZE, SCREEN_SIZE, SDL_WINDOW_SHOWN);
    if (window == NULL)
    {
      printf("Window could not be created! SDL_ERROR: %s\n", SDL_GetError());
    }
    else
    {
      // get window surface
      screenSurface = SDL_GetWindowSurface(window);
      renderer = SDL_GetRenderer(window);
      quit = false;
    }
  }

  // setupNumbers(renderer);

  // game loop
  SDL_Event e;

  unsigned tickPerFrame = 1000 / 60;

  while (!quit)
  {
    unsigned startTick = SDL_GetTicks();

    while (SDL_PollEvent(&e) != 0)
    {
      switch (e.type)
      {
      case SDL_QUIT:
      {
        quit = true;
        break;
      }
      }
    }

    // clear renderer
    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
    SDL_RenderClear(renderer);

    SDL_RenderPresent(renderer);

    unsigned delay = startTick - tickPerFrame;
    if (delay > 0)
      SDL_Delay(delay);
  }

  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}