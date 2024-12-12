#include "header/hamming.h"

using namespace std;

vector<uint8_t> GenerateBinaryBlocks(unsigned long long inputValue) {
    string binary = bitset<64>(inputValue).to_string();
    binary.erase(0, binary.find_first_not_of('0'));

    cout << "Original value " << inputValue << " as binary: " << binary << endl;

    vector<uint8_t> blocks;
    while (binary.size() % 4 != 0) {
        binary = "0" + binary;
    }

    int blockIndex = 0;
    cout << "Value divided into " << binary.size() / 4 << " blocks of 4 bits:" << endl;

    for (size_t i = 0; i < binary.size(); i += 4) {
        string chunk = binary.substr(i, 4);
        uint8_t blockValue = static_cast<uint8_t>(stoi(chunk, nullptr, 2));
        cout << ++blockIndex << ". " << bitset<4>(blockValue) << endl;
        blocks.push_back(blockValue);
    }

    return blocks;
}

void PrintMenu() {
    cout << "\nCommands available:" << endl;
    cout << " 1. Encode the data" << endl;
    cout << " 2. Decode the data" << endl;
    cout << " 3. Flip a bit in encoded data" << endl;
    cout << " 4. Input a new number" << endl;
    cout << " 5. Exit the program" << endl;
}

void ExecuteCommand(int command, vector<uint8_t>& byteArray, vector<uint8_t>& encodedData, vector<uint8_t>& decodedData, bool& isEncoded, unsigned long long& inputNumber) {
    int byteCounter = 0;
    switch (command) {
        case 1:
            if (!byteArray.empty()) {
                encodedData = ParityCorrection::GenerateParityCode(byteArray);
                cout << "Encoded data for " << inputNumber << ":" << endl;
                for (uint8_t encodedByte : encodedData) {
                    cout << ++byteCounter << ". " << bitset<8>(encodedByte) << endl;
                }
                isEncoded = true;
            } else {
                cout << "First, generate the byte array!" << endl;
            }
            break;

        case 2:
            if (isEncoded) {
                decodedData = ParityCorrection::RecoverData(encodedData);
                if (!decodedData.empty()) {
                    cout << "Decoded data: ";
                    for (uint8_t decodedByte : decodedData) {
                        cout << bitset<4>(decodedByte);
                    }
                    cout << endl;
                } else {
                    cout << "The data could not be corrected!" << endl;
                }
            } else {
                cout << "Please encode the data first." << endl;
            }
            break;

        case 3:
            if (isEncoded) {
                int blockIndex, bitPosition;
                cout << "Enter the block index (1 to " << encodedData.size() << "): ";
                cin >> blockIndex;
                cout << "Enter the bit position (1 to 8): ";
                cin >> bitPosition;

                if (bitPosition >= 1 && bitPosition <= 8) {
                    encodedData[blockIndex - 1] ^= (1 << (bitPosition - 1));

                    cout << "After flipping the bit, the encoded data is:" << endl;
                    byteCounter = 0;
                    for (uint8_t encodedByte : encodedData) {
                        cout << ++byteCounter << ". " << bitset<8>(encodedByte) << endl;
                    }
                } else {
                    cout << "Error: The bit position should be between 1 and 8." << endl;
                }
            } else {
                cout << "No encoded data to flip a bit. Encode first." << endl;
            }
            break;

        case 4:
            cout << "Enter a new number: ";
            cin >> inputNumber;
            byteArray = GenerateBinaryBlocks(inputNumber);
            encodedData.clear();
            decodedData.clear();
            isEncoded = false;
            break;

        case 5:
            cout << "Exiting the program..." << endl;
            exit(0);

        default:
            cout << "Invalid command. Please try again." << endl;
    }
}

int main() {
    setlocale(LC_ALL, "");

    unsigned long long inputNumber;
    vector<uint8_t> byteArray, encodedData, decodedData;
    bool isEncoded = false;

    cout << "Enter a positive number: ";
    cin >> inputNumber;
    byteArray = GenerateBinaryBlocks(inputNumber);

    PrintMenu();

    while (true) {
        int command;
        cout << "Select a command: ";
        cin >> command;

        ExecuteCommand(command, byteArray, encodedData, decodedData, isEncoded, inputNumber);

        PrintMenu();
    }

    return 0;
}
