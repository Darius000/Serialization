#pragma once

#include "SoundWaveProperties.h"
#include <string>

class SoundWave
{
public:
	using int8 = char;
	using int64 = long;

	SoundWave();
	SoundWave(const SoundWave& other);
	~SoundWave();

public:
	//Get raw file buffer data
	const int8* GetRawData() const { return Buffer; }

	//Get Wave FIle Info
	const SoundWaveProperties& GetInfo() const {return Info; }

	const std::string& GetFilePath() const {return FilePath; }

	void PrintInfo() const;

	void Play();

	void Stop();

public:
	const bool IsPlaying() const{ return bIsPlaying; }

public:

	SoundWave& operator=(const SoundWave& other);

	friend std::ostream& operator<<(std::ostream& os, const SoundWave& file);
	friend class Importer;

public:
	bool bLoop;

private:
	bool bIsPlaying;

private:
	int8* Buffer;
	SoundWaveProperties Info;
	std::string FilePath;
	int64 FileSize;
};

inline std::ostream& operator<<(std::ostream& os, const SoundWave& file)
{
	os << file.FilePath << "\n" << file.Info << "\n";

	auto bps = file.Info.Format.BitsPerSample;
	auto numChannels = file.Info.Format.NumChannels;
	const unsigned int samplesToProcess = file.Info.DataChunk.subChunk2Size / numChannels / file.Info.Format.BitsPerSample / 8;

	if (bps == 8)
	{
		for (unsigned int i = 0; i < samplesToProcess; i++)
		{
			auto data = (char*)file.Info.DataChunk.Data;
			int sample = (data[i] - '0');
			os << sample << " ,";
		}
	}
	else if (bps == 16)
	{
		for (unsigned int i = 0; i < samplesToProcess; i++)
		{
			auto data = (short*)file.Info.DataChunk.Data;
			int sample = data[i];
			os << sample << " ,";
		}
	}
	else if (bps == 32)
	{
		for (unsigned int i = 0; i < samplesToProcess; i++)
		{
			auto data = (int*)file.Info.DataChunk.Data;
			int sample = data[i];
			os << sample << " ,";
		}
	}

	return os;
}



