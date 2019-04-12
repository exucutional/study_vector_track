/*!
 * \brief mvector.hpp
 * \version 0.5
 */

#ifndef MVECTOR_HPP_
#define MVECTOR_HPP_

#define DEFLOG
#define DEFBUG

#ifdef DEFLOG
#define LOG(code) code
FILE* log = fopen("./logs/vecmemlogs.txt", "w");
#else
#define LOG(code)
#endif

#ifdef DEFBUG
#define DEBUG(code) code
#else
#define DEBUG(code)
#endif

#include <cstring>
#include <cassert>
#include "mexcpt.hpp"

template<typename T>
class Vector
{
	T* data;
	int capacity;
	int size;
public:
	Vector();
	Vector(int cap);
	Vector(T* dt, int cap, int sz);
	Vector(const Vector<T>& rhs);
	T& operator[](int index);
	Vector<T>& operator+=(const Vector<T>& rhs);
	Vector<T>& operator-=(const Vector<T>& rhs);
	Vector<T>& operator=(const Vector<T>& rhs);
	Vector<T>& operator=(Vector<T>&& rhs);
	Vector<T> copy(const Vector<T>& rhs);
	LOG(
	void* operator new(size_t size, const char* file, int line);
	void operator delete(void* mem, const char* file, int line);
	)
	void push_back(T val);
	void swap(Vector<T>& rhs);
	T pop_back();
	~Vector();
	friend Vector<T> operator+ (Vector<T> lhs, const Vector<T>& rhs)
	{
		if (lhs.size != rhs.size) {
			try {
				throw Mexcept(1, "vector - vector sizes error", __FILE__, __LINE__);
			}
			catch (const Mexcept& mxcpt) {
				std::cerr << "\nMy exception was caught, with message: "<< mxcpt;
			}
		}
		//assert(lhs.size == rhs.size);
		T* tmpptr = new T[lhs.size];
		for (int i = 0; i < lhs.size; i++)
			tmpptr[i] = lhs.data[i] + rhs.data[i];
		return Vector<T>(tmpptr, lhs.size, rhs.capacity);
	}
	friend const Vector<T> operator-(const Vector<T>& lhs, const Vector<T>& rhs)
	{
		if (lhs.size != rhs.size) {
			try {
				throw Mexcept(1, "vector - vector sizes error", __FILE__, __LINE__);
			}
			catch (const Mexcept& mxcpt) {
				std::cerr << "\nMy exception was caught, with message: "<< mxcpt;
			}
		}
		//assert(lhs.size == rhs.size);
		T* tmpptr = new T[lhs.size];
		for (int i = 0; i < lhs.size; i++)
			tmpptr[i] = lhs.data[i] - rhs.data[i];
		return Vector<T>(tmpptr, lhs.size, rhs.capacity);
	}
	friend std::ostream& operator <<(std::ostream &out, const Vector<T>& rhs)
	{
		if (!rhs.data) {
			try {
				throw Mexcept(1, "vector outout data nullptr", __FILE__, __LINE__);
			}
			catch (const Mexcept& mxcpt) {
				std::cerr << "\nMy exception was caught, with message: "<< mxcpt;
			}
		}
		out << "Vector of size " << rhs.size << std::endl;
		for (int i = 0; i < rhs.size; i++)
			out << "[" << i << "]: " << rhs.data[i] << std::endl;
		return out;
	}
	friend std::istream& operator >>(std::istream &in, Vector<T>& rhs)
	{
		if (!rhs.data) {
			try {
				throw Mexcept(1, "vector input data nullptr", __FILE__, __LINE__);
			}
			catch (const Mexcept& mxcpt) {
				std::cerr << "\nMy exception was caught, with message: "<< mxcpt;
			}
		}
		std::cout << "Enter vector of size " << rhs.capacity << std::endl;
		for (int i = 0; i < rhs.capacity; i++) {
			in >> rhs.data[i];
			rhs.size++;
		}
		return in;
	}
};

#include "mvectorbool.hpp"

#include "mvectorimplem.cpp"

#undef DEFLOG
#undef DEFBUG
#endif /* MVECTOR_HPP_ */
