//
// Created by dominica on 04.04.17.
//

#include <string>
#include "lazy_string.h"
#include <memory>

lazy_string::lazy_string() {
    ptr = std::make_shared<std::string>("");
    index = stlen = 0;
}

lazy_string::lazy_string(const std::string &st) {
    ptr = std::make_shared<std::string>(st);
    index = 0;
    stlen = st.size();
}

lazy_string::operator std::string() {
    return std::__cxx11::string();
}

size_t lazy_string::size() const {
    return stlen;
}

size_t lazy_string::length() const {
    return stlen;
}

char lazy_string::at(size_t pos) const {
    return (*this)[index + pos];
}

lazy_string::lazy_char lazy_string::at(size_t pos) {
    return lazy_char(this, pos);
}

lazy_string::lazy_char lazy_string::operator[](size_t pos) {
    return lazy_char(this, pos);
}

char lazy_string::operator[](size_t pos) const {
    return (*this)[index + pos];
}

std::istream &operator>>(std::istream & in, lazy_string & str) {
    std::shared_ptr<std::string> buffer = std::make_shared<std::string>();
    in >> *buffer;
    str.ptr = buffer;
    str.index = 0;
    str.stlen = buffer->length();
    return in;
}

std::ostream &operator<<(std::ostream & out, lazy_string const & str) {
    for (size_t i = 0; i < str.size(); i++)
        out << str[i];
    return out;
}

lazy_string lazy_string::substr(size_t begin, size_t len) {
    lazy_string substring;
    substring.ptr = ptr;
    substring.index= begin + this->index;
    substring.stlen = begin + len > stlen ? stlen - index : len;
    return substring;
}

lazy_string::lazy_char &lazy_string::lazy_char::operator=(char c) {
    if (lsptr->ptr.use_count() >= 2) {
        lsptr->index = 0;
        lsptr->ptr = std::make_shared<std::__cxx11::string>(lsptr->ptr->substr(lsptr->index, lsptr->stlen));
    }
    (*lsptr->ptr)[lsptr->index + index] = c;
    return *this;
}

lazy_string::lazy_char::lazy_char(lazy_string * ptr, size_t ind): lsptr(ptr), index(ind) {}