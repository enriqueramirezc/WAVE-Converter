#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <cmath>
#include <cstdint>
#include "FileHeader.hpp"
#include "ReadHeader.hpp"
#include "ReadData.hpp"
#include "WriteWav.hpp"
#include "WriteCsv.hpp"

// Print a short per-channel summary 
static void printChannelSummary(int index, const std::vector<int16_t>& ch, uint32_t sampleRate) {
	int16_t peak = 0;
	double sumSquares = 0.0;
	for (int16_t s : ch) {
		if (std::abs(s) > peak) peak = std::abs(s);
		sumSquares += static_cast<double>(s) * s;
	}
	double rms = ch.empty() ? 0.0 : std::sqrt(sumSquares / ch.size());

	std::cout << "Channel " << index
	          << ": samples=" << ch.size()
	          << " duration=" << static_cast<double>(ch.size()) / sampleRate << "s"
	          << " peak=" << peak
	          << " rms=" << rms << std::endl;
}

int main(int argc, char* argv[]) {

	// Read file name and optional flag from arguments
	//   --csv     one raw sample per row
	//   --csv N   one row (time,peak,rms) per block of N samples
	if (argc < 2 || argc > 4 || (argc >= 3 && std::string(argv[2]) != "--csv")) {
		std::cout << "Usage: " << argv[0] << " <audio file> [--csv [block size]]" << std::endl;
		return 0;
	}
	std::string input = argv[1];
	bool writeCsv = (argc >= 3);
	size_t csvBlock = (argc == 4) ? std::stoul(argv[3]) : 1;

	// Open file
	std::ifstream ifs(input, std::ios::binary);

	// Case where it couldn't be opened.
	if (!ifs.is_open()) {
		std::cout << "File " << input << " not found" << std::endl;
		return 0;
	}
	std::cout << "Processing " << input << " file" << std::endl;

	FileHeader h;
	ReadHeader in;

	if (in.fetchMetadata(h, ifs) != 1) {
		return 1;
	}
	h.printHeaderInfo();

	if (h.AudioFormat != 1 || h.BitsPerSample != 16) {
		std::cout << "Only 16-bit PCM is supported" << std::endl;
		return 1;
	}

	ReadData data;
	if (data.fetchData(h, ifs) != 1) {
		std::cout << "Could not read audio data" << std::endl;
		return 1;
	}

	// Output goes to output/<name>_chN.wav (and .csv if requested)
	std::filesystem::create_directories("output");
	std::string base = "output/" + std::filesystem::path(input).stem().string();

	std::vector<std::vector<int16_t>> channels = data.splitChannels(h);
	WriteWav wav;
	WriteCsv csv;

	std::cout << "---------------" << std::endl;
	for (size_t ch = 0; ch < channels.size(); ch++) {
		std::string name = base + "_ch" + std::to_string(ch + 1);

		printChannelSummary(static_cast<int>(ch + 1), channels[ch], h.SampleRate);

		if (wav.write(name + ".wav", channels[ch], h.SampleRate) == 1) {
			std::cout << "  wrote " << name << ".wav" << std::endl;
		}
		if (writeCsv && csv.write(name + ".csv", channels[ch], h.SampleRate, csvBlock) == 1) {
			std::cout << "  wrote " << name << ".csv" << std::endl;
		}
	}

	return 0;
}
