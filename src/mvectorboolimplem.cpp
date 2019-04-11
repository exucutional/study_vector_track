template<>
Vector<bool>::Vector(int cap):
	data(nullptr),
	capacity(cap),
	size(0)
{
	DEBUG(std::cout << "Vector(capacity(" << cap << ")) ctor\n");
	if (cap % 8 == 0)
		data = reinterpret_cast<bool*>(new uint8_t[cap / 8 - 1]);
	else 
		data = reinterpret_cast<bool*>(new uint8_t[cap / 8 + 1]);
}