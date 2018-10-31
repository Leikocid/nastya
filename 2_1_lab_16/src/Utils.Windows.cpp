/**
 * @brief
 *
 *  реализация вспомогательных методов, которые имеют специфику реализации для Windows
 *
 */
#include "Utils.h"
#include <wchar.h>
#include <iostream>

namespace Utils {
    // Converts from wide chars to chars
    char* toChars(const wchar_t* wideString) {
        int    size   = wcslen(wideString) + 1;
        char*  result = new char[size];
        size_t outSize;
        wcstombs_s(&outSize, result, size, wideString, size);
        return result;
    }

    // Converts from chars to wide chars
    wchar_t* toWideChars(const char* string) {
        size_t	 size	= strlen(string) + 1;
        wchar_t* result = new wchar_t[size];
        size_t	 outSize;
        mbstowcs_s(&outSize, result, size, string, size);
        return result;
    }

    // Copy wide chars
    void     copyWideChars(wchar_t* destination, const wchar_t* source) {
        wcscpy_s(destination, wcslen(source) + 1, source);
    }

    // Copy chars
    void     copyChars(char* destination, const char* source) {
        strcpy_s(destination, strlen(source) + 1, source);
    }

    // Append wide chars from source to destination
    void appendWideChars(wchar_t* destination, const wchar_t* source) {
        wcsncat_s(destination, wcslen(destination) + wcslen(source) + 1, source, wcslen(source));
    }

    // Append chars from source to destination
    void     appendChars(char* destination, const char* source) {
        strcat_s(destination, strlen(destination) + strlen(source) + 1, source);
    }

    // Get sub string
    char* subString(const char* source, const int begin, const int length) {
        char* result = new char[length + 1];
        memcpy_s(result, length + 1, &source[begin], length);
        result[length] = '\0';
        return result;
    }

    // Return current local time
    void getCurrentTime(tm &tm) {
        time_t t = time(NULL);
        localtime_s(&tm, &t);
    }
}
