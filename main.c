#include "raylib.h"
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
#include "terminal.h"
int main(int argc, char* argv[]) {
    int screen_height = 500;
    int screen_width = 900;
    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_WINDOW_UNFOCUSED);
    InitWindow(screen_width, screen_height, "Prod Tool");
    SetTargetFPS(60);
    bool show_message_box = 0;
    int display = GetCurrentMonitor();
    while(!WindowShouldClose()) {
        if(IsWindowResized()) {
           screen_height = GetScreenHeight(); 
           screen_width = GetScreenWidth();
           printf("%dx%d\n", screen_height, screen_width);
        }
        if(IsWindowFullscreen()) {
            display=GetCurrentMonitor();
            SetWindowSize(GetMonitorWidth(display),GetMonitorHeight(display));

        }
        GuiSetStyle(DEFAULT,TEXT_SIZE,24*((float)screen_width/GetMonitorWidth(display)));
        GuiButton((Rectangle){0,0,screen_width/8.0, 50}, "Add programs!");
        BeginDrawing();
        ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR)));

        
        EndDrawing();
    }
}

