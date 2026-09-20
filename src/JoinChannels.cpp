#include "JoinChannels.hpp"
#include "FileHeader.hpp"
#include "ReadHeader.hpp"
#include "ReadData.hpp"
#include <fstream>
#include <iostream>

// read one mono file and keep it as a new channel
int JoinChannels::addFile(const std::string& path) {
	std::ifstream ifs(path, std::ios::binary);
	if (!ifs.is_open()) {
		std::cout << "File " << path << " not found" << std::endl;
		return 0;
	}

	FileHeader h;
	ReadHeader in;
	if (in.fetchMetadata(h, ifs) != 1) {
		return 0;
	}

	if (h.FormatTag != 1 || h.BitsPerSample != 16) {
		std::cout << path << ": only 16-bit PCM is supported" << std::endl;
		return 0;
	}

	if (h.NumChannels != 1) {
		std::cout << path << ": expected a mono file, found "
			<< h.NumChannels << " channels" << std::endl;
		return 0;
	}

	// every input has to agree on the sample rate, otherwise the
	// result would play back at the wrong speed for some channels
	if (SampleRate == 0) {
		SampleRate = h.SampleRate;
	} else if (SampleRate != h.SampleRate) {
		std::cout << path << ": sample rate " << h.SampleRate
			<< " does not match " << SampleRate << std::endl;
		return 0;
	}

	ReadData data;
	if (data.fetchData(h, ifs) != 1) {
		std::cout << "Could not read audio data from " << path << std::endl;
		return 0;
	}

	channels.push_back(data.samples);
	return 1;
}

// interleave the loaded channels, padding short ones with silence
std::vector<int16_t> JoinChannels::interleave() {
	const size_t numChannels = channels.size();

	// the output is as long as the longest input
	size_t numFrames = 0;
	for (const std::vector<int16_t>& ch : channels) {
		if (ch.size() > numFrames) numFrames = ch.size();
	}

	std::vector<int16_t> samples(numFrames * numChannels, 0);

	for (size_t ch = 0; ch < numChannels; ch++) {
		for (size_t frame = 0; frame < channels[ch].size(); frame++) {
			samples[frame * numChannels + ch] = channels[ch][frame];
		}
	}
	return samples;
}
