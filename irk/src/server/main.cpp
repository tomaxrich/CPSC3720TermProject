#include <restbed>
#include <nlohmann/json.hpp>
#include <memory>
#include <string>
#include <future>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include "Convert.h"
#include "IssueManager.h"

enum OPERATION {CREATEISSUE, GETISSUE, LISTALL, ASSIGNISSUE, UPDATEISSUE, DELETEISSUE, CREATEUSER,
DELETEUSER, LISTALLUSERS, UNKNOWN};

struct expression {
OPERATION op;
std::string title;
std::string input;
std::string input1;
std::string input2;
};
//test

// Response header to prevent a cross-site validation problem
#define ALLOW_ALL { "Access-Control-Allow-Origin", "*" }

// Response header to close connection
#define CLOSE_CONNECTION { "Connection", "close" }

std::string createTempIssue(int temp) {
Convert c;
  nlohmann::json j = {
    {"ID#", temp},
    {"Title", ""},
    {"Comments", ""},
    {"Status", ""},
    {"Assigned", -1},
    {"Component", ""},
    {"Priority", ""},
    {"Reporter", ""},
    {"Voting", ""},
    {"Type", ""},
    {"UsersGroup", ""},
    };
  return c.convertToString(j);
}

void set_operation(expression* expr, const char* operation) {
  if (strcmp("createissue", operation) == 0)
    expr->op = CREATEISSUE;
  else if (strcmp("getissue", operation) == 0)
    expr->op = GETISSUE;
  else if (strcmp("listall", operation) == 0)
    expr->op = LISTALL;
  else if (strcmp("assignissue", operation) == 0)
    expr->op = ASSIGNISSUE;
  else if (strcmp("updateissue", operation) == 0)
    expr->op = UPDATEISSUE;
  else if (strcmp("deleteissue", operation) == 0)
    expr->op = DELETEISSUE;
  else if (strcmp("createuser", operation) == 0)
    expr->op = CREATEUSER;
  else if (strcmp("deleteuser", operation) == 0)
    expr->op = DELETEUSER;
  else if (strcmp("listallusers", operation) == 0)
    expr->op = LISTALLUSERS;
  else
    expr->op = UNKNOWN;
}

/**
 * Parses an expression of the format "<OPERATION>,<string>"
 * @param data The string to parse.
 * @param exp A pointer to the expression struct to fill in.
 */
void parse(const char* data, expression* expr) {
char* data_mutable = const_cast<char*>(data);
char* operation = strtok_r(data_mutable, ",", &data_mutable);
char* title = strtok_r(nullptr, ",", &data_mutable);
char* input1 = strtok_r(nullptr, ",", &data_mutable);
char* input2 = strtok_r(nullptr, ",", &data_mutable);

set_operation(expr, operation);
expr->title = title;
expr->input1 = input1;
expr->input2 = input2;
std::cout << expr->title << std::endl;
}
/**
* Replies with either the answer or an error message.
*/
void compute(expression exp,
             const std::shared_ptr<restbed::Session >& session) {
    nlohmann::json j;
    IssueManager service;
    std::string tempIssue = exp.title;
    std::string tempAttribute1 = exp.input1;
    std::string tempAttribute2 = exp.input2;

    //attempts at communication
    std::string pass;
    std::string packet;
    Convert c;
    service.load();
    std::string tempJsonObject;
    //try {
        switch (exp.op) {
        case CREATEISSUE:
          pass = service.createIssue();
          service.save();
          break;
        case GETISSUE:
          tempJsonObject = createTempIssue(std::stoi(tempIssue));
          pass = service.getIssue(tempJsonObject);
          break;
        case LISTALL:
          pass = service.listAllIssues();
          break;
        case UPDATEISSUE:
          pass = service.setIssueAttribute(
          tempIssue, tempAttribute1, tempAttribute2);
          service.save();
          break;
        case DELETEISSUE:
          tempJsonObject = createTempIssue(std::stoi(tempIssue));
          pass = service.deleteIssue(tempJsonObject);
          service.save();
          break;
        case CREATEUSER:
          pass = service.createUser();
          service.save();
          break;
        case DELETEUSER:
            pass = service.deleteUser(service.createUser(tempIssue));
            service.save();
            break;
        case LISTALLUSERS:
            pass = service.listAllUsers();
            service.save();
            break;
        default:
            std::string errorMsg = "Invalid Operator";
            session->close(restbed::BAD_REQUEST, "Invalid Operator", { ALLOW_ALL, { "Content-Length", std::to_string(errorMsg.length()) }, CLOSE_CONNECTION });
            return;
        }
    std::string response = pass;
    std::string temp = pass;
    session->close(restbed::OK, response, { ALLOW_ALL, { "Content-Length", std::to_string(response.length()) }, CLOSE_CONNECTION });
}

/**
* POST request callback function.
*/
void post_request(const std::shared_ptr<restbed::Session >&
                  session, const restbed::Bytes & body) {
expression exp;
const char* data = reinterpret_cast<const char*>(body.data());
parse(data, &exp);
compute(exp, session);
}
/**
* Handle a POST request.
* @param session The request session.
*/
void post_method_handler(const std::shared_ptr<restbed::Session>& session) {
const auto request = session->get_request();
size_t content_length = request->get_header("Content-Length", 0);
session->fetch(content_length, &post_request);
}

/**
* Handle a GET request.
* @param session The request session.
*/
void get_method_handler(const std::shared_ptr<restbed::Session>& session) {
const auto request = session->get_request();

expression exp;
exp.op = UNKNOWN;
exp.title = "";

  if (request->has_query_parameter("op")) {
    set_operation(&exp, request->get_query_parameter("op").c_str());
      if (request->has_query_parameter("title")) {
        exp.title = request->get_query_parameter("title");
      }
  }

compute(exp, session);
}

int main(const int, const char**) {
// Setup service and request handlers
auto resource = std::make_shared<restbed::Resource>();
resource->set_path("/service");
resource->set_method_handler("POST", post_method_handler);
resource->set_method_handler("GET", get_method_handler);

auto settings = std::make_shared<restbed::Settings>();
settings->set_port(1234);

// Publish and start service
restbed::Service service;
service.publish(resource);

service.start(settings);
return EXIT_SUCCESS;
}


