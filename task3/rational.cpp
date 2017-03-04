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

rational rational::operator+(rational const &right) const {
    return rational(denom * right.num + right.denom * num, denom * right.denom);
}

rational rational::operator-(rational const &right) const {
    return rational(right.denom * num - denom * right.num, denom * right.denom);
}

rational rational::operator*(rational const &right) const {
    return rational(num * right.num, denom * right.denom);
}

rational rational::operator/(rational const &right) const {
    return rational(num * right.denom, denom * right.num);
}