using int64 = long long;

vector< int64 > divisor(int64 n)
{
  vector< int64 > ret;
  for(int64 i = 1; i * i <= n; i++) {
    if(n % i == 0) {
      ret.push_back(i);
      if(i * i != n) ret.push_back(n / i);
    }
  }
  sort(begin(ret), end(ret));
  return(ret);
}
