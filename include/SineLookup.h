#pragma once
#include <map>
#include <string>

class SineLookup {
private:
    std::map<int, double> table;
    std::string file_path;

    static double interpolate(int wanted_angle,int begin_angle,int end_angle, double begin_value, double end_value);

public:
    explicit SineLookup(const std::string &file_path) : file_path(file_path) {
    }

    ~SineLookup() = default;

    static int normalise_angle(int angle);

    void load_lookup_table() ;

    double get_sin(int angle);

};
