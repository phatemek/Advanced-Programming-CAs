CC=g++
STD=-std=c++11 -Wall -pedantic
CF=$(STD)
BUILD_DIR=build
TEMPLATE_DIR=.template

all: $(BUILD_DIR) utaxi.out

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/template_parser.o: utils/template_parser.cpp utils/template_parser.hpp utils/request.cpp utils/request.hpp utils/utilities.hpp utils/utilities.cpp
	$(CC) $(CF) -c utils/template_parser.cpp -o $(BUILD_DIR)/template_parser.o

$(BUILD_DIR)/response.o: utils/response.cpp utils/response.hpp utils/include.hpp
	$(CC) $(CF) -c utils/response.cpp -o $(BUILD_DIR)/response.o

$(BUILD_DIR)/request.o: utils/request.cpp utils/request.hpp utils/include.hpp utils/utilities.hpp
	$(CC) $(CF) -c utils/request.cpp -o $(BUILD_DIR)/request.o

$(BUILD_DIR)/utilities.o: utils/utilities.cpp utils/utilities.hpp
	$(CC) $(CF) -c utils/utilities.cpp -o $(BUILD_DIR)/utilities.o

$(BUILD_DIR)/server.o: server/server.cpp server/server.hpp server/route.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp utils/template_parser.hpp utils/template_parser.cpp
	$(CC) $(CF) -c server/server.cpp -o $(BUILD_DIR)/server.o

$(BUILD_DIR)/route.o: server/route.cpp server/route.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	$(CC) $(CF) -c server/route.cpp -o $(BUILD_DIR)/route.o

$(BUILD_DIR)/Handlers.o: utaxi/Handlers.cpp utaxi/UTaxi.hpp utaxi/ErrorsMap.hpp server/server.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	$(CC) $(CF) -c utaxi/Handlers.cpp -o $(BUILD_DIR)/Handlers.o

$(BUILD_DIR)/main.o: utaxi/main.cpp server/server.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp utaxi/UTaxi.hpp utaxi/Handlers.hpp
	$(CC) $(CF) -c utaxi/main.cpp -o $(BUILD_DIR)/main.o

$(BUILD_DIR)/Database.o: utaxi/Database.hpp utaxi/User.hpp utaxi/Location.hpp utaxi/Trip.hpp utaxi/Database.cpp
	$(CC) $(CF) -c utaxi/Database.cpp -o $(BUILD_DIR)/Database.o

$(BUILD_DIR)/DeleteRequest.o: utaxi/DeleteRequest.hpp utaxi/CLRequest.hpp utaxi/DeleteRequest.cpp
	$(CC) $(CF) -c utaxi/DeleteRequest.cpp -o $(BUILD_DIR)/DeleteRequest.o

$(BUILD_DIR)/Driver.o: utaxi/Driver.hpp utaxi/User.hpp utaxi/Driver.cpp
	$(CC) $(CF) -c utaxi/Driver.cpp -o $(BUILD_DIR)/Driver.o

$(BUILD_DIR)/Error.o: utaxi/Error.hpp utaxi/Error.cpp
	$(CC) $(CF) -c utaxi/Error.cpp -o $(BUILD_DIR)/Error.o

$(BUILD_DIR)/GetRequest.o: utaxi/GetRequest.hpp utaxi/CLRequest.hpp utaxi/GetRequest.cpp
	$(CC) $(CF) -c utaxi/GetRequest.cpp -o $(BUILD_DIR)/GetRequest.o

$(BUILD_DIR)/IOHandler.o: utaxi/IOHandler.hpp utaxi/Database.hpp utaxi/Error.hpp utaxi/IOHandler.cpp
	$(CC) $(CF) -c utaxi/IOHandler.cpp -o $(BUILD_DIR)/IOHandler.o

$(BUILD_DIR)/Location.o: utaxi/Location.hpp utaxi/Location.cpp
	$(CC) $(CF) -c utaxi/Location.cpp -o $(BUILD_DIR)/Location.o

$(BUILD_DIR)/Passenger.o: utaxi/Passenger.hpp utaxi/User.hpp utaxi/Passenger.cpp
	$(CC) $(CF) -c utaxi/Passenger.cpp -o $(BUILD_DIR)/Passenger.o

$(BUILD_DIR)/PostRequest.o: utaxi/PostRequest.hpp utaxi/CLRequest.hpp utaxi/PostRequest.cpp
	$(CC) $(CF) -c utaxi/PostRequest.cpp -o $(BUILD_DIR)/PostRequest.o

$(BUILD_DIR)/CLRequest.o: utaxi/CLRequest.hpp utaxi/Location.hpp utaxi/Database.hpp utaxi/User.hpp utaxi/Driver.hpp utaxi/Passenger.hpp utaxi/IOHandler.hpp utaxi/CLRequest.cpp
	$(CC) $(CF) -c utaxi/CLRequest.cpp -o $(BUILD_DIR)/CLRequest.o

$(BUILD_DIR)/Trip.o: utaxi/Trip.hpp utaxi/Location.hpp utaxi/Trip.cpp
	$(CC) $(CF) -c utaxi/Trip.cpp -o $(BUILD_DIR)/Trip.o

$(BUILD_DIR)/User.o: utaxi/User.hpp utaxi/User.cpp
	$(CC) $(CF) -c utaxi/User.cpp -o $(BUILD_DIR)/User.o

$(BUILD_DIR)/UTaxi.o: utaxi/UTaxi.hpp utaxi/Database.hpp utaxi/Error.hpp utaxi/IOHandler.hpp utaxi/CLRequest.hpp utaxi/GetRequest.hpp utaxi/PostRequest.hpp utaxi/DeleteRequest.hpp utaxi/UTaxi.cpp
	$(CC) $(CF) -c utaxi/UTaxi.cpp -o $(BUILD_DIR)/UTaxi.o

utaxi.out: $(BUILD_DIR)/main.o $(BUILD_DIR)/Handlers.o $(BUILD_DIR)/Database.o $(BUILD_DIR)/DeleteRequest.o $(BUILD_DIR)/Driver.o $(BUILD_DIR)/Error.o $(BUILD_DIR)/GetRequest.o $(BUILD_DIR)/IOHandler.o $(BUILD_DIR)/Location.o $(BUILD_DIR)/Passenger.o $(BUILD_DIR)/PostRequest.o $(BUILD_DIR)/CLRequest.o $(BUILD_DIR)/Trip.o $(BUILD_DIR)/User.o $(BUILD_DIR)/UTaxi.o $(BUILD_DIR)/response.o $(BUILD_DIR)/request.o $(BUILD_DIR)/utilities.o $(BUILD_DIR)/server.o $(BUILD_DIR)/route.o $(BUILD_DIR)/template_parser.o
	$(CC) $(CF) $(BUILD_DIR)/main.o $(BUILD_DIR)/Database.o $(BUILD_DIR)/Handlers.o $(BUILD_DIR)/DeleteRequest.o $(BUILD_DIR)/Driver.o $(BUILD_DIR)/Error.o $(BUILD_DIR)/GetRequest.o $(BUILD_DIR)/IOHandler.o $(BUILD_DIR)/Location.o $(BUILD_DIR)/Passenger.o $(BUILD_DIR)/PostRequest.o $(BUILD_DIR)/CLRequest.o $(BUILD_DIR)/Trip.o $(BUILD_DIR)/User.o $(BUILD_DIR)/UTaxi.o $(BUILD_DIR)/response.o $(BUILD_DIR)/request.o $(BUILD_DIR)/utilities.o $(BUILD_DIR)/server.o $(BUILD_DIR)/route.o $(BUILD_DIR)/template_parser.o  -o utaxi.out

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR) $(TEMPLATE_DIR) *.o *.out &> /dev/null
