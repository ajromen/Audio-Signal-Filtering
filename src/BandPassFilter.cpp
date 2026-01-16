#include <BandPassFilter.h>

BandPassFilter::BandPassFilter(double alpha, int mod_deg, SineLookup& sine_lookup)
    : Filter(alpha,mod_deg,sine_lookup), high_pass_filter_(alpha, mod_deg, sine_lookup), low_pass_filter_(alpha, mod_deg, sine_lookup)
{
}

/**
 * Kombinacija LowPassFilter-a i HighPassFiltera
 *
 * @param input vektor<double> vrednosti ulaznog signala za konvertovanje
 * @return vector<double> procesovanih sample-ova
 */
std::vector<double> BandPassFilter::process(const std::vector<double>& input) {
    std::vector<double> temp = high_pass_filter_.process(input);
    std::vector<double> output = low_pass_filter_.process(temp);
    return output;
}