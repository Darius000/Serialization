#include "SoundMpeg.h"
#include <windows.h>

SoundMpeg::SoundMpeg()
	:Buffer(nullptr)
{

}

SoundMpeg::~SoundMpeg()
{
	if(Buffer) delete[] Buffer;
}

void SoundMpeg::Play()
{
	PlaySoundW((wchar_t*)FilePath.c_str(), nullptr, SND_RESOURCE);
}
