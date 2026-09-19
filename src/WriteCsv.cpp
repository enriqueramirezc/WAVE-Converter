#include "WriteCsv.hpp"
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iostream>

// Write one channel as CSV
int WriteCsv::write(const std::string& path, const std::vector<int16_t>& samples, uint32_t sampleRate, size_t block) {
	std::ofstream ofs(path);
	if (!ofs.is_open()) {
		std::cout << "Could not create " << path << std::endl;
		return 0;
	}

	if (block <= 1) {
		// raw samples, row number / sampleRate gives the time
		ofs << "sample\n";
		for (int16_t s : samples) {
			ofs << s << '\n';
		}
		return ofs.good() ? 1 : 0;
	}

	// one summary row per block of samples
	ofs << "time_s,peak,rms\n";
	for (size_t start = 0; start < samples.size(); start += block) {
		size_t end = std::min(start + block, samples.size());
		int peak = 0;
		double sumSquares = 0.0;
		for (size_t i = start; i < end; i++) {
			int s = samples[i];
			if (std::abs(s) > peak) peak = std::abs(s);
			sumSquares += static_cast<double>(s) * s;
		}
		double rms = std::sqrt(sumSquares / (end - start));
		ofs << static_cast<double>(start) / sampleRate << ',' << peak << ',' << rms << '\n';
	}

	return ofs.good() ? 1 : 0;
}
