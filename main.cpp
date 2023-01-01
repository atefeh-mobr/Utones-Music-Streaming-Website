#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <algorithm>
#include "functions.hpp"
#include "application.hpp"
#include "handlers.hpp"
#include "my_server.hpp"
#include <cstdlib>
#include <ctime> 

using namespace std;

int main (int argc, char **argv) {
	string command;
	vector<vector<string>> songsInformation = readCsv(argv[1]);
	vector<vector<string>> likedSongsInformation = readCsv(argv[2]);
	songsInformation.erase(songsInformation.begin());
	likedSongsInformation.erase(likedSongsInformation.begin());
	Application *application = new Application();
	application->saveSongs(songsInformation);
	application->saveLikedSongs(likedSongsInformation);

	srand(time(NULL));
	MyServer server(10000);
	while(1) {
		try {
	    
	    server.get("/", new ShowPage("static/home.html"));
	    server.get("/home.png", new ShowImage("static/home.png"));
	    server.get("/nobodyLoggedIn", new ShowPage("static/home.html"));

	    server.get("/signup", new ShowPage("static/signup.html"));
	    server.post("/signup", new SignUpHandler(application));

	    server.get("/login", new ShowPage("static/login.html"));
	    server.post("/login", new LoginHandler(application));
	    server.post("/logout", new LogOutHandler(application));

	    server.get("/showSongInformation", new ShowSongInformation(application));
	    server.post("/likeSong", new LikeSong(application));
	    server.post("/dislikeSong", new DislikeSong(application));

	    server.get("/showLikedSongs", new ShowLikedSongs(application));
	    server.get("/showPlaylists", new ShowPlaylists(application));

	    server.get("/makePlaylist", new ShowPage("static/makePlaylist.html"));
	    server.post("/makePlaylist", new MakePlaylist(application));
	    server.get("/editPlaylist", new EditPlaylist(application));

	    server.get("/addSong", new ShowPage("static/addSong.html"));
	    server.post("/addSong", new AddSong(application));

	    server.get("/deleteSong", new ShowPage("static/deleteSong.html"));
	    server.post("/deleteSong", new DeleteSong(application));
	    

	    server.get("/home", new ShowSongs(application));

	    server.run();
	  } 
	  catch (exception e) {
	  	cout << "error occured" << endl;
	    server.post("/exception", new ShowError(e.what()));
	    cerr << e.what() << endl;
	  }
	}
	return 0;
}


