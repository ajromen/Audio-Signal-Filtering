#include <HighPassFilter.h>

HighPassFilter::HighPassFilter(double alpha, int mod_deg, SineLookup &sine_lookup)
    : Filter(alpha, mod_deg, sine_lookup) {
}

/**
 * Primena IIR high-pass filtera prvog reda
 *
 * @param input vektor<double> vrednosti ulaznog signala za konvertovanje
 * @return vector<double> procesovanih sample-ova
 */
std::vector<double> HighPassFilter::process(const std::vector<double> &input) {
    std::vector<double> output(input.size());

    if (input.empty()) {
        return output;
    }

    output[0] = 0.0;

    for (size_t i = 1; i < input.size(); i++) {
        double m = this->compute_modulation(i);
        output[i] = alpha * (output[i - 1] + m * input[i] - m * input[i - 1]);
    }
    return output;
}
