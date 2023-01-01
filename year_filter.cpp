#include <iostream>
#include "year_filter.hpp"
#include "song.hpp"
#include "bad_request_error.hpp"

const int ZERO = 0;

YearFilter::YearFilter(int _minYear, int _maxYear)
				: Filter() {
	BadRequestError bad_request;
	if(_minYear > _maxYear)
		throw bad_request;
	minYear = _minYear;
	maxYear = _maxYear;
}

std::vector<Song*>  YearFilter::filter(std::vector<Song*> songs) {
	std::vector<Song*> filteredSongs;
	for(int i = ZERO; i < songs.size(); i++)
		if(songs[i]->isInPeriod(minYear, maxYear))
			filteredSongs.push_back(songs[i]);
	return filteredSongs;
}
