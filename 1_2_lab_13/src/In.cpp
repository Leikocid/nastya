#include "Error.h"
#include "In.h"
#include <fstream>

// #include <sstream>
// #include <iostream>
#include "Utils.h"

using namespace std;
using namespace Utils;

namespace In {
    // ввести и проверить входной поток
    IN getin(wchar_t infile[]) {
        IN input = *(new IN());

        string	 fileName = toChars(infile);
        ifstream stream;
        stream.open(fileName);
        if (!stream.is_open()) {
            throw ERROR_THROW(110);
        }
        unsigned char c;
        bool readOk = true;
        int  i = 0;
        int  line = 0;       int  col    = 0;
        do {
            stream.read(((char*)&c), sizeof(unsigned char));
            readOk = !stream.fail();
            if (readOk) {
                input.size++;
                int status = input.code[c];
                if (status == IN::F) {
                    throw ERROR_THROW_IN(111, line, col);
                } else if (status == IN::T) {
                    input.text[i] = c;
                    i++;
                } else if (status <= 255) {
                    input.text[i] = (unsigned char)status;
                    i++;
                } else {
                    input.ignor++;
                }
                if (c == IN_CODE_ENDL) {
                    line++;
                    col = 0;
                } else {
                    col++;
                }
            }
        } while (readOk && i < IN_MAX_LEN_TEXT - 1);

        input.lines   = line + 1;
        input.text[i] = 0;
        stream.close();
        return input;
    }
}
