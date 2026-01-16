#pragma once

#include <vector>
#include <string>

class WavWriter {
private:
    static constexpr int BITS_PER_SAMPLE = 16;
    static constexpr int NUM_CHANNELS = 1;
    static constexpr int BYTE_RATE = 44100 * NUM_CHANNELS * BITS_PER_SAMPLE / 8;
    static constexpr int BLOCK_ALIGN = NUM_CHANNELS * BITS_PER_SAMPLE / 8;

public:
    static void write(const std::string &filename, const std::vector<double> &samples, int sampleRate = 44100);
};
