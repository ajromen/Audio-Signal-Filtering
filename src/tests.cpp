#include "tests.h"

#include <cassert>
#include <iostream>
#include "SineLookup.h"
#include "LowPassFilter.h"
#include "HighPassFilter.h"

static void test_sine_lookup() {
    SineLookup sl("data/sine_test.txt");

    sl.debug_print_table();
    std::cout << "[TEST] sin(90): " << sl.get_sin(90);
    std::cout << "[TEST] sin(45): " << sl.get_sin(45);
    std::cout << "[TEST] sin(-1): " << sl.get_sin(SineLookup::normalise_angle(-1));
}

static void test_lowpass() {
    SineLookup sl("data/sine_table.txt");

    std::vector<double> step = {0,0,0,1,1,1};
    LowPassFilter lp(0.1, 1, sl);
    auto out = lp.process(step);

    std::cout << "[TEST] Low-pass output:\n";
    for (double v : out) std::cout << v << " ";
    std::cout << "\n";

    for (size_t i = 1; i < out.size(); ++i) {
        assert(out[i] >= out[i - 1]);
        assert(out[i] <= 1.0);
    }

}

static void test_highpass() {
    SineLookup sl("data/sine_table.txt");

    std::vector<double> dc = {1,1,1,1,1};
    HighPassFilter hp(0.1, 1, sl);
    auto out = hp.process(dc);

    std::cout << "[TEST] High-pass output:\n";
    for (double v : out) std::cout << v << " ";
    std::cout << "\n";

    for (double v : out) {
        assert(std::abs(v) < 1e-6);
    }
}

static void test_modulation_range() {
    std::cout << "\n[TEST] Modulation range\n";

    SineLookup sl("data/sine_table.txt");
    LowPassFilter lp(0.2, 10, sl);

    for (int i = 0; i < 20; ++i) {
        double m = lp.compute_modulation(i);
        std::cout << "m(" << i << ") = " << m << "\n";

        if (m < 0.8 || m > 1.2) {
            std::cerr << "ERROR: modulation out of expected range: "<<m<<std::endl;
        }
    }
}


void run_tests() {
    std::cout << "TEST MODE\n";
    test_sine_lookup();
    test_lowpass();
    test_highpass();
    test_modulation_range();
}