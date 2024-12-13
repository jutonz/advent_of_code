FILE* open_file(const char *filename);
char* check_args(int argc, char *argv[]);

typedef void (*each_line_t)(char*);
void read_file(char *filename, each_line_t each_line);
