#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <iostream>
#include <vector>
#include "song.hpp"

class Playlist {
public:
	Playlist(std::string _name, std::string _privacy, int _id);
	std::string toString();
	std::string getPrivacy();
	std::string songsToString();
	int getID();
	void addSong(Song* song);
	void deleteASong(Song* song);
	bool isEqualTo(int playlistID);
	std::vector<std::string> showAllSongs();
private:
	int id;
	std::string name;
	std::string privacy;
	std::vector<Song*> songs;
	void removeASong(Song* song);
	bool hasThisSong(Song* song);
	std::vector<Song*> sortSongs();
	std::vector<int> findIndexesOfSongs();
	Song* findSong(int _id);
};

#endif
