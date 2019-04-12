template<typename T>
Vector<T>::Vector():
	data(nullptr),
	capacity(0),
	size(0)
	{DEBUG(std::cout << "Vector ctor\n");}
template<typename T>
Vector<T>::Vector(int cap):
	data(new T[cap]),
	capacity(cap),
	size(0)
	{DEBUG(std::cout << "Vector(capacity(" << cap << ")) ctor\n");}
template<typename T>
Vector<T>::Vector(T* dt, int cap, int sz):
	data(dt),
	capacity(cap),
	size(sz)
	{DEBUG(std::cout << "Vector (data, capacity(" << cap << "), size(" << sz << ")) ctor\n");}
template<typename T>
Vector<T>::Vector(const Vector<T>& rhs)
{
	data = new T[rhs.capacity];
	memcpy(data, rhs.data, sizeof(T) * rhs.capacity);
	size = rhs.size;
	capacity = rhs.capacity;
	{DEBUG(std::cout << "Vector copy(capacity(" << capacity << "), size(" << size << ")) ctor\n");}
}
template<typename T>
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
template<typename T>
Vector<T> Vector<T>::copy(const Vector<T>& rhs)
{
	T* tmpptr = new T[rhs.capacity];
	memcpy(tmpptr, rhs.data, sizeof(T) * rhs.capacity);
	return Vector<T>(tmpptr, rhs.capacity, rhs.size);
}
template<typename T>
T& Vector<T>::operator[](int index)
{
	if (!(0 <= index && index <= size)) {
		try {
			throw Mexcept(1, "vector[] wrong index", __FILE__, __LINE__);
		}	
		catch (const Mexcept& mxcpt) {
			std::cerr << "\nMy exception was caught, with message: "<< mxcpt;
		}
	}
	return data[index];
}
template<typename T>
Vector<T>& Vector<T>::operator+=(const Vector<T>& rhs)
{
	if (size != rhs.size) {
		try {
			throw Mexcept(1, "vector+= wrong size", __FILE__, __LINE__);
		}
		catch (const Mexcept& mxcpt) {
			std::cerr << "\nMy exception was caught, with message: "<< mxcpt;
		}
	}
	*this = *this + rhs;
	return *this;
}
template<typename T>
Vector<T>& Vector<T>::operator-=(const Vector<T>& rhs)
{
	if (size != rhs.size) {
		try {
			throw Mexcept(1, "vector-= wrong size", __FILE__, __LINE__);
		}
		catch (const Mexcept& mxcpt) {
			std::cerr << "\nMy exception was caught, with message: "<< mxcpt;
		}
	}
	*this = *this - rhs;
	return *this;
}
template<typename T>
Vector<T>& Vector<T>::operator=(const Vector<T>& rhs)
{
	size = rhs.size;
	capacity = rhs.capacity;
	delete[] data;
	data = new T[rhs.capacity];
	memcpy(data, rhs.data	, sizeof(T) * size);
	return *this;
}
template<typename T>
Vector<T>& Vector<T>::operator=(Vector<T>&& rhs)
{
	swap(rhs);
	return *this;
}
template<typename T>
void Vector<T>::push_back(T value)
{
	if (size < capacity) {
		data[size++] = value;
	}
	else {
		T* tmpptr = new T[capacity * 2];
		assert(tmpptr);
		for (int i = 0; i < capacity; i++) {
			tmpptr[i] = data[i];
		}
		delete[] data;
		data = tmpptr;
		capacity *= 2;
		data[size++] = value;
	}
}
template<typename T>
T Vector<T>::pop_back()
{
	if (size <= 0) {
		try {
			throw Mexcept(1, "vector pop_back wrong size", __FILE__, __LINE__);
		}
		catch (const Mexcept& mxcpt) {
			std::cerr << "\nMy exception was caught, with message: "<< mxcpt;
		}
	}
	return data[--size];
}
LOG(
template<typename T>
void* Vector<T>::operator new(size_t size, const char* file, int line)
{
	auto mem = static_cast<Vector<T>*>(calloc(1, sizeof(Vector<T>)));
	assert(log);
	fprintf(log,"new vector[%p] FILE:%s LINE:%d\n", mem, file, line);
	return mem;
}
template<typename T>
void Vector<T>::operator delete(void* mem, const char* file, int line)
{
	assert(log);
	fprintf(log,"delete	vector[%p] FILE:%s LINE:%d\n", mem, file, line);
	assert(mem);
	auto del = static_cast<Vector<T>*>(mem);;
	del->~Vector();
	free(del);
}
)
template<typename T>
Vector<T>::~Vector()
{
	delete[] data;
	data = nullptr;
	size = 0;
	DEBUG(std::cout << "Vector dtor\n");
}