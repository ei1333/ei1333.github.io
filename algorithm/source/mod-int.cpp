template< int mod >
struct ModInt
{
  int x;

  ModInt() : x(0) {}

  ModInt(long long y) : x(y >= 0 ? y % mod : (mod - (-y) % mod) % mod) {}

  ModInt &operator+=(const ModInt &p)
  {
    if((x += p.x) >= mod) x -= mod;
    return *this;
  }

  ModInt &operator-=(const ModInt &p)
  {
    if((x += mod - p.x) >= mod) x -= mod;
    return *this;
  }

  ModInt &operator*=(const ModInt &p)
  {
    x = 1LL * x * p.x % mod;
    return *this;
  }

  ModInt &operator/=(const ModInt &p)
  {
    x = 1LL * x * p.inverse() % mod;
    return *this;
  }

  ModInt operator-() const { return ModInt(-x); }

  ModInt operator+(const ModInt &p) const { return ModInt(*this) += p; }

  ModInt operator-(const ModInt &p) const { return ModInt(*this) -= p; }

  ModInt operator*(const ModInt &p) const { return ModInt(*this) *= p; }

  ModInt operator/(const ModInt &p) const { return ModInt(*this) /= p; }

  ModInt inverse() const
  {
    int a = x, b = mod, u = 1, v = 0, t;
    while(b > 0) {
      t = a / b;
      a -= t * b;
      swap(a, b);
      u -= t * v;
      swap(u, v);
    }
    return ModInt(u);
  }

  friend ostream &operator<<(ostream &os, ModInt< mod > &p)
  {
    return os << p.x;
  }

  friend istream &operator>>(istream &is, ModInt< mod > &a)
  {
    long long x;
    is >> a.x;
    a = ModInt< mod >(a.x);
    return (is);
  }
  
};

const int mod = 1e9 + 7;
using modint = ModInt< mod >;
