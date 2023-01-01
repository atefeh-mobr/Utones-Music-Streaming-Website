#ifndef BADREQUESTERROR_H
#define BADREQUESTERROR_H

#include <iostream>
#include <exception>

#define BAD_REQUEST "Bad Request"

class BadRequestError : public std::exception {
public:
	virtual const char* what() const throw() {
		return BAD_REQUEST;
	}
};
#endif
