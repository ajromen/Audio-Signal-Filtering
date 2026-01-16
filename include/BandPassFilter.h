#pragma once
#include "Filter.h"
#include "LowPassFilter.h"
#include "HighPassFilter.h"

/**
 * Nasledjuje abstraktnu klasu Filter i sluzi za vrsenje BandPass filtera za zadati signal
 */
class BandPassFilter : public Filter {
public:
    BandPassFilter(double alpha, int modDeg, SineLookup& sineLookup);

    std::vector<double> process(const std::vector<double>& input) override;

private:
    HighPassFilter high_pass_filter_;
    LowPassFilter low_pass_filter_;
};
