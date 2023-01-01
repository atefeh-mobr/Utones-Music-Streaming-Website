#ifndef PERMISSIONDENIEDERROR_H
#define PERMISSIONDENIEDERROR_H

#include <iostream>
#include <exception>

#define PERMISSION_DENIED "Permission Denied"

class PermissionDeniedError : public std::exception {
	virtual const char* what() const throw() {
		return PERMISSION_DENIED;
	}
};
#endif