struct Manachan
{
  vector< int > radius;

  void build(const string &s)
  {
    radius.resize(s.size());

    int i = 0, j = 0;
    while(i < s.size()) {
      while(i - j >= 0 && i + j < s.size() && s[i - j] == s[i + j]) {
        ++j;
      }
      radius[i] = j;
      int k = 1;
      while(i - k >= 0 && i + k < s.size() && k + radius[i - k] < j) {
        radius[i + k] = radius[i - k];
        ++k;
      }
      i += k;
      j -= k;
    }
  }

  int operator[](const int k) const
  {
    return (radius[k]);
  }

  size_t size()
  {
    return (radius.size());
  }
};
