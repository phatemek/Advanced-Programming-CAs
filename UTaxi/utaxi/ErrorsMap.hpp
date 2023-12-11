#ifndef __ERRORS__MAP__
#define __ERRORS__MAP__
#include <map>
#include <string>

const std::map<std::string, std::string> errors_map = {
    { "Not Found", "/notFound" },
    { "Permission Denied", "/permissionDenied" },
    { "Signup Bad Request", "/signupBadRequest" },
    { "Trip Bad Request", "/tripBadRequest" },
    { "Delete Bad Request", "/deleteBadRequest" },
    { "Delete Permission Denied", "/deletePermissionDenied" },
    { "Delete Not Found", "/deleteNotFound" },
    { "Trips List Bad Request", "/trispListBadRequest" },
    { "Trips List Permission Denied", "/tripsListPermissionDenied" },
    { "Trips List Not Found", "/tripsListNotFound" }
};

#endif
