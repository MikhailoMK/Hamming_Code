#include "hamming.h"
#include <iostream>
#include <cstdint>
#include <bitset>
#include <vector>

using namespace std;

namespace hamming
{
    uint8_t EncodeHelper(uint8_t byte) {
        bool d1 = (byte >> 3) & 1;
        bool d2 = (byte >> 2) & 1;
        bool d3 = (byte >> 1) & 1;
        bool d4 = (byte >> 0) & 1;

        bool p1 = 1 ^ d1 ^ d3 ^ d4;
        bool p2 = 1 ^ d1 ^ d2 ^ d4;
        bool p3 = 1 ^ d1 ^ d2 ^ d3;
        bool p4 = 1 ^ p1 ^ p2 ^ p3 ^ d1 ^ d2 ^ d3 ^ d4;

        uint8_t result = 0;
        result |= (p1 << 7);
        result |= (d1 << 6);
        result |= (p2 << 5);
        result |= (d2 << 4);
        result |= (p3 << 3);
        result |= (d3 << 2);
        result |= (p4 << 1);
        result |= (d4 << 0);

        return result;
    }

    vector<uint8_t> Encode(const vector<uint8_t> bytes) {
        vector<uint8_t> resBytes;
        cout << "Encoding..." << endl;
        for (uint8_t byte : bytes) {
            uint8_t resByte = EncodeHelper(byte);
            cout << bitset<4>(byte) << " -> " << bitset<8>(resByte) << endl;
            resBytes.push_back(resByte);
        }

        return resBytes;
    }

    uint8_t DecodeHelper(uint8_t x, int byteNum) {
        bool p1 = (x & 0b10000000) != 0;
        bool p2 = (x & 0b00100000) != 0;
        bool p3 = (x & 0b00001000) != 0;
        bool p4 = (x & 0b00000010) != 0;
        bool d1 = (x & 0b01000000) != 0;
        bool d2 = (x & 0b00010000) != 0;
        bool d3 = (x & 0b00000100) != 0;
        bool d4 = (x & 0b00000001) != 0;

        bool A = p1 ^ d1 ^ d3 ^ d4 == 1;
        bool B = p2 ^ d1 ^ d2 ^ d4 == 1;
        bool C = p3 ^ d1 ^ d2 ^ d3 == 1;
        bool D = p1 ^ p2 ^ p3 ^ p4 ^ d1 ^ d2 ^ d3 ^ d4 == 1;

        if ((!A || !B || !C) && D)
            return 0b10000000;

        int temp = !A + !B * 2 + !C * 4 + !D * 8;

        if (temp > 0)
            cout << "In the " << byteNum << " -th byte, an error was corrected in the  ";

        switch (temp) {
        case 15:
            d1 ^= 1;
            cout << "7-th bit." << endl;
            break;
        case 14:
            d2 ^= 1;
            cout << "5-th bit." << endl;
            break;
        case 13:
            d3 ^= 1;
            cout << "3-th bit." << endl;
            break;
        case 11:
            d4 ^= 1;
            cout << "1-th bit." << endl;
            break;
        }

        return (d1 << 3) | (d2 << 2) | (d3 << 1) | d4;
    }

    vector<uint8_t> Decode(const vector<uint8_t> bytes) {
        int index = 1;
        vector<uint8_t> resBytes;
        cout << "Decoding..." << endl;
        for (uint8_t byte : bytes) {
            uint8_t res = DecodeHelper(byte, index);
            if (res == 0b10000000) {
                cout << index << ". " << bitset<8>(byte) << " -> Double error." << endl;
                return vector<uint8_t>();
            }
            else
                cout << index << ". " << bitset<8>(byte) << " -> " << bitset<4>(res) << endl;
            index++;
            resBytes.push_back(res);
        }
        return resBytes;
    }
}