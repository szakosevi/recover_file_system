#ifndef INDENT_H
#define INDENT_H
/* Handling indent to JSON form print*/
class Indent
{
  private:
    unsigned int n=0;

  public:
    void push(){n++;}
    void pop(){n--;}
    friend std::ostream& operator<<(std::ostream& out, const Indent& id)
    {
      for(int i=0;i<id.n;i++)out<<" ";
      return out;
    }
};

#endif