#include <nlohmann/json.hpp>
#include <iostream>
#include "clientView.h"
#include <string>

Display::Display() {}
Display::~Display() {}

void Display::logo() {
  std::cout << std::endl;
  std::cout << "        **        " << std::endl;
  std::cout << "   /|  <  >  /|   " << std::endl;
  std::cout << "  /  |  __  /  |  " << std::endl;
  std::cout << "      |/  |/      " << std::endl;
  std::cout << "      /    |      " << std::endl;
  std::cout << "     /      |     " << std::endl;
  std::cout << "   Angel Tracker  " << std::endl;
  std::cout << "       2.0        " << std::endl;
  std::cout << std::endl;
}
void Display::menu() {
  std::cout<< std::endl << std::endl;
  std::cout << "List of Commands:" << std::endl;
  std::cout<< std::endl;

  std::cout << "Issues Commands:" << std::endl;
  std::cout << "  -createissue: creates issue" << std::endl;
  std::cout << "  -getissue: gets issue" << std::endl;
  std::cout << "  -listall: list all issues" << std::endl;
  std::cout << "  -setissueattribute: sets an issue attribute" << std::endl;
  std::cout << "  -deleteissue: deletes an issue" <<  std::endl << std::endl;

  std::cout << "User Commands" << std::endl;
  std::cout << "  -createuser: creates a user" << std::endl;
  std::cout << "  -listallusers: lists all user id" << std::endl;
  std::cout << "  -deleteuser: deletes an issue" << std::endl << std::endl;
  std::cout << "  -exit: exits program" << std::endl;
  std::cout << "  -help: prints the cmd list" << std::endl;
  std::cout << std::endl;
  std::cout << "Enter command: ";
}

void Display::createissue() {
  std::cout << "Creating title...\n";
}

void Display::getissue() {
  std::cout << "Enter ID#: \n";
}

void Display::listall() {
  std::cout << "please hit enter\n";
  std::cout << "Listing Issues:\n";
}

void Display::assignissue() {
  std::cout << "Enter technician: ";
}

void Display::updateissue() {
  std::cout << "Enter ID first\n";
  std::cout << "Enter Key Value\n";
  std::cout << "Enter associated pair\n";
}

void Display::settitle() {
  std::cout << "Enter title: ";
}

void Display::updatetitle() {
  std::cout << "Enter title: ";
}

void Display::setstatus() {
  std::cout << "Enter status: ";
}

void Display::updatestatus() {
  std::cout << "Enter status: ";
}

void Display::deleteissue() {
  std::cout << "Enter ID#: ";
}

void Display::getcomment() {
  std::cout << "Enter ID#: ";
}

void Display::deletecomment() {
  std::cout << "Enter ID#: ";
}

void Display::updatecomment() {
  std::cout << "Enter Comment: ";
}

void Display::confirmation() {
  std::cout << "Confirmed";
}

void Display::error() {
  std::cout << "failed";
}

void Display::endline() {
  std::cout << std::endl;
}
