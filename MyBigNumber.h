#ifndef TA14_MYBIGNUMBER_H
#define TA14_MYBIGNUMBER_H

#include "BigNumber.h"
#include <string>

class MyBigNumber :  public BigNumber {

    friend MyBigNumber operator-( const MyBigNumber & num1, const BigNumber & num2);
    friend std::ostream& operator<<(std::ostream & output, const MyBigNumber & myBig );

private:
    MyBigNumber();

public:
    MyBigNumber( const std::string & str );
    MyBigNumber( const char * myCharArray ) : BigNumber((std::string) myCharArray) {}
    MyBigNumber(const long & intNum );
    MyBigNumber multByOneDigit( int a);
    MyBigNumber operator*( const BigNumber& myBig) ;
    MyBigNumber& operator+=( BigNumber number);
    MyBigNumber& operator=( const MyBigNumber& number);
    MyBigNumber(const MyBigNumber& number);
    MyBigNumber(const BigNumber& number);
    MyBigNumber ( MyBigNumber && myBig ) noexcept;  // move constructor
    MyBigNumber & operator=(MyBigNumber && rightNum) noexcept ;   // move assignment overloading
    MyBigNumber operator /( MyBigNumber& myBig);
    MyBigNumber operator %( MyBigNumber& myBig);
    static MyBigNumber power ( const BigNumber& myBig , unsigned pow );
    MyBigNumber operator () (int a , int b);
    MyBigNumber upside_down();

};



#endif
