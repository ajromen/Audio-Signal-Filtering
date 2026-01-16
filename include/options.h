#pragma once
#include <string>


/**
 * Razlicite podrzane vrste filtera
 */
enum class FilterType {
    LowPass,
    HighPass,
    BandPass
};


/**
 * Opcije/Podesavanja programa
 */
class Options {
public:
    FilterType type = FilterType::LowPass;   // default
    double alpha = 0.15;                     // default
    int mod_deg = 5;                         // default
    std::string signal = "data/signal.txt";  // default
    std::string sine = "data/sine_table.txt";// default
    std::string out = "output.wav";          // default

    static Options parse_options(int argc, char **argv);
};