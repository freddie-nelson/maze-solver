#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include "globals.h"
#include "maze.h"

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
  // seed rand
  srand(time(NULL));

  SDL_Window *window = NULL;
  SDL_Renderer *renderer = NULL;

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

  if (SDL_Init(SDL_INIT_VIDEO) < 0)
  {
    printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    exit(EXIT_FAILURE);
  }

  // Create a window usable with OpenGL context
  window = SDL_CreateWindow("Title", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_SIZE, SCREEN_SIZE, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);

  // Select render driver
  // - A render driver that supports HW acceleration is used when available
  // - Otherwise a render driver supporting software fallback is selected
  SDL_RendererInfo renderDriverInfo;
  uint32_t rendererFlags = SDL_RENDERER_TARGETTEXTURE;
  int32_t nbRenderDrivers = SDL_GetNumRenderDrivers(), index = 0;
  if (nbRenderDrivers < 0)
  {
    exit(EXIT_FAILURE);
  }

  while (index < nbRenderDrivers)
  {
    if (SDL_GetRenderDriverInfo(index, &renderDriverInfo) == 0)
    {
      if (((renderDriverInfo.flags & rendererFlags) == rendererFlags) && ((renderDriverInfo.flags & SDL_RENDERER_ACCELERATED) == SDL_RENDERER_ACCELERATED))
      {
        // Using render driver with HW acceleration
        rendererFlags |= SDL_RENDERER_ACCELERATED;
        SDL_SetHint(SDL_HINT_RENDER_DRIVER, renderDriverInfo.name);
        break;
      }
    }
    ++index;
  }

  if (index == nbRenderDrivers)
  {
    // Let SDL use the first render driver supporting software fallback
    rendererFlags |= SDL_RENDERER_SOFTWARE;
    index = -1;
  }

  // Create renderer
  renderer = SDL_CreateRenderer(window, index, rendererFlags);
  if (renderer == NULL)
  {
    printf("renderer SDL_Error: %s\n", SDL_GetError());
    exit(EXIT_FAILURE);
  }

  bool quit = false;

  // generate maze
  const unsigned SIZE = 80;
  Maze *m;
  m = newMaze(SIZE, SIZE);

  // for (size_t i = 0; i < m->height; i++)
  // {
  //   for (size_t j = 0; j < m->width; j++)
  //   {
  //     unsigned index = MAZE_INDEX(m, j, i);
  //     printf(" x: %u, y: %u \n", m->cells[index].x, m->cells[index].y);
  //   }
  // }

  generateMaze(m, DEPTH_FIRST);
  solveMaze(m, &m->cells[MAZE_INDEX(m, 0, 0)], &m->cells[MAZE_INDEX(m, SIZE - 1, SIZE - 1)]);

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

    drawMaze(m, renderer);

    SDL_RenderPresent(renderer);

    unsigned frameTime = SDL_GetTicks() - startTick;
    printf("\r FRAME_TIME: %u ", frameTime);
    if (frameTime < tickPerFrame && !quit)
      SDL_Delay(tickPerFrame - frameTime);
  }

  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}