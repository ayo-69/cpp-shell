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

    // Parse input
    vector<char *> args = parse(input);

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

    // exit
    if (input == "exit")
      break;
  }
  return 0;
}
