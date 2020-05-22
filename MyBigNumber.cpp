#include "MyBigNumber.h"

#include <utility>

BigNumber MyBigNumber::multByOneDigit( int a ){
    MyBigNumber temp ;
    temp.sign = ((this->sign && a>=0) || (!(this->sign) && a<0));
    temp.numOfDigits = this->numOfDigits + 1;
    temp.numArray = new int8_t(temp.numOfDigits);

    size_t i{0};
    int8_t carry = 0;
    int8_t s;

    for (; i < temp.numOfDigits ; ++i) {
        s = this->numArray[i]*a + carry;
        temp[i] = s % 10;
        carry = s / 10;
    }

    if (carry >= 1) {
        temp[i] = carry;
    }
    else if (carry == 0) {
        //sum[i] = 0;
        temp.numOfDigits -= 1;
    }

    return temp;
}

MyBigNumber::MyBigNumber( const std::string & str ) : BigNumber(str) {

}

MyBigNumber::MyBigNumber() : BigNumber() {

}

