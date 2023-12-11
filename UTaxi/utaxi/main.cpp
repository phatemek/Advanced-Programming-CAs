#include <iostream>
#include <fstream>
#include "UTaxi.hpp"
#include "../server/server.hpp"
#include "Handlers.hpp"
using namespace std;

const string html_dir = "static/html/";
const string css_dir = "static/css/";
const string css_mime_type = "text/css";

int main(int argc, char* argv[]) {
    Database database;
    UTaxi utaxi(argv[1], database);
    utaxi.run();
    Server server;
    try{
        server.setNotFoundErrPage("static/404.html");
        server.get("/", new ShowPage(html_dir + "signup.html"));
        server.get("/signup.css", new ShowFile(css_dir + "signup.css", css_mime_type));
        server.get("/homePage", new ShowPage(html_dir + "home.html"));
        server.get("/homePage.css", new ShowFile(css_dir + "homePage.css", css_mime_type));
        server.get("/tripRequest", new ShowPage(html_dir + "tripRequest.html"));
        server.get("/tripRequest.css", new ShowFile( css_dir + "tripRequest.css", css_mime_type));
        server.get("/cancelTrip", new ShowPage(html_dir + "deleteTrip.html"));
        server.get("/cancelTrip.css", new ShowFile(css_dir + "deleteTrip.css", css_mime_type));
        server.get("/tripsList", new ShowPage(html_dir + "tripsList.html"));
        server.get("/tripsList.css", new ShowFile(css_dir + "tripsList.css", css_mime_type));
        server.get("/noTrips", new ShowPage(html_dir + "noTrips.html"));
        server.get("/noTrips.css", new ShowFile(css_dir + "noTrips.css", css_mime_type));
        server.get("/deleteConfirmation", new ShowPage(html_dir + "deleteConfirmation.html"));
        server.get("/deleteConfirmation.css", new ShowFile(css_dir + "deleteConfirmation.css", css_mime_type));
        server.get("/tripsListPage.css", new ShowFile(css_dir + "tripsListPage.css", css_mime_type));
        server.get("/tripId.css", new ShowFile(css_dir + "tripId.css", css_mime_type));
        server.get("/tripCost.css", new ShowFile(css_dir + "tripCost.css", css_mime_type));

        server.get("/notFound", new ShowPage(html_dir + "notFound.html"));
        server.get("/permissionDenied", new ShowPage(html_dir + "permissionDenied.html"));
        server.get("/signupBadRequest", new ShowPage(html_dir + "signupBadRequest.html"));
        server.get("/tripBadRequest", new ShowPage(html_dir + "tripBadRequest.html"));
        server.get("/deleteBadRequest", new ShowPage(html_dir + "deleteBadRequest.html"));
        server.get("/deletePermissionDenied", new ShowPage(html_dir + "deletePermissionDenied.html"));
        server.get("/deleteNotFound", new ShowPage(html_dir + "deleteNotFound.html"));
        server.get("/trispListBadRequest", new ShowPage(html_dir + "trispListBadRequest.html"));
        server.get("/tripsListPermissionDenied", new ShowPage(html_dir + "tripsListPermissionDenied.html"));
        server.get("/tripsListNotFound", new ShowPage(html_dir + "tripsListNotFound.html"));

        server.post("/signup", new SignupHandler(&database));
        server.post("/makeTrip", new TripRequestHandler(&database));
        server.post("/cancelTrip", new DeleteTripHandler(&database));
        server.post("/getCost", new ShowCostHandler(&database));
        server.post("/tripsList", new TripsListHandler(&database));
        server.post("/acceptTrip", new AcceptTripHandler(&database));
        server.post("/finishTrip", new FinishTripHandler(&database));
        
        server.run();
    }
    catch(Server::Exception& exeption) {
        cerr << exeption.getMessage() << endl;
    }
    return 0;
}
