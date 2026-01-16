#pragma once
#include "Filter.h"



/**
 * Nasledjuje abstraktnu klasu Filter i sluzi za vrsenje LowPass filtera za zadati signal
 */
class LowPassFilter : public Filter {
public:
    LowPassFilter(double alpha,int mod_deg, SineLookup& sine_lookup);

    std::vector<double> process(const std::vector<double> &input) override;

};
