#ifndef _MY_HANDLERS_
#define _MY_HANDLERS_

#include "server/server.hpp"
#include <cstdlib> 
#include <ctime>   
#include <iostream>
#include "application.hpp"

class ShowSongs : public RequestHandler {
private:
	Application* application;
public:
	ShowSongs(Application* _application) { application = _application; }
  	Response *callback(Request *);
};

class SignUpHandler : public RequestHandler {
private:
	Application* application;
public:
	SignUpHandler(Application* _application) { application = _application; }
  	Response *callback(Request *);
};

class LoginHandler : public RequestHandler {
private:
	Application* application;
public:
	LoginHandler(Application* _application) { application = _application; }
  	Response *callback(Request *);
};

class LogOutHandler : public RequestHandler {
private:
	Application* application;
public:
	LogOutHandler(Application* _application) { application = _application; }
  	Response *callback(Request *);
};

class ShowSongInformation : public RequestHandler {
private:
	Application* application;
public:
	ShowSongInformation(Application* _application) { application = _application; }
  	Response *callback(Request *);
};

class LikeSong : public RequestHandler {
private:
	Application* application;
public:
	LikeSong(Application* _application) { application = _application; }
  	Response *callback(Request *);
};

class DislikeSong : public RequestHandler {
private:
	Application* application;
public:
	DislikeSong(Application* _application) { application = _application; }
  	Response *callback(Request *);
};

class ShowLikedSongs : public RequestHandler {
private:
	Application* application;
public:
	ShowLikedSongs(Application* _application) { application = _application; }
  	Response *callback(Request *);
};

class ShowPlaylists : public RequestHandler {
private:
	Application* application;
public:
	ShowPlaylists(Application* _application) { application = _application; }
  	Response *callback(Request *);
};

class MakePlaylist : public RequestHandler {
private:
	Application* application;
public:
	MakePlaylist(Application* _application) { application = _application; }
  	Response *callback(Request *);
};

class EditPlaylist : public RequestHandler {
private:
	Application* application;
public:
	EditPlaylist(Application* _application) { application = _application; }
  	Response *callback(Request *);
};

class AddSong : public RequestHandler {
private:
	Application* application;
public:
	AddSong(Application* _application) { application = _application; }
  	Response *callback(Request *);
};

class DeleteSong : public RequestHandler {
private:
	Application* application;
public:
	DeleteSong(Application* _application) { application = _application; }
  	Response *callback(Request *);
};

class ShowError : public RequestHandler {
private:
	const char* error;
public:
	ShowError(const char* _error) { error = _error; }
  	Response *callback(Request *);
};

#endif
