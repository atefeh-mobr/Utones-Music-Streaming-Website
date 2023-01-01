#ifndef APPLICATION_H
#define APPLICATION_H

#include <iostream>
#include <vector>
#include <string>
#include "song.hpp"
#include "user.hpp"

class Application {
public:
	Application();
	void saveSongs(std::vector<std::vector<std::string>> information);
	void saveLikedSongs(std::vector<std::vector<std::string>> information);
	void doPostOrders(std::string information);
	void doGetOrders(std::string information);
	void doDeleteOrders(std::string information);
	std::vector<Song*> getAllSongs();
	std::vector<Song*> showRecommendedSongs(const std::vector<std::string> information);
	std::string showAPlaylist(std::string playlistID);
	std::string showASongInformation(std::string songID);
	std::vector<std::string> showAllPlaylists();
	std::vector<std::string> showAllLikedSongs();
	std::vector<std::string> showAPlaylistSongs(std::string playlistID);
private:
	std::vector<Song*> songs;
	std::vector<User*> users;
	std::vector<std::string> usernames;
	std::vector<std::vector<int>> usersMatrix;
	std::vector<std::vector<double>> similarityMatrix;
	int numOfPlaylists;
	std::string currentFilter;
	User* currentUser;
	void logOut();
	void showSongs();
	void deleteFilters();
	void showLikedSongs();
	void showUsersNames();
	void findUsersAndSimilarityMatrix();
	void doLike(const std::string songID);
	void searchEmails(const std::string _email);
	void searchUsernames(const std::string _username);
	void logIn(const std::vector<std::string> information);
	void signUp(const std::vector<std::string> information);
	void likeSong(const std::vector<std::string> information);
	void addFilter(const std::vector<std::string> information);
	void addComment(const std::vector<std::string> information);
	void deleteALike(const std::vector<std::string> information);
	void addPlaylist(const std::vector<std::string> information);
	void showComments(const std::vector<std::string> information);
	void showSimilarUsers(const std::vector<std::string> information);
	void addSongToPlaylist(const std::vector<std::string> information);
	void showUserPlaylists(const std::vector<std::string> information);
	void showPlaylistsSongs(const std::vector<std::string> information);
	void showSongInformation(const std::vector<std::string> information);
	void deleteASongOfPlaylist(const std::vector<std::string> information);
	void saveUser(std::string _username, std::string _email, long long _password);
	void saveLikedSong(std::vector<std::string> likedSongInformation);
	std::string findArtistName(const std::vector<std::string> information);
	std::string checkOrderShowSong(const std::vector<std::string> information);
	std::string checkOrderShowPlaylist(const std::vector<std::string> information);
	std::string checkOrderShowComments(const std::vector<std::string> information);
	std::string checkOrderShowSimilarUsers(const std::vector<std::string> information);
	std::string checkOrderShowPlaylistsSongs(const std::vector<std::string> information);
	std::vector<std::string> extractInput(const std::string information);
	std::vector<std::string> checkOrderLogIn(const std::vector<std::string> information);
	std::vector<std::string> checkOrderSignUp(const std::vector<std::string> information);
	std::vector<std::string> checkOrderAddFilter(const std::vector<std::string> information);
	std::vector<std::string> checkOrderAddComment(const std::vector<std::string> information);
	std::vector<std::string> checkOrderAddPlaylist(const std::vector<std::string> information);
	std::vector<std::string> checkOrderAddSongToPlaylist(const std::vector<std::string> information);
	std::vector<std::vector<int>> findUsersMatrix();
	std::vector<std::vector<double>> findSimilarityMatrix();
	std::vector<std::pair<double, std::string>> assignSimilaritiesAndUsers(const std::vector<double> userSimilarityMatrix);
	Song* findSong(std::string _songID);
	User* findEmail(const std::string _email);
	User* findUser(const std::string _username);
	User* findOwnerOfPlaylist(const int playlistID);
	long long getHash(const std::string s); 
	bool isValidUser(const std::string _username);
	int findUserIndex(User* user);
	int findSimilarityOrRecommended(const std::vector<std::string> information);
};

#endif
