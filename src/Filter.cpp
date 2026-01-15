#include <Filter.h>

double Filter::compute_modulation(int n, SineLookup &sine) {
    n = sine.normalise_angle(n);
    return this->mod_offset+ this->mod_amplitude * sine.get_sin(n);
}
