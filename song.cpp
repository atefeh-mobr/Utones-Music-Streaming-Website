#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include "song.hpp"
#include "empty_error.hpp"

const std::string LIKES        = "#likes: ";
const std::string COMMENTS     = "#comments: ";
const std::string PLAYLISTS    = "#playlists: ";
const std::string SPACE        = " ";
const std::string COLON        = ":";
const std::string EMPTY_STRING = "";

const int ZERO = 0;

Song::Song(std::string _id, std::string _title, std::string _artist, std::string _release_year, std::string _link) {
	id = stoi(_id);
	title = _title;
	artist = _artist;
	release_year = std::stoi(_release_year);
	link = _link;
	num_of_likes = ZERO;
	num_of_comments = ZERO;
	num_of_playlists = ZERO;
}

int Song::getID() {
	return id;
}

int Song::getReleaseYear() {
	return release_year;
}
std::string Song::getTitle() {
	return title;
}
std::string Song::getArtist() {
	return artist;
}

std::string Song::getLink() {
	return link;
}

bool Song::isEqualArtist(std::string _artist) {
	if(artist == _artist)
		return true;
	return false;
}

bool Song::isInPeriod(int minYear, int maxYear) {
	if(release_year > maxYear || release_year < minYear)
		return false;
	return true;
}

bool Song::isEqualLike(int _minLike, int _maxLike) {
	if(num_of_likes > _maxLike || num_of_likes < _minLike)
		return false;
	return true;
}

std::string Song::toStringWithExtraInformation() {
	std::ostringstream os;
	//os << id << std::endl << title << std::endl << artist << std::endl << release_year << std::endl << link << std::endl << LIKES << num_of_likes << std::endl << COMMENTS << num_of_comments << std::endl << PLAYLISTS << num_of_playlists << std::endl;
	os << title << std::endl << artist << std::endl << release_year << std::endl << link << std::endl << num_of_likes << std::endl << num_of_playlists << std::endl;
	return os.str();
}

std::string Song::mainToString() {
	std::ostringstream os;
	os << id << std::endl << title << std::endl << artist << std::endl << release_year << std::endl;
	return os.str();
}

std::string Song::toString() {
	return idToString() + detailsToString();
}

std::string Song::idToString() {
	std::ostringstream os;
	os << id << SPACE;
	return os.str();
}

std::string Song::detailsToString() {
	std::ostringstream os;
	os << title << SPACE << artist << SPACE << release_year << std::endl;
	return os.str();
}

void Song::applyLike() {
	num_of_likes ++;
}

void Song::undoLike() {
	num_of_likes --;
}

void Song::addComment(std::string username, int time, std::string comment) {
	std::pair<int, std::string> timeAndUser;
	CommentInformation commentInformation;
	timeAndUser.first = time;
	timeAndUser.second = username;
	commentInformation.first = timeAndUser;
	commentInformation.second = comment;
	commentsInformation.push_back(commentInformation);
	num_of_comments ++;
}

std::string Song::commentsToString() {
	std::string information = EMPTY_STRING;
	EmptyError empty_error;
	if(commentsInformation.size() == ZERO)
		throw empty_error;
	std::sort(commentsInformation.begin(), commentsInformation.end());
	for(int i = ZERO; i < commentsInformation.size(); i++)
		information += commentToString(i);
	return information;
}

std::string Song::commentToString(int index) {
	std::ostringstream os;
	os << commentsInformation[index].first.first << SPACE << commentsInformation[index].first.second << COLON << SPACE << commentsInformation[index].second << std::endl;
	return os.str();
}

void Song::addNumberOfPlaylists() {
	num_of_playlists ++;
}

void Song::discountNumberOfPlaylists() {
	num_of_playlists --;
}
