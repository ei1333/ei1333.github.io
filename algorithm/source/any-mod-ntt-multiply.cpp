// http://math314.hateblo.jp/entry/2015/05/07/014908
inline int add(unsigned x, int y, int mod)
{
  x += y;
  if(x >= mod) x -= mod;
  return (x);
}

inline int mul(int a, int b, int mod)
{
  unsigned long long x = (long long) a * b;
  unsigned xh = (unsigned) (x >> 32), xl = (unsigned) x, d, m;
  asm("divl %4; \n\t" : "=a" (d), "=d" (m) : "d" (xh), "a" (xl), "r" (mod));
  return (m);
}

inline int mod_pow(int x, int n, int mod)
{
  int ret = 1;
  while(n > 0) {
    if(n & 1) ret = mul(ret, x, mod);
    x = mul(x, x, mod);
    n >>= 1;
  }
  return ret;
}

inline int inverse(int x, int mod)
{
  return (mod_pow(x, mod - 2, mod));
}

vector< int > AnyModNTTMultiply(vector< int > a, vector< int > b, int mod)
{
  for(auto &x : a) x %= mod;
  for(auto &x : b) x %= mod;
  NumberTheoreticTransform ntt1(167772161, 3);
  NumberTheoreticTransform ntt2(469762049, 3);
  NumberTheoreticTransform ntt3(1224736769, 3);
  auto x = ntt1.Multiply(a, b);
  auto y = ntt2.Multiply(a, b);
  auto z = ntt3.Multiply(a, b);
  const int m1 = ntt1.mod, m2 = ntt2.mod, m3 = ntt3.mod;
  const int m1_inv_m2 = inverse(m1, m2);
  const int m12_inv_m3 = inverse(mul(m1, m2, m3), m3);
  const int m12_mod = mul(m1, m2, mod);
  vector< int > ret(x.size());
  for(int i = 0; i < x.size(); i++) {
    int v1 = mul(add(y[i], m2 - x[i], m2), m1_inv_m2, m2);
    int v2 = mul(add(z[i], m3 - add(x[i], mul(m1, v1, m3), m3), m3), m12_inv_m3, m3);
    ret[i] = add(x[i], add(mul(m1, v1, mod), mul(m12_mod, v2, mod), mod), mod);
  }
  return ret;
}
