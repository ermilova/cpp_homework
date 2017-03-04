//
// Created by dominica on 04.03.17.
//

#include "rational.h"
#include <algorithm>

rational::rational(int val) : num(val), denom(1) {}

rational::rational(int val1, int val2) {
    int gcd = std::__gcd(val1, val2);
    num = val1 / gcd;
    num = val2 / gcd;
}

int rational::getNum() const {
    return num;
}

int rational::getDenom() const {
    return denom;
}

const rational operator+(const rational &left, const rational &right) {
    return rational(left.denom * right.num + right.denom * left.num, left.denom * right.denom);
}

const rational operator*(const rational &left, const rational &right) {
    return rational(left.num * right.num, left.denom * right.denom);
}

const rational operator-(const rational &left, const rational &right) {
    return rational(right.denom * left.num - left.denom * right.num, left.denom * right.denom);
}

const rational operator/(const rational &left, const rational &right) {
    return rational(left.num * right.denom, left.denom * right.num);
}