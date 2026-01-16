#include <Options.h>
#include <SineLookup.h>
#include <Filter.h>
#include <BandPassFilter.h>
#include <HighPassFilter.h>
#include <WavWriter.h>
#include <LowPassFilter.h>
#include <Signal.hpp>

#include "tests.h"

#ifdef TEST_MODE
int main() {
    run_tests();
    return 0;
}
#else
int main(int argc, char **argv) {
    // uzimamo flag-ove
    Options opt = Options::parse_options(argc, argv);

    // pravimo tabelu sinusa iz ulaznog fajla
    SineLookup sine_lookup(opt.sine);

    // ucitavamo signal fajl
    Signal signal(opt.signal);

    // biramo filter
    Filter* filter;
    if (opt.type == FilterType::LowPass) {
        filter =  new LowPassFilter(opt.alpha, opt.mod_deg, sine_lookup);
    }
    else if (opt.type == FilterType::HighPass) {
        filter =  new HighPassFilter(opt.alpha, opt.mod_deg, sine_lookup);
    }
    else {
        filter =  new BandPassFilter(opt.alpha, opt.mod_deg, sine_lookup);
    }

    // procesujemo signal
    Signal processed_signal = filter->process(signal.get_data());

    // konvertujemo u wav format i upisujemo u opt.out file
    WavWriter::write(opt.out, processed_signal.get_data());
}
#endif
