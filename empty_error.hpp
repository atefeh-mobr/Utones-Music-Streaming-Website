#ifndef EMPTYERROR_H
#define EMPTYERROR_H

#include <iostream>
#include <exception>

#define EMPTY_ERROR "Empty"

class EmptyError : public std::exception {
	virtual const char* what() const throw() {
		return EMPTY_ERROR;
	}
};
#endif
