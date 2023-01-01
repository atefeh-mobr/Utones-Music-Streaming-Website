#ifndef FILTER_H
#define FILTER_H

#include <iostream>
#include <string>
#include <vector>
#include "song.hpp"

class Filter {
public:
	Filter();
	virtual std::vector<Song*> filter(std::vector<Song*> songs) = 0;
protected:
};

#endif
