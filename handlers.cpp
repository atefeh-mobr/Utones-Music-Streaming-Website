#include "handlers.hpp"
#include "functions.hpp"
#include <sstream>

using namespace std;

Response *SignUpHandler::callback(Request *req) {
  Response *res = new Response;
  res->setHeader("Content-Type", "text/html");

  string email = req->getBodyParam("email");
  string username = req->getBodyParam("username");
  string password = req->getBodyParam("password");

  string command = "POST signup ? email " + email + " username " + username + " password " + password;
  run_command(command, application);
  res = Response::redirect("/home");

  return res;
}

Response *LoginHandler::callback(Request *req)
{
  Response *res = new Response;
  res->setHeader("Content-Type", "text/html");

  string email = req->getBodyParam("email");
  string password = req->getBodyParam("password");

  string command = "POST login ? email " + email + " password " + password;
  run_command(command, application);

  res->setSessionId("SID");
  res = Response::redirect("/home");

  return res;
}

Response *LogOutHandler::callback(Request *req)
{
  string command = "POST logout";
  run_command(command, application);
  Response *res = Response::redirect("/nobodyLoggedIn");

  return res;
}

Response *LikeSong::callback(Request *req) { 
  string id = req->getBodyParam("id");

  string command = "POST likes ? id " + id;
  run_command(command, application);

  return Response::redirect("/home");
}

Response *DislikeSong::callback(Request *req) { 
  string id = req->getBodyParam("id");

  string command = "DELETE likes ? id " + id;
  run_command(command, application);
  
  return Response::redirect("/home");
}

Response *MakePlaylist::callback(Request *req) { 
  Response *res = new Response;
  res->setHeader("Content-Type", "text/html");

  string name = req->getBodyParam("name");
  string privacy = req->getBodyParam("privacy");

  string command = "POST playlists ? name " + name + " privacy " + privacy;
  run_command(command, application);
  
  return Response::redirect("/home");
}

Response *AddSong::callback(Request *req) { 
  Response *res = new Response;
  res->setHeader("Content-Type", "text/html");

  string playlistID = req->getBodyParam("playlistID");
  string songID = req->getBodyParam("songID");

  string command = "POST playlists_songs ? playlist_id " + playlistID + " song_id " + songID;
  run_command(command, application);
  
  return Response::redirect("/home");
}

Response *DeleteSong::callback(Request *req) { 
  Response *res = new Response;
  res->setHeader("Content-Type", "text/html");
  string playlistID = req->getBodyParam("playlistID");
  string songID = req->getBodyParam("songID");

  string command = "DELETE playlists_songs ? playlist_id " + playlistID + " song_id " + songID;
  run_command(command, application);
  
  return Response::redirect("/home");
}

Response *ShowError::callback(Request *req)
{
  Response *res = new Response;
  res->setHeader("Content-Type", "text/html");
  ostringstream ss;
  ss << error;
  string body;
  body += "<!DOCTYPE html>";
  body += "<html>";
  body += "<head><title>" + ss.str() + "</title>";
  body += "</head>";
  body += "<body>";

  body += "</br> </br>";
  body += "<form align=\"center\" name=\"log_out_form\" method=\"post\" action=\"/logout\">";
  body += "<label class=\"logoutLblPos\">";
  body += "<input name=\"log_out\" type=\"submit\" id=\"log_out_submit\" value=\"Log Out\">";
  body += "</label>";
  body += "</form>";

  body += "</body>";
  body += "</html>";
  res->setBody(body);
  cout << "to\n";
  return res;
}

Response *ShowSongs::callback(Request *req) {
  Response *res = new Response;
  res->setHeader("Content-Type", "text/html");
  
  vector<Song*> allSongs = application->getAllSongs();

  string body;
  body += "<!DOCTYPE html>";
  body += "<html>";
  body += "<head><title>Songs</title>";
  body += "</head>";
  body += "<body>";
  body += "<table border=1>";
  body += "<tr>";
  body += "<th>Id</th>";
  body += "<th>Title</th>";
  body += "<th>Artist</th>";
  body += "<th>Release_Year</th>";
  body += "<th>&nbsp</th>";
  body += "</tr>";

  for(int i = 0; i < allSongs.size(); i++) {
    body += "<tr>";
    body += "<td>" + to_string(allSongs[i]->getID()) + "</td>";
    body += "<td>" + allSongs[i]->getTitle() + "</a></td>";
    body += "<td>" + allSongs[i]->getArtist() + "</td>";
    body += "<td>" + to_string(allSongs[i]->getReleaseYear()) + "</td>";
    body += "<td><a href='showSongInformation?id=" + to_string(allSongs[i]->getID()) + "'>Show Song Information</a></td>";
    body += "</tr>";
  }
  body += "</table>";

  body += "</br> </br>";
  body += "<form align=\"center\" name=\"show_liked_songs_form\" method=\"get\" action=\"/showLikedSongs\">";
  body += "<label class=\"logoutLblPos\">";
  body += "<input name=\"show_liked_songs\" type=\"submit\" id=\"show_liked_songs_submit\" value=\"Liked Songs\">";
  body += "</label>";
  body += "</form>";

  body += "</br> </br>";
  body += "<form align=\"center\" name=\"make_playlist_form\" method=\"get\" action=\"/makePlaylist\">";
  body += "<label class=\"logoutLblPos\">";
  body += "<input name=\"make_playlist\" type=\"submit\" id=\"make_playlist_submit\" value=\"Add Playlist\">";
  body += "</label>";
  body += "</form>";

  body += "</br> </br>";
  body += "<form align=\"center\" name=\"show_playlists_form\" method=\"get\" action=\"/showPlaylists\">";
  body += "<label class=\"logoutLblPos\">";
  body += "<input name=\"show_playlists\" type=\"submit\" id=\"show_playlists_submit\" value=\"Your Playlists\">";
  body += "</label>";
  body += "</form>";

  body += "</br> </br>";
  body += "<form align=\"center\" name=\"exception_form\" method=\"post\" action=\"/exception\">";
  body += "<label class=\"logoutLblPos\">";
  body += "</label>";
  body += "</form>";

  body += "</br> </br>";
  body += "<form align=\"center\" name=\"log_out_form\" method=\"post\" action=\"/logout\">";
  body += "<label class=\"logoutLblPos\">";
  body += "<input name=\"log_out\" type=\"submit\" id=\"log_out_submit\" value=\"Log Out\">";
  body += "</label>";
  body += "</form>";


  body += "</body>";
  body += "</html>";
  res->setBody(body);
  return res;
}

Response *ShowSongInformation::callback(Request *req)
{
  Response *res = new Response;
  res->setHeader("Content-Type", "text/html");

  string id = req->getQueryParam("id");
  string information = application->showASongInformation(id);
  vector<string> splitedInformation = splitByEnter(information);
  vector<Song*> recommendedSongs = application->showRecommendedSongs({"?", "count", to_string(4)});
  
  string body;
  body += "<!DOCTYPE html>";
  body += "<html>";
  body += "<head><title>Song Information</title>";
  body += "</head>";
  body += "<body>";
  body += "<table border=1>";
  body += "<tr>";
  body += "<th>Title</th>";
  body += "<th>Artist</th>";
  body += "<th>Release_Year</th>";
  body += "<th>Number of Likes</th>";
  body += "<th>Number of Playlists</th>";
  body += "<th>&nbsp</th>";
  body += "</tr>";

  body += "<tr>";
  body += "<td>" + splitedInformation[0] + "</td>";
  body += "<td>" + splitedInformation[1] + "</td>";
  body += "<td>" + splitedInformation[2] + "</td>";
  body += "<td>" + splitedInformation[4] + "</td>";
  body += "<td>" + splitedInformation[5] + "</td>";

  body += "</tr>";
  body += "</table>";

  body += "<audio controls>";
  body += "<source src=" + splitedInformation[3] + "type='audio/mpeg'>";
  body += "</audio>";


  body += "</br> </br>";
  body += "<form align=\"center\" name=\"like_form\" method=\"post\" action=\"/likeSong\">";
  body += "<input type= \"hidden\" name=\"id\" value=" + id + "/><be/>";
  body += "<label class=\"logoutLblPos\">";
  body += "<input name=\"like_song\" type=\"submit\" id=\" " + id + "\" value=\"Like\">";
  body += "</label>";
  body += "</form>";

  body += "</br> </br>";
  body += "<form align=\"center\" name=\"dislike_form\" method=\"post\" action=\"/dislikeSong\">";
  body += "<input type= \"hidden\" name=\"id\" value=" + id + "/><be/>";
  body += "<label class=\"logoutLblPos\">";
  body += "<input name=\"dislike_song\" type=\"submit\" id=\" " + id + "\" value=\"Dislike\">";
  body += "</label>";
  body += "</form>";

  body += "<head><title>Recommended Songs</title>";
  body += "</head>";
  body += "<body>";
  body += "<table border=1>";
  body += "<tr>";
  body += "<th>Title</th>";
  body += "<th>Artist</th>";
  body += "<th>Release_Year</th>";
  body += "</tr>";

  for(int i = 0; i < recommendedSongs.size(); i++) {
    body += "<tr>";
    body += "<td>" + recommendedSongs[i]->getTitle() + "</a></td>";
    body += "<td>" + recommendedSongs[i]->getArtist() + "</td>";
    body += "<td>" + to_string(recommendedSongs[i]->getReleaseYear()) + "</td>";
    body += "</tr>";
  }
  body += "</table>";

  body += "</br> </br>";
  body += "<form align=\"center\" name=\"exception_form\" method=\"post\" action=\"/exception\">";
  body += "<label class=\"logoutLblPos\">";
  body += "</label>";
  body += "</form>";

  body += "</br> </br>";
  body += "<form align=\"center\" name=\"log_out_form\" method=\"post\" action=\"/logout\">";
  body += "<label class=\"logoutLblPos\">";
  body += "<input name=\"log_out\" type=\"submit\" id=\"log_out_submit\" value=\"Log Out\">";
  body += "</label>";
  body += "</form>";

  body += "</body>";
  body += "</html>";
  res->setBody(body);

  return res;
}

Response *ShowLikedSongs::callback(Request *req) { 
  Response *res = new Response;
  res->setHeader("Content-Type", "text/html");
  
  vector<string> likedSongsInformation = application->showAllLikedSongs();

  string body;
  body += "<!DOCTYPE html>";
  body += "<html>";
  body += "<head><title>Songs</title>";
  body += "</head>";
  body += "<body>";
  body += "<table border=1>";
  body += "<tr>";
  body += "<th>Title</th>";
  body += "<th>Artist</th>";
  body += "<th>Release_Year</th>";
  body += "<th>&nbsp</th>";
  body += "<th>&nbsp</th>";
  body += "</tr>";

  for(int i = 0; i < likedSongsInformation.size(); i++) {
    vector<string> splitedInformation = splitByEnter(likedSongsInformation[i]);
    body += "<tr>";
    body += "<td>" + splitedInformation[1] + "</a></td>";
    body += "<td>" + splitedInformation[2] + "</td>";
    body += "<td>" + splitedInformation[3] + "</td>";

    body += "<td>";
    body += "</br> </br>";
    body += "<form align=\"center\" name=\"dislike_form\" method=\"post\" action=\"/dislikeSong\">";
    body += "<input type= \"hidden\" name=\"id\" value=" + splitedInformation[0] + "/><be/>";
    body += "<label class=\"logoutLblPos\">";
    body += "<input name=\"dislike_song\" type=\"submit\" id=\" " + splitedInformation[0] + "\" value=\"Dislike\">";
    body += "</label>";
    body += "</form>";
    body += "</td>";

    body += "<td><a href='showSongInformation?id=" + splitedInformation[0] + "'>Show Song Information</a></td>";
    body += "</tr>";
  }
  body += "</table>";

  body += "</br> </br>";
  body += "<form align=\"center\" name=\"log_out_form\" method=\"post\" action=\"/logout\">";
  body += "<label class=\"logoutLblPos\">";
  body += "<input name=\"log_out\" type=\"submit\" id=\"log_out_submit\" value=\"Log Out\">";
  body += "</label>";
  body += "</form>";


  body += "</body>";
  body += "</html>";
  res->setBody(body);
  return res;
}

Response *ShowPlaylists::callback(Request *req) { 
  Response *res = new Response;
  res->setHeader("Content-Type", "text/html");
  
  vector<string> playlistsInformation = application->showAllPlaylists();

  string body;
  body += "<!DOCTYPE html>";
  body += "<html>";
  body += "<head><title>Songs</title>";
  body += "</head>";
  body += "<body>";
  body += "<table border=1>";
  body += "<tr>";
  body += "<th>Name</th>";
  body += "<th>Privacy</th>";
  body += "<th>&nbsp</th>";
  body += "<th>&nbsp</th>";
  body += "</tr>";

  vector<string> splitedInformation;
  for(int i = 0; i < playlistsInformation.size(); i++) {
    splitedInformation = splitByEnter(playlistsInformation[i]);
    body += "<tr>";
    body += "<td>" + splitedInformation[1] + "</a></td>";
    body += "<td>" + splitedInformation[2] + "</td>";

    body += "<td>";
    body += "</br> </br>";
    body += "<form align=\"center\" name=\"edit_playlist_form\" method=\"get\" action=\"/editPlaylist\">";
    body += "<input type= \"hidden\" name=\"id\" value=" + splitedInformation[0] + "/><be/>";
    body += "<label class=\"logoutLblPos\">";
    body += "<input name=\"edit_playlist\" type=\"submit\" id=\" " + splitedInformation[0] + "\" value=\"Edit Playlist\">";
    body += "</label>";
    body += "</form>";
    body += "</td>";

    body += "</tr>";
  }

  body += "</table>";

  body += "</br> </br>";
  body += "<form align=\"center\" name=\"make_playlist_form\" method=\"get\" action=\"/makePlaylist\">";
  body += "<label class=\"logoutLblPos\">";
  body += "<input name=\"make_playlist\" type=\"submit\" id=\"make_playlist_submit\" value=\"Add Playlist\">";
  body += "</label>";
  body += "</form>";

  body += "</br> </br>";
  body += "<form align=\"center\" name=\"log_out_form\" method=\"post\" action=\"/logout\">";
  body += "<label class=\"logoutLblPos\">";
  body += "<input name=\"log_out\" type=\"submit\" id=\"log_out_submit\" value=\"Log Out\">";
  body += "</label>";
  body += "</form>";


  body += "</body>";
  body += "</html>";
  res->setBody(body);
  return res;
}

Response *EditPlaylist::callback(Request *req) { 
  Response *res = new Response;
  res->setHeader("Content-Type", "text/html");
  string id = req->getQueryParam("id");

  string playlistInformation = application->showAPlaylist(id);
  vector<string> playlistsSongs = application->showAPlaylistSongs(id);

  string body;
  body += "<!DOCTYPE html>";
  body += "<html>";
  body += "<head><title>Songs</title>";
  body += "</head>";
  body += "<body>";
  body += "<table border=1>";
  body += "<tr>";
  body += "<th>ID</th>";
  body += "<th>Name</th>";
  body += "<th>Privacy</th>";
  body += "</tr>";

  vector<string> splitedInformation = splitByEnter(playlistInformation);
  body += "<tr>";
  body += "<td>" + splitedInformation[0] + "</td>";
  body += "<td>" + splitedInformation[1] + "</td>";
  body += "<td>" + splitedInformation[2] + "</td>";
  body += "<td>";
  body += "</table>";

  body += "<table border=1>";
  body += "<tr>";
  body += "<th>Title</th>";
  body += "<th>Artist</th>";
  body += "<th>Release_Year</th>";
  body += "<th>&nbsp</th>";
  body += "</tr>";

  for(int i = 0; i < playlistsSongs.size(); i++) {
    splitedInformation = splitByEnter(playlistsSongs[i]);
    body += "<tr>";
    body += "<td>" + splitedInformation[1] + "</a></td>";
    body += "<td>" + splitedInformation[2] + "</td>";
    body += "<td>" + splitedInformation[3] + "</td>";
    body += "<td><a href='showSongInformation?id=" + splitedInformation[0] + "'>Show Song Information</a></td>";
    body += "</tr>";
  }
  body += "</table>";

  body += "</br> </br>";
  body += "<form align=\"center\" name=\"add_song_form\" method=\"get\" action=\"/addSong\">";
  body += "<label class=\"logoutLblPos\">";
  body += "<input name=\"add_song\" type=\"submit\" id=\"add_song_submit\" value=\"Add Song\">";
  body += "</label>";
  body += "</form>";

  body += "</br> </br>";
  body += "<form align=\"center\" name=\"delete_song_form\" method=\"get\" action=\"/deleteSong\">";
  body += "<label class=\"logoutLblPos\">";
  body += "<input name=\"delete_song\" type=\"submit\" id=\"delete_song_submit\" value=\"Delete Song\">";
  body += "</label>";
  body += "</form>";

  body += "</br> </br>";
  body += "<form align=\"center\" name=\"log_out_form\" method=\"post\" action=\"/logout\">";
  body += "<label class=\"logoutLblPos\">";
  body += "<input name=\"log_out\" type=\"submit\" id=\"log_out_submit\" value=\"Log Out\">";
  body += "</label>";
  body += "</form>";


  body += "</body>";
  body += "</html>";


  body += "</body>";
  body += "</html>";
  res->setBody(body);
  return res;
}