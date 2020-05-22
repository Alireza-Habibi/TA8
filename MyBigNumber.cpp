#include "MyBigNumber.h"

BigNumber MyBigNumber::multByOneDigit(BigNumber &myBig, int a){
    BigNumber temp {myBig};
    temp.sign = ((myBig.sign && a>=0) || (!(myBig.sign) && a<0));
    temp.numOfDigits = myBig.numOfDigits + 1;

    size_t i{0};
    int8_t carry = 0;
    int8_t s;

    for (; i < temp.numOfDigits ; ++i) {
        s = myBig[i]*a + carry;
        temp[i] = s % 10;
        carry = s / 10;
    }

    if (carry == 1) {
        temp[i] = 1;
    }
    else if (carry == 0) {
        //sum[i] = 0;
        temp.numOfDigits -= 1;
    }

    return temp;
}
