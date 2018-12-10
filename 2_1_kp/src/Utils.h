#ifndef UTILS_H
#define UTILS_H

#include <ctime>

namespace Utils {
    // Converts from wide chars to chars
    char*    toChars(const wchar_t* wideString);

    // Converts from chars to wide chars
    wchar_t* toWideChars(const char* string);

    // Copy wide chars
    void     copyWideChars(wchar_t* destination, const wchar_t* source);

    // Copy chars
    void     copyChars(char* destination, const char* source);

    // Append wide chars from source to destination
    void     appendWideChars(wchar_t* destination, const wchar_t* source);

    // Append chars from source to destination
    void     appendChars(char* destination, const char* source);

    // Get sub string
    char*    subString(const char* source, const int begin, const int length);

    // Return current local time
    void     getCurrentTime(tm &tm);
}

#endif // UTILS_H
