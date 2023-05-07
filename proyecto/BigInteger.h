//
// Created by Nikolas Jimenez on 6/05/2023.
//
#include "lista.h"
#include <string>
#include <iostream>
#ifndef BIGINTEGRER_BIGINTEGER_H
#define BIGINTEGRER_BIGINTEGER_H
class BigInteger{
    Lista lista;
public:
    BigInteger(string);
    BigInteger(&BigInteger);
    BigInteger sumarListaValores(&BigInteger,&BigInteger);
    BigInteger multiplicarListaValores(&BigInteger,&BigInteger);
    void add(&BigInteger);
    void subtrac(&BigInteger);
    void produc(&BigInteger);
    void remainder(&BigInteger);
    void pow(&BigInteger);
    void quotient(&BigInteger);
    string toString();
    BigInteger operator +(BigInteger);
    BigInteger operator -(BigInteger);
    BigInteger operator /(BigInteger);
    BigInteger operator *(BigInteger);
    BigInteger operator %(BigInteger);
    bool operator == (BigInteger);
    bool operator < (BigInteger);
    bool operator <= (BigInteger);
};
#endif //BIGINTEGRER_BIGINTEGER_H
