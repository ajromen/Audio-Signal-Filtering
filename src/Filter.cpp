#include <Filter.h>

/**
 * Racuna faktor modulacije za dati indeks sample-a
 *
 * mod_offset   = 1.0
 * mod_amplitude = 0.1
 * modulacija u opsegu: [0.9, 1.1].
 *
 * @param n Redni broj sample-a
 * @return Faktor modulacije
 */
double Filter::compute_modulation(int n) const {
    n = (SineLookup::normalise_angle(n) * mod_deg) % 360;
    return this->mod_offset + this->sine_lookup.get_sin(n) * this->mod_amplitude;
}
