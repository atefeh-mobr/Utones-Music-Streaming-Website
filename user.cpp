#include <iostream>
#include <string>
#include <algorithm>
#include <sstream>
#include <iomanip>
#include "user.hpp"
#include "song.hpp"
#include "playlist.hpp"
#include "filter.hpp"
#include "artist_filter.hpp"
#include "year_filter.hpp"
#include "like_filter.hpp"
#include "bad_request_error.hpp"
#include "empty_error.hpp"
#include "permission_denied_error.hpp"

const std::string PUBLIC 		   = "public";
const std::string PRIVATE 		   = "private";
const std::string PERCENT_SIGN	   = "%";
const std::string SPACE			   = " ";

const int INVALID = -1;
const int VALID   = 1;
const int ZERO    = ZERO;
const int PRECESION_VALUE = 2; 
const double PERCENT = 100;

User::User(std::string _username, std::string _email, long long _password, std::vector<Song*> _songs) {
	username = _username;
	email = _email;
	password = _password;
	isLogin = true;
	indexOfYearFilter = INVALID;
	indexOfLikeFilter = INVALID;
	indexOfArtistFilter = INVALID;
	filteredSongs = _songs;
	songs = _songs;
}

std::string User::getEmail() {
	return email;
}

std::string User::getUsername() {
	return username;
}

void User::checkPassword(long long _password) {
	BadRequestError bad_request;
	if(_password != password)
		throw bad_request;
}

void User::login(long long _password) {
	checkPassword(_password);
	isLogin = true;
}

void User::logout() {
	isLogin = false;
	deleteFilters();
}

bool User::isLikeOrNot(Song* song) {
	for(int i = ZERO; i < likedSongs.size(); i++) {
		if(song == likedSongs[i])
			return true;
	}
	return false;
}

void User::like(Song* song) {
	BadRequestError bad_request;
	if(isLikeOrNot(song))
		throw bad_request;
	likedSongs.push_back(song);
	song->applyLike();
}

void User::removeALikedSong(Song* song) {
	for(int i = ZERO; i < likedSongs.size(); i++)
		if(likedSongs[i] == song)
			likedSongs.erase(likedSongs.begin() + i);
}

void User::unlike(Song* song) {
	BadRequestError bad_request;
	if(!isLikeOrNot(song))
		throw bad_request;
	removeALikedSong(song);
	song->undoLike();
}

std::vector<int> User::findIndexesOfSongs() {
	std::vector<int> songsIndexes;
	for(int i = ZERO; i < likedSongs.size(); i++)
		songsIndexes.push_back(likedSongs[i]->getID());
	return songsIndexes;
}

Song* User::findLikedSong(int _id) {
	Song* song;
	for(int i = ZERO; i < likedSongs.size(); i++)
		if(likedSongs[i]->getID() == _id)
			song = likedSongs[i];
	return song;
}

std::vector<Song*> User::sortLikedSongs() {
	std::vector<Song*> sortedSongs;
	std::vector<int> songsIndexes = findIndexesOfSongs();
	std::sort(songsIndexes.begin(), songsIndexes.end());
	for(int i = ZERO; i < songsIndexes.size(); i++)
		sortedSongs.push_back(findLikedSong(songsIndexes[i]));
	return sortedSongs;
}

void User::showLikedSongs() {
	EmptyError empty_error;
	if(likedSongs.size() == ZERO)
		throw empty_error;
	std::vector<Song*> sortedSongs = sortLikedSongs();
	for(int i = ZERO; i < sortedSongs.size(); i++)
		std::cout << sortedSongs[i]->toString();
}

std::vector<std::string> User::showAllLikedSongs() {
	EmptyError empty_error;
	std::vector<std::string> info;
	if(likedSongs.size() == ZERO)
		throw empty_error;
	std::vector<Song*> sortedSongs = sortLikedSongs();
	for(int i = ZERO; i < sortedSongs.size(); i++)
		info.push_back(sortedSongs[i]->mainToString());
	return info;
}



void User::addPlaylist(std::string _name, std::string _privacy, int _id) {
	Playlist *playlist = new Playlist(_name, _privacy, _id);
	playlists.push_back(playlist);
}

std::string User::allPlaylistsToString() {
	std::string information = "";
	EmptyError empty_error;
	if(playlists.size() == ZERO)
		throw empty_error;
	for(int i = ZERO; i < playlists.size(); i++)
		information += playlists[i]->toString();
	return information;
}

std::vector<std::string> User::playlistsToString() {
	std::string information = "";
	EmptyError empty_error;
	std::vector<std::string> allInformation;
	if(playlists.size() == ZERO)
		throw empty_error;
	for(int i = ZERO; i < playlists.size(); i++)
		allInformation.push_back(playlists[i]->toString());
	return allInformation;
}

std::string User::publicPlaylistsToString() {
	std::string information = "";
	EmptyError empty_error;
	std::vector<Playlist*> publicPlaylists = findPublicPlaylists();
	if(publicPlaylists.size() == ZERO)
		throw empty_error;
	for(int i = ZERO; i < publicPlaylists.size(); i++)
		information += publicPlaylists[i]->toString();
	return information;
}

std::string User::showAPlaylist(std::string playlistID) {
	std::string information;
	for(int i = ZERO; i < playlists.size(); i++)
		if(playlists[i]->isEqualTo(std::stoi(playlistID)))
			information = playlists[i]->toString();
	return information;
}

std::vector<Playlist*> User::findPublicPlaylists() {
	std::vector<Playlist*> publicPlaylists;
	for(int i = ZERO; i < playlists.size(); i++)
		if(playlists[i]->getPrivacy() == PUBLIC)
			publicPlaylists.push_back(playlists[i]);
	return publicPlaylists;
}

void User::addSongToPlaylist(std::string playlistID, Song* song) {
	Playlist* playlist = findAPlaylist(stoi(playlistID));
	playlist->addSong(song);
}

Playlist* User::findAPlaylist(int playlistID) {
	PermissionDeniedError permission_denied;
	for(int i = ZERO; i < playlists.size(); i++)
		if(playlists[i]->getID() == playlistID)
			return playlists[i];
	throw permission_denied;
}

bool User::hasThisPlaylist(int playlistID) {
	for(int i = ZERO; i < playlists.size(); i++)
		if(playlists[i]->getID() == playlistID)
			return true;
	return false;
}

std::string User::showPlaylistsSongs(int playlistID) {
	Playlist* playlist = findAPlaylist(playlistID);
	return playlist->songsToString();
}

std::vector<std::string> User::showPlaylistSongs(int playlistID) {
	Playlist* playlist = findAPlaylist(playlistID);
	return playlist->showAllSongs();
}

std::string User::showPublicPlaylistsSongs(int playlistID) {
	PermissionDeniedError permission_denied;
	Playlist* playlist = findAPlaylist(playlistID);
	if(playlist->getPrivacy() == PRIVATE)
		throw permission_denied;
	return playlist->songsToString();
}

void User::deleteASongOfPlaylist(int playlistID, Song* song) {
	Playlist* playlist = findAPlaylist(playlistID);
	playlist->deleteASong(song);
}

void User::addArtistFilter(std::string artistName) {
	if(indexOfArtistFilter != INVALID)
		filters.erase(filters.begin() + indexOfArtistFilter);
	ArtistFilter *artistFilter = new ArtistFilter(artistName);
	numberOfFilters ++;
	indexOfArtistFilter = filters.size();
	addFilter(artistFilter);
}

void User::addLikeFilter(int minLike, int maxLike) {
	if(indexOfLikeFilter != INVALID)
		filters.erase(filters.begin() + indexOfLikeFilter);
	LikeFilter *likeFilter = new LikeFilter(minLike, maxLike);
	numberOfFilters++;
	indexOfLikeFilter = filters.size();
	addFilter(likeFilter);
}

void User::addYearFilter(int minYear, int maxYear) {
	if(indexOfYearFilter != INVALID)
		filters.erase(filters.begin() + indexOfYearFilter);
	YearFilter *yearFilter = new YearFilter(minYear, maxYear);
	numberOfFilters ++;
	indexOfYearFilter = filters.size();
	addFilter(yearFilter);
}

void User::addFilter(Filter* filter) {
	filters.push_back(filter);
	filteredSongs.clear();
	filteredSongs = filter->filter(songs);
	for(int i = 0; i < filters.size() - 1; i++)
		filteredSongs = filters[i]->filter(filteredSongs);
}

void User::deleteFilters() {
	filters.clear();
	indexOfYearFilter = INVALID;
	indexOfLikeFilter = INVALID;
	indexOfArtistFilter = INVALID;
	numberOfFilters = ZERO;
}

bool User::isValidFilter() {
	if(numberOfFilters == ZERO)
		return false;
	return true;
}

std::vector<Song*> User::getSongs() {
	EmptyError empty_error;
	if(filteredSongs.size() == ZERO)
		throw empty_error;
	return filteredSongs;
}

std::vector<int> User::fillLikedSongsInformation() {
	std::vector<int> information(songs.size(), ZERO);
	for(int i = 0; i < songs.size(); i++)
		for(int j = 0; j < likedSongs.size(); j++)
			if(likedSongs[j] == songs[i])
				information[i] = VALID;
	return information;
}

std::vector<std::vector<double>> User::findSimilarities(const std::vector<std::vector<int>> usersMatrix, std::vector<std::vector<double>> &sampleSimilarityMatrix, int index) {
	for(int i = 0; i < sampleSimilarityMatrix.size(); i++) {
		if(i != index && sampleSimilarityMatrix[index][i] == INVALID && sampleSimilarityMatrix[i][index] == INVALID) {
			double similarityRate = findSimiarity(usersMatrix[index], usersMatrix[i]);
			sampleSimilarityMatrix[index][i] = similarityRate;
			sampleSimilarityMatrix[i][index] = similarityRate;
		}
	}
	return sampleSimilarityMatrix;
}

double User::findSimiarity(const std::vector<int> firstUserMatrix, const std::vector<int> secondUserMatrix) {
	int numberOfSharedSongs = 0;
	for(int i = 0; i < firstUserMatrix.size(); i++)
		if(firstUserMatrix[i] == VALID && secondUserMatrix[i] == VALID)
			numberOfSharedSongs++; 
	return (double)numberOfSharedSongs / (double)songs.size();
}

std::string User::similarUsersToString(const int count, const std::vector<std::pair<double, std::string>> usersAndSimilarities) {
	std::string information = "";
	std::vector<std::pair<double, std::string>> sortedSimilarities = sortSimilarities(usersAndSimilarities);
	for(int i = ZERO; i < count; i++)
		information += similarityPairToString(sortedSimilarities[i]);
	return information;
}

std::vector<std::pair<double, std::string>> User::sortSimilarities(const std::vector<std::pair<double, std::string>> &usersAndSimilarities) {
	std::vector<std::pair<double, std::string>> sortedSimilarities(usersAndSimilarities.begin(), usersAndSimilarities.end());
	std::sort(sortedSimilarities.rbegin(), sortedSimilarities.rend());
	for(int i = 0; i < sortedSimilarities.size(); i++)
		for(int j = i + 1; j < sortedSimilarities.size(); j++)
			if(sortedSimilarities[i].first == sortedSimilarities[j].first && sortedSimilarities[i].second > sortedSimilarities[j].second)
				std::swap(sortedSimilarities[i], sortedSimilarities[j]);
	return sortedSimilarities;
}

std::string User::similarityPairToString(std::pair<double, std::string> userSimilarityPair) {
	std::ostringstream os;
	double percent = userSimilarityPair.first * PERCENT;
	os << std::fixed << std::setprecision(PRECESION_VALUE) << percent << PERCENT_SIGN << SPACE << userSimilarityPair.second << std::endl;
	return os.str();
}

std::vector<Song*> User::showRecommendedSongs(const int userIndex, int count, const std::vector<std::vector<int>> &userMatrix, const std::vector<double> &userSimilarityMatrix) {
	std::vector<Song*> recomSongs;
	std::vector<std::string> information;
	std::vector<std::pair<double, Song*>> assignedConfidencesAndSongs = findRecommendedSongs(userIndex, userMatrix, userSimilarityMatrix);
	std::sort(assignedConfidencesAndSongs.rbegin(), assignedConfidencesAndSongs.rend());
	if(count > songs.size() - likedSongs.size())
		count = songs.size() - likedSongs.size();
	for(int i = ZERO; i < count; i++)
		recomSongs.push_back(assignedConfidencesAndSongs[i].second);
	return recomSongs;
}

std::string User::recommendPairToString(std::pair<double, Song*> userRecommendPair) {
	std::ostringstream os;
	double percent = userRecommendPair.first * PERCENT;
	os << userRecommendPair.second->idToString() << std::fixed << std::setprecision(PRECESION_VALUE) << percent << PERCENT_SIGN << SPACE << userRecommendPair.second->detailsToString();
	return os.str();
}

std::vector<std::pair<double, Song*>> User::findRecommendedSongs(const int userIndex, const std::vector<std::vector<int>> &userMatrix, const std::vector<double> &userSimilarityMatrix) {
	std::vector<std::pair<double, Song*>> assignedConfidencesAndSongs;
	for(int i = 0; i < songs.size(); i++)
		if(userMatrix[userIndex][i] == ZERO) {
			double confidence = findConfidenceFactor(i, userMatrix, userSimilarityMatrix);
			assignedConfidencesAndSongs.push_back({confidence, findSong(i + 1)});
		}
	return assignedConfidencesAndSongs;
}

double User::findConfidenceFactor(const int songID, const std::vector<std::vector<int>> &userMatrix, const std::vector<double> &userSimilarityMatrix) {
	double confidence = 0;
	for(int i = 0; i < userSimilarityMatrix.size(); i++)
		if(userSimilarityMatrix[i] != INVALID)
			confidence += (double)userSimilarityMatrix[i] * (double)userMatrix[i][songID];
	return (double)confidence / (double)(userSimilarityMatrix.size() - 1);
}

Song* User::findSong(const int songID) {
	Song* song;
	for(int i = ZERO; i < songs.size(); i++)
		if(songs[i]->getID() == songID)
			song = songs[i];
	return song;
}