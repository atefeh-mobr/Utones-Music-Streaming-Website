#ifndef ARTISTFILTER_H
#define ARTISTFILTER_H

#include <iostream>
#include "filter.hpp"

class ArtistFilter : public Filter {
public:
	ArtistFilter(std::string _artistName);
	virtual std::vector<Song*> filter(std::vector<Song*> songs);
private:
	std::string artistName;
};

#endif
