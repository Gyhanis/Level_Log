#ifndef _GYHANIS_LEVEL_LOG_TOOLS_H
#define _GYHANIS_LEVEL_LOG_TOOLS_H

#include <stdio.h>

#define _GYHANIS_LEVEL_LOG_TOOLS_DO_EXPAND(VAL)  VAL ## 1
#define _GYHANIS_LEVEL_LOG_TOOLS_EXPAND(VAL)     _GYHANIS_LEVEL_LOG_TOOLS_DO_EXPAND(VAL)
#define _GYHANIS_LEVEL_LOG_TOOLS_IS_EMPTY(VAL) (VAL != 0 && _GYHANIS_LEVEL_LOG_TOOLS_EXPAND(VAL) == 1)

#define _GYHANIS_LEVEL_LOG_TOOLS_FEATURE_LOCATION       1

#define _GYHANIS_LEVEL_LOG_TOOLS_FEATURE_MAX     \
        _GYHANIS_LEVEL_LOG_TOOLS_FEATURE_LOCATION 

#ifndef LOG_LEVEL
        #warning "LOG_LEVEL not defined, assuming NONE(0)"
        #define LOG_LEVEL 0
#elif _GYHANIS_LEVEL_LOG_TOOLS_IS_EMPTY(LOG_LEVEL) 
        #warning "LOG_LEVEL empty, assuming NONE"
        #undef LOG_LEVEL
        #define LOG_LEVEL 0
#endif 

#if LOG_LEVEL == 4 
        #define _GYHANIS_LOG_TOOLS_LEVEL_DEBUG
        #define _GYHANIS_LOG_TOOLS_LEVEL_INFO
        #define _GYHANIS_LOG_TOOLS_LEVEL_WARNING
        #define _GYHANIS_LOG_TOOLS_LEVEL_ERROR
#elif LOG_LEVEL == 3
        #define _GYHANIS_LOG_TOOLS_LEVEL_INFO
        #define _GYHANIS_LOG_TOOLS_LEVEL_WARNING
        #define _GYHANIS_LOG_TOOLS_LEVEL_ERROR
#elif LOG_LEVEL == 2
        #define _GYHANIS_LOG_TOOLS_LEVEL_WARNING
        #define _GYHANIS_LOG_TOOLS_LEVEL_ERROR
#elif LOG_LEVEL == 1
        #define _GYHANIS_LOG_TOOLS_LEVEL_ERROR
#elif LOG_LEVEL != 0
        #error Invalid value for LOG_LEVEL! Valid values: 1)DEBUG 2)INFO 3)WARNING 4)ERROR 0)NONE
#endif 

#ifndef LOG_FEATURE
        #define LOG_FEATURE 0
#elif _GYHANIS_LEVEL_LOG_TOOLS_IS_EMPTY(LOG_FEATURE)
        #warning "LOG_FEATURE empty, assuming 0"
        #undef LOG_FEATURE
        #define LOG_FEATURE 0
#endif 

#if LOG_FEATURE > _GYHANIS_LEVEL_LOG_TOOLS_FEATURE_MAX
        #error Invalid value for LOG_FEATURE!
#endif 

#if LOG_FEATURE & _GYHANIS_LEVEL_LOG_TOOLS_FEATURE_LOCATION 
        #define _GYHANIS_LOG_TOOLS_FLOC_FMT "@%s:%d\t in func %s:\t"
        #define _GYHANIS_LOG_TOOLS_FLOC_FUNC ,__func__
        #define _GYHANIS_LOG_TOOLS_FLOC_FILE ,__FILE__
        #define _GYHANIS_LOG_TOOLS_FLOC_LINE ,__LINE__
#else 
        #define _GYHANIS_LOG_TOOLS_FLOC_FMT 
        #define _GYHANIS_LOG_TOOLS_FLOC_FILE
        #define _GYHANIS_LOG_TOOLS_FLOC_LINE
        #define _GYHANIS_LOG_TOOLS_FLOC_FUNC 
#endif

#ifdef _GYHANIS_LOG_TOOLS_LEVEL_DEBUG
        #define DEBUG(fmt, ...) printf("[DEBUG]\t\t" \
        _GYHANIS_LOG_TOOLS_FLOC_FMT fmt \
        _GYHANIS_LOG_TOOLS_FLOC_FILE \
        _GYHANIS_LOG_TOOLS_FLOC_LINE \
        _GYHANIS_LOG_TOOLS_FLOC_FUNC, ##__VA_ARGS__)
        #define FDEBUG(fp, fmt, ...) fprintf(fp, "[DEBUG]\t\t" \
        _GYHANIS_LOG_TOOLS_FLOC_FMT fmt \
        _GYHANIS_LOG_TOOLS_FLOC_FILE \
        _GYHANIS_LOG_TOOLS_FLOC_LINE \
        _GYHANIS_LOG_TOOLS_FLOC_FUNC, ##__VA_ARGS__)
#else 
        #define DEBUG(...) 
        #define FDEBUG(...)
#endif 

#ifdef _GYHANIS_LOG_TOOLS_LEVEL_INFO
        #define INFO(fmt, ...) printf("[INFO]\t\t" \
        _GYHANIS_LOG_TOOLS_FLOC_FMT fmt \
        _GYHANIS_LOG_TOOLS_FLOC_FILE \
        _GYHANIS_LOG_TOOLS_FLOC_LINE \
        _GYHANIS_LOG_TOOLS_FLOC_FUNC, ##__VA_ARGS__)
        #define FINFO(fp, fmt, ...) fprintf(fp, "[INFO]\t\t" \
        _GYHANIS_LOG_TOOLS_FLOC_FMT fmt \
        _GYHANIS_LOG_TOOLS_FLOC_FILE \
        _GYHANIS_LOG_TOOLS_FLOC_LINE \
        _GYHANIS_LOG_TOOLS_FLOC_FUNC, ##__VA_ARGS__)
#else 
        #define INFO(...)
        #define FINFO(...)
#endif 


#ifdef _GYHANIS_LOG_TOOLS_LEVEL_WARNING
        #define WARNING(fmt, ...) printf("[WARNING]\t" \
        _GYHANIS_LOG_TOOLS_FLOC_FMT fmt \
        _GYHANIS_LOG_TOOLS_FLOC_FILE \
        _GYHANIS_LOG_TOOLS_FLOC_LINE \
        _GYHANIS_LOG_TOOLS_FLOC_FUNC, ##__VA_ARGS__)
        #define FWARNING(fp, fmt, ...) fprintf(fp, "[WARNING]\t" \
        _GYHANIS_LOG_TOOLS_FLOC_FMT fmt \
        _GYHANIS_LOG_TOOLS_FLOC_FILE \
        _GYHANIS_LOG_TOOLS_FLOC_LINE \
        _GYHANIS_LOG_TOOLS_FLOC_FUNC, ##__VA_ARGS__)
#else 
        #define WARNING(...)
        #define FWARNING(...)
#endif

#ifdef _GYHANIS_LOG_TOOLS_LEVEL_ERROR
        #define ERROR(fmt, ...) printf("[ERROR]\t\t" \
        _GYHANIS_LOG_TOOLS_FLOC_FMT fmt \
        _GYHANIS_LOG_TOOLS_FLOC_FILE \
        _GYHANIS_LOG_TOOLS_FLOC_LINE \
        _GYHANIS_LOG_TOOLS_FLOC_FUNC, ##__VA_ARGS__)
        #define FERROR(fp, fmt, ...) fprintf(fp, "[ERROR]\t\t" \
        _GYHANIS_LOG_TOOLS_FLOC_FMT fmt \
        _GYHANIS_LOG_TOOLS_FLOC_FILE \
        _GYHANIS_LOG_TOOLS_FLOC_LINE \
        _GYHANIS_LOG_TOOLS_FLOC_FUNC, ##__VA_ARGS__)
#else 
        #define ERROR(...)
        #define FERROR(...)
#endif

#endif 