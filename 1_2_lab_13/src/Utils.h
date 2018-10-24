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

    // Append wide chars from source to destination
    void     appendWideChars(wchar_t* destination, const wchar_t* source);

    // Append chars from source to destination
    void     appendChars(char* destination, const char* source);

    // Return current local time
    tm*	     getCurrentTime();
}

#endif // !UTILS_H
