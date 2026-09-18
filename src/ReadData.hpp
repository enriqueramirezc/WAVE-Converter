#ifndef READDATA_HPP
#define READDATA_HPP

#include "FileHeader.hpp"
#include <fstream>
#include <vector>

class ReadData {

 public:

    // this assumes bits per sample always = 16
    std::vector<int16_t> samples;

    // interleaved samples, one per channel per frame
    int fetchData(FileHeader& h, std::ifstream& ifs);

    // de-interleave `samples` into one vector per channel
    std::vector<std::vector<int16_t>> splitChannels(const FileHeader& h);
};
#endif
