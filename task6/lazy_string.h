//
// Created by dominica on 04.04.17.
//

#ifndef TASK6_LAZY_STRING_H
#define TASK6_LAZY_STRING_H

#include <string>
#include <memory>
#include <iostream>

struct lazy_string {
    struct lazy_char {
    public:
        lazy_char &operator=(char);

        friend class lazy_string;

    private:
        lazy_char(lazy_string *, size_t);

        const size_t index;
        lazy_string *const lsptr;
    };

    lazy_string();

    lazy_string(const std::string &);


    operator std::string();

    size_t size() const;

    size_t length() const;


    char at(size_t) const;

    lazy_char at(size_t);

    char operator[](size_t) const;

    lazy_char operator[](size_t);

    friend std::istream &operator>>(std::istream &, lazy_string &);

    friend std::ostream &operator<<(std::ostream &, lazy_string const &);

    lazy_string substr(size_t, size_t);


private:
    std::shared_ptr<std::string> ptr;
    size_t index, stlen;

};

#endif //TASK6_LAZY_STRING_H
