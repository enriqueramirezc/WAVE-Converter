#ifndef JOINCHANNELS_HPP
#define JOINCHANNELS_HPP

#include <cstdint>
#include <string>
#include <vector>

// Combines several mono `.wav` files into one multi-channel file
class JoinChannels {

 public:
	// samples of every input, in the order they were loaded
	std::vector<std::vector<int16_t>> channels;

	// sample rate shared by all inputs
	uint32_t SampleRate = 0;

	// read one mono 16-bit PCM file and keep it as a new channel.
	// returns 1 on success, 0 on failure
	int addFile(const std::string& path);

	// interleave the loaded channels into a single sample vector.
	// shorter channels are padded with silence
	std::vector<int16_t> interleave();
};
#endif // JOINCHANNELS_HPP
