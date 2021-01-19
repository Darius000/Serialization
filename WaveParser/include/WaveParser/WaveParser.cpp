#include "WaveParser.h"
#include <fstream>
#include <iostream>
#include <windows.h>


WaveFile::WaveFile(const std::string& file)
{
	if(!OpenFile(file)) return;

	FileSize = ReadFileBuffer();
	if(!FileSize) return;

	if (ReadWaveHeader())
	{
		ReadWaveFormat();
		ReadWaveData();
	}
}

WaveFile::WaveFile()
	:Buffer(nullptr), FileSize(0)
{

}

WaveFile::WaveFile(const WaveFile& other)
{
	Buffer = (int8*)::operator new(other.FileSize);
	memcpy_s(Buffer, other.FileSize, other.Buffer, other.FileSize);

	FilePath = other.FilePath;
	FileSize = other.FileSize;
	Info = other.Info;
}

WaveFile::~WaveFile()
{
	if(Buffer) delete[] Buffer;
}

long WaveFile::ReadFileBuffer()
{
	//Find the file size to create the buffer
	long begin = (long)ifs.tellg();
	ifs.seekg(0, std::ios::end);
	long end = (long)ifs.tellg();
	ifs.seekg(0);

	long fileSize = end - begin;

	//store file contents into buffer
	Buffer = new int8[fileSize];
	ifs.read(Buffer, fileSize);
	ifs.seekg(0);

	return fileSize;
}

bool WaveFile::ReadWaveHeader()
{
	char chunkId[20] = "";
	unsigned int chunkSize = -1;
	char chunkFormat[20] = "";

	ifs.read(chunkId, sizeof(char) * 4);

	if (strcmp(chunkId, "RIFF"))
	{
		Print("Invalid Wave File! Missing RIFF in header! \n");
		return false;
	}

	ifs.read((char*)&chunkSize, sizeof(int));

	//Chunk size if the size of the file after the id and if the file size - 8 is not equal, file is corrupted
	if (chunkSize != (FileSize - 8))
	{
		Print("Invalid File size! \n");
		return false;
	}

	ifs.read(chunkFormat, sizeof(int));

	//Check if the format is actually a WAVE
	if (strcmp(chunkFormat, "WAVE"))
	{
		Print("Not a valid wave file \n");
		return false;
	}

	Info.Header = {chunkId, chunkSize, chunkFormat};

	return true;
}

void WaveFile::ReadWaveFormat()
{
	char subChunkID[20] = "";
	unsigned int subChunkSize = -1;
	unsigned short audioFormat = -1;
	unsigned short numChannels = -1;
	unsigned int sampleRate = -1;
	unsigned int byteRate = -1;
	unsigned short blockAlign = -1;
	unsigned short bitsPerSample = -1;

	ifs.read(subChunkID, sizeof(int));
	ifs.read((char*)&subChunkSize, sizeof(int));
	ifs.read((char*)&audioFormat, sizeof(short));
	ifs.read((char*)&numChannels, sizeof(short));
	ifs.read((char*)&sampleRate, sizeof(int));
	ifs.read((char*)&byteRate, sizeof(int));
	ifs.read((char*)&blockAlign, sizeof(short));
	ifs.read((char*)&bitsPerSample, sizeof(short));

	const unsigned int expectedByteRate = sampleRate * numChannels * bitsPerSample / 8;
	if (byteRate != expectedByteRate)
	{
		Print("Invalid Byte rate! \n");
		return ;
	}

	const unsigned int expectedBlockAlign = numChannels * bitsPerSample / 8;

	if (blockAlign != expectedBlockAlign)
	{
		Print("Invalid Block Align! \n");
		return ;
	}

	Info.Format = { subChunkID,  subChunkSize, audioFormat, numChannels, sampleRate,
		byteRate, blockAlign, bitsPerSample };
}

void WaveFile::ReadWaveData()
{
	char subChunk2ID[20] = "";
	unsigned int subChunk2Size = -1;

	ifs.read(subChunk2ID, sizeof(char) * 4);
	ifs.read((char*)&subChunk2Size, sizeof(int));

	Info.DataChunk.subChunk2ID = subChunk2ID;
	Info.DataChunk.subChunk2Size = subChunk2Size;

	auto bitsPerSample = Info.Format.BitsPerSample;

	if (bitsPerSample == 8)
	{
		auto data = ReadSoundData<char>(subChunk2Size);
		Info.DataChunk.Data = data;
	}
	else if (bitsPerSample == 16)
	{
		auto data = ReadSoundData<short>(subChunk2Size);
		Info.DataChunk.Data = data;
	}
	else if (bitsPerSample == 32)
	{
		auto data = ReadSoundData<int>(subChunk2Size);
		Info.DataChunk.Data = data;
	}
	else
	{
		Print("Unsupported BitsPerSample! \n");
		return;
	}
}

bool WaveFile::OpenFile(const std::string& file)
{
	FilePath = file;

	ifs.open(FilePath.c_str(), std::ios::binary);

	//did the file successfully open
	if (ifs.is_open() == false) return false;

	return true;
}

void WaveFile::CloseFile()
{
	//close the file
	ifs.close();
}

void WaveFile::PrintInfo() const
{
	std::cout << *this << "\n\n";
}

void WaveFile::Play()
{
	PlaySoundA((char*)Buffer, nullptr, SND_MEMORY);
}

WaveFile& WaveFile::operator=(const WaveFile& other)
{
	Buffer = (int8*)::operator new(other.FileSize);
	memcpy_s(Buffer, other.FileSize, other.Buffer, other.FileSize);

	FilePath = other.FilePath;
	FileSize = other.FileSize;
	Info = other.Info;

	return *this;
}
