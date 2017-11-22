int64_t combination(int64_t n, int64_t k)
{
  if(k < 0 || n < k) return (0);
  int64_t ret = 1;
  for(int64_t i = 1; i <= k; ++i) {
    ret *= n--;
    ret /= i;
  }
  return (ret);
}
