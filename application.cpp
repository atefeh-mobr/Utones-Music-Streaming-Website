#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include "application.hpp"
#include "song.hpp"
#include "user.hpp"
#include "playlist.hpp"
#include "filter.hpp"
#include "artist_filter.hpp"
#include "year_filter.hpp"
#include "like_filter.hpp"
#include "bad_request_error.hpp"
#include "not_found_error.hpp"
#include "empty_error.hpp"
#include "permission_denied_error.hpp"

#define SIGNUP_INDEX			0
#define LOGIN_INDEX				0
#define LOGOUT_INDEX			0
#define QUESTION_MARK_INDEX 	0
#define EMAIL_INDEX         	1
#define USERNAME_INDEX      	3
#define PASSWORD_INDEX			5
#define SONGS_INDEX				0
#define ID_INDEX				1
#define LIKES_INDEX				0
#define PLAYLISTS_INDEX			0
#define NAME_INDEX				1
#define PRIVACY_INDEX			3
#define PRIVACY_SITUATION_INDEX 4
#define PLAYLISTS_SONGS_INDEX 	0
#define PLAYLIST_ID_INDEX		1
#define SONG_ID_INDEX			3
#define USERS_INDEX				0
#define FILTERS_INDEX			0
#define ARTIST_INDEX			1
#define MIN_YEAR_INDEX			1
#define MAX_YEAR_INDEX			3
#define MIN_LIKE_INDEX			1
#define MAX_LIKE_INDEX			3
#define COMMENTS_INDEX			0
#define TIME_INDEX				3
#define COMMENT_INDEX           5
#define CSV_ID_INDEX			0
#define CSV_TITLE_INDEX			1
#define CSV_ARTIST_INDEX		2
#define CSV_RELEASE_YEAR_INDEX  3
#define CSV_LINK_INDEX			4
#define SIMILAR_USERS_INDEX     0
#define COUNT_INDEX				1
#define RECOMMENDED_INDEX		0

const std::string OK 			  = "OK";
const std::string SIGN_UP 		  = "signup";
const std::string LOG_IN 		  = "login";
const std::string LOG_OUT 		  = "logout";
const std::string QUESTION_MARK   = "?";
const std::string EMAIL 		  = "email";
const std::string USERNAME 		  = "username";
const std::string PASSWORD 		  = "password";
const std::string SONGS 		  = "songs";
const std::string ID 			  = "id";
const std::string LIKES 		  = "likes";
const std::string PLAYLISTS 	  = "playlists";
const std::string NAME 			  = "name";
const std::string PRIVACY 		  = "privacy";
const std::string PRIVATE 		  = "private";
const std::string PUBLIC          = "public";
const std::string PLAYLISTS_SONGS = "playlists_songs";
const std::string PLAYLIST_ID     = "playlist_id";
const std::string SONG_ID         = "song_id";
const std::string USERS           = "users";
const std::string COMMENTS        = "comments";
const std::string TIME            = "time";
const std::string COMMENT         = "comment";
const std::string FILTERS         = "filters";
const std::string ARTIST          = "artist";
const std::string LIKE            = "like";
const std::string YEAR            = "year";
const std::string MIN_YEAR        = "min_year";
const std::string MAX_YEAR        = "max_year";
const std::string MIN_LIKE        = "min_like";
const std::string MAX_LIKE        = "max_like";
const std::string EMPTY_STRING	  = "";
const std::string SPACE			  = " ";
const std::string SIMILAR_USERS   = "similar_users";
const std::string COUNT 		  = "count";
const std::string RECOMMENDED     = "recommended";

const char CHARACTER_a = 'a';

const int ZERO  = 0;
const int ONE   = 1;
const int TWO   = 2;
const int THREE = 3;
const int FOUR  = 4;
const int FIVE  = 5;
const int SIX   = 6;
const int SEVEN = 7;
const int PERFORMANCE = 53;
const int MODE   = 1e9 + 9;
const int INVAlid 	  = -1; 


Application::Application() {
	currentUser = NULL;
	numOfPlaylists = ZERO;
	usernames.push_back(EMPTY_STRING);
}

void Application::saveSongs(std::vector<std::vector<std::string>> information) {
	for(int i = ZERO; i < information.size(); i++) {
		Song *song = new Song(information[i][CSV_ID_INDEX], information[i][CSV_TITLE_INDEX], information[i][CSV_ARTIST_INDEX], information[i][CSV_RELEASE_YEAR_INDEX], information[i][CSV_LINK_INDEX]);
		songs.push_back(song);
	}
}

void Application::saveLikedSongs(std::vector<std::vector<std::string>> information) {
	for(int i = ZERO; i < information.size(); i++)
		saveLikedSong(information[i]);
	currentUser = NULL;
}

void Application::saveLikedSong(std::vector<std::string> likedSongInformation) {
	std::string _username = likedSongInformation[ZERO], _email = likedSongInformation[ONE], _password = likedSongInformation[TWO], _likedSongID = likedSongInformation[THREE];
	if(isValidUser(_username))
		currentUser = findUser(_username);
	else
		saveUser(_username, _email, getHash(_password));
	doLike(_likedSongID);
}

bool Application::isValidUser(const std::string _username) {
	for(int i = ZERO; i < users.size(); i++)
		if(users[i]->getUsername() == _username)
			return true;
	return false;
}

void Application::doPostOrders(std::string information) {
	std::vector<std::string> newInformation = extractInput(information);
	if(newInformation[SIGNUP_INDEX] == SIGN_UP) {
		newInformation.erase(newInformation.begin());
		signUp(newInformation);
	}
	else if(newInformation[LOGIN_INDEX] == LOG_IN) {
		newInformation.erase(newInformation.begin());
		logIn(newInformation);
	}
	else if(newInformation[LOGOUT_INDEX] == LOG_OUT)
		logOut();
	else if(newInformation[LIKES_INDEX] == LIKES) {
		newInformation.erase(newInformation.begin());
		likeSong(newInformation);
	}
	else if(newInformation[PLAYLISTS_INDEX] == PLAYLISTS) {
		newInformation.erase(newInformation.begin());
		addPlaylist(newInformation);
	}
	else if(newInformation[PLAYLISTS_SONGS_INDEX] == PLAYLISTS_SONGS) {
		newInformation.erase(newInformation.begin());
		addSongToPlaylist(newInformation);
	}
	else if(newInformation[COMMENTS_INDEX] == COMMENTS) {
		newInformation.erase(newInformation.begin());
		addComment(newInformation);
	}
	else if(newInformation[FILTERS_INDEX] == FILTERS) {
		newInformation.erase(newInformation.begin());
		addFilter(newInformation);
	}
	else 
		throw not_found;
}

void Application::doGetOrders(std::string information) {
	PermissionDeniedError permission_denied;
	if(currentUser == NULL)
		throw permission_denied;
	std::vector<std::string> newInformation = extractInput(information);
	if(newInformation[SONGS_INDEX] == SONGS && newInformation.size() == ONE)
		showSongs();
	else if(newInformation[SONGS_INDEX] == SONGS) {
		newInformation.erase(newInformation.begin());
		showSongInformation(newInformation);
	}
	else if(newInformation[LIKES_INDEX] == LIKES)
		showLikedSongs();
	else if(newInformation[PLAYLISTS_INDEX] == PLAYLISTS) {
		newInformation.erase(newInformation.begin());
		showUserPlaylists(newInformation);
	}
	else if(newInformation[PLAYLISTS_SONGS_INDEX] == PLAYLISTS_SONGS) {
		newInformation.erase(newInformation.begin());
		showPlaylistsSongs(newInformation);
	}
	else if(newInformation[USERS_INDEX] == USERS)
		showUsersNames();
	else if(newInformation[COMMENTS_INDEX] == COMMENTS) {
		newInformation.erase(newInformation.begin());
		showComments(newInformation);
	}
	else if(newInformation[SIMILAR_USERS_INDEX] == SIMILAR_USERS) {
		newInformation.erase(newInformation.begin());
		showSimilarUsers(newInformation);
	}
	else if(newInformation[RECOMMENDED_INDEX] == RECOMMENDED) {
		newInformation.erase(newInformation.begin());
	}
	else 
		throw not_found;
}

void Application::doDeleteOrders(std::string information) {
	PermissionDeniedError permission_denied;
	if(currentUser == NULL)
		throw permission_denied;
	std::vector<std::string> newInformation = extractInput(information);
	if(newInformation[LIKES_INDEX] == LIKES) {
		newInformation.erase(newInformation.begin());
		deleteALike(newInformation);
	}
	else if(newInformation[PLAYLISTS_SONGS_INDEX] == PLAYLISTS_SONGS) {
		newInformation.erase(newInformation.begin());
		deleteASongOfPlaylist(newInformation);
	}
	else if(newInformation[FILTERS_INDEX] == FILTERS)
		deleteFilters();
	else 
		throw not_found;
}

void Application::showSongs() {
	std::vector<Song*> filteredSongs;
	if(!currentUser->isValidFilter())
		filteredSongs = songs;
	else
		filteredSongs = currentUser->getSongs();
	for(int i = ZERO; i < filteredSongs.size(); i++)
		std::cout << filteredSongs[i]->toString();
}

std::vector<Song*> Application::getAllSongs() {
	return songs;
}

void Application::signUp(const std::vector<std::string> information) {
	std::vector<std::string> newInformation = checkOrderSignUp(information);
	searchEmails(newInformation[ZERO]);
	searchUsernames(newInformation[ONE]);
	saveUser(newInformation[ONE], newInformation[ZERO], getHash(newInformation[TWO]));
	std::cout << OK << std::endl;
}

void Application::logIn(const std::vector<std::string> information) {
	std::vector<std::string> newInformation = checkOrderLogIn(information);
	User* user = findEmail(newInformation[ZERO]);
	user->login(getHash(newInformation[ONE]));
	currentUser = user;
	std::cout << OK << std::endl;
}

void Application::logOut() {
	PermissionDeniedError permission_denied;
	if(currentUser == NULL)
		throw permission_denied;
	currentUser->logout();
	currentUser = NULL;
	std::cout << OK << std::endl;
}

std::vector<std::string> Application::checkOrderSignUp(const std::vector<std::string> information) {
	std::vector<std::string> finalInformation;
	BadRequestError bad_request;
	if(information[QUESTION_MARK_INDEX] == QUESTION_MARK && information[EMAIL_INDEX] == EMAIL && information[USERNAME_INDEX] == USERNAME && information[PASSWORD_INDEX] == PASSWORD && information.size() == SEVEN) {
		finalInformation.push_back(information[TWO]);
		finalInformation.push_back(information[FOUR]);
		finalInformation.push_back(information[SIX]);
	}
	else
		throw bad_request;
	return finalInformation;
}

std::vector<std::string> Application::checkOrderLogIn(const std::vector<std::string> information) {
	std::vector<std::string> finalInformation;
	BadRequestError bad_request;
	if(information[QUESTION_MARK_INDEX] == QUESTION_MARK && information[EMAIL_INDEX] == EMAIL && information[THREE] == PASSWORD && information.size() == FIVE) {
		finalInformation.push_back(information[TWO]);
		finalInformation.push_back(information[FOUR]);
	}
	else
		throw bad_request;
	return finalInformation;
}

void Application::searchEmails(const std::string _email) {
	BadRequestError bad_request;
	for(int i = ZERO; i < users.size(); i++)
		if(users[i]->getEmail() == _email)
			throw bad_request;
}

void Application::searchUsernames(const std::string _username) {
	BadRequestError bad_request;
	for(int i = ZERO; i < users.size(); i++)
		if(users[i]->getUsername() == _username)
			throw bad_request;
}

User* Application::findEmail(const std::string _email) {
	BadRequestError bad_request;
	for(int i = ZERO; i < users.size(); i++)
		if(users[i]->getEmail() == _email)
			return users[i];
	throw bad_request;
}

std::vector<std::string> Application::extractInput(const std::string information) {
	std::string word;
	std::vector<std::string> words;
	std::stringstream input(information);
    while(input >> word)
        words.push_back(word);
    return words;
}

void Application::saveUser(std::string _username, std::string _email, long long _password) {
	User *user = new User(_username, _email, _password, songs);
	users.push_back(user);
	usernames.push_back(_username);
	currentUser = user;
}

void Application::showSongInformation(const std::vector<std::string> information) {
	std::string songID = checkOrderShowSong(information);
	Song* song = findSong(songID);
	std::cout << song->toStringWithExtraInformation();
}

std::string Application::showASongInformation(std::string songID) {
	Song* song = findSong(songID);
	std::string info = song->toStringWithExtraInformation();
	return info;
}

std::string Application::checkOrderShowSong(const std::vector<std::string> information) {
	BadRequestError bad_request;
	std::string songID;
	if(information[QUESTION_MARK_INDEX] == QUESTION_MARK && information[ID_INDEX] == ID && information.size() == THREE)
		songID = information[TWO];
	else
		throw bad_request;
	return songID;
}

Song* Application::findSong(std::string _songID) {
	int id = std::stoi(_songID);
	for(int i = ZERO; i < songs.size(); i++)
		if(songs[i]->getID() == id)
			return songs[i];
	throw not_found;
}

void Application::likeSong(const std::vector<std::string> information) {
	PermissionDeniedError permission_denied;
	if(currentUser == NULL)
		throw permission_denied;
	std::string songID = checkOrderShowSong(information);
	doLike(songID);
	std::cout << OK << std::endl;
}

void Application::doLike(const std::string songID) {
	Song* song = findSong(songID);
	currentUser->like(song);
}

void Application::deleteALike(const std::vector<std::string> information) {
	std::string songID = checkOrderShowSong(information);
	Song* song = findSong(songID);
	currentUser->unlike(song);
	std::cout << OK << std::endl;
}

void Application::addPlaylist(const std::vector<std::string> information) {
	PermissionDeniedError permission_denied;
	if(currentUser == NULL)
		throw permission_denied;
	std::vector<std::string> finalInformation = checkOrderAddPlaylist(information);
	numOfPlaylists ++;
	currentUser->addPlaylist(finalInformation[ZERO], finalInformation[ONE], numOfPlaylists);
	std::cout << numOfPlaylists << std::endl;
}

std::vector<std::string> Application::checkOrderAddPlaylist(const std::vector<std::string> information) {
	std::vector<std::string> finalInformation;
	BadRequestError bad_request;
	if(information[QUESTION_MARK_INDEX] == QUESTION_MARK && information[NAME_INDEX] == NAME && information[PRIVACY_INDEX] == PRIVACY && (information[PRIVACY_SITUATION_INDEX] == PRIVATE || information[PRIVACY_SITUATION_INDEX] == PUBLIC) && information.size() == FIVE) {
		finalInformation.push_back(information[TWO]);
		finalInformation.push_back(information[FOUR]);
	}
	else
		throw bad_request;
	return finalInformation;
}

void Application::showUserPlaylists(const std::vector<std::string> information) {
	std::string _username = checkOrderShowPlaylist(information);
	if(currentUser->getUsername() == _username)
		std::cout << currentUser->allPlaylistsToString();
	else {
		User *user = findUser(_username);
		std::cout << user->publicPlaylistsToString();
	}
}

std::vector<std::string> Application::showAllPlaylists() {
	return currentUser->playlistsToString();
}

std::string Application::showAPlaylist(std::string playlistID) {
	return currentUser->showAPlaylist(playlistID);
}

std::vector<std::string> Application::showAPlaylistSongs(std::string playlistID) {
	return currentUser->showPlaylistSongs(std::stoi(playlistID));
}

std::string Application::checkOrderShowPlaylist(const std::vector<std::string> information) {
	std::string _username;
	BadRequestError bad_request;
	if(information[QUESTION_MARK_INDEX] == QUESTION_MARK && information[ONE] == USERNAME && information.size() == THREE)
		_username = information[TWO];
	else
		throw bad_request;
	return _username;
}

User* Application::findUser(const std::string _username) {
	BadRequestError bad_request;
	for(int i = ZERO; i < users.size(); i++)
		if(users[i]->getUsername() == _username)
			return users[i];
	throw bad_request;
}

void Application::addSongToPlaylist(const std::vector<std::string> information) {
	std::vector<std::string> finalInformation = checkOrderAddSongToPlaylist(information);
	Song* song = findSong(finalInformation[ONE]);
	currentUser->addSongToPlaylist(finalInformation[ZERO], song);
	std::cout << OK << std::endl;
}


std::vector<std::string> Application::checkOrderAddSongToPlaylist(const std::vector<std::string> information) {
	std::vector<std::string> finalInformation;
	BadRequestError bad_request;
	if(information[QUESTION_MARK_INDEX] == QUESTION_MARK && information[PLAYLIST_ID_INDEX] == PLAYLIST_ID && information[SONG_ID_INDEX] == SONG_ID && information.size() == FIVE) {
		finalInformation.push_back(information[TWO]);
		finalInformation.push_back(information[FOUR]);
	}
	else
		throw bad_request;
	return finalInformation;
}

void Application::showPlaylistsSongs(const std::vector<std::string> information) {
	std::string playlistID = checkOrderShowPlaylistsSongs(information);
	if(currentUser->hasThisPlaylist(std::stoi(playlistID)))
		std::cout << currentUser->showPlaylistsSongs(std::stoi(playlistID));
	else {
		User *user = findOwnerOfPlaylist(std::stoi(playlistID));
		std::cout << user->showPublicPlaylistsSongs(std::stoi(playlistID));
	}
}

std::string Application::checkOrderShowPlaylistsSongs(const std::vector<std::string> information) {
	std::string playlistID;
	BadRequestError bad_request;
	if(information[QUESTION_MARK_INDEX] == QUESTION_MARK && information[PLAYLIST_ID_INDEX] == PLAYLIST_ID && information.size() == THREE)
		playlistID = information[TWO];
	else
		throw bad_request;
	return playlistID;
}

User* Application::findOwnerOfPlaylist(const int playlistID) {
	User* user;
	for(int i = ZERO; i < users.size(); i++)
		if(users[i]->hasThisPlaylist(playlistID))
			user = users[i];
	return user;
}

void Application::deleteASongOfPlaylist(const std::vector<std::string> information) {
	std::vector<std::string> finalInformation = checkOrderAddSongToPlaylist(information);
	Song* song = findSong(finalInformation[ONE]);
	currentUser->deleteASongOfPlaylist(std::stoi(finalInformation[ZERO]), song);
	std::cout << OK << std::endl;
}

void Application::showLikedSongs() {
	currentUser->showLikedSongs();
}

std::vector<std::string> Application::showAllLikedSongs() {
	return currentUser->showAllLikedSongs();
}

void Application::showUsersNames() {
	EmptyError empty_error;
	if(usernames.size() == TWO)
		throw empty_error;
	else {
		usernames.erase(usernames.begin());
		std::sort(usernames.begin(), usernames.end());
		for(int i = ZERO; i < usernames.size(); i++)
			if(usernames[i] != currentUser->getUsername() && usernames[i] != EMPTY_STRING)
				std::cout << usernames[i] << std::endl;
	}
}

void Application::addComment(const std::vector<std::string> information) {
	PermissionDeniedError permission_denied;
	if(currentUser == NULL)
		throw permission_denied;
	std::vector<std::string> finalInformation = checkOrderAddComment(information);
	Song* song = findSong(finalInformation[ZERO]);
	song->addComment(currentUser->getUsername(), std::stoi(finalInformation[ONE]), finalInformation[TWO]);
	std::cout << OK << std::endl;
}

std::vector<std::string> Application::checkOrderAddComment(const std::vector<std::string> information) {
	std::vector<std::string> finalInformation;
	BadRequestError bad_request;
	if(information[QUESTION_MARK_INDEX] == QUESTION_MARK && information[ONE] == SONG_ID && information[TIME_INDEX] == TIME && information[COMMENT_INDEX] == COMMENT && information.size() == SEVEN) {
		finalInformation.push_back(information[TWO]);
		finalInformation.push_back(information[FOUR]);
		finalInformation.push_back(information[SIX]);
	}
	else
		throw bad_request;
	return finalInformation;
}

void Application::showComments(const std::vector<std::string> information) {
	std::string songID = checkOrderShowComments(information);
	Song* song = findSong(songID);
	std::cout << song->commentsToString();
}

std::vector<std::vector<int>> Application::findUsersMatrix() {
	std::vector<std::vector<int>> sampleUsersMatrix;
	for(int i = 0; i < users.size(); i++)
		sampleUsersMatrix.push_back(users[i]->fillLikedSongsInformation());
	return sampleUsersMatrix;
}

std::vector<std::vector<double>> Application::findSimilarityMatrix() {
	std::vector<double> sampleLine(users.size(), INVAlid);
	std::vector<std::vector<double>> sampleSimilarityMatrix(users.size(), sampleLine);
	for(int i = 0; i < users.size(); i++)
		sampleSimilarityMatrix = users[i]->findSimilarities(usersMatrix, sampleSimilarityMatrix, i);
	return sampleSimilarityMatrix;
}

void Application::showSimilarUsers(const std::vector<std::string> information) {
	int count = findSimilarityOrRecommended(information);
	if(count > users.size() - 1)
		count = users.size() - 1;
	findUsersAndSimilarityMatrix();
	std::vector<std::pair<double, std::string>> usersAndSimilarities = assignSimilaritiesAndUsers(similarityMatrix[findUserIndex(currentUser)]);
	std::cout << currentUser->similarUsersToString(count, usersAndSimilarities);
}

std::vector<Song*> Application::showRecommendedSongs(const std::vector<std::string> information) {
	int count = findSimilarityOrRecommended(information);
	findUsersAndSimilarityMatrix();
	return currentUser->showRecommendedSongs(findUserIndex(currentUser), count, usersMatrix, similarityMatrix[findUserIndex(currentUser)]);
}

int Application::findSimilarityOrRecommended(const std::vector<std::string> information) {
	std::string count = checkOrderShowSimilarUsers(information);
	int countNumber = stoi(count);
	return countNumber;
}

void Application::findUsersAndSimilarityMatrix() {
	usersMatrix.clear();
	similarityMatrix.clear();
	usersMatrix = findUsersMatrix();
	similarityMatrix = findSimilarityMatrix();
}

std::vector<std::pair<double, std::string>> Application::assignSimilaritiesAndUsers(const std::vector<double> userSimilarityMatrix) {
	std::vector<std::pair<double, std::string>> usersAndSimilarities;
	std::pair<double, std::string> sample;
	for(int i = 0; i < userSimilarityMatrix.size(); i++) {
		sample.first = userSimilarityMatrix[i];
		sample.second = users[i]->getUsername();
		usersAndSimilarities.push_back(sample);
	}
	return usersAndSimilarities;
}

int Application::findUserIndex(User* user) {
	int index;
	for(int i = 0; i < users.size(); i++)
		if(users[i] == user)
			index = i;
	return index;
}

std::string Application::checkOrderShowComments(const std::vector<std::string> information) {
	std::string songID;
	BadRequestError bad_request;
	if(information[QUESTION_MARK_INDEX] == QUESTION_MARK && information[ONE] == SONG_ID && information.size() == THREE)
		songID = information[TWO];
	else
		throw bad_request;
	return songID;
}

std::string Application::checkOrderShowSimilarUsers(const std::vector<std::string> information) {
	std::string count;
	BadRequestError bad_request;
	if(information[QUESTION_MARK_INDEX] == QUESTION_MARK && information[COUNT_INDEX] == COUNT && information.size() == THREE)
		count = information[TWO];
	else
		throw bad_request;
	return count;
}

void Application::addFilter(const std::vector<std::string> information) {
	std::vector<std::string> finalInformation = checkOrderAddFilter(information);
	if(currentFilter == ARTIST)
		currentUser->addArtistFilter(finalInformation[ZERO]);
	else if(currentFilter == YEAR)
		currentUser->addYearFilter(std::stoi(finalInformation[ZERO]), std::stoi(finalInformation[ONE]));
	else if(currentFilter == LIKE) {
		currentUser->addLikeFilter(std::stoi(finalInformation[ZERO]), std::stoi(finalInformation[ONE]));
	}
	std::cout << OK << std::endl;
}

std::string Application::findArtistName(const std::vector<std::string> information) {
	std::string artistName = EMPTY_STRING;
	if(information.size() == THREE)
		artistName = information[TWO];
	else {
		std::vector<std::string> names;
		for(int i = TWO; i < information.size(); i++) {
			names.push_back(information[i]);
			names.push_back(SPACE);
		}
		for(int j = ZERO; j < names.size() - ONE; j++)
			artistName += names[j];
	}
	return artistName;
}

std::vector<std::string> Application::checkOrderAddFilter(const std::vector<std::string> information) {
	std::vector<std::string> finalInformation;
	BadRequestError bad_request;
	if(information[QUESTION_MARK_INDEX] == QUESTION_MARK && information[ARTIST_INDEX] == ARTIST && information.size() > TWO) {
		finalInformation.push_back(findArtistName(information));
		currentFilter = ARTIST;
	}
	else if(information[QUESTION_MARK_INDEX] == QUESTION_MARK && information[MIN_YEAR_INDEX] == MIN_YEAR && information[MAX_YEAR_INDEX] == MAX_YEAR && information.size() == FIVE) {
		finalInformation.push_back(information[TWO]);
		finalInformation.push_back(information[FOUR]);
		currentFilter = YEAR;
	}
	else if(information[QUESTION_MARK_INDEX] == QUESTION_MARK && information[MIN_LIKE_INDEX] == MIN_LIKE && information[MAX_LIKE_INDEX] == MAX_LIKE && information.size() == FIVE) {
		finalInformation.push_back(information[TWO]);
		finalInformation.push_back(information[FOUR]);
		currentFilter = LIKE;
	}
	else
		throw bad_request;
	return finalInformation;
}

void Application::deleteFilters() {
	currentUser->deleteFilters();
	std::cout << OK << std::endl;
}

long long Application::getHash(std::string s) {
    long long hashValue = ZERO, performancePower = ONE;
    for (char c : s) {
        hashValue = (hashValue + (c - CHARACTER_a + ONE) * performancePower) % MODE;
        performancePower = (performancePower * PERFORMANCE) % MODE;
    }
    return hashValue;
}
