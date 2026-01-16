#include <CLI/CLI.hpp>
#include <options.h>
#include <iostream>

#include <CLI/CLI.hpp>
#include <options.h>
#include <SineLookup.h>
#include <Filter.h>
#include <BandPassFilter.h>
#include <HighPassFilter.h>
#include <WavWriter.h>


#include <filesystem>
#include <stdexcept>

#include <LowPassFilter.h>



Options parse_options(int argc, char **argv) {
    Options opt;

    CLI::App app{"Audio Signal Filtering"};

    std::string type_str = "lowpass";
    opt.alpha = 0.15;
    opt.mod_deg = 5;
    opt.signal = "data/signal.txt";
    opt.sine   = "data/sine_table.txt";
    opt.out    = "output.wav";

    app.add_option("--type", type_str,
                   "Filter type: lowpass | highpass | bandpass")
        ->check(CLI::IsMember({"lowpass", "highpass", "bandpass"}));

    app.add_option("--alpha", opt.alpha, "Alpha coefficient")
        ->check(CLI::Range(0.0, 1.0));

    app.add_option("--mod_deg", opt.mod_deg, "Modulation degree")
        ->check(CLI::PositiveNumber);

    app.add_option("--signal", opt.signal, "Input signal file");

    app.add_option("--sine", opt.sine, "Sine table file");

    app.add_option("--out", opt.out, "Output WAV file");

    try {
        app.parse(argc, argv);
    } catch (const CLI::ParseError &e) {
        std::exit(app.exit(e));
    }

    if (type_str == "lowpass")       opt.type = FilterType::LowPass;
    else if (type_str == "highpass") opt.type = FilterType::HighPass;
    else if (type_str == "bandpass") opt.type = FilterType::BandPass;


    opt.signal = std::filesystem::absolute(opt.signal).string();
    opt.sine   = std::filesystem::absolute(opt.sine).string();
    opt.out    = std::filesystem::absolute(opt.out).string();


    if (!std::filesystem::exists(opt.signal)) {
        std::cout << opt.signal;
        throw std::runtime_error("Signal file not found: " + opt.signal);
    }

    if (!std::filesystem::exists(opt.sine)) {
        throw std::runtime_error("Sine table file not found: " + opt.sine);
    }

    return opt;
}

/**
 *
 * @param file_path relative or absolute path to input file
 * @return vector of normalized values
 */
std::vector<double> loadSignal(const std::string& file_path) {
    std::vector<double> signal;

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
        signal.push_back(sample);
    }

    file.close();

    return signal;
}

int main(int argc, char **argv) {
    Options opt = parse_options(argc, argv);

    SineLookup sine_lookup(opt.sine);

    std::vector<double> signal = loadSignal(opt.signal);

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

    const std::vector<double> processed_signal = filter->process(signal);

    WavWriter::write(opt.out, processed_signal);
}
