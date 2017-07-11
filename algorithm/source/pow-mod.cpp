typedef long long int64;

int64 pow_mod(int64 x, int64 n, int64 mod)
{
  int64 ret = 1;
  while(n > 0) {
    if(n & 1) (ret *= x) %= mod;
    (x *= x) %= mod;
    n >>= 1;
  }
  return ret;
}

