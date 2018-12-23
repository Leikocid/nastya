#include <iostream>

using namespace std;

bool checkAddress(char* ip_) {
    int points	= 0, // количество точек
        numbers = 0; // значение октета
    char* buff;      // буфер для одного октета
    buff    = new char[4];
    buff[0] = 0;
    buff[1] = 0;
    buff[2] = 0;
    buff[3] = 0;

    for (int i = 0; ip_[i] != '\0'; i++) {        // для строки IP-адреса
        if ((ip_[i] <= '9') && (ip_[i] >= '0')) { // если цифра
            if (numbers > 3) {
                return false;
            }

            // если больше трех чисел в октете – ошибка
            numbers++;
            buff[numbers]     = ip_[i];
            buff[numbers + 1] = 0;
        } else if (ip_[i] == '.') { // если точка
            if (atoi(buff) > 255) {
                // проверить диапазон октета
                return false;
            }
            if (numbers == 0) {
                // если числа нет - ошибка
                return false;
            }
            numbers = 0;
            points++;
            delete[] buff;
            buff    = new char[4];
            buff[0] = 0;
            buff[1] = 0;
            buff[2] = 0;
            buff[3] = 0;
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

bool checkMask(unsigned long addr) {
    int mode	       = -1; // -1 - start, 1 - ones, 0 - zeros
    unsigned long mask = 1 << 30;
    mask <<= 1;
    for (int i = 0; i < 32; i++) {
        if (addr & mask) {
            // 1
            if (mode == -1) {
                mode = 1;
            } else if (mode == 0) {
                return false; // встретили 1-у в конце маски
            }
        } else {
            // 0
            if (mode == -1) {
                return false; // должно начинаться с 1
            } else if (mode == 1) {
                mode = 0;
            }
        }
    }
    return true;
}

void print(const char* name, unsigned long addr) {
    cout << name;

    int* a  = new int[4];
    int	 av = 0;
    int	 ai = 0;

    unsigned long mask = 1 << 30;
    mask <<= 1;
    for (int i = 0; i < 32; i++) {
        if (addr & mask) {
            cout << '1';
            av++;
        } else {
            cout << '0';
        }
        mask >>= 1;
        if (i % 8 == 7) {
            cout << ' ';
            a[ai] = av;
            av	  = 0;
            ai++;
        }
        av <<= 1;
    }

    cout << "\t" << a[0] << '.' << a[1] << '.' << a[2] << '.' << a[3] << endl;
}

unsigned long charToLong(char* ip_) {
    unsigned long out = 0; // число для IP-адреса
    char* buff;
    buff    = new char[4];
    buff[0] = 0;
    buff[1] = 0;
    buff[2] = 0;
    buff[3] = 0;

    // буфер для хранения одного октета
    for (int i = 0, j = 0, k = 0; ip_[i] != '\0'; i++, j++) {
        if (ip_[i] != '.') {  // если не точка
            buff[j] = ip_[i]; // записать символ в буфер
        }
        if ((ip_[i] == '.') || (ip_[i + 1] == '\0')) {
            // если следующий октет или последний
            out <<= 8; // сдвинуть число на 8 бит
            if (atoi(buff) > 255) {
                return 0;
            }

            // еcли октет больше 255 – ошибка
            out += (unsigned long)atoi(buff);

            // преобразовать и добавить
            // к числу IP-адреса
            k++;
            j = -1;

            delete[] buff;
            buff    = new char[3];
            buff[0] = 0;
            buff[1] = 0;
            buff[2] = 0;
            buff[3] = 0;
        }
    }
    return out;
}

int main(int argc, char* argv[]) {
    setlocale(LC_ALL, "rus");

    unsigned long ip, mask;
    char* temp = new char[17];
    bool  flag = true;
    do {
        if (!flag) {
            cout << "Неверно введён адрес!" << endl;
        }
        cout << "IP: ";
        cin >> temp;
        if (strcmp("exit", temp) == 0) {
            return 0;
        }
    } while (!(flag = checkAddress(temp)));

    ip	 = charToLong(temp);
    flag = true;
    do {
        if (!flag) {
            cout << "Неправильная маска!" << endl;
        }
        flag = true;
        do {
            if (!flag) {
                cout << "Неверно введена маска!" << endl;
            }
            cout << "Маска: ";
            cin >> temp;
            if (strcmp("exit", temp) == 0) {
                return 0;
            }
        } while (!(flag = checkAddress(temp)));

        mask = charToLong(temp);
    } while (!(flag = checkMask(mask)));

    cout << endl;
    print("               IP:\t", ip);
    print("            Маска:\t", mask);
    print("       ID подсети:\t", (ip & mask));
    print("         ID хоста:\t", (ip & ~mask));
    print("Broadcast address:\t", ((ip & mask) | ~mask));
    return 0;
}
