#ifndef FILE_UTILS
#define FILE_UTILS

int read_file( char* filename, char **buffer );
int read_file_split(char* filename, char* delimiter, char*** outBuffer);
int write_file( char* filename, char *buffer, int size);

#endif