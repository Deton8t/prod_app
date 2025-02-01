#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "terminal.h"
void hunt(char programs[40][40], int count) {
    puts(programs[0]);
    for(int i = 0; i < count; i++) {
        if(is_program_running(programs[i])) {
            char command[120] = "kill $(pidof ";
            strcat(command,programs[i]);
            strcat(command,")");
            puts(command);
            system(command);
        }
    }
}
