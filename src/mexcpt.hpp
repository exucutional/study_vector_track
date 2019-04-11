/*
 * mexcpt.hpp
 *
 *  Created on: 20 Mar 2019
 *      Author: exucutional
 */

#ifndef MEXCPT_HPP_
#define MEXCPT_HPP_

#include <iostream>

#define DEFBUG

#ifdef DEFBUG
#define DEBUG(code) code
#else
#define DEBUG(code)
#endif

class Mexcept
{
	int errnumber;
	const char* reason;
	const char* file;
	int line;
	const class Mexpect* parent;
public:
	Mexcept(int errnum, const char* rson, const char* fle, int lne,  const Mexpect* par);
	~Mexcept();
	friend std::ostream& operator <<(std::ostream &out, const Mexcept& rhs);
};

Mexcept::Mexcept(int errnum, const char* rson, const char* fle, int lne, const Mexpect* par = nullptr):
	errnumber(errnum),
	reason(rson),
	file(fle),
	line(lne),
	parent(par)
	{DEBUG(std::cout << "Mexcept ctor");}

std::ostream& operator <<(std::ostream &out, const Mexcept& rhs)
{
	out << rhs.reason;
	out << "\nFILE: " << rhs.file << "\nLINE: " << rhs.line << std::endl;
	if (rhs.parent)
		out << " because\n" << rhs.parent;
	return out;
}


Mexcept::~Mexcept()
	{DEBUG(std::cout << "Mexcept dtor");}

#endif /* MEXCPT_HPP_ */
