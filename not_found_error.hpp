#ifndef NOTFOUNDERROR_H
#define NOTFOUNDERROR_H

#include <iostream>
#include <exception>

#define NOT_FOUND "Not Found"

class NotFoundError : public std::exception {
	virtual const char* what() const throw() {
		return NOT_FOUND;
	}
}not_found;

#endif