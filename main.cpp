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

//      cout << myBig1.multByOneDigit(3)<<endl
//      << myBig2* myBig1 << endl;
//    MyBigNumber multByOneDigit( int a);
//    MyBigNumber operator*( const BigNumber& myBig) ;
//    MyBigNumber& operator+=( BigNumber number);
//    MyBigNumber& operator=( const MyBigNumber& number);
//    MyBigNumber(const MyBigNumber& number);
//    MyBigNumber(const BigNumber& number);
//    MyBigNumber ( MyBigNumber && myBig ) noexcept;  // move constructor
//    MyBigNumber & operator=(MyBigNumber && rightNum) noexcept ;   // move assignment overloading
//    MyBigNumber operator /( MyBigNumber& myBig);
//    MyBigNumber operator %( MyBigNumber& myBig);
//    static MyBigNumber power ( const BigNumber& myBig , unsigned pow );
//    MyBigNumber operator () (int a , int b);
//    MyBigNumber upside_down();
    return 0;
}
