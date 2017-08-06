//
// Created by chloridecull on 2017-08-05.
//

#include <stdexcept>
#include <array>
#include <algorithm>
#include "Utils.hpp"

std::uint8_t Utils::hexchar_to_halfbyte(const char byte) {
    switch (byte) {
        case '0':
            return 0b00000000;
        case '1':
            return 0b00000001;
        case '2':
            return 0b00000010;
        case '3':
            return 0b00000011;
        case '4':
            return 0b00000100;
        case '5':
            return 0b00000101;
        case '6':
            return 0b00000110;
        case '7':
            return 0b00000111;
        case '8':
            return 0b00001000;
        case '9':
            return 0b00001001;
        case 'a':
        case 'A':
            return 0b00001010;
        case 'b':
        case 'B':
            return 0b00001011;
        case 'c':
        case 'C':
            return 0b00001100;
        case 'd':
        case 'D':
            return 0b00001101;
        case 'e':
        case 'E':
            return 0b00001110;
        case 'f':
        case 'F':
            return 0b00001111;
        default:
            throw std::invalid_argument("Character isn't a hex characters.");
    }
}

char Utils::halfbyte_to_hexchar(const uint8_t byte) {
    const uint8_t maskedbyte = byte & 0b00001111;
    switch (maskedbyte) {
        case 0b00000000:
            return '0';
        case 0b00000001:
            return '1';
        case 0b00000010:
            return '2';
        case 0b00000011:
            return '3';
        case 0b00000100:
            return '4';
        case 0b00000101:
            return '5';
        case 0b00000110:
            return '6';
        case 0b00000111:
            return '7';
        case 0b00001000:
            return '8';
        case 0b00001001:
            return '9';
        case 0b00001010:
            return 'a';
        case 0b00001011:
            return 'b';
        case 0b00001100:
            return 'c';
        case 0b00001101:
            return 'd';
        case 0b00001110:
            return 'e';
        case 0b00001111:
            return 'f';
        default:
            throw std::invalid_argument("Byte not a half byte");
    }
}

std::vector<uint8_t> Utils::DecodeHex(const std::string &hex) {
    std::vector<uint8_t> output;
    std::array<char, 2> tmpHolder;
    bool isFirst = true;
    std::for_each(hex.cbegin(), hex.cend(), [&](const char character){
        if (isFirst) {
            tmpHolder[0] = character;
            isFirst = false;
        } else {
            tmpHolder[1] = character;
            output.insert(output.cend(), (hexchar_to_halfbyte(tmpHolder[0]) << 4) | hexchar_to_halfbyte(tmpHolder[1]));
            tmpHolder[0] = 0x00;
            tmpHolder[1] = 0x00;
            isFirst = true;
        }
    });
    return output;
}

std::string Utils::EncodeHex(const std::vector<uint8_t> &data) {
    std::string output;
    std::for_each(data.cbegin(), data.cend(), [&](const uint8_t byte) {
        output.insert(output.cend(), halfbyte_to_hexchar(byte >> 4));
        output.insert(output.cend(), halfbyte_to_hexchar(byte));
    });
    return output;
}