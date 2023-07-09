#include<bits/stdc++.h>
using namespace std;

enum WhereEnum { FROM, TO };

int main() {
  WhereEnum w;
  cerr << "W: " << w << endl;

  string s = "hello";
  cerr << "To Upper (" << s << "):";
  transform(
    s.cbegin(), s.cend(),
    s.begin(),
    [](unsigned char c) { return toupper(c); }
    );
  cerr << s << endl;
}
