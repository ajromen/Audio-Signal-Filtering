#pragma once
#include "Filter.h"

class LowPassFilter : public Filter {
public:
    LowPassFilter(double alpha,int mod_deg, SineLookup& sine_lookup);

    std::vector<double> process(const std::vector<double> &input) override;

};
