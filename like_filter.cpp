#include <iostream>
#include "like_filter.hpp"
#include "song.hpp"
#include "bad_request_error.hpp"

const int ZERO = 0;

LikeFilter::LikeFilter(int _minLike, int _maxLike)
				: Filter() {
	BadRequestError bad_request;
	if(_minLike < ZERO || _maxLike < ZERO || _maxLike < _minLike)
		throw bad_request;
	minLike = _minLike;
	maxLike = _maxLike;
}

std::vector<Song*> LikeFilter::filter(std::vector<Song*> songs) {
	std::vector<Song*> filteredSongs;
	for(int i = ZERO; i < songs.size(); i++)
		if(songs[i]->isEqualLike(minLike, maxLike))
			filteredSongs.push_back(songs[i]);
	return filteredSongs;
}
