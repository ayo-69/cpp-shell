#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <sched.h>
#include <sstream>
#include <string>
#include <sys/wait.h>
#include <unistd.h>
#include <vector>

using namespace std;

vector<char *> parse(string line) {
  stringstream stream(line);
  vector<char *> tokens;
  string t;
  while (stream >> t)
    tokens.push_back(const_cast<char *>(t.c_str()));
  tokens.push_back(nullptr);
  return tokens;
}

int main() {

  for (;;) {
    // Get input
    cout << "$ ";
    string input;
    getline(cin, input);

    // exit
    if (input == "exit")
      break;

    // Parse input
    vector<char *> args = parse(input);

    // cd
    if (string cd = "cd"; args[0] == cd) {
      if (args.size() > 1) {
        if (chdir(args[1]) != 0) perror("cd failed"); 
      } else {
        cerr << "cd: missing arguements" << endl; 
      }
      continue;
    }

    // // author
    // if (args[0] == "author") {
    //   cout << "Isaac N. Hayab <isaachayab0@gmail.com>" << endl; 
    //   continue;
    // }

    // // gemini
    // if (args[0] == "gemini") {
    //   cout << "Hello from Gemini!" << endl;
    //   continue;
    // }

    if (args[0] == "cd") {
      const char *dir = (args.size() > 1) ? args[1] : getenv("HOME");
      if (!dir) dir = "/";
      if (chdir(dir) != 0) perror("cd failed"); 
      continue;
    }

    // Execute
    pid_t pid = fork();
    if (pid == 0) {
      // Child process
      if (execvp(args[0], args.data()) == -1)
        perror("execvp failed");
      exit(EXIT_FAILURE);
    } else if (pid < 0) {
      cerr << "fork failed" << endl;
      continue;
    } else {
      // Parent process
      wait(nullptr);
    }
  }
  return 0;
}
