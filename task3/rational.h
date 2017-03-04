//
// Created by dominica on 04.03.17.
//

#ifndef TASK3_RATIONAL_H
#define TASK3_RATIONAL_H
struct rational {
    rational(int);
    rational(int, int);
    int getNum() const;
    int getDenom() const;
    rational operator +(rational const&) const;
    rational operator -(rational const&) const;
    rational operator *(rational const&) const;
    rational operator /(rational const&) const;
private:
    int num, denom;
};

#endif //TASK3_RATIONAL_H