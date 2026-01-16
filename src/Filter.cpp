#include <Filter.h>

double Filter::compute_modulation(int n) const {
    n = (SineLookup::normalise_angle(n) * mod_deg) % 360;
    return this->mod_offset + this->sine_lookup.get_sin(n) * this->mod_amplitude;
}
