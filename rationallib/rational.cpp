#include <iostream>
#include "rational.hpp"

Rational operator-(const Rational& r) {
    return {-r.GetNum(), r.GetDenum()};
}

Rational& Rational::operator+=(const Rational& r) {
    int64_t lmc = denom * r.GetDenum() / std::gcd(denom, r.GetDenum());

    num *= lmc / denom;
    denom *= lmc / denom;

    // Почему могу обращаться к num, хотя он private?
    // this->num += r.num * lmc;
    num += r.GetNum() * lmc / r.GetDenum();

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
    this->num *= r.GetNum();
    this->denom *= r.GetDenum();
    simplify();
    return *this;
}

Rational operator*(const Rational& l, const Rational& r) {
    Rational rational = l;
    rational *= r;
    return rational;
}

Rational& Rational::operator/=(const Rational& r) {
    if (r.GetNum() == 0) {
        throw std::runtime_error("Zero division");
    }

    this->num *= r.GetDenum();
    this->denom *= r.GetNum();
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
    return l.GetNum() == r.GetNum() && l.GetDenum() == r.GetDenum();
}

bool operator!=(const Rational& l, const Rational& r) {
    return !operator==(l, r);
}

int64_t Rational::GetNum() const {
    return num;
}

int64_t Rational::GetDenum() const {
    return denom;
}

std::istream& Rational::ReadFrom(std::istream& istream) {
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

inline std::ostream& Rational::WriteTo(std::ostream& ostream) const {
    ostream << GetNum() << '/' << GetDenum() << "\n";
    return ostream;
}

std::ostream& operator<<(std::ostream& ostream, const Rational& r) {
    r.WriteTo(ostream);
    return ostream;
}

std::istream& operator>>(std::istream& istream, Rational& r) {
    r.ReadFrom(istream);
    return istream;
}
