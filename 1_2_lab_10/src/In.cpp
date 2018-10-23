#include "Error.h"
#include "In.h"
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

namespace In {
    // ввести и проверить входной поток
    IN getin(wchar_t infile[]) {
        IN  input     = *(new IN);
        int code[256] = IN_CODE_TABLE_ASTAKHOVA;
        memcpy(input.code, code, 256 * sizeof(int));
        input.text = new unsigned char[IN_MAX_LEN_TEXT];

        wstring	 wideFileName(infile);
        string	 fileName(wideFileName.begin(), wideFileName.end());
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
