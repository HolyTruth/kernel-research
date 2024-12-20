#pragma once

#include <cstdint>
#include <fstream>
#include <vector>
#include "util/error.cpp"

static std::vector<uint8_t> read_file(const char* filename) {
    std::ifstream file(filename, std::ios::binary);
    if (file.fail())
        throw ExpKitError("file not found: %s", filename);
    std::vector<uint8_t> data((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    return data;
}
