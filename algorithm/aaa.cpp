#include<bits/stdc++.h>
using namespace std;
int main()
{
  string s;

  vector< string > out;
  bool flag = false;
  while(getline(cin, s)) {
    if(s.find("section") != string::npos) flag ^= 1;
    if(flag) out.emplace_back(s);
  }
  out.emplace_back("</section>");
  for(auto& p : out) {
    cout << p << endl;
  }
}
