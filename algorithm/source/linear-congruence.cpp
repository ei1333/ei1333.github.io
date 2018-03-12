template< typename T >
pair< T, T > linear_congruence(vector< T > &A, vector< T > &B, vector< T > &M) {
  T x = 0, m = 1;
  for(int i = 0; i < A.size(); i++) {
    T a = A[i] * m, b = B[i] - A[i] * x;
    T d = __gcd(M[i], a);
    if(b % d != 0) return {0, -1};
    T t = b / d * mod_inv(a / d, M[i] / d) % (M[i] / d);
    x += m * t;
    m *= M[i] / d;
  }
  return {x % m, m};
};
