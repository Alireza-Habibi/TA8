#include <iostream>
#include <cstdint>

#include "BigNumber.h"
#include "MyBigNumber.h"
#include <exception>

using namespace std;

int main() {
    cout << boolalpha;

      MyBigNumber myBig1 = "432";
      MyBigNumber myBig2 = "04";
      try{
      cout << myBig1/myBig2  <<endl;}
      catch(out_of_range e ){
          cout << e.what();
      }

      cout << myBig1.multByOneDigit(3)<<endl
      << myBig2* myBig1 << endl
      << MyBigNumber::power(myBig2,3);

      myBig1 = myBig2;
      cout<< myBig1;


    return 0;
}
