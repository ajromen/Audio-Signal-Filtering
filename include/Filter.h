#pragma once
#include <vector>

class Filter {
protected:
    double alpha;
    int mod_deg;

public:
    Filter(const double a, const int m) : alpha(a), mod_deg(m) {}
    virtual ~Filter() = default;

    virtual std::vector<double> process(const std::vector<double>& input) = 0;
    virtual void reset() = 0;
};