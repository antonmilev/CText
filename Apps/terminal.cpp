/**
 * @file UnitTests.cpp
 * @brief Advanced Text Proccessing Library
 * @author Anton Milev, baj.mile@abv.bg
 * @version 1.0
 * @date November, 2019
 */

#include <stdio.h>

#ifdef WIN32
#include <Windows.h>
#include <varargs.h>

static CONSOLE_SCREEN_BUFFER_INFO ConsoleInfo;
static HANDLE  screen = GetStdHandle(STD_OUTPUT_HANDLE);
void printc(int color,const char* output,...)
{
    GetConsoleScreenBufferInfo(screen,&ConsoleInfo);
    SetConsoleTextAttribute(screen,color);
    va_list argList;
    va_start(argList,output);
    vprintf(output,argList);
    va_end(argList);
    SetConsoleTextAttribute(screen,ConsoleInfo.wAttributes);
}

void printResult(const char* fname,bool bRes)
{
    printf("%-#40s: ",fname);
    bRes? printc(2,"Passed\n") :  printc(4,"Failed\n");
}
#else
void printResult(const char* fname,bool bRes)
{
    printf("%-40s: %s\n",fname,bRes? "\033[032m Passed \033[0m":"\033[031m Failed \033[0m");
}
#endif
