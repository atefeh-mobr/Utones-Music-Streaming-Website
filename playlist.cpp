#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include "playlist.hpp"
#include "song.hpp"
#include "empty_error.hpp"
#include "bad_request_error.hpp"

const std::string SPACE 		  = " ";
const std::string EMPTY_STRING = "";

const int ZERO = 0;

Playlist::Playlist(std::string _name, std::string _privacy, int _id) {
	name = _name;
	privacy = _privacy;
	id = _id;
}

std::string Playlist::toString() {
	std::ostringstream os;
	os << id << std::endl << name << std::endl << privacy << std::endl;
	return os.str();
}

std::string Playlist::getPrivacy() {
	return privacy;
}

int Playlist::getID() {
	return id;
}

void Playlist::addSong(Song* song) {
	songs.push_back(song);
	song->addNumberOfPlaylists();
}

std::string Playlist::songsToString() {
	std::string information = EMPTY_STRING;
	EmptyError empty_error;
	if(songs.size() == ZERO)
		throw empty_error;
	std::vector<Song*> sortedSongs = sortSongs();
	for(int i = ZERO; i < sortedSongs.size(); i++)
		information += sortedSongs[i]->toString();
	return information;
}

std::vector<int> Playlist::findIndexesOfSongs() {
	std::vector<int> songsIndexes;
	for(int i = ZERO; i < songs.size(); i++)
		songsIndexes.push_back(songs[i]->getID());
	return songsIndexes;
}

Song* Playlist::findSong(int _id) {
	Song* song;
	for(int i = ZERO; i < songs.size(); i++)
		if(songs[i]->getID() == _id)
			song = songs[i];
	return song;
}

std::vector<Song*> Playlist::sortSongs() {
	std::vector<Song*> sortedSongs;
	std::vector<int> songsIndexes = findIndexesOfSongs();
	std::sort(songsIndexes.begin(), songsIndexes.end());
	for(int i = ZERO; i < songsIndexes.size(); i++)
		sortedSongs.push_back(findSong(songsIndexes[i]));
	return sortedSongs;
}

void Playlist::deleteASong(Song* song) {
	BadRequestError bad_request;
	if(!hasThisSong(song))
		throw bad_request;
	removeASong(song);
	song->discountNumberOfPlaylists();
}

void Playlist::removeASong(Song* song) {
	for(int i = ZERO; i < songs.size(); i++)
		if(songs[i] == song)
			songs.erase(songs.begin() + i);
}

bool Playlist::hasThisSong(Song* song) {
	for(int i = ZERO; i < songs.size(); i++)
		if(songs[i] == song)
			return true;
	return false;
}

bool Playlist::isEqualTo(int playlistID) {
	if(id == playlistID)
		return true;
	return false;
}

std::vector<std::string> Playlist::showAllSongs() {
	std::vector<std::string> info;
	for(int i = ZERO; i < songs.size(); i++)
		info.push_back(songs[i]->mainToString());
	return info;
}
