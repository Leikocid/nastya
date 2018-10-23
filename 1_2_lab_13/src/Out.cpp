#include <fstream>
#include "string.h"
#include "Utils.h"
#include "Out.h"
#include "Error.h"

using namespace Utils;
using namespace std;

namespace Out {
    void writeResult(const wchar_t outfile[], const unsigned char* text) {
        string fileName	 = toChars(outfile);
        ofstream* stream = new ofstream();
        stream->open(fileName);
        if (!stream->is_open()) {
            throw ERROR_THROW(112);
        }
        *(stream) << text;
        stream->close();
    }
}
