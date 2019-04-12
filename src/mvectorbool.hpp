#ifndef MVECTOR_BOOL_HPP_
#define MVECTOR_BOOL_HPP_
class Boolcell
{
public:
	uint index;
	uint8_t data;
	Boolcell();
	Boolcell(uint index, uint8_t data);
	Boolcell& operator=(bool value);
	Boolcell& operator=(const Boolcell& rhs)
	{
		bool value = rhs.data & (1 << rhs.index);
		if (value)
			data |= (1 << index);
		else 
			data -= (1 << index);
		return *this;
	}
	~Boolcell();	
};

template <>
class Vector<bool>
{
	Boolcell* data;
	int capacity;
	int size;
public:
	Vector();
	Vector(int cap);
	Vector(Boolcell* dt, int cap, int sz);
	Vector(const Vector<bool>& rhs);
	bool operator[](int index);
	Boolcell& at(int index);
	Vector<bool> copy(const Vector<bool>& rhs);
	Vector<bool>& operator=(const Vector<bool>& rhs);
	void push_back(bool val);
	bool pop_back();
};

#include "mvectorboolimplem.cpp"
#endif