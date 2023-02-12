#include <iosfwd>
#include "stdexcept"
#include "numeric"

class Rational {
public:
    Rational() = default;

    Rational(const Rational& r) = default;

    Rational(int64_t num, int64_t denom) : num(num), denom(denom) {
        if (denom == 0) {
            throw std::runtime_error("Zero division");
        }
        if (num * denom < 0) {
            this->num = -std::abs(num);
            this->denom = std::abs(denom);
        }
        simplify();
    }

    ~Rational() = default;

    Rational& operator=(const Rational& r) = default;

    Rational& operator+=(const Rational& r);

    Rational& operator-=(const Rational& r);

    Rational& operator*=(const Rational& r);

    Rational& operator/=(const Rational& r);

    Rational& operator++();

    Rational operator++(int);

    Rational& operator--();

    Rational operator--(int);

    std::istream& readFrom(std::istream& istream);

    std::ostream& writeTo(std::ostream& ostream) const;

    int64_t getNum() const;

    int64_t getDenum() const;

private:
    int64_t num = 1;
    int64_t denom = 1;

    void simplify() {
        int64_t gcd = denom;
        if (num != 0) {
            gcd = std::gcd(num, denom);
        }
        num /= gcd;
        denom /= gcd;
    }
};

Rational operator-(const Rational& r);

Rational operator+(const Rational& l, const Rational& r);

Rational operator-(const Rational& l, const Rational& r);

Rational operator*(const Rational& l, const Rational& r);

Rational operator/(const Rational& l, const Rational& r);

bool operator==(const Rational& l, const Rational& r);

bool operator!=(const Rational& l, const Rational& r);

std::ostream& operator<<(std::ostream& ostream, const Rational& r);

std::istream& operator>>(std::istream& istream, Rational& r);