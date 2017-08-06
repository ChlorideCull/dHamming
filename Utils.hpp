//
// Created by chloridecull on 2017-08-05.
//

#ifndef DHAMMING_UTILS_H
#define DHAMMING_UTILS_H

#include <cstdint>
#include <vector>

class Utils {
private:
    static std::uint8_t hexchar_to_halfbyte(const char byte);
    static char halfbyte_to_hexchar(const uint8_t byte);
public:
    static std::vector<uint8_t> DecodeHex(const std::string &hex);
    static std::string EncodeHex(const std::vector<uint8_t> &data);
};


#endif //DHAMMING_UTILS_H
