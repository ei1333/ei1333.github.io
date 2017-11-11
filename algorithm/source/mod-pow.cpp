using int64 = long long;

int64 mod_pow(int64 x, int64 n, int64 mod)
{
  int64 ret = 1;
  while(n > 0) {
    if(n & 1) (ret *= x) %= mod;
    (x *= x) %= mod;
    n >>= 1;
  }
  return ret;
}

