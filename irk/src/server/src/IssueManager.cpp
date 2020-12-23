#include <nlohmann/json.hpp>
#include <iostream>
#include "IssueManager.h"
#include <fstream>
#include <iomanip>
#include "Convert.h"
#include <sstream>
#include <string>
#include <vector>

using json = nlohmann::json;

IssueManager::IssueManager() {}

void IssueManager::load() {
std::ifstream i("issues.json");
i >> issues;
i.close();

std::ifstream o("users.json");
o >> users;
o.close();
}

void IssueManager::save() {
std::ofstream o("issues.json");
o << std::setw(4) << issues << std::endl;
o.close();

std::ofstream j("users.json");
j << std::setw(4) << users << std::endl;
j.close();
}

// issues

std::string IssueManager::createIssue() {
Convert Convertor;
int ID = (issues.at(issues.size() - 1).at("ID#"));
ID++;
  json j = {
    {"ID#", ID},
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
    issues += j;
  return Convertor.convertToString(j);
}

std::string IssueManager::createIssue(std::string tempID) {
Convert Convertor;
int ID = stoi(tempID);
  json j = {
    {"ID#", ID},
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
  return Convertor.convertToString(j);
}

std::string IssueManager::deleteIssue(std::string tempIssue) {
Convert Convertor;
json deleteIssue = Convertor.convertToJson(tempIssue);
json temp;
int tempID = -1;
int deleteID = deleteIssue.at("ID#");
  if (doesIssueExist(deleteID) == true) {
    for (auto& element : issues) {
      tempID = element.at("ID#");
        if (tempID != deleteID)
          temp += element;
    }
    issues = temp;
    Convert Convertor;
    json j = {
    {"Result:", "Issue Deleted"}, };
    return Convertor.convertToString(j);
  }
return issueDoesNotExistMsg();
}

std::string IssueManager::listAllIssues() {
std::string temp; //NOLINT
Convert Convertor;
std::vector<int> c_vector;
// json j_vec(c_vector);
int tempID;

  for (auto & element : issues) {
    tempID = element.at("ID#");
    c_vector.push_back(tempID);
  }

  json j(c_vector);
  return Convertor.convertToString(j);
}

std::string IssueManager::getIssue(std::string tempIssue) {
Convert Convertor;
json temp = Convertor.convertToJson(tempIssue);
int returnIssueID = temp.at("ID#");
int issueID = 1;

  if (doesIssueExist(returnIssueID) != true) {
    return issueDoesNotExistMsg();
  } else {
     for (auto & element : issues) {
       issueID = element.at("ID#");
         if (returnIssueID == issueID)
           temp = element;
     }
    return Convertor.convertToString(temp);
  }
}

std::string IssueManager::updateIssue(std::string tempIssue) {
Convert Convertor;
json updateIssue = Convertor.convertToJson(tempIssue);
int tempID = -1;
int updateID = updateIssue.at("ID#");

std::cout << "json object in updateIssue" << std::endl;
std::cout << updateIssue;

  if (doesIssueExist(updateID) == true) {
    for (auto& element : issues) {
      tempID = element.at("ID#");
      if (tempID == updateID) {
        element = updateIssue;
        return Convertor.convertToString(updateIssue);
      }
    }
  }
return issueDoesNotExistMsg();
}

std::string IssueManager::setIssueAttribute (std::string ID, //NOLINT
std::string whatAttribute, std::string attributeValue) { //NOLINT
Convert convertor;
std::string jsonInStringFormat; //NOLINT
json tempJson;
int tempID = -1;
int issueID = std::stoi(ID);

// if(doesAttributeExist(whatAttribute) != true)
// return attributeExistMsg();

std::cout << "issue manager 1" << std::endl;

  if (doesIssueExist(issueID) == true) {
    // get temp issue
    jsonInStringFormat = createIssue(ID);
    // get correct issue
    jsonInStringFormat = getIssue(jsonInStringFormat);
    // convert to string
    tempJson = convertor.convertToJson(jsonInStringFormat);
    // update value
    tempJson[whatAttribute] = attributeValue;
    // convert to string
    jsonInStringFormat = updateIssue(convertor.convertToString(tempJson));

    return jsonInStringFormat;
  } else {
      return issueDoesNotExistMsg();
  }
}

std::string IssueManager::issueDoesNotExistMsg() {
Convert Convertor;
json j = {
{"Result:", "Issue Does Not Exist"}, };
return Convertor.convertToString(j);
}

std::string IssueManager::attributeExistMsg() {
Convert Convertor;
json j = {
{"Result:", "Attribute Does Not Exist"}, };
return Convertor.convertToString(j);
}

bool IssueManager::doesIssueExist(int ID) {
int tempID = -1;
  for (auto & element : issues) {
    tempID = element.at("ID#");
    if (tempID == ID)
      return true;
  }
return false;
}

bool IssueManager::doesAttributeExist(std::string attribute) {
  if ( (attribute == "Assigned") ||
       (attribute ==  "Comments") ||
       (attribute ==  "Component") ||
       (attribute == "Priority") ||
       (attribute == "Reporter") ||
       (attribute == "Status") ||
       (attribute == "Title") ||
       (attribute == "Type") ||
       (attribute == "UsersGroup") ||
       (attribute == "Voting") )
  return true;
  else
  return false;
}

// users

std::string IssueManager::createUser() {
Convert Convertor;
int ID = (users.at(users.size() - 1).at("ID#"));
ID++;
  json j = {
  {"username", ""},
  {"ID#", ID},
	{"group", ""}, //NOLINT
  };
  users += j;
  return Convertor.convertToString(j);
}

std::string IssueManager::createUser(std::string tempID) {
Convert Convertor;
  json j = {
  {"username", ""},
  {"ID#", std::stoi(tempID)},
	{"group", ""}, //NOLINT
  };
  return Convertor.convertToString(j);
}

std::string IssueManager::deleteUser(std::string tempUser) {
Convert Convertor;
json deleteUser = Convertor.convertToJson(tempUser);
json temp;
int tempID = -1;
int deleteID = deleteUser.at("ID#");
  if (doesUserExist(deleteID) == true) {
    for (auto& element : users) {
	    tempID = element.at("ID#"); //NOLINT
        if (tempID != deleteID)  //NOLINT
		      temp += element;      //NOLINT
	} //NOLINT
    users = temp;
    Convert Convertor;
    json j = {
    {"Result:", "User Deleted"}, };
    return Convertor.convertToString(j);
  }
return userDoesNotExistMsg();
}


std::string IssueManager::listAllUsers() {
std::string temp; //NOLINT
Convert Convertor;
std::vector<int> c_vector;
// json j_vec(c_vector);
int tempID;
for (auto & element : users) {
tempID = element.at("ID#");
c_vector.push_back(tempID);
}
json j(c_vector);
return Convertor.convertToString(j);
}

std::string IssueManager::updateUser(std::string tempUser) {
Convert Convertor;
json temp = Convertor.convertToJson(tempUser);
int returnIssueID = temp.at("ID#");
int userID = -1;

if(doesUserExist(returnIssueID) != true)
return userDoesNotExistMsg();

  for (auto & element : users) {
    userID = element.at("ID#");
      if (returnIssueID == userID) {
        element = temp;
      }
  }

json j = {
{"Result:", "User Updated"}, };
return Convertor.convertToString(j);
}

bool IssueManager::doesUserExist(int ID) {
int tempID = -1;
  for (auto & element : users) {
    tempID = element.at("ID#");
      if (tempID == ID)
        return true;
  }
return false;
}

std::string IssueManager::userDoesNotExistMsg() {
Convert Convertor;
json j = {
{"Result:", "User Does Not Exist"}, };
return Convertor.convertToString(j);
}

IssueManager::~IssueManager() {}
