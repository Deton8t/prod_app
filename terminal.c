#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int is_program_running(const char* name) {
    FILE *fp;
    char buffer[512];
    char command[100] = "pstree | grep \"\\-"; 
    strcat(command, name);
    strcat(command, "-\"");
    puts(command);
    fp = popen(command,"r");
    if(fp == NULL) { 
        puts("Command failed");
        exit(1);
    }
    if(fgets(buffer, sizeof(buffer), fp) == NULL) {
        return 0;
    }
    return 1; 
}
