// 2_1_ksis_09.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include <Winsock2.h>
#include <Iphlpapi.h>


#pragma comment(lib, "WS2_32.lib")
#pragma comment(lib, "IPHlpApi.Lib")



using namespace std;


bool checkAddress(char* ip_) {
    int points = 0,                              // количество точек
        numbers = 0;                              // значение октета
    char* buff;                                   // буфер для одного октета
    buff = new char[4];
    for (int i = 0; ip_[i] != '\0'; i++) {        // для строки IP-адреса
        if ((ip_[i] <= '9') && (ip_[i] >= '0')) { // если цифра
            if (numbers > 3) {
                return false;
            }

            // если больше трех чисел в октете – ошибка
            buff[numbers] = ip_[i];
            buff[numbers + 1] = 0;
            numbers++;
        } else if (ip_[i] == '.') { // если точка
            if (numbers == 0) {
                // если числа нет - ошибка
                return false;
            }
            if (atoi(buff) > 255) {
                // проверить диапазон октета
                return false;
            }
            numbers = 0;
            points++;
            delete[] buff;
            buff = new char[4];
        } else {
            return false;
        }
    }
    if (points != 3) {
        // если количество точек в IP-адресе не 3 - ошибка
        return false;
    }
    if ((numbers == 0) || (numbers > 3)) {
        return false;
    }
    return true;
}


int main()
{
    // Инициализация  Winsock
    WSADATA WsaData;

    if (WSAStartup(0x0202, &WsaData) != NULL) {
        cout << "WSA: Ошибка !\n";
    } else {

        char *ip_, *ip_end_;
        DWORD ip, ip_end;
        bool flag = true;
        ip_ = new char[16];
        SOCKET udp_s;
        SOCKADDR_IN udp_sin;
        do {
            if (!flag) cout << "Неверный IP" << endl;
            cout << "Введите  IP: ";
            cin >> ip_;
            if (strcmp("exit", ip_) == 0) {
                return 0;
            }
        } while (!(flag = checkAddress(ip_)));
        udp_s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
        if (udp_s != SOCKET_ERROR) {
            //Сокет успешно открыт

            ip = inet_addr(ip_);
            udp_sin.sin_family = AF_INET; //семейство
            udp_sin.sin_port = htons(5234); //порт
            udp_sin.sin_addr.S_un.S_addr = ip; //IP адресс

        } else {
            cout << "Ошибка открытия socket\n";
        }
    }


    int result;
    cin >> result;
    return 0;
}

