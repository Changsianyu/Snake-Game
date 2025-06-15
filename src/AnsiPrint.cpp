#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <iostream>
#include "AnsiPrint.h"
#include "unit.h"

const char *init="\x1b[";
const char *endc="m";
const char *hilit="1;";
const char *blink="5;";
const char *recover="\x1b[0m";
const int kFormatStrSize=20;

std::string AnsiPrint(const char *str, Color fg, Color bg, bool hi, bool blinking) {
    if ((str==NULL)||(strlen(str)==0))
        return "";

    char foreground_code[5] = "";
    char background_code[5] = "";

    if (fg != NOCHANGE) {
        sprintf(foreground_code, "3%d;", (int)fg);
    }
    if (bg != NOCHANGE) {
        sprintf(background_code, "4%d;", (int)bg);
    }

    char formatStr[kFormatStrSize*2]="";
    strcat(formatStr, init);
    if (hi) {
        strcat(formatStr, hilit);
    }
    if (blinking) {
        strcat(formatStr, blink);
    }
    if (fg != NOCHANGE) {
        strcat(formatStr, foreground_code);
    }
    if (bg != NOCHANGE) {
        strcat(formatStr, background_code);
    }
    if (strlen(formatStr) > strlen(init) && formatStr[strlen(formatStr)-1]==';')
        formatStr[strlen(formatStr)-1]= '\0';
    strcat(formatStr,endc);

    std::string res;
#ifdef _WIN
    res.append(str);
#else
    res.append(formatStr);
    res.append(str);
    res.append(recover);
#endif

    return res;
}

std::string AnsiPrint(const char *str, bool hi, bool blinking) {
    return AnsiPrint(str, NOCHANGE, NOCHANGE, hi, blinking);
}
