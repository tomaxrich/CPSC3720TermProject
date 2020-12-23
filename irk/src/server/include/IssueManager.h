#ifndef IssueManager_H
#define IssueManager_H
#include <restbed>
#include <nlohmann/json.hpp>
#include <cstring>
#include <cstdlib>
#include <memory>
#include <string>

using json = nlohmann::json;

class IssueManager {
 public:
  IssueManager();
  void load();
  void save();

// issues
  // @return issue created
  std::string createIssue(); //  tested

  std::string createIssue(std::string tempID);

  // @return issued deleted or issue does not exist
  std::string deleteIssue(std::string tempIssue); // tested
  // @return list all issue id numbers e.g. [1,2,4]
  std::string listAllIssues(); //  tested
  // @return returns and complete issue
  std::string getIssue(std::string tempIssue); //  tested
  // @return issue updated or issued does not exist
  std::string updateIssue(std::string tempIssue); //  tested


  std::string setIssueAttribute(std::string ID,
  std::string whatAttribute, std::string attributeValue);
  //

  std::string attributeExistMsg();
  std::string issueDoesNotExistMsg(); //  tested

  bool doesAttributeExist(std::string attribute);
  bool doesIssueExist(int ID); //   tested

// users

  // @return user created
  std::string createUser(); // tested
  std::string createUser(std::string tempID);
  // @return user deleted or user does not exist
  std::string deleteUser(std::string s);  // tested
  // @return list all user id numbers e.g. [1,2,4]
  std::string listAllUsers(); // tested
  std::string updateUser(std::string s); // tested
  std::string userDoesNotExistMsg(); //  tested
  bool doesUserExist(int ID); // //  tested

// both

  void test();
  ~IssueManager();

 private:
  json issues;
  json users;
};
#endif  // ISSUEMANAGER_H
