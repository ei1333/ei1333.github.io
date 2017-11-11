using int64 = long long;

map< int64, int > prime_factor(int64 n)
{
  map< int64, int > ret;
  for(int64 i = 2; i * i <= n; i++){
    while(n % i == 0) {
      ret[i]++;
      n /= i;
    }
  }
  if(n != 1) ret[n] = 1;
  return(ret);
}
