#pragma once

#include "WaveInfo.h"
#include <string>
#include <fstream>

class WaveFile
{
public:
	using int8 = char;
	using int64 = long;

	WaveFile();
	WaveFile(const WaveFile& other);
	WaveFile(const std::string& file);
	~WaveFile();

private:
	/*read in file buffer
	@Params return file size
	*/
	long ReadFileBuffer();

	/*Parse the wave file header
	@Params return if file is a wave
	*/
	bool ReadWaveHeader();

	//Parse wave file format type
	void ReadWaveFormat();

	//Parse actual wave file sound data
	void ReadWaveData();

	template<typename T>
	void* ReadSoundData(unsigned int datasize);

	/*
	@Params returns if file was successfully opened
	*/
	bool OpenFile(const std::string& file);

	void CloseFile();

public:
	//Get raw file buffer data
	const int8* GetRawData() const { return Buffer; }

	//Get Wave FIle Info
	const WaveInfo& GetInfo() const {return Info; }

	const std::string& GetFilePath() const {return FilePath; }

	void PrintInfo() const;

	void Play();

	WaveFile& operator=(const WaveFile& other);

	template<typename T>
	void Print(T str);

	friend std::ostream& operator<<(std::ostream& os, const WaveFile& file);

private:
	int8* Buffer;
	WaveInfo Info;
	std::string FilePath;
	int64 FileSize;
	std::ifstream ifs;
};

inline std::ostream& operator<<(std::ostream& os, const WaveFile& file)
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

template<typename T>
void* WaveFile::ReadSoundData(unsigned int datasize)
{
	void* data = (void*)::operator new(datasize);
	ifs.read((char*)data, datasize * sizeof(T));

	return data;
}

template<typename T>
void WaveFile::Print(T str)
{
	std::cout << FilePath << ":" << str << "\n\n";
}