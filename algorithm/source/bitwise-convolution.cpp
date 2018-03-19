namespace BitWiseConvolution {

  int mod_pow(int64_t x, int n, int mod) {
    int64_t ret = 1;
    while(n > 0) {
      if(n & 1) (ret *= x) %= mod;
      (x *= x) %= mod;
      n >>= 1;
    }
    return (int) ret;
  }

  inline int add(int a, int b, int mod) {
    a += b;
    if(a >= mod) a -= mod;
    return a;
  }

  inline int mul(int a, int b, int mod) {
    unsigned long long x = (long long) a * b;
    unsigned xh = (unsigned) (x >> 32), xl = (unsigned) x, d, m;
    asm("divl %4; \n\t" : "=a" (d), "=d" (m) : "d" (xh), "a" (xl), "r" (mod));
    return (m);
  }

  void FastWalshHadamardTransform(vector< int > &F, int mod) {
    const int N = (int) F.size();
    for(int i = 1; i < N; i <<= 1) {
      for(int j = 0; j < N; j += i * 2) {
        for(int k = 0; k < i; k++) {
          int s = F[j + k], t = F[j + k + i];
          F[j + k] = add(s, t, mod);
          F[j + k + i] = add(s, mod - t, mod);
        }
      }
    }
  }

  void FastAndTransform(vector< int > &F, int mod, bool inv) {
    const int N = (int) F.size();
    for(int i = 1; i < N; i <<= 1) {
      for(int j = 0; j < N; j += i * 2) {
        for(int k = 0; k < i; k++) {
          int s = F[j + k], t = F[j + k + i];
          if(inv) F[j + k] = add(s, mod - t, mod);
          else F[j + k] = add(s, t, mod);
        }
      }
    }
  }


  void FastOrTransform(vector< int > &F, int mod, bool inv) {
    const int N = (int) F.size();
    for(int i = 1; i < N; i <<= 1) {
      for(int j = 0; j < N; j += i * 2) {
        for(int k = 0; k < i; k++) {
          int s = F[j + k], t = F[j + k + i];
          if(inv) F[j + k + i] = add(mod - s, t, mod);
          else F[j + k + i] = add(s, t, mod);
        }
      }
    }
  }

  vector< int > xor_convolution(vector< int > a, vector< int > b, int mod) {
    FastWalshHadamardTransform(a, mod);
    FastWalshHadamardTransform(b, mod);
    for(int i = 0; i < a.size(); i++) a[i] = mul(a[i], b[i], mod);
    FastWalshHadamardTransform(a, mod);
    auto rev = mod_pow((int) a.size(), mod - 2, mod);
    for(auto &x : a) x = (int) (1LL * x * rev % mod);
    return a;
  }

  vector< int > and_convolution(vector< int > a, vector< int > b, int mod) {
    FastAndTransform(a, mod, false);
    FastAndTransform(b, mod, false);
    for(int i = 0; i < a.size(); i++) a[i] = mul(a[i], b[i], mod);
    FastAndTransform(a, mod, true);
    return a;
  }

  vector< int > or_convolution(vector< int > a, vector< int > b, int mod) {
    FastOrTransform(a, mod, false);
    FastOrTransform(b, mod, false);
    for(int i = 0; i < a.size(); i++) a[i] = mul(a[i], b[i], mod);
    FastOrTransform(a, mod, true);
    return a;
  }
};
