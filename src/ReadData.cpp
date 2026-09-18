#include "ReadData.hpp"

// fetch data after file header
int ReadData::fetchData(FileHeader& h, std::ifstream& ifs) {
	samples.resize(h.SubChunk2Size / sizeof(int16_t));
	ifs.read(reinterpret_cast<char*>(samples.data()), h.SubChunk2Size);
	return 1;
}

// de-interleave `samples` into one vector per channel
std::vector<std::vector<int16_t>> ReadData::splitChannels(const FileHeader& h) {
	const size_t numChannels = h.NumChannels;
	const size_t numFrames   = samples.size() / numChannels;

	std::vector<std::vector<int16_t>> channels(numChannels, std::vector<int16_t>(numFrames));

	for (size_t frame = 0; frame < numFrames; frame++) {
		for (size_t ch = 0; ch < numChannels; ch++) {
			channels[ch][frame] = samples[frame * numChannels + ch];
		}
	}
	return channels;
}
