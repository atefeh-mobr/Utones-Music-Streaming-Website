#ifndef SONG_H
#define SONG_H

#include <iostream>
#include <string>
#include <vector>

typedef std::pair<std::pair<int, std::string>, std::string> CommentInformation;

class Song {
public:
	Song(std::string _id, std::string _title, std::string _artist, std::string _release_year, std::string _link);
	void undoLike();
	void applyLike();
	void addNumberOfPlaylists();
	void discountNumberOfPlaylists();
	void addComment(std::string username, int time, std::string comment);
	int getID();
	int getReleaseYear();
	std::string getLink();
	std::string getTitle();
	std::string getArtist();
	bool isEqualArtist(std::string _artist);
	bool isInPeriod(int minYear, int maxYear);
	bool isEqualLike(int _minLike, int _maxLike);
	std::string toString();
	std::string idToString();
	std::string mainToString();
	std::string detailsToString();
	std::string commentsToString();
	std::string commentToString(int index);
	std::string toStringWithExtraInformation();
private:
	int id;
	int release_year;
	int num_of_likes;
	int num_of_comments;
	int num_of_playlists;
	std::string link; 
	std::string title;
	std::string artist;
	std::vector<CommentInformation> commentsInformation;
};

#endif
