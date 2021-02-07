#pragma once

#include<string>

struct MpegProperties
{
	std::string SyncWord;
};

class SoundMpeg
{
public:
	SoundMpeg();
	~SoundMpeg();

	void Play();

private:
	MpegProperties Properties;

	char* Buffer;
	std::wstring FilePath;

	friend class Importer;
};