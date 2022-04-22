# Log Tool

## Introduction

This is a log tool with 5 levels:

- ERROR: Level 1
- WARNING: Level 2
- INFO: Level 3
- DEBUG: Level 4
- NONE: Level 0

Logs whose levels are higher than the output 
level set by the macro *LOG_LEVEL*
will be removed before compilation, and will not 
hinder the performance at runtime.

This tool works on newest GNU gcc, other compiler 
is not yet testes.

## Usage

Include *"log_tool.h"* in your source file, and use `ERROR()`,
`WARNING()`, `INFO()` and `DEBUG()` the same way you use `printf()`.
Also, there are `FERROR()`, `FWARNING()`, `FINFO()` and `FDEBUG()`
that works as `fprintf()` to log to files if needed. For more 
details , please read the *Examples* chapter.

## Examples

### Usage of *LOG_LEVEL*

Followings are contents of example.c

        #include "log_tool.h"

        int main(){
                ERROR("This is a error message\n");
                WARNING("A warning message with para %d\n", 123);
                INFO("multi para %05d ,%s and %.3f\n", 123, "???", 1.281284);
                DEBUG("This is a debug message\n");
                return 0;
        }

Compile it with *LOG_LEVEL* set as the greatest level *DEBUG*(which 
is 4):

        $ gcc example.c -DLOG_LEVEL=4 -o example 

Run example, and the output from console is:

        [ERROR]         This is a error message
        [WARNING]       A warning message with para 123
        [INFO]          multi para 00123 ,??? and 1.281
        [DEBUG]         This is a debug message

Comiple it again with *LOG_LEVEL* set as the level *WARNING*(which is 2)
and run it:

        $ gcc example.c -DLOG_LEVEL=4 -o example ; ./example

And the output becomes:

        [ERROR]         This is a error message
        [WARNING]       A warning message with para 123

Notice that levels higher than *WARNING*, which are *INFO* and *DEBUG*, are 
removed. This is done by the preprocessor of the compiler. From the program's
perspective, it runs as if the logging code were not existed in the source, 
instead of doing a `if` condictional branch.

*NONE* (Level 0) is the smallest log level, an it removes all the logs even from *ERROR* :

        $ gcc example.c -DLOG_LEVEL=0 -o example ; ./example
        $

*NONE* is also the default log level:

        $ gcc example.c -o example ; ./example
        In file included from example.c:1:
        log_tool.h:16:10: warning: #warning "LOG_LEVEL not defined, assuming NONE(0)" [-Wcpp]
             16 |         #warning "LOG_LEVEL not defined, assuming NONE(0)"
                |          ^~~~~~~
        $

### Usage of *LOG_FEATURE* 

Yet, there is only one feature, *LOCATION* (Feature code 1), 
which adds information on where the log is post.

        $ gcc example.c -DLOG_LEVEL=4 -DLOG_FEATURE=1 -o example ; ./example
        [ERROR]         @example.c:4     in func main:  This is a error message
        [WARNING]       @example.c:5     in func main:  A warning message with para 123
        [INFO]          @example.c:6     in func main:  multi para 00123 ,??? and 1.281
        [DEBUG]         @example.c:7     in func main:  This is a debug message
        $

Leave *LOG_FEATURE* undefined or define it as 0 to disable 
*LOCATION* feature.

### Others

It is possible to define *LOG_LEVEL* and *LOG_FEATURE* in the source
file, but do it **before** you include *"log_tool.h"*.

Contents of example2.c:

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

Compile and run:

        $ gcc example2.c -o example2 ; ./example2
        [ERROR]         @example2.c:7    in func main:  This is a error message
        [WARNING]       @example2.c:8    in func main:  This is a warning message with para 123
        [INFO]          @example2.c:9    in func main:  This is a info message with multi para 123 ,??? and 1.280000
        $