map< int64_t, int > moebius(int64_t n) {
  vector< int64_t > factor;
  for(int64_t i = 2; i * i <= n; i++) {
    if(n % i == 0) {
      factor.emplace_back(i);
      while(n % i == 0) n /= i;
    }
  }
  if(n > 1) factor.emplace_back(n);

  map< int64_t, int > ret;
  for(int i = 0; i < (1 << factor.size()); i++) {
    int mu = 1;
    int64_t dd = 1;
    for(int j = 0; j < factor.size(); j++) {
      if((i >> j) & 1) {
        mu *= -1;
        dd *= factor[j];
      }
    }
    ret[dd] = mu;
  }
  return ret;
}
