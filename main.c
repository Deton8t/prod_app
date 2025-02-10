#include "raylib.h"
#include <string.h>
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
#include "terminal.h"
#include "app.h"
#include "daemon.h"

#define SEARCH_TEXT_SIZE 40
#define PATH_SIZE 1024
#define FZF_SEARCH_SIZE 1024

int main(int argc, char* argv[]) {
    int screen_height = 500;
    int screen_width = 900;
    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_WINDOW_UNFOCUSED);
    InitWindow(screen_width, screen_height, "Prod Tool");
    SetTargetFPS(60);
    int display = GetCurrentMonitor();
    int show_input = 0;
    char text[SEARCH_TEXT_SIZE];
    strcpy(text,"");
    char blocked_programs[40][40]; // rm magic number idk
    int blocked_count = 0;
    int activate_that_mf_demon=0;
    uint frame_counter;
    // allocate path;
    char path[PATH_SIZE];
    get_path(path);
    puts(path);
    char search_text[SEARCH_TEXT_SIZE];
    while(!WindowShouldClose()) {
        if(activate_that_mf_demon) {
            frame_counter++;
            if(frame_counter > 180) {
                hunt(blocked_programs,blocked_count);
                frame_counter = 0;
            }
        }
        resize_logic(&screen_height, &screen_width, &display);
        
        GuiSetStyle(DEFAULT,TEXT_SIZE,24*((float)screen_width/GetMonitorWidth(display)));
        if(GuiButton((Rectangle){0,0,screen_width/8.0, 50}, "Add programs!")) {
            show_input = 1;
        }
        if(show_input) {
            GuiSetStyle(DEFAULT,TEXT_SIZE,15);
            int input_result = GuiTextInputBox((Rectangle){screen_width/2.0-75,screen_height/2.0-50,150,100},"Input Program","", "Add;Stop",text, 40 , false);

            if(input_result == 0) {
                show_input = 0;
                puts("hi!");
            }
            if(input_result == 1) {
                blocked_count++;
                strcpy(blocked_programs[blocked_count-1],text);
                puts(text);
                strcpy(text,"");

            }
            if(input_result == 2) {
                activate_that_mf_demon = 1;
                show_input = 0;
            }
            char results [1024];
            if(strchr(text,'\"')) {
                strcpy(text, search_text);
            }
            if(strcmp(search_text, text) != 0) {
                live_fzf(results,path,text);
            }
            GuiTextBox((Rectangle){screen_width/2.0-150,screen_height/2.0+50,300,180},results, 4, false);
            strcpy(search_text,text);

        }
        BeginDrawing();
        ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR)));

        
        EndDrawing();
    }
}

