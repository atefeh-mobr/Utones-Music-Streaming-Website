#ifndef YEARFILTER_H
#define YEARFILTER_H

#include <iostream>
#include "filter.hpp"

class YearFilter : public Filter {
public:
	YearFilter(int _minYear, int _maxYear);
	virtual std::vector<Song*> filter(std::vector<Song*> songs);
private:
	int minYear;
	int maxYear;
};

#endif
