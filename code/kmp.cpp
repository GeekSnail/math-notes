#include <iostream>
#include <string>
#include <cassert>

using namespace std;

void prefix(const string pat, int lps[]) {
  int m = pat.size();
  int k = 0;
  lps[0] = 0;
  for (int i=1; i<m; i++) {
    while (k > 0 && pat[k] != pat[i])
      k = lps[k-1];
    if (pat[k] == pat[i])
      k++; //update length and also the next compared index
    lps[i] = k;
  }
}

void kmp(const string P, const string T) {
  const int m = P.size();
  const int n = T.size();
  int lps[m] = {0}; //int* lps = new int(m);
  int k = 0;
  prefix(P, lps);
  for (int i=0; i<n; i++) {
    while (k > 0 && P[k] != T[i])
      k = lps[k-1];
    if (P[k] == T[i]) {
      k++;
      if (k == m) {
        cout << "found pattern at index " << i-(k-1) << endl;
        k = lps[k-1];
      }
    }
  } 
}

int main() {
  string pat = "ababaca";
  string txt = "abababacaba";
  // int lps[pat.size()] = {0};
  // prefix(pat, lps);
  // kmp(pat, txt);//2
  kmp("AABA", "AABAACAADAABAABA");//0,9,12
  return 0;
}