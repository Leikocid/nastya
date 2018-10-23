#include "Util.h"
#include <wchar.h>
#include <iostream>

namespace Utils {
    // Convert from wide chars to chars
    char* toChars(const wchar_t* wideString) {
        int   len = wcslen(wideString) + 1;
        char* str = new char[len];
        wcstombs(str, wideString, len);
        return str;
    }
}
