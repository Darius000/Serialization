#pragma once

#include "../FileReadWriter/Reader/FileReader.h"
#include "../Sound/SoundWave.h"

class Importer
{
public:
	template<typename T>
	static T* Import(const wchar_t* path);

private:

	template<typename T>
	static T* OnImport(const wchar_t* path);

	template<typename T>
	static void Print(T str);

	static FileReader fileReader;
};

template<typename T>
void Importer::Print(T str)
{
	std::cout << str << "\n\n";
}

template<typename T>
T* Importer::Import(const wchar_t* path)
{
	return OnImport<T>(path);
}

template<typename T>
inline void* ReadSoundData(unsigned int datasize)
{
	void* data = (void*)::operator new(datasize);
	ifs.read((char*)data, datasize * sizeof(T));

	return data;
}

template<>
SoundWave* Importer::OnImport(const wchar_t* path)
{
	SoundWave* wave = nullptr;

	if (fileReader.Open(path, ReadMode::Binary))
	{
		wave = new SoundWave();
		long filesize = fileReader.GetFileSize();
		wave->FileSize = filesize;

		//read entire file into buffer
		wave->Buffer = new char[filesize];
		fileReader.Read(wave->Buffer, filesize);
		fileReader.Begin();

		//Read Header
		char chunkId[20] = "";
		unsigned int chunkSize = -1;
		char chunkFormat[20] = "";

		fileReader.Read(chunkId, sizeof(char) * 4);

		if (strcmp(chunkId, "RIFF"))
		{
			Print("Invalid Wave File! Missing RIFF in header! \n");
			return nullptr;
		}

		fileReader.Read(chunkSize, sizeof(int));

		//Chunk size if the size of the file after the id and if the file size - 8 is not equal, file is corrupted
		if (chunkSize != (filesize - 8))
		{
			Print("Invalid File size! \n");
			return nullptr;
		}

		fileReader.Read(chunkFormat, sizeof(int));

		//Check if the format is actually a WAVE
		if (strcmp(chunkFormat, "WAVE"))
		{
			Print("Not a valid wave file \n");
			return nullptr;
		}

		wave->Info.Header = { chunkId, chunkSize, chunkFormat };

		//Read formatting
		char subChunkID[20] = "";
		unsigned int subChunkSize = -1;
		unsigned short audioFormat = -1;
		unsigned short numChannels = -1;
		unsigned int sampleRate = -1;
		unsigned int byteRate = -1;
		unsigned short blockAlign = -1;
		unsigned short bitsPerSample = -1;

		fileReader.Read(subChunkID, sizeof(int));
		fileReader.Read(subChunkSize, sizeof(int));
		fileReader.Read(audioFormat, sizeof(short));
		fileReader.Read(numChannels, sizeof(short));
		fileReader.Read(sampleRate, sizeof(int));
		fileReader.Read(byteRate, sizeof(int));
		fileReader.Read(blockAlign, sizeof(short));
		fileReader.Read(bitsPerSample, sizeof(short));

		const unsigned int expectedByteRate = sampleRate * numChannels * bitsPerSample / 8;
		if (byteRate != expectedByteRate)
		{
			Print("Invalid Byte rate! \n");
			return nullptr;
		}

		const unsigned int expectedBlockAlign = numChannels * bitsPerSample / 8;

		if (blockAlign != expectedBlockAlign)
		{
			Print("Invalid Block Align! \n");
			return nullptr;
		}

		wave->Info.Format = { subChunkID,  subChunkSize, audioFormat, numChannels, sampleRate,
			byteRate, blockAlign, bitsPerSample };

		//read data
		char subChunk2ID[20] = "";
		unsigned int subChunk2Size = -1;

		fileReader.Read(subChunk2ID, sizeof(char) * 4);
		fileReader.Read(subChunk2Size, sizeof(int));

		wave->Info.DataChunk.subChunk2ID = subChunk2ID;
		wave->Info.DataChunk.subChunk2Size = subChunk2Size;

		void* data = (void*)::operator new(subChunk2Size);

		if (bitsPerSample == 8)
		{			
			fileReader.Read(data, subChunk2Size * sizeof(char));
			wave->Info.DataChunk.Data = data;
		}
		else if (bitsPerSample == 16)
		{
			fileReader.Read(data, subChunk2Size * sizeof(short));
			wave->Info.DataChunk.Data = data;
		}
		else if (bitsPerSample == 32)
		{
			fileReader.Read(data, subChunk2Size * sizeof(int));
			wave->Info.DataChunk.Data = data;
		}
		else
		{
			Print("Unsupported BitsPerSample! \n");
			return nullptr;
		}

		fileReader.Close();
	}

	return wave;
}

__declspec(selectany) FileReader Importer::fileReader;

