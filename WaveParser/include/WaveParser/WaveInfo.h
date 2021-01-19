#pragma once

#include <map>
#include <vector>
#include <ostream>
#include <string>

struct WaveHeader
{
	std::string ChunkID;
	unsigned int ChunkSize;
	std::string  Format;

	friend std::ostream& operator<<(std::ostream& os, const WaveHeader& header);
};

inline std::ostream& operator<<(std::ostream& os, const WaveHeader& header)
{
	return os << "[ Header: ID = " << header.ChunkID << ", S = " <<  header.ChunkSize <<
		", Fmt = " << header.Format << "]";
}

struct WaveFormat
{
	std::string subChunkID;
	unsigned int subChunkSize;
	unsigned short AudioFormat;
	unsigned short NumChannels;
	unsigned int SampleRate;
	unsigned int ByteRate;
	unsigned short BlockAlign;
	unsigned short BitsPerSample;

	friend std::ostream& operator<<(std::ostream& os, const WaveFormat& format);
};

inline std::ostream& operator<<(std::ostream& os, const WaveFormat& format)
{
	return os << "[ Format : ID = " << format.subChunkID << ", S = " << format.subChunkSize << ", AF = " << format.AudioFormat <<
	", CHs = " << format.NumChannels << ", SR = " << format.SampleRate << ", BR = " << format.ByteRate << ", BA = " <<
	 format.BlockAlign << ", BPS = " << format.BitsPerSample << "]";
}

template<typename T>
using ChannelData = std::map<unsigned int, std::vector<T>>;

struct WaveDataChunk
{
	std::string subChunk2ID;
	unsigned int subChunk2Size;
	void* Data;

	friend std::ostream& operator<<(std::ostream& os, const WaveDataChunk& Data);
};

inline std::ostream& operator<<(std::ostream& os, const WaveDataChunk& Data)
{
	return os << "[ Data : ID = " << Data.subChunk2ID << ", S = " << Data.subChunk2Size << "]";
}

struct WaveInfo
{
	WaveHeader Header;
	WaveFormat Format;
	WaveDataChunk DataChunk;

	friend std::ostream& operator<<(std::ostream& os, const WaveInfo& Info);
};

inline std::ostream& operator<<(std::ostream& os, const WaveInfo& Info)
{
	return os << Info.Header << "\n" << Info.Format << "\n" << Info.DataChunk << "\n";
}