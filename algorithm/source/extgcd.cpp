int extgcd(int a, int b, int &x, int &y)
{
  x = 1, y = 0;
  int g = a;
  if(b != 0) {
    g = extgcd(b, a % b, y, x);
    y -= a / b * x;
  }
  return g;
}
