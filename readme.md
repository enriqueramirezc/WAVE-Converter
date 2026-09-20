# Wave Audio Channel Manipulation Tool

Simple C++ program for handling `.wav` audio files.

## Features

- Show file metadata.
- Create multi-channel WAVE files from separate
  single-channel files: `./bin/program --join <output file> <channel 1 input file> <channel 2 input file>`
- Splitting multi-channel WAVE files into multiple
  single-channel files: `./bin/program <input file>`
- Get `.csv` representation of data: `./bin/program <audio file> [--csv [block size]]`

## Usage examples

Audio files were sourced from [here](https://www.mmsp.ece.mcgill.ca/Documents/AudioFormats/WAVE/Samples.html).

Remember to do `make clean` and `make`.

- `./bin/program input/M1F1-int16WE-AFsp.wav` will give the following output:

```bash
RIFF Format: WAVE
---------------
fmt id: fmt 
fmt size: 40
fmt audio format: 65534 (extensible, sub-format 1)
fmt Channels: 2
fmt Sample rate: 8000
fmt byte range: 32000
fmt Block align: 4
fmt Bits per sample: 16
---------------
Data id: data
Data size: 93972
---------------
Channel 1: samples=23493 duration=2.93662s peak=14325 rms=887.649
  wrote output/M1F1-int16WE-AFsp_ch1.wav
Channel 2: samples=23493 duration=2.93662s peak=6415 rms=811.139
  wrote output/M1F1-int16WE-AFsp_ch2.wav
```

Input file was stereo, so each channel got converted
into its own mono file: `output/M1F1-int16WE-AFsp_ch1.wav`, and `output/M1F1-int16WE-AFsp_ch2.wav`.

- Similarly, we could also take those two mono files and join them to make a new stereo file `./bin/program --join output/stereo.wav input/M1F1-int16WE-AFsp_ch1.wav input/M1F1-int16WE-AFsp_ch2.wav`; which would give us the following output:

```bash
Reading input/M1F1-int16WE-AFsp_ch1.wav
Reading input/M1F1-int16WE-AFsp_ch2.wav
---------------
wrote output/stereo.wav: channels=2 sample rate=8000 duration=2.93662s
```

## Notes

- If you happen to need a more sophisticated audio
  manipulation tool, `ffmpeg` is probably the way to go.
- This project assumes you're using Linux.
- I initially coded this tool for my job in order to do some analysis on a dataset before doing diarization tasks. Later on I stopped needing it, so some of the later code in this repository was made using AI. I'll polish it up a bit whenever I have some spare time, but it works fine "as is".
