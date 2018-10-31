#ifndef LOG_H
#define LOG_H

#include <fstream>
#include <iostream>
#include "In.h"
#include "Parm.h"
#include "Error.h"
#include "LT.h"
#include "IT.h"

using namespace std;
using namespace Parm;
using namespace Error;
using namespace In;

// Работа с протоколом
namespace Log {
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

    // протокол
    class LOG : public ostream {
        private:
            ComposedBuffer buf;
            ofstream* stream;

        public:
            LOG(ofstream* stream, bool logToConsole) : ostream(&buf), buf(stream->rdbuf(), logToConsole ? cout.rdbuf() : nullptr), stream(
                    stream) {}

            void logLine(const char* с, ...);                                // вывести в протокол конкатенацию строк
            void logLine(const wchar_t* с, ...);                             // вывести в протокол конкатенацию строк
            void logLog();                                                   // вывести в протокол заголовок
            void logParm(PARM parm);                                         // вывести в пртокол информацию о входных параметрах
            void logIn(IN in);                                               // вывести в протокол информацию o входном потоке
            void logError(ERROR error);                                      // вывести в протокол инфомацию об ошибке
            void logLexemTables(LT::LexTable lextable, IT::IdTable idtable); // вывести в протокол таблице лексем и идентификаторов
            void closeLog();                                                 // закрыть протокол
    };

    LOG*	 getLog(Parm::PARM params);                                  // сформировать структуру LOG
}

#endif // !LOG_H
