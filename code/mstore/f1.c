int f1(int n) {
  if ( n > 1) 
    return n * f1(n-1);
  return 1;
}
