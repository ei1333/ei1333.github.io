struct Z_algorithm
{
  vector< int > prefix;

  void build(const string &s)
  {
    prefix.assign(s.size(), 0);
    for(int i = 1, j = 0; i < s.size(); i++) {
      if(i + prefix[i - j] < j + prefix[j]) {
        prefix[i] = prefix[i - j];
      } else {
        int k = max(0, j + prefix[j] - i);
        while(i + k < s.size() && s[k] == s[i + k]) ++k;
        prefix[i] = k;
        j = i;
      }
    }
    prefix[0] = (int) s.size();
  }

  int operator[](const int k) const
  {
    return (prefix[k]);
  }

  size_t size()
  {
    return(prefix.size());
  }
};
