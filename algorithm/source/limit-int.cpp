template< typename T >
struct LimitInt
{
  T x;
  const T low, high;

  LimitInt() : x(0), low(numeric_limits< T >::min() + 10), high(numeric_limits< T >::max() - 10) {}

  LimitInt(const T &x) : x(x), low(numeric_limits< T >::min() + 10), high(numeric_limits< T >::max() - 10) {}

  LimitInt &operator+=(const LimitInt &y)
  {
    x = (double) x + y.x > high ? high : x + y.x;
    return (*this);
  }

  LimitInt &operator-=(const LimitInt &y)
  {
    x = (double) x - y.x < low ? low : x - y.x;
    return (*this);
  }

  LimitInt &operator*=(const LimitInt &y)
  {
    x = (double) x * y.x > high ? high : x * y.x;
    return (*this);
  }

  LimitInt &operator/=(const LimitInt &y)
  {
    x /= y.x;
    return (*this);
  }

  LimitInt operator-() const
  {
    return -x;
  }

  LimitInt operator+(const LimitInt &y) const
  {
    LimitInt ret(x);
    ret += y;
    return ret;
  }
  
  LimitInt operator-(const LimitInt &y) const
  {
    LimitInt ret(x);
    ret -= y;
    return ret;
  }

  LimitInt operator*(const LimitInt &y) const
  {
    LimitInt ret(x);
    ret *= y;
    return ret;
  }

  LimitInt operator/(const LimitInt &y) const
  {
    LimitInt ret(*this);
    ret /= y;
    return ret;
  }

  LimitInt operator==(const LimitInt &y) const
  {
    return (x == y.x);
  }

  LimitInt operator!=(const LimitInt &y) const
  {
    return (x != y.x);
  }

  LimitInt operator<(const LimitInt &y) const
  {
    return (x < y.x);
  }

  LimitInt operator>(const LimitInt &y) const
  {
    return (x > y.x);
  }

  LimitInt operator<=(const LimitInt &y) const
  {
    return (x <= y.x);
  }

  LimitInt operator>=(const LimitInt &y) const
  {
    return (x >= y.x);
  }

  T get() const
  {
    return (x);
  }
};

