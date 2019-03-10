/*!
 * \brief mvector.hpp
 * \version 0.5
 */

#ifndef MVECTOR_HPP_
#define MVECTOR_HPP_

#define DEFLOG

#ifdef DEFLOG
#define LOG(code) code
FILE* log = fopen("logs/vecmemlogs.txt", "w");
#else
#define LOG(code)
#endif

#include <cstring>
#include <cassert>

template<class T>
class Vector
{
	T* data;
	int capacity;
	int size;
public:
	Vector();
	Vector(int cap);
	Vector(T* dt, int cap, int sz);
	T& operator[](int index);
	Vector<T>& operator+=(const Vector<T>& rhs);
	Vector<T>& operator-=(const Vector<T>& rhs);
	Vector<T>& operator=(const Vector<T>& rhs);
	Vector<T> copy(const Vector<T>& rhs);
	LOG(
	void* operator new(size_t size, const char* file, int line);
	void operator delete(void* mem, const char* file, int line);
	)
	void push_back(T val);
	void swap(Vector<T>& rhs);
	T pop_back();
	~Vector();
	friend const Vector<T> operator+(const Vector<T>& lhs, const Vector<T>& rhs)
	{
		assert(lhs.size == rhs.size);
		T* tmpptr = new T[lhs.size];
		for (int i = 0; i < lhs.size; i++)
			tmpptr[i] = lhs.data[i] + rhs.data[i];
		return Vector<T>(tmpptr, lhs.size, rhs.capacity);
	}
	friend const Vector<T> operator-(const Vector<T>& lhs, const Vector<T>& rhs)
		{
			assert(lhs.size == rhs.size);
			T* tmpptr = new T[lhs.size];
			for (int i = 0; i < lhs.size; i++)
				tmpptr[i] = lhs.data[i] - rhs.data[i];
			return Vector<T>(tmpptr, lhs.size, rhs.capacity);
		}
	friend std::ostream& operator <<(std::ostream &out, const Vector<T>& rhs)
	{
			assert(rhs.data);
			out << "Vector of size " << rhs.size << std::endl;
			for (int i = 0; i < rhs.size; i++)
				out << "[" << i << "]: " << rhs.data[i] << std::endl;
			return out;
	}
	friend std::istream& operator >>(std::istream &in, Vector<T>& rhs)
	{
		assert(rhs.data);
		std::cout << "Enter vector of size " << rhs.capacity << std::endl;
		for (int i = 0; i < rhs.capacity; i++) {
			in >> rhs.data[i];
			rhs.size++;
		}
		return in;
	}
};

template<class T>
Vector<T>::Vector():
	data(nullptr),
	capacity(0),
	size(0)
	{std::cout << "Vector ctor\n";}
template<class T>
Vector<T>::Vector(int cap):
	data(new int[cap]),
	capacity(cap),
	size(0)
	{std::cout << "Vector(capacity) ctor\n";}
template<class T>
Vector<T>::Vector(T* dt, int cap, int sz):
	data(dt),
	capacity(cap),
	size(sz)
	{std::cout << "Vector(data, capacity, size) ctor\n";}
template<class T>
void Vector<T>::swap(Vector<T>& rhs)
{
	int tmp = rhs.capacity;
	rhs.capacity = this->capacity;
	this->capacity = tmp;
	tmp = rhs.size;
	rhs.size = this->size;
	this->size = tmp;
	T* tmpptr = rhs.data;
	rhs.data = this->data;
	this->data = tmpptr;
}
template<class T>
Vector<T> Vector<T>::copy(const Vector<T>& rhs)
{
	T* tmpptr = new T[rhs.capacity];
	memcpy(tmpptr, rhs.data, sizeof(T) * rhs.capacity);
	return Vector<T>(tmpptr, rhs.capacity, rhs.size);
}
template<class T>
T& Vector<T>::operator[](int index)
{
	assert(0 <= index && index <= size);
	return data[index];
}
template<class T>
Vector<T>& Vector<T>::operator+=(const Vector<T>& rhs)
{
	assert(size == rhs.size);
	*this = *this + rhs;
	return *this;
}
template<class T>
Vector<T>& Vector<T>::operator-=(const Vector<T>& rhs)
{
	assert(size == rhs.size);
	*this = *this - rhs;
	return *this;
}
template<class T>
Vector<T>& Vector<T>::operator=(const Vector<T>& rhs)
{
	size = rhs.size;
	capacity = rhs.capacity;
	delete[] data;
	data = new T[rhs.capacity];
	memcpy(data, rhs.data, sizeof(T) * size);
	return *this;
}
template<class T>
void Vector<T>::push_back(T value)
{
	data[size++] = value;
}
template<class T>
T Vector<T>::pop_back()
{
	assert(size > 0);
	return data[--size];
}
template<class T>
void* Vector<T>::operator new(size_t size, const char* file, int line)
{
	auto mem = static_cast<Vector<T>*>(calloc(1, sizeof(Vector<T>)));
	assert(log);
	fprintf(log,"new vector[%p] FILE:%s LINE:%d\n", mem, file, line);
	return mem;
}
template<class T>
void Vector<T>::operator delete(void* mem, const char* file, int line)
{
	assert(log);
	fprintf(log,"delete	vector[%p] FILE:%s LINE:%d\n", mem, file, line);
	assert(mem);
	auto del = static_cast<Vector<T>*>(mem);;
	del->~Vector();
	free(del);
}

template<class T>
Vector<T>::~Vector()
{
	delete[] data;
	data = nullptr;
	size = 0;
	std::cout << "Vector dtor\n";
}

#undef DEFLOG
#endif /* MVECTOR_HPP_ */
