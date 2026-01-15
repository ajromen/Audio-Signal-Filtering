#include <CLI/CLI.hpp>
#include <options.h>
#include <iostream>

#include <CLI/CLI.hpp>
#include <options.h>

#include <filesystem>
#include <iostream>
#include <stdexcept>

Options parse_options(int argc, char **argv) {
    Options opt;

    CLI::App app{"Audio Signal Filtering"};

    // Defaults
    std::string type_str = "lowpass";
    opt.alpha = 0.15;
    opt.mod_deg = 5;
    opt.signal = "data/signal.txt";
    opt.sine   = "data/sine_table.txt";
    opt.out    = "output.wav";

    // CLI options
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

    // Parse FIRST
    try {
        app.parse(argc, argv);
    } catch (const CLI::ParseError &e) {
        std::exit(app.exit(e));
    }

    // Convert type string → enum
    if (type_str == "lowpass")       opt.type = FilterType::LowPass;
    else if (type_str == "highpass") opt.type = FilterType::HighPass;
    else if (type_str == "bandpass") opt.type = FilterType::BandPass;

    // Resolve paths relative to CURRENT WORKING DIRECTORY
    opt.signal = std::filesystem::absolute(opt.signal).string();
    opt.sine   = std::filesystem::absolute(opt.sine).string();
    opt.out    = std::filesystem::absolute(opt.out).string();

    // Validate files
    if (!std::filesystem::exists(opt.signal)) {
        std::cout << opt.signal;
        throw std::runtime_error("Signal file not found: " + opt.signal);
    }

    if (!std::filesystem::exists(opt.sine)) {
        throw std::runtime_error("Sine table file not found: " + opt.sine);
    }

    return opt;
}


int main(int argc, char **argv) {
    Options opt = parse_options(argc, argv);

    // std::cout << "type: " << opt.type << "\n";
    std::cout << "alpha: " << opt.alpha << "\n";
    std::cout << "mod_deg: " << opt.mod_deg << "\n";
    std::cout << "signal: " << opt.signal << "\n";
    std::cout << "sine: " << opt.sine << "\n";
    std::cout << "out: " << opt.out << "\n";
}
