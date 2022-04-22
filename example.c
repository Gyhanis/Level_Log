#include "log_tool.h"

int main(){
        ERROR("This is a error message\n");
        WARNING("A warning message with para %d\n", 123);
        INFO("multi para %05d ,%s and %.3f\n", 123, "???", 1.281284);
        DEBUG("This is a debug message\n");
        return 0;
}