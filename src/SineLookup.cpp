#include <filesystem>
#include <SineLookup.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include <stdexcept>


double SineLookup::interpolate(int wanted_angle, int begin_angle, int end_angle, double begin_value, double end_value) {
    //osiguravamo deljenje sa 0
    if (begin_angle == end_angle) {
        return begin_value;
    }

    double t = double(wanted_angle - begin_angle)/ double(end_angle - begin_angle);
    return begin_value + (end_value - begin_value)*t;
}

int SineLookup::normalise_angle(int angle) {
    angle %= 360;
    if (angle < 0) angle += 360;
    return angle;
}

void SineLookup::load_lookup_table() {
    //postoji li fajl?

    if (!std::filesystem::exists(this->file_path)) {
        throw std::runtime_error("SineLookup::load_lookup_table() File does not exist.");
    }

    std::ifstream file(this->file_path);
}


