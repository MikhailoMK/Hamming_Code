#include <iostream>
#include <vector>
#include <cmath>
#include <windows.h>

using namespace std;

// Функция для вычисления контрольных битов для кода Хемминга
vector<int> encodeHamming(const vector<int>& data) {
    int m = data.size();
    int r = 0;

    // Определяем минимальное количество контрольных битов
    while ((1 << r) < (m + r + 1)) {
        r++;
    }

    vector<int> encoded(m + r);

    int dataIndex = 0;
    for (int i = 0; i < m + r; ++i) {
        // Пропускаем позиции, которые соответствуют контрольным битам
        if ((i + 1) & (i) == 0) {
            encoded[i] = 0;
        } else {
            encoded[i] = data[dataIndex++];
        }
    }

    // Рассчитываем значения контрольных битов
    for (int i = 0; i < r; ++i) {
        int parity = 0;
        for (int j = 0; j < m + r; ++j) {
            // Проверяем, попадает ли позиция в диапазон, управляемый данным битом
            if (((j + 1) & (1 << i)) != 0) {
                parity ^= encoded[j];
            }
        }
        // Устанавливаем значение контрольного бита
        encoded[(1 << i) - 1] = parity;
    }

    return encoded;
}

// Функция для декодирования кода Хемминга и исправления ошибок
vector<int> decodeHamming(vector<int>& encoded) {
    int n = encoded.size();
    int r = 0;

    // Определяем количество контрольных битов
    while ((1 << r) <= n) {
        r++;
    }

    // Проверяем на наличие ошибок с помощью контрольных битов
    int errorPos = 0;
    for (int i = 0; i < r; ++i) {
        int parity = 0;
        for (int j = 0; j < n; ++j) {
            if (((j + 1) & (1 << i)) != 0) {
                parity ^= encoded[j];
            }
        }
        if (parity != 0) {
            errorPos += (1 << i);
        }
    }

    vector<int> decoded;
    // Если ошибка обнаружена, то исправляем её
    if (errorPos != 0) {
        cout << "Ошибка обнаружена в позиции: " << errorPos << endl;
        encoded[errorPos - 1] ^= 1;
    }

    // Извлекаем данные из кода Хемминга, игнорируя контрольные биты
    int dataIndex = 0;
    for (int i = 0; i < n; ++i) {
        if ((i + 1) & (i) != 0) {
            decoded.push_back(encoded[i]);
        }
    }

    return decoded;
}

int main() {
    SetConsoleOutputCP(65001);

    //vector<int> data = {1, 1, 1, 1, 0, 0, 0, 0};
    vector<int> data = {1, 1, 1, 1};

    cout << "Исходные данные: ";
    for (int bit : data) {
        cout << bit;
    }
    cout << endl;

    vector<int> encoded = encodeHamming(data);

    cout << "Закодированные данные: ";
    for (int bit : encoded) {
        cout << bit;
    }
    cout << endl;

    encoded[2] = encoded[2] == 0 ? 1 : 0;

    vector<int> decoded = decodeHamming(encoded);

    cout << "Декодированные данные: ";
    for (int bit : decoded) {
        cout << bit;
    }
    cout << endl;

    return 0;
}
