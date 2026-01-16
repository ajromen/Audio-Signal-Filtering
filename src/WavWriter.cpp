#include <algorithm>
#include <cstdint>
#include <fstream>
#include <WavWriter.h>

void WavWriter::write(const std::string &filename, const std::vector<double> &samples, int sampleRate) {
    std::ofstream out(filename, std::ios::binary);
    if (!out) {
        throw std::runtime_error("Cannot open WAV output file");
    }

    // valicina fajla
    int dataChunkSize = samples.size() * sizeof(int16_t);
    int fileSize = 36 + dataChunkSize;


    // RIFF header
    out.write("RIFF", 4);
    out.write(reinterpret_cast<const char*>(&fileSize), 4);
    out.write("WAVE", 4);

    // format
    out.write("fmt ", 4);
    int subChunk1Size = 16;
    out.write(reinterpret_cast<const char*>(&subChunk1Size), 4);
    int16_t audioFormat = 1; // PCM
    out.write(reinterpret_cast<const char*>(&audioFormat), 2);
    out.write(reinterpret_cast<const char*>(&NUM_CHANNELS), 2);
    out.write(reinterpret_cast<const char*>(&sampleRate), 4);
    out.write(reinterpret_cast<const char*>(&BYTE_RATE), 4);
    out.write(reinterpret_cast<const char*>(&BLOCK_ALIGN), 2);
    out.write(reinterpret_cast<const char*>(&BITS_PER_SAMPLE), 2);

    //data
    out.write("data", 4);
    out.write(reinterpret_cast<const char*>(&dataChunkSize), 4);

    //pmc
    for (double s : samples) {
        s = std::clamp(s, -1.0, 1.0);
        int16_t pcm = static_cast<int16_t>(s * 32767.0);
        out.write(reinterpret_cast<const char*>(&pcm), sizeof(pcm));
    }

    out.close();
}
