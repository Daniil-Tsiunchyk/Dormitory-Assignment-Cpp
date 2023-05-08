#include <cstdint>
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <vector>

#ifndef HASHSHA_256_H
#define HASHSHA_256_H

#include <cstdint>
#include <string>

uint32_t rightRotate(uint32_t value, size_t bits);
std::string makeHash(const std::string& input);

#endif 
