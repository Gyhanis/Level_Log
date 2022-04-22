#define LOG_LEVEL 3
#define LOG_FEATURE 1
#include "log_tool.h"

int main(){
        FILE *fp = fopen("/dev/stdout", "w");
        FERROR(fp, "This is a error message\n");
        FWARNING(fp, "This is a warning message with para %d\n", 123);
        FINFO(fp, "This is a info message with multi para %d ,%s and %f\n", 123, "???", 1.28);
        FDEBUG(fp, "This is a debug message\n");
        fclose(fp);
        return 0;
}