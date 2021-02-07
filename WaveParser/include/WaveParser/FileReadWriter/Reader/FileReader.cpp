#include "FileReader.h"


FileReader::FileReader()
	:fileSize(0)
{

}

FileReader::FileReader(const wchar_t* file, ReadMode mode)
{
	Open(file, mode);
}

bool FileReader::Open(const wchar_t* file, ReadMode mode)
{
	stream.open(file, static_cast<int>(ReadMode::In | mode));

	if(!stream.is_open()) return false;

	CalculateFileSize();

	//no point in reading if file size is 0 bytes
	if(!fileSize) return false;

	path = file;

	return true;
}

void FileReader::Close()
{
	stream.close();
}

void FileReader::Begin()
{
	stream.seekg(0);
}

void FileReader::CalculateFileSize()
{
	//Find the file size to create the buffer
	long begin = (long)stream.tellg();
	stream.seekg(0, std::ios::end);
	long end = (long)stream.tellg();
	stream.seekg(0);

	fileSize = end - begin;
}
