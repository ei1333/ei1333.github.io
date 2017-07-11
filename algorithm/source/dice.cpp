struct Dice
{
  int x, y;
  int l, r, f, b, d, u;
 
  void RollF()
  {
    --y;
    int buff = d;
    d = f;
    f = u;
    u = b;
    b = buff;
  }
 
  void RollB()
  {
    ++y;
    int buff = d;
    d = b;
    b = u;
    u = f;
    f = buff;
  }
 
  void RollL()
  {
    --x;
    int buff = d;
    d = l;
    l = u;
    u = r;
    r = buff;
  }
 
  void RollR()
  {
    ++x;
    int buff = d;
    d = r;
    r = u;
    u = l;
    l = buff;
  }
};
