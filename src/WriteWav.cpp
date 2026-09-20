#include "WriteWav.hpp"
#include <fstream>
#include <iostream>

// Write one mono 16-bit PCM channel to `path`
int WriteWav::write(const std::string& path, const std::vector<int16_t>& samples, uint32_t sampleRate) {
	return write(path, samples, sampleRate, 1);
}

// Write interleaved 16-bit PCM samples to `path`
int WriteWav::write(const std::string& path, const std::vector<int16_t>& samples, uint32_t sampleRate,
                    uint16_t numChannels) {
	std::ofstream ofs(path, std::ios::binary);
	if (!ofs.is_open()) {
		std::cout << "Could not create " << path << std::endl;
		return 0;
	}

	const uint16_t bitsPerSample = 16;
	const uint16_t blockAlign    = numChannels * bitsPerSample / 8;
	const uint32_t byteRate      = sampleRate * blockAlign;
	const uint32_t dataSize      = static_cast<uint32_t>(samples.size() * sizeof(int16_t));
	const uint32_t chunkSize     = 36 + dataSize;
	const uint32_t fmtSize       = 16;
	const uint16_t audioFormat   = 1; // PCM

	// RIFF chunk descriptor
	ofs.write("RIFF", 4);
	ofs.write(reinterpret_cast<const char*>(&chunkSize), 4);
	ofs.write("WAVE", 4);

	// fmt sub-chunk
	ofs.write("fmt ", 4);
	ofs.write(reinterpret_cast<const char*>(&fmtSize), 4);
	ofs.write(reinterpret_cast<const char*>(&audioFormat), 2);
	ofs.write(reinterpret_cast<const char*>(&numChannels), 2);
	ofs.write(reinterpret_cast<const char*>(&sampleRate), 4);
	ofs.write(reinterpret_cast<const char*>(&byteRate), 4);
	ofs.write(reinterpret_cast<const char*>(&blockAlign), 2);
	ofs.write(reinterpret_cast<const char*>(&bitsPerSample), 2);

	// data sub-chunk
	ofs.write("data", 4);
	ofs.write(reinterpret_cast<const char*>(&dataSize), 4);
	ofs.write(reinterpret_cast<const char*>(samples.data()), dataSize);

	return ofs.good() ? 1 : 0;
}
