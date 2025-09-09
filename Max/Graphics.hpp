#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <iostream>
#ifdef __EMSCRIPTEN__
#include <emscripten/emscripten.h>
#endif
#include "SDL3/SDL.h"
#include "SDL3/SDL_main.h"


#include "Cylinder.hpp"

class Graphics
{

private:

    int* gFrameBuffer;
    SDL_Window* gSDLWindow;
    SDL_Renderer* gSDLRenderer;
    SDL_Texture* gSDLTexture;
    int gDone;
    const int WINDOW_WIDTH = 1920 / 2;
    const int WINDOW_HEIGHT = 1080 / 2;

    float angle = 0.0f;

    bool update()
    {
        SDL_Event e;

        if (SDL_PollEvent(&e))
        {
            if (e.type == SDL_EVENT_QUIT)
            {
            return false;
            }
            if (e.type == SDL_EVENT_KEY_UP && e.key.key == SDLK_ESCAPE)
            {
            return false;
            }
        }

        glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);  // Dark gray background
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();

        float proj[16];
        perspective(60.0f, 800.0f / 600.0f, 0.1f, 100.0f, proj);
        glLoadMatrixf(proj);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glTranslatef(0.0f, 0.0f, -5.0f);
        glRotatef(angle, 1.0f, 0.0f, 0.0f);

        Cylinder C;
        C.drawCylinder(1, 1, 20);

        SDL_GL_SwapWindow(gSDLWindow);

        angle += 0.1f;

        //SDL_RenderPresent(gSDLRenderer);
        SDL_Delay(1);
        return true;
    }

    void render(Uint64 aTicks)
    {
    for (int i = 0, c = 0; i < WINDOW_HEIGHT; i++)
    {
        for (int j = 0; j < WINDOW_WIDTH; j++, c++)
        {
        gFrameBuffer[c] = (int)(i * i + j * j + aTicks) | 0xff000000;
        }
    }
    }

    void loop()
    {
    if (!update())
    {
        gDone = 1;
    #ifdef __EMSCRIPTEN__
        emscripten_cancel_main_loop();
    #endif
    }
    else
    {
        render(SDL_GetTicks());
    }
    }

    void perspective(float fovY, float aspect, float zNear, float zFar, float* matrix) {
        float f = 1.0f / tanf(fovY * 0.5f * (3.14159265358979323846f / 180.0f));
        matrix[0]  = f / aspect;
        matrix[1]  = 0;
        matrix[2]  = 0;
        matrix[3]  = 0;

        matrix[4]  = 0;
        matrix[5]  = f;
        matrix[6]  = 0;
        matrix[7]  = 0;

        matrix[8]  = 0;
        matrix[9]  = 0;
        matrix[10] = (zFar + zNear) / (zNear - zFar);
        matrix[11] = -1;

        matrix[12] = 0;
        matrix[13] = 0;
        matrix[14] = (2 * zFar * zNear) / (zNear - zFar);
        matrix[15] = 0;
    }

public:

    int MaximRender()
    {
    if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS))
    {
        return -1;
    }

    gFrameBuffer = new int[WINDOW_WIDTH * WINDOW_HEIGHT];
    gSDLWindow = SDL_CreateWindow("SDL3 window", WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
    gSDLRenderer = SDL_CreateRenderer(gSDLWindow, NULL);
    gSDLTexture = SDL_CreateTexture(gSDLRenderer, SDL_PIXELFORMAT_ABGR8888, SDL_TEXTUREACCESS_STREAMING, WINDOW_WIDTH, WINDOW_HEIGHT);

    SDL_GLContext glContext = SDL_GL_CreateContext(gSDLWindow);
    if (!glContext) {
        std::cerr << "GL Context Error: " << SDL_GetError() << "\n";
        SDL_DestroyWindow(gSDLWindow);
        SDL_Quit();
        return 1;
    }

    glEnable(GL_DEPTH_TEST);

    if (!gFrameBuffer || !gSDLWindow || !gSDLRenderer || !gSDLTexture)
        return -1;

    gDone = 0;
    #ifdef __EMSCRIPTEN__
    emscripten_set_main_loop(loop, 0, 1);
    #else
    while (!gDone)
    {
        loop();
    }
    #endif

    SDL_DestroyTexture(gSDLTexture);
    SDL_DestroyRenderer(gSDLRenderer);
    SDL_DestroyWindow(gSDLWindow);
    SDL_Quit();

    return 0;
    }
};

#endif