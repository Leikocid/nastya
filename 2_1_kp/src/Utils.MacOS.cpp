/**
 * @brief
 *
 *  реализация вспомогательных методов, которые имеют специфику реализации для MacOs
 *
 */
#include "Utils.h"
#include <wchar.h>
#include <iostream>

namespace Utils {
    // Converts from wide chars to chars
    char* toChars(const wchar_t* wideString) {
        int   len = wcslen(wideString) + 1;
        char* str = new char[len];
        wcstombs(str, wideString, len);
        return str;
    }

    // Converts from chars to wide chars
    wchar_t* toWideChars(const char* string) {
        const size_t size   = strlen(string) + 1;
        wchar_t*     result = new wchar_t[size];
        mbstowcs(result, string, size);
        return result;
    }

    // Copy wide chars
    void     copyWideChars(wchar_t* destination, const wchar_t* source) {
        wcscpy(destination, source);
    }

    // Copy chars
    void     copyChars(char* destination, const char* source) {
        strcpy(destination, source);
    }

    // Append wide chars from source to destination
    void appendWideChars(wchar_t* destination, const wchar_t* source) {
        wcsncat(destination, source, wcslen(source));
    }

    // Append chars from source to destination
    void     appendChars(char* destination, const char* source) {
        strcat(destination, source);
    }

    // Get sub string
    char* subString(const char* source, const int begin, const int length) {
        char* result = new char[length + 1];
        memcpy(result, &source[begin], length);
        result[length] = '\0';
        return result;
    }

    // Return current local time
    void getCurrentTime(tm &tm) {
        time_t t = time(NULL);
        tm = *localtime(&t);
    }
}
