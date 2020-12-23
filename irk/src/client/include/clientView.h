#ifndef CLIENTVIEW_H
#define CLIENTVIEW_H
#include <restbed>
#include <nlohmann/json.hpp>
#include <cstring>
#include <cstdlib>
#include <memory>
#include <string>

class Display {
 public:
  Display();
  ~Display();
  void logo();
  void menu();
  void createissue();
  void getissue();
  void listall();
  void assignissue();
  void updateissue();
  void settitle();
  void updatetitle();
  void setstatus();
  void updatestatus();
  void deleteissue();
  void getcomment();
  void deletecomment();
  void updatecomment();
  void confirmation();
  void error();
  void endline();

 private:
};

#endif  // CLIENTVIEW_H
