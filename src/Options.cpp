#include <Options.h>
#include <CLI/CLI.hpp>

/**
 * Ucitava, proverava i vraca cli flagove
 *
 * @return Popunjen Options objekat
 */
Options Options::parse_options(int argc, char **argv) {
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

    // salje exception ako je npr unet 'abc' za int
    try {
        app.parse(argc, argv);
    } catch (const CLI::ParseError &e) {
        std::exit(app.exit(e));
    }

    if (type_str == "lowpass")       opt.type = FilterType::LowPass;
    else if (type_str == "highpass") opt.type = FilterType::HighPass;
    else if (type_str == "bandpass") opt.type = FilterType::BandPass;


    // postavlja apsolutne adrese
    opt.signal = std::filesystem::absolute(opt.signal).string();
    opt.sine   = std::filesystem::absolute(opt.sine).string();
    opt.out    = std::filesystem::absolute(opt.out).string();


    // proveravanje postojanja fajlova
    if (!std::filesystem::exists(opt.signal)) {
        std::cout << opt.signal;
        throw std::runtime_error("Signal file not found: " + opt.signal);
    }

    if (!std::filesystem::exists(opt.sine)) {
        throw std::runtime_error("Sine table file not found: " + opt.sine);
    }

    return opt;
}
