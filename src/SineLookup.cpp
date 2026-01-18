#include <algorithm>
#include <filesystem>
#include <SineLookup.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include <stdexcept>
#include <cmath>



/**
 * Za dati Key interpolate-uje vrednost koristeci prvi manji i prvi veci kluc i vrednost
 * (ideci u krug ako ih ne nadje) , zapisuje je u tabelu
 *
 * @param wanted_angle normalizovan ugao za koji ne postoji vrednost u tabeli
 * @return interpolate-ovana vrednost
 */
double SineLookup::interpolate(int wanted_angle) {

    auto it_upper = table.lower_bound(wanted_angle);
    auto it_lower = get_first_or_lower(wanted_angle);


    //ako ne postoji manji element kruzno sa kraja uzima poslednji
    if (it_lower == table.end()) {
        it_lower = std::prev(table.end());
    }

    // ako ne postoji veci element kruzno sa pocetka uzima prvi
    if (it_upper == table.end()) {
        it_upper = table.begin();
    }

    // ako ne postoje dva elementa izmedju kojih moze da se interpolate-uje
    if (it_upper == it_lower) {
        return it_upper->second;
    }

    // if (it_lower->first>it_upper->first)
    //     swap(it_upper, it_lower);

    int begin_angle=it_lower->first;
    int end_angle=it_upper->first;
    double begin_value = it_lower->second;
    double end_value = it_upper->second;

    //ako se obilazi krug garantuje nenegativne
    double delta = (end_angle - begin_angle + 360) % 360;

    if (delta == 0) {
        throw std::runtime_error("Sine interpolate: zero angle delta");
    }

    double t = (wanted_angle - begin_angle + 360) % 360 / delta;



    double value = begin_value + (end_value - begin_value) * t;

    if (!std::isfinite(value) || value < -1.0 || value > 1.0) {
        throw std::runtime_error("Interpolated sine value out of range");
    }

    table.insert(std::make_pair(wanted_angle, value));
    return value;
}

/**
 * @param wanted_angle  Key of (key, value) pair to be located.
 * @return Iterator pointing to the first element <= than key, or begin().
 */
std::map<int, double>::iterator SineLookup::get_first_or_lower(int wanted_angle) {
    if (table.empty()) return table.end();

    auto it = table.lower_bound(wanted_angle);
    if (it == table.begin()) return std::prev(table.end());
    if (it == table.end() || it->first > wanted_angle) it--;
    return it;
}


/**
 * Ispisuje sadrzaj lookup tabele
 */
void SineLookup::debug_print_table() {
    for (auto it = table.begin(); it != table.end(); ++it) {
        std::cout << it->first << ": " << it->second << std::endl;
    }
}

/**
 * Normalizuje ugao
 *
 * @param angle nenormalizovani ugao
 * @return normalizovani ugao u rasponu od 0 do 359
 */
int SineLookup::normalise_angle(int angle) {
    angle %= 360;
    if (angle < 0) angle += 360;
    return angle;
}

/**
 * Ucitava lookup tabelu za sinus iz ulaznog fajla
 */
void SineLookup::load_lookup_table() {
    //postoji li fajl?
    if (!std::filesystem::exists(this->file_path)) {
        throw std::runtime_error("File does not exist.");
    }

    std::ifstream file(this->file_path);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open sine lookup table file.");
    }

    std::string line;

    while (std::getline(file, line)) {
        if (line.empty()) continue;
        if (!line.empty() && !isdigit(line[0])) {
            std::cerr << "Sine Lookup load: Skipping invalid line: " << line << std::endl;
        }

        std::stringstream ss(line);
        int key;
        double value;

        if (!(ss >> key >> value)) {
            std::cerr << "Sine Lookup load: Skipping invalid line: " << line << std::endl;
        }

        if (!std::isfinite(value) || value < -1.0 || value > 1.0) {
            throw std::runtime_error("Invalid sine value (must be in [-1,1])");
        }


        key = normalise_angle(key);

        if (table.contains(key)) {
            std::cerr<<"Duplicate sine angle detected skipping line. key: "<<key<<std::endl;
            continue;
        }

        table.insert(std::make_pair(key, value));

    }

    file.close();


    // ako je tabela prazna ne sme se nastaviti program
    if (table.empty() || table.size()<2) {
        throw std::runtime_error("Sine Lookup load: Lookup table too small.");
    }
}

/**
 *
 * @param file_path ulazni fajl za lookup tabelu
 */
SineLookup::SineLookup(const std::string &file_path) {
    this->file_path=file_path;
    load_lookup_table();
}


/**
 * Vraca datu ili interpolate-ovanu vrednost sinusa
 *
 * @param angle vec normalizovani ugao
 * @return vrednost sinusa za dati ugao
 */
double SineLookup::get_sin(int angle)  {
    try {
        return table.at(angle);
    } catch (std::out_of_range&) {
        return interpolate(angle);
    }
}


