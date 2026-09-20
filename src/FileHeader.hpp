#ifndef FILEHEADER_HPP
#define FILEHEADER_HPP
#include <cstdint>
#include <iostream>

// `.wav` file header
class FileHeader {

  public:
	// RIFF chunk descriptor
	char ChunkID[4];
	uint32_t ChunkSize;
	char Format[4];

	// fmt sub-chunk
	char SubChunk1ID[4];
	uint32_t SubChunk1Size;
	uint16_t AudioFormat;
	uint16_t NumChannels;
	uint32_t SampleRate;
	uint32_t ByteRate;
	uint16_t BlockAlign;
	uint16_t BitsPerSample;

	// real format code. same as AudioFormat, except when AudioFormat is
	// 65534 (extensible), where it comes from the SubFormat GUID instead
	uint16_t FormatTag;

	// data sub-chunk
    char SubChunk2ID[4];
	uint32_t SubChunk2Size;

	void printHeaderInfo();
};
#endif // FILEHEADER_HPP
