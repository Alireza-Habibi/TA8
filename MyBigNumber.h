#ifndef TA14_MYBIGNUMBER_H
#define TA14_MYBIGNUMBER_H

#include "BigNumber.h"
#include <string>

class MyBigNumber :  public BigNumber {
private:
    MyBigNumber();
public:
    MyBigNumber( const std::string & str );
    MyBigNumber( const char * myCharArray ) : BigNumber((std::string) myCharArray) {}
    BigNumber multByOneDigit( int a);
};



#endif
