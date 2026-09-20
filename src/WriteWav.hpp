#ifndef WRITEWAV_HPP
#define WRITEWAV_HPP

#include <cstdint>
#include <string>
#include <vector>

// Writes a 16-bit PCM `.wav` file
class WriteWav {

 public:
	// returns 1 on success, 0 on failure
	int write(const std::string& path, const std::vector<int16_t>& samples, uint32_t sampleRate);

	// same, but `samples` is already interleaved across `numChannels`
	int write(const std::string& path, const std::vector<int16_t>& samples, uint32_t sampleRate,
	          uint16_t numChannels);
};
#endif // WRITEWAV_HPP
