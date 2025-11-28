#include <unistd.h>
#include <iostream>
#include <sched.h>
#include <sstream>
#include <string>
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
    vector<char*> tokens = parse(input); 

    // Execute
    
    // exit 
    if (input == "exit")
      break;
  }
  return 0;
}
