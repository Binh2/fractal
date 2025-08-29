/*******************************************************************************************
*
*   raylib [core] example - basic window
*
*   Example complexity rating: [★☆☆☆] 1/4
*
*   NOTE: This example is prepared to compile for PLATFORM_WEB, and PLATFORM_DESKTOP
*   As you will notice, code structure is slightly diferent to the other examples...
*   To compile it for PLATFORM_WEB just uncomment #define PLATFORM_WEB at beginning
*
*   Example originally created with raylib 1.3, last time updated with raylib 1.3
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2015-2025 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "raylib.h"

//#define PLATFORM_WEB

#if defined(PLATFORM_WEB)
#include <emscripten/emscripten.h>
#endif

//----------------------------------------------------------------------------------
// Global Variables Definition
//----------------------------------------------------------------------------------
const int screenWidth = 500;
const int screenHeight = 500;

//----------------------------------------------------------------------------------
// Module functions declaration
//----------------------------------------------------------------------------------
void UpdateDrawFrame(void);     // Update and Draw one frame


#include <stdio.h>
#include <time.h>
// Custom logging function
void CustomLog(int msgType, const char *text, va_list args)
{
    char timeStr[64] = { 0 };
    time_t now = time(NULL);
    struct tm *tm_info = localtime(&now);
    
    strftime(timeStr, sizeof(timeStr), "%Y-%m-%d %H:%M:%S", tm_info);
    printf("[%s] ", timeStr);
    
    switch (msgType)
    {
        case LOG_INFO: printf("hiiiiiiiiii[INFO] : "); break;
        case LOG_ERROR: printf("hiiiiiiiiii[ERROR]: "); break;
        case LOG_WARNING: printf("hiiiiiiiiii[WARN] : "); break;
        case LOG_DEBUG: printf("hiiiiiiiiii[DEBUG]: "); break;
        default: break;
    }
    
    vprintf(text, args);
    printf("\n");
}


#include "Complex.h"

int mandelbrot_point(double real, double imag) {
    struct Complex c = Complex.new(real, imag);
    for (int i = 0; i < 256; i++) {
        struct Complex s = c.sqr(&c);
        if ((s.re < -2 || s.re > 2) || (s.im < -2 || s.im > 2)) {
            return i;
        }
    }
    return 255;
}
void render_mandelbrot(int width, int height, int img[width][height]) { // grayscale image
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            img[i][j] = mandelbrot_point(
                (j - height/2)*2.0 / height,
                (i - width/2)*2.0 / width
            );
        }
    }
    // return img;
}

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
static int img[screenWidth][screenHeight];
int main(void)
{
    struct Complex c = Complex.new(1.0, 2.0);
    struct Complex d = Complex.new(3.0, 4.0);
    struct Complex e = c.mul(&c, &d);
    struct Complex f = c.add(&c, &d);
    struct Complex g = c.sub(&c, &d);
    printf("Complex number: %.1f + %.1fi\n", c.re, c.im);
    printf("Absolute value: %.2f\n", c.abs(&c));
    printf("Multiplication: %.1f + %.1fi\n", e.re, e.im);
    printf("Addition: %.1f + %.1fi\n", f.re, f.im);
    printf("Subtraction: %.1f + %.1fi\n", g.re, g.im);
    printf("Complex conjugate: %.1f - %.1fi\n", c.re, -c.im);

    render_mandelbrot(screenWidth, screenHeight, img);

    // Set custom logger
    SetTraceLogCallback(CustomLog);
    // SetTraceLogLevel(LOG_DEBUG); // Set desired log level

    printf("Helllllllllllllllllll");

    // Initialization
    //--------------------------------------------------------------------------------------
    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

#if defined(PLATFORM_WEB)
    emscripten_set_main_loop(UpdateDrawFrame, 0, 1);
#else
    SetTargetFPS(60);   // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        UpdateDrawFrame();
    }
#endif

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}

//----------------------------------------------------------------------------------
// Module Functions Definition
//----------------------------------------------------------------------------------
void UpdateDrawFrame(void)
{
    // Update
    //----------------------------------------------------------------------------------
    // TODO: Update your variables here
    //----------------------------------------------------------------------------------

    // Draw
    //----------------------------------------------------------------------------------
    BeginDrawing();

        ClearBackground(RAYWHITE);

        // DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);
        // DrawText("This is working on both desktop and HTML5!", 210, 240, 20, LIGHTGRAY);
        // Draw the 2d img
        for (int i = 0; i < screenWidth; i++) {
            for (int j = 0; j < screenHeight; j++) {
                int color = img[i][j];
                DrawPixel(i, j, (Color){color, color, color, 255});
            }
        }
    EndDrawing();
    //----------------------------------------------------------------------------------
}