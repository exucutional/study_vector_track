Boolcell::Boolcell():
	index(0),
	data(0)
	{DEBUG(std::cout << "Boolcell ctor\n");}
Boolcell::Boolcell(uint i, uint8_t d):
	index(i),
	data(d)
{
	DEBUG(std::cout << "Boolcell ctor(index, data)\n");
	if (index > 8) {
		try {
			throw Mexcept(1, "Boolcell wrong index", __FILE__, __LINE__);
		}
		catch (const Mexcept& mxcpt) {
			std::cerr << "\nMy exception was caught, with message: "<< mxcpt;
		}
	}
}
Boolcell::~Boolcell()
	{DEBUG(std::cout << "Boolcell dtor\n");}
Boolcell& Boolcell::operator=(bool value)
{
	if (value)
		data |= (1 << index);
	else 
		data &= ~(1 << index);
	return *this;
}
Vector<bool>::Vector(int cap):
	data(nullptr),
	capacity(cap),
	size(0)
{
	DEBUG(std::cout << "Vector(capacity(" << capacity << ")) ctor\n");
	if (cap % 8 == 0)
		data = new Boolcell[cap / 8];
	else 
		data = new Boolcell[cap / 8 + 1];
}
Vector<bool>::Vector(Boolcell* dt, int cap, int sz):
	data(dt),
	capacity(cap),
	size(sz)
	{DEBUG(std::cout << "Vector(data, capacity(" << capacity << ") size(" << size << ")) ctor\n");}
Vector<bool>::Vector(const Vector<bool>& rhs)
{
	data = new Boolcell[rhs.capacity];
	memcpy(data, rhs.data, sizeof(Boolcell) * rhs.capacity);
	size = rhs.size;
	capacity = rhs.capacity;
	{DEBUG(std::cout << "Vector copy(capacity(" << capacity << "), size(" << size << ")) ctor\n");}
}
Vector<bool> Vector<bool>::copy(const Vector<bool>& rhs)
{
	auto tmpptr = new Boolcell[rhs.capacity];
	memcpy(tmpptr, rhs.data, sizeof(Boolcell) * rhs.capacity);
	return Vector<bool>(tmpptr, rhs.capacity, rhs.size);
}
Vector<bool>& Vector<bool>::operator=(const Vector<bool>& rhs)
{
	size = rhs.size;
	capacity = rhs.capacity;
	delete[] data;
	data = new Boolcell[rhs.capacity];
	memcpy(data, rhs.data, sizeof(Boolcell) * size);
	return *this;
}
Boolcell& Vector<bool>::at(int index)
{
	if (!(0 <= index && index <= size)) {
		try {
			throw Mexcept(1, "vector[] wrong index", __FILE__, __LINE__);
		}
		catch (const Mexcept& mxcpt) {
			std::cerr << "\nMy exception was caught, with message: "<< mxcpt;
		}
	}
	data[index / 8].index = 8;
	return data[index / 8];
}
bool Vector<bool>::operator[](int index)
{
	if (!(0 <= index && index <= size)) {
		try {
			throw Mexcept(1, "vector[] wrong index", __FILE__, __LINE__);
		}
		catch (const Mexcept& mxcpt) {
			std::cerr << "\nMy exception was caught, with message: "<< mxcpt;
		}
	}
	return data[index / 8].data & (1 << index);
}
void Vector<bool>::push_back(bool val) 
{
	if (++size % 8 == 0) {
		data[size / 8 - 1].index = 7;
		data[size / 8 - 1] = val;
	}
	else { 
		data[size / 8].index = size % 8 - 1;
		data[size / 8] = val;
	}
}
bool Vector<bool>::pop_back() 
{
	if (size <= 0) {
		try {
			throw Mexcept(1, "vector pop_back wrong size", __FILE__, __LINE__);
		}
		catch (const Mexcept& mxcpt) {
			std::cerr << "\nMy exception was caught, with message: "<< mxcpt;
		}
	}
	int sz = size;
	size--;
	if (sz % 8 == 0)
		return data[sz / 8 - 1].data & (1 << size);
	else
		return data[sz / 8].data & (1 << size);
}