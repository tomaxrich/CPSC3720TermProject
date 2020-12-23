# CPSC3720TermProject
Angel Tracker User Manual

To run the program:
1. cd into the ‘irk’ directory in one terminal window.
2. Enter ‘make server’.
3. Enter ‘./issueServer’ to run the server.
4. In another terminal window, cd into the ‘irk’ directory.
5. Enter ‘make client’.
6. Enter ‘./issueClient’ to run the client.
7. To exit the client enter ‘exit’ in the ‘Enter command’ prompt within the client
program
8. To stop the server press ‘ctrl + c’ with the server terminal window in focus.
Using Angel Tracker:
Enter commands at the prompt. Commands must have no spaces.
Valid Commands:
createissue – Creates an issue, enter the issue title in the ‘Enter title’ prompt.
Titles must have no spaces.
exit – Exits the client program.
Notes:
Currently, the createissue command creates a json object, sets the title attribute, and
prints it to a file called ‘test.json’ in the ‘irk’ directory. If a new issue is created, it
overwrites the issue that was previously created.
