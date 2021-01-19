#pragma once


template<long FROM,  long TO>
class Iterator
{
	long num = FROM;

public:
	Iterator(long _num = 0) : num(_num){}
	Iterator& operator++(){ num = TO >= FROM ? num + 1: num - 1; return *this; }
	Iterator operator++(int) { Iterator retval = *this; ++(*this); return retval; }
	bool operator==(Iterator other) const { return num == other.num; }
	bool operator !=(Iterator other) const {  return !(*this == other); }
	long operator*(){ return &num; }
	long operator->(){ return num; }

	using difference_type = long;
	using value_type = long;
	using pointer = const long*;
	using reference = const long&;
	using iterator_category = std::forward_iterator_tag;
};