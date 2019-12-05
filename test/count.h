#ifndef COUNT_H
#define COUNT_H
#include <stdio.h>

typedef unsigned short data;

namespace count{
void open(){
    FILE *f=fopen("count","ab");
    data zero=0;
    fwrite(&zero,sizeof(data),1,f);
    fclose(f);
}
  data get(){
      data b;
      FILE *f;
      f=fopen("count", "rb");
      fread(&b, sizeof(data), 1, f);
      fclose(f);
      return b;
  }
  void set(data many){
    FILE *f;
    f=fopen("count", "wb");
    fwrite(&many, sizeof(data), 1, f);
    fclose(f);
  }
  void close(){
      remove("count");
  }
}

#endif // COUNT_H
