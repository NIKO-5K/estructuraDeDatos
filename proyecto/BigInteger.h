//
// Created by Nikolas Jimenez on 6/05/2023.
//
#include <iostream>
#include <stdlib.h>
#include <string>
#include <list>

#ifndef BIGINTEGER_H
#define BIGINTEGER_H

class BigInteger {
    std::list<int> lista;

public:
    BigInteger(std::string number);
    BigInteger(const BigInteger& other);
    BigInteger sumarListaValores(const BigInteger& num1, const BigInteger& num2);
    BigInteger multiplicarListaValores(const BigInteger& num1, const BigInteger& num2);
    void add(const BigInteger& other);
    void subtrac(const BigInteger& other);
    void produc(const BigInteger& other);
    void remainder(const BigInteger& other);
    void pow(const BigInteger& other);
    void quotient(const BigInteger& other);
    std::string toString();

    BigInteger operator+(const BigInteger& other);
    BigInteger operator-(const BigInteger& other);
    BigInteger operator/(const BigInteger& other);
    BigInteger operator*(const BigInteger& other);
    BigInteger operator%(const BigInteger& other);

    bool operator==(const BigInteger& other);
    bool operator<(const BigInteger& other);
    bool operator<=(const BigInteger& other);
};

#endif // BIGINTEGER_H

