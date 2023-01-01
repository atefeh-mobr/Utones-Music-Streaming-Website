#ifndef USER_H
#define USER_H

#include <iostream>
#include <vector>
#include <string>
#include "song.hpp"
#include "playlist.hpp"
#include "filter.hpp"

class User {
public:
	User(std::string _username, std::string _email, long long _password, std::vector<Song*> _songs);
	void logout();
	void like(Song* song);
	void showLikedSongs();
	void unlike(Song* song);
	void deleteFilters();
	void addYearFilter(int minYear, int maxYear);
	void addLikeFilter(int minLike, int maxLike);
	void addArtistFilter(std::string artistName);
	void login(long long _password);
	void deleteASongOfPlaylist(int playlistID, Song* song);
	void addSongToPlaylist(std::string playlistID, Song* song);
	void addPlaylist(std::string _name, std::string _privacy, int _id);
	void addFilter(std::vector<std::string> finalInformation, std::string currentFilter);
	std::string getEmail();
	std::string getUsername();
	std::string allPlaylistsToString();
	std::string publicPlaylistsToString();
	std::string showPlaylistsSongs(int playlistID);
	std::string showAPlaylist(std::string playlistID);
	std::string showPublicPlaylistsSongs(int playlistID);
	std::string similarUsersToString(const int count, const std::vector<std::pair<double, std::string>> usersAndSimilarities);
	std::vector<Song*> getSongs();
	std::vector<Song*> showRecommendedSongs(const int userIndex, int count, const std::vector<std::vector<int>> &userMatrix, const std::vector<double> &userSimilarityMatrix);
	std::vector<int> fillLikedSongsInformation();
	std::vector<std::string> showAllLikedSongs();
	std::vector<std::string> showPlaylistSongs(int playlistID);
	std::vector<std::string> playlistsToString();
	std::vector<std::vector<double>> findSimilarities(const std::vector<std::vector<int>> usersMatrix, std::vector<std::vector<double>> &similarityMatrix, int i);
	bool isValidFilter();
	bool hasThisPlaylist(int playlistID);
private:
	std::string username;
	std::string email;
	long long password;
	std::vector<Filter*> filters;
	std::vector<Song*> likedSongs;
	std::vector<Song*> songs;
	std::vector<Song*> filteredSongs;
	std::vector<Playlist*> playlists;
	int indexOfYearFilter;
	int indexOfLikeFilter;
	int indexOfArtistFilter;
	int numberOfFilters;
	bool isLogin;
	void addFilter(Filter* filter);
	void removeALikedSong(Song* song);
	void checkPassword(long long _password);
	bool isLikeOrNot(Song* song);
	double findSimiarity(const std::vector<int> firstUserMatrix, const std::vector<int> secondUserMatrix);
	double findConfidenceFactor(const int songID, const std::vector<std::vector<int>> &userMatrix, const std::vector<double> &userSimilarityMatrix);
	std::vector<Song*> sortLikedSongs();
	std::vector<int> findIndexesOfSongs();
	std::vector<Playlist*> findPublicPlaylists();
	std::vector<std::pair<double, std::string>> sortSimilarities(const std::vector<std::pair<double, std::string>> &usersAndSimilarities);
	std::vector<std::pair<double, Song*>> findRecommendedSongs(const int userIndex, const std::vector<std::vector<int>> &userMatrix, const std::vector<double> &userSimilarityMatrix);
	std::string recommendPairToString(std::pair<double, Song*> userRecommendPair);
	std::string similarityPairToString(std::pair<double, std::string> userSimilarityPair);
	Song* findLikedSong(int _id);
	Song* findSong(const int songID);
	Playlist* findAPlaylist(int playlistID);
};

#endif
