#include "header/hamming.h"

using namespace std;

vector<uint8_t> MakeVector(unsigned long long number) {
    string input = bitset<64>(number).to_string();
    input.erase(0, input.find_first_not_of('0'));

    cout << "Number " << number << " in binary representation: " << input << endl;

    vector<uint8_t> bytes;
    while (input.size() % 4 != 0) {
        input = "0" + input;
    }

    int index = 0;

    cout << "Number " << number << " was divided into " << input.size() / 4 << " blocks of 4 bit values:" << endl;

    for (size_t i = 0; i < input.size(); i += 4) {
        string temp = input.substr(i, 4);
        uint8_t value = static_cast<uint8_t>(stoi(temp, nullptr, 2));
        cout << ++index << ". " << bitset<4>(value) << endl;
        bytes.push_back(value);
    }

    return bytes;
}

void ShowCommands() {
    cout << "Command list" << endl;
    cout << " 1. Encoding;" << endl;
    cout << " 2. Decoding;" << endl;
    cout << " 3. Invert a bit in an encoded vector;" << endl;
    cout << " 4. Enter a new value;" << endl;
    cout << " 5. Exit." << endl;
}

int main() {
    setlocale(LC_ALL, "");

    unsigned long long number;
    cout << "Enter a positive integer N: ";
    cin >> number;

    vector<uint8_t> bytes, encodedBytes, decodedBytes;
    bool vectorMaked = false, encoded = false;
    bytes = MakeVector(number);
    vectorMaked = true;

    cout << endl;
    ShowCommands();

    while (true) {
        int command, index = 0;
        cout << "Select command: ";
        cin >> command;
        cout << endl;

        if (command == 1) {
            if (vectorMaked) {
                encodedBytes = Hamming::Encode(bytes);
                cout << "N " << number << " after encoding: " << endl;
                for (uint8_t byte: encodedBytes) {
                    cout << ++index << ". " << bitset<8>(byte) << endl;
                }
                encoded = true;
                index = 0;
            } else {
                cout << "The vector of 4 bit values has not been compiled. Please compose the vector first.";
            }
            cout << endl;
            ShowCommands();
        }
        else if (command == 2) {
            if (encoded) {
                decodedBytes = Hamming::Decode(encodedBytes);
                if (decodedBytes.size() > 0) {
                    cout << "Binary decoding result: " << endl;
                    for (uint8_t byte: decodedBytes) {
                        cout << bitset<4>(byte);
                    }
                }
                else {
                    cout << "Data can't be corrected." << endl;
                }
            }
            else {
                cout << "The vector of 4 bit values has not been compiled. Please compose the vector first.";
            }
            cout << endl;
            ShowCommands();
        }
        else if (command == 3) {
            if (encoded) {
                int itemNumber, byteNumber;
                if (encodedBytes.size() > 1){
                    cout << "Enter in which element of the vector you want to invert the bit (integer N from 1 to " << encodedBytes.size() << "): ";
                    cin >> itemNumber;
                }
                else
                    itemNumber = 1;
                cout << "Enter in which bit of the element you want to invert the bit (integer N from 1 to 8): ";
                cin >> byteNumber;

                if (byteNumber >= 1 && byteNumber <= 8) {
                    int itemIndex = itemNumber - 1;
                    int bitPosition = byteNumber - 1;

                    cout << "Bit successfully inverted:" << endl;

                    encodedBytes[itemIndex] ^= (1 << bitPosition);

                    for (uint8_t byte: encodedBytes) {
                        cout << ++index << ". " << bitset<8>(byte) << endl;
                    }
                    index = 0;
                }
                else {
                    cout << "Error: the bit number must be between 1 and 8." << endl;
                }
            }
            else {
                cout << "The vector of 4 bit values has not been compiled. Please compose the vector first.";
            }
            cout << endl;
            ShowCommands();
        }
        else if (command == 4) {
            cout << "Enter a positive integer N: ";
            cin >> number;
            vectorMaked = encoded = false;
            bytes = MakeVector(number);
            vectorMaked = true;
            cout << endl;
            ShowCommands();
        }
        else if (command == 5) {
            cout << "End of program..." << endl;
            return 0;
        }
        else {
            cout << "There's no such operation." << endl;
            ShowCommands();
        }
    }
}
