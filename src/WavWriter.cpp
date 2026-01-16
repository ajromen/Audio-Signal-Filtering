#include <algorithm>
#include <cstdint>
#include <fstream>
#include <WavWriter.h>

/**
 * Zapisuje niz sample-a u WAV fajl
 *
 * @param filename Izlazni fajl
 * @param samples vector<double> signala koji se sacuvava
 * @param sample_rate frekvencija izlaznog zvuka
 */
void WavWriter::write(const std::string &filename, const std::vector<double> &samples, int sample_rate) {
    std::ofstream out(filename, std::ios::binary);
    if (!out) {
        throw std::runtime_error("Cannot open WAV output file");
    }

    // valicina fajla
    int data_chunk_size = samples.size() * sizeof(int16_t);
    int file_size = 36 + data_chunk_size;


    // RIFF header
    out.write("RIFF", 4);
    out.write(reinterpret_cast<const char*>(&file_size), 4);
    out.write("WAVE", 4);

    // format
    out.write("fmt ", 4);
    int sub_chunk_size = 16;
    out.write(reinterpret_cast<const char*>(&sub_chunk_size), 4);
    int16_t audio_format = 1; // PCM
    out.write(reinterpret_cast<const char*>(&audio_format), 2);
    out.write(reinterpret_cast<const char*>(&NUM_CHANNELS), 2);
    out.write(reinterpret_cast<const char*>(&sample_rate), 4);
    out.write(reinterpret_cast<const char*>(&BYTE_RATE), 4);
    out.write(reinterpret_cast<const char*>(&BLOCK_ALIGN), 2);
    out.write(reinterpret_cast<const char*>(&BITS_PER_SAMPLE), 2);

    //data
    out.write("data", 4);
    out.write(reinterpret_cast<const char*>(&data_chunk_size), 4);

    //pmc
    for (double s : samples) {
        s = std::clamp(s, -1.0, 1.0);
        int16_t pcm = static_cast<int16_t>(s * 32767.0);
        out.write(reinterpret_cast<const char*>(&pcm), sizeof(pcm));
    }

    out.close();
}
