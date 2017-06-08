template< class T >
struct AdditionalBIT : BinaryIndexedTree< T >
{
  int curr;

  AdditionalBIT(int sz) : BinaryIndexedTree< T >(sz)
  {
    curr = 1;
    while(curr <= sz) curr <<= 1;
  }

  int lower_bound(T w)
  {
    if(w <= 0) return (0);
    int i = 0;
    for(int k = curr; k > 0; k >>= 1) {
      if(i + k < BinaryIndexedTree< T >::data.size() && BinaryIndexedTree< T >::data[i + k] < w) {
        w -= BinaryIndexedTree< T >::data[i + k];
        i += k;
      }
    }
    return (i);
  }
};
