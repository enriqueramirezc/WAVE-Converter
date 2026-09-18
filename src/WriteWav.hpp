#ifndef WRITEWAV_HPP
#define WRITEWAV_HPP

#include <cstdint>
#include <string>
#include <vector>

// Writes a mono 16-bit PCM `.wav` file
class WriteWav {

 public:
	// returns 1 on success, 0 on failure
	int write(const std::string& path, const std::vector<int16_t>& samples, uint32_t sampleRate);
};
#endif // WRITEWAV_HPP
