#pragma once
#include "Filter.h"

/**
 * Nasledjuje abstraktnu klasu Filter i sluzi za vrsenje HighPass filtera za zadati signal
 */
class HighPassFilter : public Filter {
public:
    HighPassFilter(double alpha,int mod_deg, SineLookup& sine_lookup);

    std::vector<double> process(const std::vector<double> &input) override;

};
