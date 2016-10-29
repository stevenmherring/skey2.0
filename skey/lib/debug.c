#include "skey.h"

//route all debug messages to default debug message
void debug(char* file, int level, char* str, char* str2){
  if(file == NULL){
    fprintf(stdout, "DEBUG MODE[%i]: %s, %s\n", level, str, str2);
  } else {
    FILE *fp = fopen(file, "ab+");
    if (fp == NULL){
      fprintf(stdout, "DEBUG ERROR: Could not open file\n");
      exit(1);
    }
    fprintf(fp, "DEBUG MODE[%i]: %s, %s\n", level, str, str2);
    fclose(fp);
  }
  return;
}

//1 and 3 alter enter functions
void debug_1_enter(char* file, char* str){
  debug(file, 1, "ON ENTER - ", str);
  return;
}//debug enter 1

void debug_3_enter(char* file, int n, char* arg, ...){
  va_list vars;
  va_start(vars, arg);
  char* s = arg;

  for(n = n; n > 0; n--) {
    debug(file, 3, "Arg - ", s);
    s = va_arg(vars, char*);
  }

  va_end(vars);
  return;
}//debug enter 3

//1 and 2 alter exit functions
void debug_1_exit(char* file, char* str){
  debug(file, 1, "ON EXIT - ", str);
  return;
}//debug exit 1

void debug_2_exit(char* file, char* arg){
  debug(file, 2, "RETURN - ", arg);
  return;
}//debug exit 2
