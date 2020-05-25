#include "MyBigNumber.h"
#include <iostream>
#include <utility>
#include <exception>

using namespace std;

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

MyBigNumber MyBigNumber::operator /( MyBigNumber& myBig){
    if ( myBig > *this ){
        throw invalid_argument("myBig should be less than this !!!");
    }

    size_t i {0};
    size_t c {0};
    MyBigNumber temp1;//out of section
    MyBigNumber temp2{*this};//left over
    temp1.sign = ((this->sign && myBig.sign) || (!(this->sign) && !(myBig.sign)));
    temp1.numOfDigits = this->numOfDigits - myBig.numOfDigits + 1;
    temp1.numArray = new int8_t(temp1.numOfDigits);
    int b = myBig.numOfDigits ;

    for (size_t x {0} ; x < temp1.numOfDigits ; ++x ){//initialize temp1 by 0
        temp1[x] = 0;
    }

    while ( c < temp1.numOfDigits && (temp2.numOfDigits - i ) > b-1 ){

        while ( (temp2)(temp2.numOfDigits -i -1 , b) < myBig ){
            ++b;
            temp1[c] = 0;
            ++c;
        }

        for (int a = 1 ; a < 10 ; ++a){
        if ( (temp2)(temp2.numOfDigits -i -1 , b ) < myBig.multByOneDigit(a) ){
            temp2(temp2.numOfDigits -i -1 , b) = temp2(temp2.numOfDigits -i -1 , b) - myBig.multByOneDigit(a-1);
            temp1[c] = a-1;
            ++c;
            a = 10;
        }}
            b=myBig.numOfDigits;
            ++i;
        }

    while ( temp1[temp1.numOfDigits - 1] == 0 && temp1.numOfDigits>1 )
    {
        --temp1.numOfDigits;
    }

    //temp 1 save out of section upside down so we definition temp3
    //to save out of section in order
    MyBigNumber temp3;
    temp3 = temp1.upside_down();

    return temp3;
}

MyBigNumber MyBigNumber::operator %( MyBigNumber& myBig){
    if ( myBig > *this ){
        throw invalid_argument("myBig should be less than this !!!");
    }

    size_t i {0};
    size_t c {0};
    MyBigNumber temp1;//out of section
    MyBigNumber temp2{*this};//left over
    temp1.sign = ((this->sign && myBig.sign) || (!(this->sign) && !(myBig.sign)));
    temp1.numOfDigits = this->numOfDigits - myBig.numOfDigits + 1;
    temp1.numArray = new int8_t(temp1.numOfDigits);
    int b = myBig.numOfDigits ;

    for (size_t x {0} ; x < temp1.numOfDigits ; ++x ){//initialize temp1 by 0
        temp1[x] = 0;
    }

    while ( c < temp1.numOfDigits && (temp2.numOfDigits - i ) > b-1 ){

        while ( (temp2)(temp2.numOfDigits -i -1 , b) < myBig ){
            ++b;
            temp1[c] = 0;
            ++c;
        }

        for (int a = 1 ; a < 10 ; ++a){
            if ( (temp2)(temp2.numOfDigits -i -1 , b ) < myBig.multByOneDigit(a) ){
                temp2(temp2.numOfDigits -i -1 , b) = temp2(temp2.numOfDigits -i -1 , b) - myBig.multByOneDigit(a-1);
                temp1[c] = a-1;
                ++c;
                a = 10;
            }}
        b=myBig.numOfDigits;
        ++i;
    }

    while ( temp1[temp1.numOfDigits - 1] == 0 && temp1.numOfDigits>1 )
    {
        --temp1.numOfDigits;
    }

    //temp 1 save out of section upside down so we definition temp3
    //to save out of section in order
    MyBigNumber temp3;
    temp3 = temp1.upside_down();

    return temp2(b,b);
}

MyBigNumber operator-( const MyBigNumber & num1, const BigNumber & num2){
    MyBigNumber subtract;
    if(num1.sign == num2.sign){
        subtract = BigNumber:: unsignedSubtract(num1, num2);
        subtract.sign = BigNumber:: unsignedMax(num1 , num2).sign;
    }
    else{
        subtract = BigNumber::unsignedAdd(num1, num2);
        subtract.sign = num1.sign ;
    }
    if(subtract.numOfDigits == 1 && subtract[0] == 0 ){
        subtract.sign = true;
    }
    return subtract;
}

MyBigNumber MyBigNumber::operator()(int a, int b) {
    if ( a+1 < b ){
        throw out_of_range("b must be less than a+2 !!");
    }

    MyBigNumber temp;
    temp.sign = sign;
    temp.numOfDigits = b;
    temp.numArray = new int8_t(temp.numOfDigits);

    for (int i{(int)temp.numOfDigits-1} ; i >= 0 ; --i){
        temp[i] = this->numArray[a];
        --a;
    }

    return temp;
}

MyBigNumber MyBigNumber::upside_down() {
    MyBigNumber temp;
    temp.sign = sign;
    temp.numOfDigits = numOfDigits;
    temp.numArray = new int8_t (temp.numOfDigits);

    for (size_t i{0} ; i < this->numOfDigits ; ++i ){
        temp[numOfDigits - 1 - i] = (*this)[i];
    }
    return temp;
}

//MyBigNumber &MyBigNumber::operator()(MyBigNumber myBig) {
//
//    for (int i{(int)temp.numOfDigits-1} ; i >= 0 ; --i){
//        (*this)[i] = this->numArray[a];
//        --a;
//    }
//
//    return *this;
//}
