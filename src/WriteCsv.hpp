#ifndef WRITECSV_HPP
#define WRITECSV_HPP

#include <cstdint>
#include <string>
#include <vector>

// Writes one channel as CSV
//   block == 1 : one raw sample per row       (header: sample)
//   block  > 1 : one row per `block` samples  (header: time_s,peak,rms)
class WriteCsv {

 public:
	// returns 1 on success, 0 on failure
	int write(const std::string& path, const std::vector<int16_t>& samples, uint32_t sampleRate, size_t block);
};
#endif // WRITECSV_HPP
