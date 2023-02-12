#include <iostream>
#include "rational.hpp"

Rational operator-(const Rational& r) {
    return {-r.getNum(), r.getDenum()};
}

Rational& Rational::operator+=(const Rational& r) {
    int64_t lmc = denom * r.getDenum() / std::gcd(denom, r.getDenum());

    num *= lmc / denom;
    denom *= lmc / denom;

    // Почему могу обращаться к num, хотя он private?
    // this->num += r.num * lmc;
    num += r.getNum() * lmc / r.getDenum();

    simplify();
    return *this;
}

Rational operator+(const Rational& l, const Rational& r) {
    Rational rational = l;
    rational += r;
    return rational;
}

Rational& Rational::operator-=(const Rational& r) {
    this->operator+=(-r);
    return *this;
}

Rational operator-(const Rational& l, const Rational& r) {
    Rational rational = l;
    rational -= r;
    return rational;
}

Rational& Rational::operator*=(const Rational& r) {
    this->num *= r.getNum();
    this->denom *= r.getDenum();
    simplify();
    return *this;
}

Rational operator*(const Rational& l, const Rational& r) {
    Rational rational = l;
    rational *= r;
    return rational;
}

Rational& Rational::operator/=(const Rational& r) {
    if (r.getNum() == 0) {
        throw std::runtime_error("Zero division");
    }

    this->num *= r.getDenum();
    this->denom *= r.getNum();
    simplify();
    return *this;
}

Rational operator/(const Rational& l, const Rational& r) {
    Rational rational = l;
    rational /= r;
    return rational;
}

Rational& Rational::operator++() {
    this->operator+=(Rational(1, 1));
    return *this;
}

Rational Rational::operator++(int) {
    Rational temp(*this);
    // do something
    ++*this;
    return temp;
}

Rational& Rational::operator--() {
    this->operator-=(Rational(1, 1));
    return *this;
}

Rational Rational::operator--(int) {
    Rational temp(*this);
    // do something
    --*this;
    return temp;
}

bool operator==(const Rational& l, const Rational& r) {
    return l.getNum() == r.getNum() && l.getDenum() == r.getDenum();
}

bool operator!=(const Rational& l, const Rational& r) {
    return !operator==(l, r);
}

int64_t Rational::getNum() const {
    return num;
}

int64_t Rational::getDenum() const {
    return denom;
}

std::istream& Rational::readFrom(std::istream& istream) {
    int64_t numI = 0;
    int64_t denomI = 0;
    char separator = 0;
    istream >> numI >> separator >> denomI;
    if (istream.good()) {
        if (denom == 0) {
            throw std::runtime_error("Zero division");
//            istream.setstate(std::ios_base::failbit);
        }
        if (denomI < 0 || separator != '/') {
            istream.setstate(std::ios_base::failbit);
        } else {
            num = numI;
            denom = denomI;
            simplify();
        }
    }
    return istream;
}

std::ostream& Rational::writeTo(std::ostream& ostream) const {
    ostream << getNum() << '/' << getDenum() << "\n";
    return ostream;
}

std::ostream& operator<<(std::ostream& ostream, const Rational& r) {
    r.writeTo(ostream);
    return ostream;
}

std::istream& operator>>(std::istream& istream, Rational& r) {
    r.readFrom(istream);
    return istream;
}
