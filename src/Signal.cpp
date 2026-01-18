
#include <fstream>
#include <iostream>
#include <Signal.hpp>
#include <string>
#include <utility>
#include <cmath>


/**
 *
 * @return vector of normalized values
 */
std::vector<double> Signal::get_data() {
    return data;
}

/**
 * Ucitava i sacuvava ulazni signal iz fajla
 */
void Signal::load_data() {
    std::ifstream file(file_path);

    if (!file.is_open()) {
        throw std::runtime_error("Signal load: Could not open file: " + file_path);
    }

    std::string value;

    double sample;
    while (file >> value) {
        try {
            sample = std::stod(value);

            if (!std::isfinite(sample)) {
                std::cerr << "Signal load: Skipping invalid value: " << value << std::endl;
                continue;
            }
        } catch (std::exception &e) {
            std::cerr << "Signal load: Skipping invalid value: " << value << std::endl;
            continue;
        }
        if (sample < -1.0 || sample > 1.0) {
            std::cerr << "Signal load: Skipping out-of-range sample: " << sample << std::endl;
            continue;
        }
        data.push_back(sample);
    }

    file.close();

    if (data.size() > MAX_SAMPLES) {
        std::cerr << "Warning: Signal has more samples than supported. Truncating to "
                  << MAX_SAMPLES;
        data.resize(MAX_SAMPLES);
    }

    if (data.empty()) {
        throw std::runtime_error("Signal load: No valid samples loaded");
    }
}

Signal::Signal(std::string file_path):file_path(std::move(file_path)) {
    this->load_data();
}

