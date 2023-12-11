#include "Handlers.hpp"

using namespace std;

SignupHandler::SignupHandler(Database* _database) {
    database = _database;
}

TripRequestHandler::TripRequestHandler(Database* _database) {
    database = _database;
}

DeleteTripHandler::DeleteTripHandler(Database* _database) {
    database = _database;
}

ShowCostHandler::ShowCostHandler(Database* _database) {
    database = _database;
}

TripsListHandler::TripsListHandler(Database* _database) {
    database = _database;
}

AcceptTripHandler::AcceptTripHandler(Database* _database) {
    database = _database;
}

FinishTripHandler::FinishTripHandler(Database* _database) {
    database = _database;
}

Response* SignupHandler::callback(Request* req) {
    PostRequest* post_request = new PostRequest();
    post_request->set_username(req->getBodyParam("username"));
    post_request->set_role(req->getBodyParam("role"));
    try {
        post_request->signup(*database);
    }
    catch(Error* error) {
        return Response::redirect(errors_map.find(error->get_message())->second);
    }
    return Response::redirect("/homePage");
}

Response* TripRequestHandler::callback(Request* req) {
    PostRequest* post_request = new PostRequest();
    post_request->set_username(req->getBodyParam("username"));
    post_request->set_origin(req->getBodyParam("origin"));
    post_request->set_destination(req->getBodyParam("destination"));
    post_request->set_in_hurry((req->getBodyParam("in_hurry") == "in_hurry") ? "yes" : "no");
    int trip_id;
    try {
        post_request->make_trip(*database);
        trip_id = post_request->get_id();
    }
    catch(Error* error) {
        return Response::redirect(errors_map.find(error->get_message())->second);
    }
    Response *res = new Response;
    res->setHeader("Content-Type", "text/html");
    string body;
    body += "<!DOCTYPE html>";
    body += "<html>";
    body += "<head>";
    body += "<title>Trip Id</title>";
    body += "<link rel=\"stylesheet\" href=\"tripId.css\">";
    body +=" </head>";
    body += "<body style=\"text-align: center;\">";
    body += "<h1>";
    body += "Your trip id: ";
    body += to_string(trip_id);
    body += "</h1>";
    body += "<form action=\"homePage\">";
    body += "<input type=\"submit\" value=\"Home\">";
    body += "</form>";
    body += "</body>";
    body += "</html>";
    res->setBody(body);
    return res;
}

Response* DeleteTripHandler::callback(Request* req) {
    DeleteRequest* delete_request = new DeleteRequest();
    delete_request->set_username(req->getBodyParam("username"));
    delete_request->set_id(req->getBodyParam("id").size() ? stoi(req->getBodyParam("id")) : invalid_id);
    try {
        delete_request->delete_trip(*database);
    }
    catch(Error* error) {
        return Response::redirect(errors_map.find(error->get_message())->second);
    }
    return Response::redirect("/deleteConfirmation");
}

Response* ShowCostHandler::callback(Request* req) {
    GetRequest* get_request = new GetRequest();
    get_request->set_username(req->getBodyParam("username"));
    get_request->set_origin(req->getBodyParam("origin"));
    get_request->set_destination(req->getBodyParam("destination"));
    get_request->set_in_hurry((req->getBodyParam("in_hurry") == "in_hurry") ? "yes" : "no");
    double price;
    try {
        price = get_request->get_cost(*database);
    }
    catch(Error* error) {
        return Response::redirect(errors_map.find(error->get_message())->second);
    }
    Response *res = new Response;
    res->setHeader("Content-Type", "text/html");
    string body;
    body += "<!DOCTYPE html>";
    body += "<html>";
    body += "<head>";
    body += "<title>Trips Cost</title>";
    body += "<link rel=\"stylesheet\" href=\"tripCost.css\">";
    body +=" </head>";
    body += "<body style=\"text-align: center;\">";
    body += "<h1>";
    body += "Trip cost: ";
    body += to_string(price);
    body += "</h1>";
    body += "<form action=\"homePage\">";
    body += "<input type=\"submit\" value=\"Home\">";
    body += "</form>";
    body += "</body>";
    body += "</html>";
    res->setBody(body);
    return res;
}

Response* TripsListHandler::callback(Request* req) {
    GetRequest* get_request = new GetRequest();
    get_request->set_username(req->getBodyParam("username"));
    get_request->set_sort_by_cost((req->getBodyParam("sort_by_cost") == "sort_by_cost") ? "yes" : "no");
    try {
        get_request->handle_trips_errors(*database);
    }
    catch(Error* error) {
        return Response::redirect(errors_map.find(error->get_message())->second);
    }
    int ongoing_trips = 0;
    for(Trip* trip : database->get_trips()) {
        if(!trip->is_canceled()) {
            ongoing_trips++;
        }
    }
    if(!ongoing_trips) {
        return Response::redirect("/noTrips");
    }
    vector <Trip*> trips = (req->getBodyParam("sort_by_cost") == "sort_by_cost") ? database->get_sorted_trips() : database->get_trips();
    Response *res = new Response;
    res->setHeader("Content-Type", "text/html");
    string body;
    body += "<!DOCTYPE html>";
    body += "<html>";
    body += "<head>";
    body += "<title>Trips List</title>";
    body += "<link rel=\"stylesheet\" href=\"tripsListPage.css\">";
    body +=" </head>";
    body += "<body style=\"text-align: center;\">";
    body += "<h1>";
    body += "Trips list";
    body += "</h1>";
    body += "<table id=\"trips\">";
    body += "<tr>";
    body += "<th>Trip id</th>";
    body += "<th>Passenger name</th>";
    body += "<th>Origin</th>";
    body += "<th>Destination</th>";
    body += "<th>Status</th>";
    body += "<th>Price</th>";
    body += "</tr>";
    for(Trip* trip : trips) {
        if(!trip->is_canceled()) {
        body += "<tr>";
        trip->show_info(body);
        body += "<td> <form method=\"post\">";
        body += "<td> <input type=\"submit\" value=\"Accept\" formaction=\"acceptTrip\"> </td>";
        body += "<td> <input type=\"submit\" value=\"Finish\" formaction=\"finishTrip\"> </td>";
        body += "<td> <input type=\"hidden\" name=\"username\" value=\"" + req->getBodyParam("username") + "\">";
        body += "<td> <input type=\"hidden\" name=\"id\" value=\"" + to_string(trip->get_id()) + "\">";
        body += "<td> </form>";
        body += "</tr>";
        }
    }
    body += "</table>";
    body += "</body>";
    body += "</html>";
    res->setBody(body);
    return res;
}

Response* AcceptTripHandler::callback(Request* req) {
    PostRequest* post_request = new PostRequest();
    post_request->set_username(req->getBodyParam("username"));
    post_request->set_id(req->getBodyParam("id").size() ? stoi(req->getBodyParam("id")) : invalid_id);
    try {
        post_request->accept_trip(*database);
    }
    catch(Error* error) {
        return Response::redirect(errors_map.find(error->get_message())->second);
    }
    return Response::redirect("/homePage");
}

Response* FinishTripHandler::callback(Request* req) {
    PostRequest* post_request = new PostRequest();
    post_request->set_username(req->getBodyParam("username"));
    post_request->set_id(req->getBodyParam("id").size() ? stoi(req->getBodyParam("id")) : invalid_id);
    try {
        post_request->finish_trip(*database);
    }
    catch(Error* error) {
        return Response::redirect(errors_map.find(error->get_message())->second);
    }
    return Response::redirect("/homePage");
}
