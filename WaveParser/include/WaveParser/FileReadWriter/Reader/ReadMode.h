#pragma once

enum class ReadMode
{
	None = 0,
	In = 1,
	Out = 2,
	Binary = 0x20,
	Ate = 4,
	App = 8,
	Trunc = 16
};

inline ReadMode operator |(ReadMode a,ReadMode b) { return static_cast<ReadMode>(static_cast<int>(a) | static_cast<int>(b)); }; 
inline ReadMode operator &(const ReadMode& a, const ReadMode& b) { return static_cast<ReadMode>(static_cast<int>(a) & static_cast<int>(b)); }; 
inline ReadMode& operator |=(ReadMode& a,ReadMode b) { return a = a | b; }; 
inline bool HasFlag(const ReadMode& a, const ReadMode& b) { return (a & b) == b; }