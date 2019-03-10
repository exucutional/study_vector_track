/*!
 * \brief unit_test.cpp
 * \version 0.5
 */
#include <iostream>
#include "mvector.hpp"

int main()
{
	Vector<int>* arr1 = new(__FILE__, __LINE__) Vector<int>(5);
	std::cin  >> *arr1;
	std::cout << *arr1;
	Vector<int> arr2(5);
	Vector<int> arr3(5);
	std::cin >> arr2 >> arr3;
	*arr1 += arr2 + arr3;
	std::cout << *arr1;
	//delete(__FILE__, __LINE__) arr1;
	arr1->operator delete(arr1, __FILE__, __LINE__);
	return EXIT_SUCCESS;
}
