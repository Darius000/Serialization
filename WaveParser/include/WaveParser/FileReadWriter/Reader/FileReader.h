#pragma once

#include "ReadMode.h"
#include <string>
#include <fstream>


class FileReader
{
public:
	FileReader();
	FileReader(const wchar_t* file, ReadMode mode = ReadMode::None);
	bool Open(const wchar_t* file, ReadMode mode = ReadMode::None);
	void Close();

	template<typename Type>
	void Read(Type& out, long long size);

	template<typename Type>
	void Read(Type* out, long long size);

	//return to beginning of file stream
	void Begin();

	const wchar_t* GetFilePath() { return path; }

public:
	long GetFileSize() const { return fileSize; }

private:
	void CalculateFileSize();

private:
	std::fstream stream;
	long fileSize;
	const wchar_t* path;
};

template<typename Type>
inline void FileReader::Read(Type& out, long long size)
{
	stream.read((char*)&out, size);
}

template<>
inline void FileReader::Read(std::string& out, long long size)
{
	out.resize(size);
	stream.read((char*)out.c_str(), size);
}

template<typename Type>
void FileReader::Read(Type* out, long long size)
{
	stream.read((char*)out, size);
}


