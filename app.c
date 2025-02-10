#include "raylib.h"
#include "stdio.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void resize_logic(int* screen_height, int *screen_width, int* display) {
        if(IsWindowResized()) {
           *screen_height = GetScreenHeight(); 
           *screen_width = GetScreenWidth();
           printf("%dx%d\n", *screen_height, *screen_width);
        }
        if(IsWindowFullscreen()) {
            *display=GetCurrentMonitor();
            SetWindowSize(GetMonitorWidth(*display),GetMonitorHeight(*display));
        }
}

void get_path(char* path) {
    FILE *fp;
    fp = popen("echo $PATH", "r"); 
    if(fp == NULL) { 
        puts("Command failed");
        exit(1);
    } 
    fgets(path, 1024*sizeof(char), fp);
    fclose(fp);
   
}

void live_fzf(char* results, char* path, char* search) {
    strcpy(results, "");
    int path_i = 0;
    int path_endpoints[128];
    path_endpoints[0] = 0;
    int endpoint_count = 1;
    char fzf_command[512];
    strcpy(fzf_command, "fzf -f \"" );
    strcat(fzf_command, search);
    strcat(fzf_command, "\"");
    while(path[path_i] != '\0') {
        if(path[path_i] == ':') {
            path_endpoints[endpoint_count] = path_i + 1;
            endpoint_count++;
        }
        path_i++;
    }
    for(int i = 0; i < endpoint_count - 1 ; i++) {
        char cd_command[512];
        int sub_len = path_endpoints[i + 1] - path_endpoints[i]; 
        char sub[sub_len];
        strncpy(sub, path + path_endpoints[i], sub_len);
        sub[sub_len - 1] = '\0';
        strcpy(cd_command, "cd ");
        strcat(cd_command, sub);
        printf("E1: %d, E2: %d, Len: %d \n%s\n",path_endpoints[i],path_endpoints[i+1], sub_len, sub);
        char final_command[1024];
        strcpy(final_command, cd_command);
        strcat(final_command, " && ");
        strcat(final_command, fzf_command);
        FILE* stream;
        stream = popen(final_command, "r");
        char output[500];
        if(stream == NULL) {
            puts("stream command error");
        }
        char temp[500];
        if(fgets(output, sizeof(output), stream) == NULL) {
            strcpy(temp, "\n");
            continue; 
        }
        strcpy(temp, "");
        strcat(temp, output);
        strcat(results,temp);
        puts("");
        puts(results);
        fclose(stream);
    }
    strcat(results, "\0");
}


