#include "SoundWave.h"
#include <iostream>
#include <windows.h>


SoundWave::SoundWave()
	:bLoop(false), bIsPlaying(false), Buffer(nullptr), FileSize(0)
{

}

SoundWave::SoundWave(const SoundWave& other)
{
	Buffer = (int8*)::operator new(other.FileSize);
	memcpy_s(Buffer, other.FileSize, other.Buffer, other.FileSize);

	FilePath = other.FilePath;
	FileSize = other.FileSize;
	Info = other.Info;
}

SoundWave::~SoundWave()
{
	if(Buffer) delete[] Buffer;
}

void SoundWave::PrintInfo() const
{
	std::cout << *this << "\n\n";
}

void SoundWave::Play()
{
	bLoop ? PlaySoundA((char*)Buffer, nullptr, SND_MEMORY | SND_ASYNC | SND_LOOP ) : 
		PlaySoundA((char*)Buffer, nullptr, SND_MEMORY);

	bIsPlaying = true;
}

void SoundWave::Stop()
{
	PlaySoundA(nullptr, nullptr, SND_MEMORY);

	bIsPlaying = false;
}

SoundWave& SoundWave::operator=(const SoundWave& other)
{
	Buffer = (int8*)::operator new(other.FileSize);
	memcpy_s(Buffer, other.FileSize, other.Buffer, other.FileSize);

	FilePath = other.FilePath;
	FileSize = other.FileSize;
	Info = other.Info;

	return *this;
}
