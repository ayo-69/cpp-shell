#include "shell.h"
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <sched.h>
#include <sstream>
#include <string>
#include <sys/wait.h>
#include <unistd.h>
#include <fstream>
#include <vector>

extern char **environ;

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

void run_shell(istream &in) {
  for (;;) {
    // Get input
    if (in.rdbuf() == cin.rdbuf()) {
      cout << "$ ";
    }
    string input;
    if (!getline(in, input)) {
      break;
    }

    // exit
    if (input == "exit")
      break;

    // Parse input
    vector<char *> args = parse(input);
    if (args.empty()) {
      continue;
    }

    // cd
    if (string cd = "cd"; args[0] == cd) {
      if (args.size() > 1) {
        if (chdir(args[1]) != 0)
          perror("cd failed");
      } else {
        cerr << "cd: missing arguements" << endl;
      }
      continue;
    }

    if (args[0] == "setenv") {
      if (args.size() != 3) {
        cerr << "setenv: incorrect number of arguments" << endl;
      } else {
        if (setenv(args[1], args[2], 1) != 0) {
          perror("setenv failed");
        }
      }
      continue;
    }

    if (args[0] == "printenv") {
      if (args.size() == 1) {
        for (char **env = environ; *env != 0; env++) {
          cout << *env << endl;
        }
      } else {
        char *value = getenv(args[1]);
        if (value != nullptr) {
          cout << value << endl;
        }
      }
      continue;
    }

    if (args[0] == "source") {
      if (args.size() != 2) {
        cerr << "source: incorrect number of arguments" << endl;
      } else {
        ifstream file(args[1]);
        if (!file.is_open()) {
          perror("source: could not open file");
          continue;
        }
        run_shell(file);
      }
      continue;
    }

    if (args[0] == "cd") {
      const char *dir = (args.size() > 1) ? args[1] : getenv("HOME");
      if (!dir)
        dir = "/";
      if (chdir(dir) != 0)
        perror("cd failed");
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
}
