struct NumberTheoreticTransform
{
  int mod;
  int primitiveroot;

  NumberTheoreticTransform(int mod, int root) : mod(mod), primitiveroot(root) {}

  inline int mod_pow(int x, int n)
  {
    int ret = 1;
    while(n > 0) {
      if(n & 1) ret = mul(ret, x);
      x = mul(x, x);
      n >>= 1;
    }
    return ret;
  }

  inline int inverse(int x)
  {
    return (mod_pow(x, mod - 2));
  }

  inline int add(unsigned x, int y)
  {
    x += y;
    if(x >= mod) x -= mod;
    return (x);
  }

  inline int mul(int a, int b)
  {
    unsigned long long x = (long long) a * b;
    unsigned xh = (unsigned) (x >> 32), xl = (unsigned) x, d, m;
    asm("divl %4; \n\t" : "=a" (d), "=d" (m) : "d" (xh), "a" (xl), "r" (mod));
    return (m);
  }

  void DiscreteFourierTransform(vector< int > &F, bool rev)
  {
    const int N = (int) F.size();
    for(int i = 0, j = 1; j + 1 < N; j++) {
      for(int k = N >> 1; k > (i ^= k); k >>= 1);
      if(i > j) swap(F[i], F[j]);
    }
    int w, wn, s, t;
    for(int i = 1; i < N; i <<= 1) {
      w = mod_pow(primitiveroot, (mod - 1) / (i * 2));
      if(rev) w = inverse(w);
      for(int k = 0; k < i; k++) {
        wn = mod_pow(w, k);
        for(int j = 0; j < N; j += i * 2) {
          s = F[j + k], t = mul(F[j + k + i], wn);
          F[j + k] = add(s, t), F[j + k + i] = add(s, mod - t);
        }
      }
    }
    if(rev) {
      int temp = inverse(N);
      for(int i = 0; i < N; i++) F[i] = mul(F[i], temp);
    }
  }

  vector< int > Multiply(const vector< int > &A, const vector< int > &B)
  {
    int sz = 1;
    while(sz < A.size() + B.size() - 1) sz <<= 1;
    vector< int > F(sz), G(sz);
    for(int i = 0; i < A.size(); i++) F[i] = A[i];
    for(int i = 0; i < B.size(); i++) G[i] = B[i];
    DiscreteFourierTransform(F, false);
    DiscreteFourierTransform(G, false);
    for(int i = 0; i < sz; i++) F[i] = mul(F[i], G[i]);
    DiscreteFourierTransform(F, true);
    F.resize(A.size() + B.size() - 1);
    return (F);
  }
};
