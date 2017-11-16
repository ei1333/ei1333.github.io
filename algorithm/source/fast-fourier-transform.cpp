namespace FastFourierTransform
{
  using C = complex< double >;

  void DiscreteFourierTransform(vector< C > &F, bool rev)
  {
    const int N = (int) F.size();
    const double PI = (rev ? -1 : 1) * acos(-1);
    for(int i = 0, j = 1; j + 1 < N; j++) {
      for(int k = N >> 1; k > (i ^= k); k >>= 1);
      if(i > j) swap(F[i], F[j]);
    }
    C w, s, t;
    for(int i = 1; i < N; i <<= 1) {
      for(int k = 0; k < i; k++) {
        w = std::polar(1.0, PI / i * k);
        for(int j = 0; j < N; j += i * 2) {
          s = F[j + k];
          t = C(F[j + k + i].real() * w.real() - F[j + k + i].imag() * w.imag(),
                F[j + k + i].real() * w.imag() + F[j + k + i].imag() * w.real());
          F[j + k] = s + t, F[j + k + i] = s - t;
        }
      }
    }
    if(rev) for(int i = 0; i < N; i++) F[i] /= N;
  }

  vector< long long > Multiply(const vector< int > &A, const vector< int > &B)
  {
    int sz = 1;
    while(sz <= A.size() + B.size()) sz <<= 1;
    vector< C > F(sz), G(sz);
    for(int i = 0; i < A.size(); i++) F[i] = A[i];
    for(int i = 0; i < B.size(); i++) G[i] = B[i];
    DiscreteFourierTransform(F, false);
    DiscreteFourierTransform(G, false);
    for(int i = 0; i < sz; i++) F[i] *= G[i];
    DiscreteFourierTransform(F, true);
    vector< long long > X(A.size() + B.size() - 1);
    for(int i = 0; i < A.size() + B.size() - 1; i++) X[i] = F[i].real() + 0.5;
    return (X);
  }
};

