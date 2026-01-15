#pragma once

enum class FilterType {
    LowPass,
    HighPass,
    BandPass
};

struct Options {
    FilterType type = FilterType::LowPass;   // default
    double alpha = 0.15;                     // default
    int mod_deg = 5;                         // default
    std::string signal = "data/signal.txt";  // default
    std::string sine = "data/sine_table.txt";// default
    std::string out = "output.wav";          // default
};