#include "MyBigNumber.h"
#include <iostream>
#include <utility>

std::ostream & operator<<( std::ostream & output, const MyBigNumber & myBig ){
    if( myBig.sign == false ){
        output << '-';
    }
    for( int i = myBig.numOfDigits - 1; i >= 0; --i){
        output << (int8_t)(myBig.numArray[i] + 48);
    }
    return output;
}


MyBigNumber MyBigNumber::multByOneDigit( int a ){
    MyBigNumber temp ;
    size_t i{0};
    int8_t carry = 0;
    int8_t s;
    temp.numArray = new int8_t( this->numOfDigits +1 );
    temp.sign = ((this->sign && a>=0) || (!(this->sign) && a<0));
    temp.numOfDigits = this->numOfDigits + 1 ;

    for (; i < this->numOfDigits ; ++i) {
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

MyBigNumber::MyBigNumber( const std::string & str ) : BigNumber(str) {}

MyBigNumber::MyBigNumber() : BigNumber() {

}


MyBigNumber MyBigNumber::operator*( const BigNumber& myBig) {
    MyBigNumber temp;
    temp.sign = ((this->sign && myBig.sign) || (!(this->sign) && !(myBig.sign)));
    temp.numOfDigits = this->numOfDigits + myBig.numOfDigits ;
    temp.numArray = new int8_t(temp.numOfDigits);

    for (size_t i {0} ; i < temp.numOfDigits ; ++i) {
        temp[i] = 0;
    }

for (size_t i{0} ; i< myBig.numOfDigits ; ++i ){
        temp += ((this->multByOneDigit(myBig[i]))<<i);
    }

    if (temp[temp.numOfDigits-1] <= 0 || temp[temp.numOfDigits-1] >= 10){
        --temp.numOfDigits;
    }

    return temp;
}

MyBigNumber& MyBigNumber::operator+=( BigNumber number){
    for(size_t i {0} ; i<number.numOfDigits ; ++i){
        numArray[i] += number[i];
        if (numArray[i] >= 10 ){
            ++numArray[i+1];
            numArray[i] = numArray[i] - 10 ;
        }
    }
    return *this;
}

MyBigNumber::MyBigNumber(const long &intNum) : BigNumber(intNum){}

MyBigNumber:: MyBigNumber(const MyBigNumber& number){
    sign = number.sign;
    numOfDigits = number.numOfDigits;
    numArray = new int8_t[numOfDigits];
    for(size_t i{0}; i < numOfDigits; ++i){
        numArray[i] = number[i];
        }
}

MyBigNumber &MyBigNumber::operator=( const MyBigNumber& rightNum) {
    if ( &rightNum != this ){
        sign = rightNum.sign;
        numOfDigits = rightNum.numOfDigits;
        delete [] numArray;
        numArray = new int8_t[numOfDigits];
        for(size_t i{0}; i < numOfDigits; ++i){
            numArray[i] = rightNum[i];
        }
    }
    return *this;
}

MyBigNumber::MyBigNumber(MyBigNumber &&myBig) noexcept
{   sign = myBig.sign;
    numOfDigits = myBig.numOfDigits;
    numArray = new int8_t[numOfDigits];
    for(size_t i{0}; i < numOfDigits; ++i){
        numArray[i] = myBig[i];
    }
    myBig.numArray = nullptr;
}

MyBigNumber &MyBigNumber::operator=(MyBigNumber &&rightNum) noexcept {
    if( &rightNum != this ){
        sign = rightNum.sign;
        numOfDigits = rightNum.numOfDigits;
        delete [] numArray;
        numArray = rightNum.numArray;
        rightNum.numArray = nullptr;
    }
    return *this;
}

MyBigNumber MyBigNumber::power ( const BigNumber& myBig , unsigned pow ){
    MyBigNumber temp = myBig;

    if ( pow ==0 ){
        return 1 ;
    }

    for (size_t i{0} ; i < pow-1 ; ++i){
        temp =  temp*myBig;
    }

    return temp;
}

MyBigNumber::MyBigNumber(const BigNumber &number) : BigNumber(number) {}
