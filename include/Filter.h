#pragma once
#include <vector>

#include "SineLookup.h"


/**
 * Abstraktna klasa. Sadrzi sve zajednicke argumete za filtere
 */
class Filter {
protected:
    double alpha;
    int mod_deg;
    const double mod_offset=1.0;
    const double mod_amplitude=0.1;
    SineLookup& sine_lookup;

public:
    double compute_modulation(int n) const;

    Filter(const double alpha, const int mod_deg, SineLookup& sine_lookup) : alpha(alpha), mod_deg(mod_deg), sine_lookup(sine_lookup) {}
    virtual ~Filter() = default;

    virtual std::vector<double> process(const std::vector<double>& input) = 0;
};
