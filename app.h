void resize_logic(int* screen_height, int *screen_width, int* display); 
// Retrieves $PATH variable
void get_path(char* path);
// Returns results of fzf
// @p dest where the results will be stored
void live_fzf(char* results, char* path, char* search);
