#pragma once
#include <limits>
#include <string>
#include <vector>

/**
 * Wrapper klasa za niz sample-a
 */
class Signal {
private:
    std::vector<double> data;
    std::string file_path;
    size_t MAX_SAMPLES = static_cast<size_t>(std::numeric_limits<int>::max());
public:
    void load_data();

    Signal(const std::string& file_path):file_path(file_path){};
    Signal(const std::vector<double>& data):data(data){};

    std::vector<double> get_data();
};
