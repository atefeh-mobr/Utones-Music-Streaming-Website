CC=g++
STD=-std=c++11 -Wall -pedantic
CF=$(STD)
BUILD_DIR=build
TEMPLATE_DIR=.template

all: $(BUILD_DIR) utunes.out

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/functions.o: functions.cpp functions.hpp application.hpp empty_error.hpp bad_request_error.hpp not_found_error.hpp permission_denied_error.hpp
	$(CC) $(CF) -c functions.cpp -o $(BUILD_DIR)/functions.o

$(BUILD_DIR)/application.o: application.cpp song.hpp user.hpp playlist.hpp filter.hpp artist_filter.hpp year_filter.hpp like_filter.hpp bad_request_error.hpp not_found_error.hpp permission_denied_error.hpp empty_error.hpp
	$(CC) $(CF) -c application.cpp -o $(BUILD_DIR)/application.o

$(BUILD_DIR)/song.o: song.cpp empty_error.hpp
	$(CC) $(CF) -c song.cpp -o $(BUILD_DIR)/song.o

$(BUILD_DIR)/user.o: user.cpp playlist.hpp filter.hpp song.hpp artist_filter.hpp year_filter.hpp like_filter.hpp bad_request_error.hpp empty_error.hpp permission_denied_error.hpp
	$(CC) $(CF) -c user.cpp -o $(BUILD_DIR)/user.o

$(BUILD_DIR)/playlist.o: playlist.cpp song.hpp empty_error.hpp bad_request_error.hpp
	$(CC) $(CF) -c playlist.cpp -o $(BUILD_DIR)/playlist.o

$(BUILD_DIR)/filter.o: filter.cpp song.hpp
	$(CC) $(CF) -c filter.cpp -o $(BUILD_DIR)/filter.o

$(BUILD_DIR)/artist_filter.o: artist_filter.cpp filter.hpp song.hpp
	$(CC) $(CF) -c artist_filter.cpp -o $(BUILD_DIR)/artist_filter.o

$(BUILD_DIR)/year_filter.o: year_filter.cpp filter.hpp song.hpp bad_request_error.hpp
	$(CC) $(CF) -c year_filter.cpp -o $(BUILD_DIR)/year_filter.o

$(BUILD_DIR)/like_filter.o: like_filter.cpp filter.hpp song.hpp bad_request_error.hpp
	$(CC) $(CF) -c like_filter.cpp -o $(BUILD_DIR)/like_filter.o



$(BUILD_DIR)/response.o: utils/response.cpp utils/response.hpp utils/include.hpp
	$(CC) $(CF) -c utils/response.cpp -o $(BUILD_DIR)/response.o

$(BUILD_DIR)/request.o: utils/request.cpp utils/request.hpp utils/include.hpp utils/utilities.hpp
	$(CC) $(CF) -c utils/request.cpp -o $(BUILD_DIR)/request.o

$(BUILD_DIR)/utilities.o: utils/utilities.cpp utils/utilities.hpp
	$(CC) $(CF) -c utils/utilities.cpp -o $(BUILD_DIR)/utilities.o

$(BUILD_DIR)/server.o: server/server.cpp server/server.hpp server/route.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	$(CC) $(CF) -c server/server.cpp -o $(BUILD_DIR)/server.o

$(BUILD_DIR)/route.o: server/route.cpp server/route.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	$(CC) $(CF) -c server/route.cpp -o $(BUILD_DIR)/route.o

$(BUILD_DIR)/handlers.o: handlers.cpp server/server.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	$(CC) $(CF) -c handlers.cpp -o $(BUILD_DIR)/handlers.o

$(BUILD_DIR)/my_server.o: my_server.cpp server/server.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	$(CC) $(CF) -c my_server.cpp -o $(BUILD_DIR)/my_server.o



$(BUILD_DIR)/main.o: main.cpp functions.hpp application.hpp server/server.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	$(CC) $(CF) -c main.cpp -o $(BUILD_DIR)/main.o

utunes.out: $(BUILD_DIR)/main.o $(BUILD_DIR)/functions.o $(BUILD_DIR)/application.o $(BUILD_DIR)/song.o $(BUILD_DIR)/user.o $(BUILD_DIR)/playlist.o $(BUILD_DIR)/filter.o $(BUILD_DIR)/artist_filter.o $(BUILD_DIR)/year_filter.o $(BUILD_DIR)/like_filter.o $(BUILD_DIR)/my_server.o $(BUILD_DIR)/handlers.o $(BUILD_DIR)/response.o $(BUILD_DIR)/request.o $(BUILD_DIR)/utilities.o $(BUILD_DIR)/server.o $(BUILD_DIR)/route.o
	$(CC) $(CF) $(BUILD_DIR)/main.o $(BUILD_DIR)/functions.o $(BUILD_DIR)/application.o $(BUILD_DIR)/song.o $(BUILD_DIR)/user.o $(BUILD_DIR)/playlist.o $(BUILD_DIR)/filter.o $(BUILD_DIR)/artist_filter.o $(BUILD_DIR)/year_filter.o $(BUILD_DIR)/like_filter.o $(BUILD_DIR)/my_server.o $(BUILD_DIR)/handlers.o $(BUILD_DIR)/response.o $(BUILD_DIR)/request.o $(BUILD_DIR)/utilities.o $(BUILD_DIR)/server.o $(BUILD_DIR)/route.o -o utunes.out

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR) $(TEMPLATE_DIR) *.o *.out &> /dev/null

