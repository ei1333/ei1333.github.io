template< typename T >
T extgcd(T a, T b, T &x, T &y) {
  x = 1, y = 0;
  int g = a;
  if(b != 0) {
    g = extgcd(b, a % b, y, x);
    y -= a / b * x;
  }
  return g;
}

template< typename T >
T mod_inv(T a, T m) {
  T x, y;
  extgcd(a, m, x, y);
  return (m + x % m) % m;
}
