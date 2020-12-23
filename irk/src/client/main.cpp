#include <restbed>
#include <nlohmann/json.hpp>
#include <memory>
#include <string>
#include <future>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include "clientView.h"
#include "Convert.h"

/* Service information */
const char* HOST = "localhost";
const int PORT = 1234;

/* Server operations */
const char* CREATEISSUE = "createissue";
const char* GETISSUE = "getissue";
const char* LISTALL = "listall";
const char* ASSIGNISSUE = "assignissue";
const char* UPDATEISSUE = "updateissue";
const char* SETTITLE = "settitle";
const char* UPDATETITLE = "updatetitle";
const char* SETSTATUS = "setstatus";
const char* UPDATESTATUS = "updatestatus";
const char* DELETEISSUE = "deleteissue";
const char* CREATEUSER = "createuser";
const char* DELETEUSER = "deleteuser";
const char* LISTALLUSERS = "listallusers";
const char* GETCOMMENT = "getcomment";
const char* DELETECOMMENT = "deletecomment";
const char* UPDATECOMMENT = "updatecomment";
/*
"createissue"
"getissue"
"listall"
"assignissue"
"updateissue"
"settitle"
"updatetitle"
"setstatus"
"updatestatus"
"deleteissue"
"getcomment"
"deletecomment"
"updatecomment"
*/
/**
* Create a POST request for the service
* @param op The command to fullfill.
* @param str The title string (so far).
*/

// move into view later
// neeed error checking later

void setToNull(std::string & s1, std::string  & s2, std::string & s3) {
s1 = "";
s1 = "null";
s2 = "";
s2 = "null";
s3 = "";
s3 = "null";
}

// move into view later

std::shared_ptr<restbed::Request> create_post_service_request(const std::string& operation, const std::string& str, const std::string& str1, const std::string& str2) {
    // Create the URI string
    std::string uri_str;
    uri_str.append("http://");
    uri_str.append(HOST);
    uri_str.append(":");
    uri_str.append(std::to_string(PORT));
    uri_str.append("/service");

    // Configure request headers
    auto request = std::make_shared<restbed::Request>(restbed::Uri(uri_str));
    request->set_header("Accept", "*/*");
    request->set_method("POST");
    request->set_header("Content-Type", "text/plain");

    // Create the message
    std::string message;
    message.append(operation);
// replace , with ^
    message.append(",");
    message.append(str);

    message.append(",");
    message.append(str1);

    message.append(",");
    message.append(str2);

    // Set the message
    request->set_header("Content-Length", std::to_string(message.length()));
    request->set_body(message);
    return request;
}

/**
* Create a GET request for the service
* @param op The command to fullfill.
* @param str The title string (so far).
*/
std::shared_ptr<restbed::Request> create_get_service_request(const std::string& operation,
    const std::string str, const std::string str1, const std::string str2) {
    // Create the URI string
  std::string uri_str;
  uri_str.append("http://");
  uri_str.append(HOST);
  uri_str.append(":");
  uri_str.append(std::to_string(PORT));
  uri_str.append("/service");

  // Configure request headers
  auto request = std::make_shared<restbed::Request>(restbed::Uri(uri_str));
  request->set_method("GET");

  // Set the parameters
  request->set_query_parameter("op", operation);
  request->set_query_parameter("title", str);
  request->set_query_parameter("input1", str1);
  request->set_query_parameter("input2", str2);
  return request;
}

/**
* Handle the response from the service.
* @param response The response object from the server.
*/
void handle_response(std::shared_ptr<restbed::Response> response) {
  int status_code = response->get_status_code();
  auto length = response->get_header("Content-Length", 0);
  Display view;
  restbed::Http::fetch(length, response);
  std::string responseStr(reinterpret_cast<char*>(response->get_body().data()), length);
  std::cout << responseStr << std::endl;
}

int main(const int, const char**) {
  std::string inputStr = "";
  std::string inputStr2 = "";
  std::string switchStr = "null";
  std::string variableStr1 = "null";
  std::string variableStr2 = "null";
  setToNull(switchStr, variableStr1, variableStr2);
  bool running = true;
  Display view;
  view.logo();
  view.menu();

  //main client loop
  while (running) {
  std::cin >> inputStr;
  view.endline();

  //convert to lowercase
  for (int i = 0; i < inputStr.length(); i++) {
    inputStr[i] = std::tolower(inputStr[i]);
  }

  if (inputStr == "createissue") {
    switchStr = "null";
  //A POST request CREATE
    std::shared_ptr<restbed::Request> request = create_post_service_request(CREATEISSUE, switchStr, variableStr1, variableStr2);
    auto response = restbed::Http::sync(request);
    handle_response(response);
    setToNull(switchStr, variableStr1, variableStr2);
  } else if (inputStr == "getissue") {
      view.getissue();
      std::cin >> switchStr;

      //A POST request GETISSUE
      std::shared_ptr<restbed::Request> request = create_post_service_request(GETISSUE, switchStr, variableStr1, variableStr2);
      auto response = restbed::Http::sync(request);
      handle_response(response);
      setToNull(switchStr, variableStr1, variableStr2);

  } else if (inputStr == "listall") {
      view.listall();
      switchStr = "null";

      std::shared_ptr<restbed::Request> request = create_post_service_request(LISTALL, switchStr, variableStr1, variableStr2);
      auto response = restbed::Http::sync(request);
      handle_response(response);
      setToNull(switchStr, variableStr1, variableStr2);

  } else if (inputStr == "setissueattribute") {
      view.getissue();
      std::cin >> switchStr;

      std::cout << "enter attribute:" << std::endl;
      std::cin >> variableStr1;

      std::cout << "enter attribute value:" << std::endl;
      std::cin >> variableStr2; // for input

      std::shared_ptr<restbed::Request> request = create_post_service_request(UPDATEISSUE, switchStr, variableStr1, variableStr2);
      auto response = restbed::Http::sync(request);
      handle_response(response);

  //A POST request UPDATEISSUE
      setToNull(switchStr, variableStr1, variableStr2);
  } else if (inputStr == "updateissue") {
      view.updateissue();
      std::cin >> switchStr;
      std::cin >> inputStr;
      std::cin >> inputStr2;

      std::shared_ptr<restbed::Request> request = create_post_service_request(UPDATEISSUE, switchStr, variableStr1, variableStr2);
      auto response = restbed::Http::sync(request);
      handle_response(response);

  //A POST request DELETEISSUE
      setToNull(switchStr, variableStr1, variableStr2);
  } else if (inputStr == "deleteissue") {
      view.deleteissue();
      std::cin >> switchStr;

      std::shared_ptr<restbed::Request> request = create_post_service_request(DELETEISSUE, switchStr, variableStr1, variableStr2);
      auto response = restbed::Http::sync(request);
      handle_response(response);

  //A POST request CREATEUSER
  } else if (inputStr == "createuser") {
      std::shared_ptr<restbed::Request> request = create_post_service_request(CREATEUSER, switchStr, variableStr1, variableStr2);
      auto response = restbed::Http::sync(request);
      handle_response(response);

  //A POST request CREATEUSER
      setToNull(switchStr, variableStr1, variableStr2);
  } else if (inputStr == "listallusers") {
      view.deleteissue();
  //A POST request DELETE
      std::shared_ptr<restbed::Request> request = create_post_service_request(LISTALLUSERS, switchStr, variableStr1, variableStr2);
      auto response = restbed::Http::sync(request);
      handle_response(response);
  } else if (inputStr == "deleteuser") {
      view.deleteissue();
      std::cin >> switchStr;
  //A POST request DELETEISSUE
      std::shared_ptr<restbed::Request> request = create_post_service_request(DELETEUSER, switchStr, variableStr1, variableStr2);
      auto response = restbed::Http::sync(request);
      handle_response(response);
  } else if (inputStr == "exit") {
      std::cout << "Exiting program..." << std::endl;
      running = false;
  } else {
      std::cout << "Invalid command." << std::endl;
    }
  }
return EXIT_SUCCESS;
}
