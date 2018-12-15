#ifndef OUT_H
#define OUT_H

#include <fstream>
#include <iostream>
#include "Parm.h"
#include "Error.h"

using namespace std;
using namespace Parm;
using namespace Error;

namespace Out {
    class ComposedBuffer : public streambuf {
        private:
            streambuf* sb1;
            streambuf* sb2;

        public:
            ComposedBuffer(streambuf* sb1, streambuf* sb2) : sb1(sb1), sb2(sb2) {}

        private:
            virtual int overflow(int c) {
                if (c == EOF) {
                    return !EOF;
                } else {
                    int const r1 = sb1->sputc(c);
                    if (sb2) {
                        int const r2 = sb2->sputc(c);
                        return r1 == EOF || r2 == EOF ? EOF : c;
                    }
                    return r1 == EOF ? EOF : c;
                }
            }

            virtual int sync() {
                int const r1 = sb1->pubsync();
                if (sb2) {
                    int const r2 = sb2->pubsync();
                    return r1 == 0 && r2 == 0 ? 0 : -1;
                }
                return r1 == 0 ? 0 : -1;
            }
    };

    // запись файла результата
    class OUT : public ostream {
        private:
            ComposedBuffer buf;
            ofstream* stream;

        public:
            OUT(ofstream* stream, bool logToConsole) : ostream(&buf), buf(stream->rdbuf(), logToConsole ? cout.rdbuf() : nullptr),
                stream(stream) {}

            void close();                      // закрыть файл
    };

    OUT*	 createOut(Parm::PARM params); // сформировать структуру OUT
}

#endif // !OUT_H
