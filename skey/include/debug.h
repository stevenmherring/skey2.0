#ifndef __DEBUG__
#define __DEBUG__

void debug(char* file, int level, char* str, char* str2);

//1 and 3 alter enter functions
void debug_1_enter(char* file, char* str);

void debug_3_enter(char* file, int n, char* arg, ...);

//1 and 2 alter exit functions
void debug_1_exit(char* file, char* str);

void debug_2_exit(char* file, char* arg);

#endif
