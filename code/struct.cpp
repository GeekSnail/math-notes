#include <iostream>

#define MaxSize 10

using namespace std;

struct Stack {
  int data[MaxSize];
  int top = -1; //
  int getTop() {
    return top;
  }
};

int main() {
  int a[] = {1,2,3};
  struct Stack S;
  cout << S.getTop();
  return 0;
}