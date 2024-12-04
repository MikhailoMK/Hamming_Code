# **Hamming_Code**

В программе реализованы функции для кодирования и декодирования данных с использованием кода Хэмминга. Вектор из 4-битовых значений кодируется в 8-битовые значения с добавлением контрольных битов, что позволяет обнаружить и исправить ошибки. При декодировании из 8-битовых значений восстанавливаются исходные 4-битовые значения, проверяя наличие и исправляя возможные ошибки в кодированных данных.

---
# **Инструкция по запуску:**

    git clone https://github.com/MikhailoMK/Hamming_Code.git
    mkdir build 
    cd build
    cmake .. -G "MinGW Makefiles"
    cmake --build .
    ./hamming_code.exe

---
# **Описание программы:**

1. После запуска программа принимает целое число N в диапазоне от 1 до 2<sup>64</sup> − 1.

2. Затем отображается список доступных операций:
```
1. Make a vector;
2. Encoding;
3. Decoding;
4. Invert a bit in an encoded vector;
5. Enter a new value;
6. Exit.
```

3. Описание операций:

    - **Make a vector**: Программа берёт введенное целое число и переводит его в двоичное представление. Если длина этого представления не кратна 4, она дополняется ведущими нулями. Затем из полученной строки формируется вектор, состоящий из 4-битовых блоков, который и возвращается.

    - **Encoding**: Эта операция берёт результат выполнения операции "Make a vector" и выполняет кодирование каждого 4-битного блока в 8-битное значение с добавлением контрольных битов (используя код Хэмминга). Если до этого не был выполнен этап составления вектора, программа запросит сначала выполнить операцию "Make a vector".

    - **Decoding**: Программа выполняет операцию, обратную кодированию, восстанавливая 4-битные блоки из кодированных 8-битных значений. Если операция кодирования еще не была выполнена, программа попросит сначала выполнить операцию "Encoding".

    - **Invert a bit in an encoded vector**: Когда кодированный вектор содержит больше одного элемента, программа попросит указать номер элемента (от 1 до размера вектора) и номер бита (от 1 до 8), который необходимо инвертировать. После этого выбранный бит будет изменен.

    - **Enter a new value**: Пользователь может ввести новое число, которое будет использоваться для создания нового вектора, заменяя предыдущее значение.

    - **Exit**: Программа будет продолжать работу, пока не будет выбрана операция "Exit".
