#pragma once
#include <string>
#include "FilterType.h"

/**
 * Opcije/Podesavanja programa
 */
class Options {
public:
    FilterType type = FilterType::LowPass;
    double alpha = 0.15;
    int mod_deg = 5;
    std::string signal = "data/signal.txt";
    std::string sine = "data/sine_table.txt";
    std::string out = "output.wav";

    static Options parse_options(int argc, char **argv);
};