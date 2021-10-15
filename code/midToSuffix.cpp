#include <string>
#include <stack>
#include <cassert>

using namespace std;

string midToSuffix(string s) {
  string str("");
  stack<char> st;
  for (string::iterator it = s.begin(); it!=s.end(); it++) {
    if (*it == '(' || *it == '*' || *it == '/') {
      st.push(*it);
    } else if (*it == ')') {
      str += st.top();
      st.pop();
      st.pop(); //'('
    } else if (*it == '+' || *it == '-') {
      if (!st.empty()) {
        char c = st.top();
        if (c == '*' || c == '/') {
          str += c;
          st.pop();
          if (!st.empty()) {
            c = st.top();
            if (c == '+' || c == '-') {
              str += c;
              st.pop();
            }
          }
        } 
      }
      st.push(*it);
    } else {
      str += *it;
    }
  }
  while (!st.empty()) {
    str += st.top();
    st.pop();
  }
  return str;
}

int main() {
  assert(("A+B*(C-D)-E/F", midToSuffix("A+B*(C-D)-E/F")=="ABCD-*+EF/-"));
  assert(midToSuffix("a+b*c+(d*e+f)*g")=="abc*+de*f+g*+");
  return 0;
}