#include <iostream>
#include "artist_filter.hpp"
#include "song.hpp"

ArtistFilter::ArtistFilter(std::string _artistName)
				: Filter() {
	artistName = _artistName;
}

std::vector<Song*> ArtistFilter::filter(std::vector<Song*> songs) {
	std::vector<Song*> filteredSongs;
	for(int i = 0; i < songs.size(); i++)
		if(songs[i]->isEqualArtist(artistName))
			filteredSongs.push_back(songs[i]);
	return filteredSongs;
}
