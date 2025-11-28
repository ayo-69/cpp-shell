#include <iostream>
#include <string>

using namespace std;

int main() {

  for (;;) {
    cout << "$ ";
    string input;
    getline(cin, input);

    if (input == "exit") break;
  }
  return 0;
}
