#include "raylib.h"
#include <string.h>
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
#include "terminal.h"
#include "pthread.h"
#include "daemon.h"
int main(int argc, char* argv[]) {
    int screen_height = 500;
    int screen_width = 900;
    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_WINDOW_UNFOCUSED);
    InitWindow(screen_width, screen_height, "Prod Tool");
    SetTargetFPS(60);
    bool show_message_box = 0;
    int display = GetCurrentMonitor();
    int show_input = 0;
    char text[40] = "Program";
    char blocked_programs[40][40];
    int blocked_count = 0;
    pthread_t daemon;
    int activate_that_mf_demon=0;
    uint frame_counter;
    while(!WindowShouldClose()) {
        if(activate_that_mf_demon) {
            frame_counter++;
            if(frame_counter > 120) {
                hunt(blocked_programs,blocked_count);
                frame_counter = 0;
            }
        }
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
        if(GuiButton((Rectangle){0,0,screen_width/8.0, 50}, "Add programs!")) {
            show_input = 1;
        }
        if(show_input) {
            GuiSetStyle(DEFAULT,TEXT_SIZE,15);
            int input_result = GuiTextInputBox((Rectangle){screen_width/2.0-75,screen_height/2.0-50,150,100},"Input Program","", "Add;Stop",text, 40 , false);
            if(input_result == 0) {
                show_input = 0;
            }
            if(input_result == 1) {
                blocked_count++;
                strcpy(blocked_programs[blocked_count-1],text);
                strcpy(text,"");
            }
            if(input_result == 2) {
                activate_that_mf_demon = 1;
                show_input = 0;
            }
        }
        BeginDrawing();
        ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR)));

        
        EndDrawing();
    }
}

