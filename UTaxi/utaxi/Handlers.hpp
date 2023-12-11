#ifndef __MY__Handlers__
#define __MY__Handlers__

#include "../server/server.hpp"
#include "UTaxi.hpp"
#include "ErrorsMap.hpp"

class SignupHandler : public RequestHandler {
private:
    Database* database;
public:
    SignupHandler(Database* _database);
    Response* callback(Request* req); 
};

class TripRequestHandler : public RequestHandler {
private:
    Database* database;
public:
    TripRequestHandler(Database* _database);
    Response* callback(Request* req);
};

class DeleteTripHandler : public RequestHandler {
private:
    Database* database;
public:
    DeleteTripHandler(Database* _database);
    Response* callback(Request* req); 
};

class ShowCostHandler : public RequestHandler {
private:
    Database* database;
public:
    ShowCostHandler(Database* _database);
    Response* callback(Request* req); 
};

class TripsListHandler : public RequestHandler {
private:
    Database* database;
public:
    TripsListHandler(Database* _database);
    Response* callback(Request* req); 
};

class AcceptTripHandler : public RequestHandler {
private:
    Database* database;
public:
    AcceptTripHandler(Database* _database);
    Response* callback(Request* req); 
};

class FinishTripHandler : public RequestHandler {
private:
    Database* database;
public:
    FinishTripHandler(Database* _database);
    Response* callback(Request* req); 
};

#endif
