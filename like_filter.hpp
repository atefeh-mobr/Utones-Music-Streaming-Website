#ifndef LIKEFILTER_H
#define LIKEFILTER_H

#include <iostream>
#include "filter.hpp"

class LikeFilter : public Filter {
public:
	LikeFilter(int _minLike, int _maxLike);
	virtual std::vector<Song*> filter(std::vector<Song*> songs);
private:
	int minLike;
	int maxLike;
};

#endif
