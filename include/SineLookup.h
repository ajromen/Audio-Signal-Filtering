#pragma once
#include <map>
#include <string>

class SineLookup {
private:
    std::map<int, double> table;
    std::string file_path;

    double interpolate(int wanted_angle);

    std::map<int, double>::iterator get_first_or_lower(int wanted_angle);

    void load_lookup_table();

public:
    explicit SineLookup(const std::string &file_path);


    void debug_print_table();

    ~SineLookup() = default;

    static int normalise_angle(int angle);

    double get_sin(int angle);

};
