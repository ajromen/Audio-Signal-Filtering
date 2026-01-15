#pragma once
#include <vector>

#include "SineLookup.h"

class Filter {
protected:
    double alpha;
    int mod_deg;
    const double mod_offset=1.0;
    const double mod_amplitude=0.1;

    double compute_modulation(int n, SineLookup& sine);

public:
    Filter(const double a, const int m) : alpha(a), mod_deg(m) {}
    virtual ~Filter() = default;

    virtual std::vector<double> process(const std::vector<double>& input) = 0;
    virtual void reset() = 0;
};
