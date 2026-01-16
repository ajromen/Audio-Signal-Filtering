
#include <fstream>
#include <iostream>
#include <limits>
#include <Signal.hpp>
#include <string>

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
        } catch (std::exception &e) {
            std::cerr << "Signal load: Skipping invalid value: " << value << std::endl;
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
}

