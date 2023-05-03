#include "Fraction.hpp"
#include <iomanip>
namespace ariel
{

    // default constructor
    Fraction::Fraction() : numerator(0), denominator(1) {}

    // destructor
    Fraction::~Fraction() {}

    // constructor with numerator and denominator
    Fraction::Fraction(int num, int den) : numerator(num), denominator(den)
    {
        if (den == 0)
        {
            throw std::invalid_argument("Denominator can't be zero.");
        }
        reduce();
    }

    // constructor of a double to fraction
    Fraction::Fraction(double number)
    {
        const int digits = 3; // use up to 3 digits beyond decimal point for accuracy
        int whole = std::floor(number);
        double decimal = number - whole;
        int den = std::pow(10, digits);
        int num = whole * den + std::round(decimal * den);
        numerator = num;
        denominator = den;
        reduce();
    }

    // copy constructor
    Fraction::Fraction(const Fraction &other) : numerator(other.numerator), denominator(other.denominator) {}

    // move constructor
    Fraction::Fraction(Fraction &&other) noexcept : numerator(std::move(other.numerator)), denominator(std::move(other.denominator)) {}

    Fraction &Fraction::operator=(const Fraction &other)
    {
        if (this != &other)
        {
            numerator = other.numerator;
            denominator = other.denominator;
        }
        return *this;
    }

    Fraction &Fraction::operator=(Fraction &&other) noexcept
    {
        if (this != &other)
        {
            numerator = std::exchange(other.numerator, 0);// the "std::exchange" is used to make sure that the values of num and den are passed
            denominator = std::exchange(other.denominator, 1);//properly from other to this.
        }
        return *this;
    }

    Fraction Fraction::operator+(const Fraction &other) const
    {
        long long num = (long long)this->numerator * other.denominator + (long long)other.numerator * this->denominator;
        long long den = (long long)this->denominator * other.denominator;

        // check for division by zero
        if (den == 0)
        {
            throw std::runtime_error("Division by zero");
        }

        // check for overflow or underflow
        if (num > std::numeric_limits<int>::max() ||
            num < std::numeric_limits<int>::min() ||
            den > std::numeric_limits<int>::max() ||
            den < std::numeric_limits<int>::min())
        {
            throw std::overflow_error("Fraction addition resulted in overflow or underflow");
        }
        // divide both num and den by their greatest common divisor until
        // they both fit within the integer range.
        long long gcd = std::__gcd(num, den);
        num /= gcd;
        den /= gcd;

        if (num > std::numeric_limits<int>::max() ||
            num < std::numeric_limits<int>::min() ||
            den > std::numeric_limits<int>::max() ||
            den < std::numeric_limits<int>::min())
        {
            throw std::overflow_error("Fraction addition resulted in overflow or underflow");
        }

        Fraction fraction(num, den);
        fraction.reduce();
        return fraction;
    }

    Fraction operator+(double temp, const Fraction &fraction)
    {
        Fraction frac = Fraction(temp) + fraction;
        frac.reduce();
        return frac;
    }

    Fraction operator+(const Fraction &fraction, double temp)
    {
        Fraction frac = fraction + Fraction(temp);
        frac.reduce();
        return frac;
    }

    Fraction Fraction::operator-(const Fraction &other) const
    {
        long long num = (long long)numerator * (long long)other.denominator - (long long)other.numerator * (long long)denominator;
        long long den = (long long)denominator * (long long)other.denominator;

        if (num > std::numeric_limits<int>::max() || num < std::numeric_limits<int>::min() ||
            den > std::numeric_limits<int>::max() || den < std::numeric_limits<int>::min())
        {
            throw std::overflow_error("Fraction subtraction resulted in overflow or underflow");
        }

        Fraction fraction(num, den);
        fraction.reduce();
        return fraction;
    }

    Fraction operator-(double temp, const Fraction &fraction)
    {
        Fraction frac = Fraction(temp) - fraction;
        frac.reduce();
        return frac;
    }

    Fraction operator-(const Fraction &fraction, double temp)
    {
        Fraction frac = fraction - Fraction(temp);
        frac.reduce();
        return frac;
    }

    Fraction Fraction::operator/(const Fraction &other) const
    {
        // Multiply by the reciprocal of the other fraction
        long long num = (long long)numerator * (long long)other.denominator;
        long long den = (long long)denominator * (long long)other.numerator;

        // Check for division by zero
        if (den == 0)
        {
            throw std::runtime_error("Division by zero");
        }

        // Check for overflow or underflow
        if (num > std::numeric_limits<int>::max() || num < std::numeric_limits<int>::min() ||
            den > std::numeric_limits<int>::max() || den < std::numeric_limits<int>::min())
        {
            throw std::overflow_error("Division overflow");
        }
        // Divide both num and den by their greatest common divisor until
        // they both fit within the integer range.
        long long gcd = std::__gcd(num, den);
        num /= gcd;
        den /= gcd;

        if (num > std::numeric_limits<int>::max() || num < std::numeric_limits<int>::min() ||
            den > std::numeric_limits<int>::max() || den < std::numeric_limits<int>::min())
        {
            throw std::overflow_error("Division overflow");
        }

        Fraction fraction(num, den);
        fraction.reduce();
        return fraction;
    }

    Fraction operator/(double temp, const Fraction &fraction)
    {
        Fraction frac = Fraction(temp) / fraction;
        frac.reduce();
        return frac;
    }

    Fraction operator/(const Fraction &fraction, double temp)
    {
        Fraction frac = fraction / Fraction(temp);
        frac.reduce();
        return frac;
    }

    Fraction Fraction::operator*(const Fraction &other) const
    {
        long long num = (long long)numerator * (long long)other.numerator;
        long long den = (long long)denominator * (long long)other.denominator;

        // Check for multiplication overflow
        if (num > std::numeric_limits<int>::max() || num < std::numeric_limits<int>::min() ||
            den > std::numeric_limits<int>::max() || den < std::numeric_limits<int>::min())
        {
            throw std::overflow_error("Multiplication overflow");
        }
        // Divide both num and den by their greatest common divisor until
        // they both fit within the integer range.
        long long gcd = std::__gcd(num, den);
        num /= gcd;
        den /= gcd;

        if (num > std::numeric_limits<int>::max() || num < std::numeric_limits<int>::min() ||
            den > std::numeric_limits<int>::max() || den < std::numeric_limits<int>::min())
        {
            throw std::overflow_error("Multiplication overflow");
        }

        if (numerator == 0 || other.numerator == 0)
        {
            return Fraction(0, 1);
        }

        Fraction fraction(num, den);
        fraction.reduce();
        return fraction;
    }

    Fraction operator*(double temp, const Fraction &fraction)
    {
        Fraction frac = Fraction(temp) * fraction;
        frac.reduce();
        return frac;
    }

    Fraction operator*(const Fraction &fraction, double temp)
    {
        Fraction frac = fraction * Fraction(temp);
        frac.reduce();
        return frac;
    }

    // prefix increment operator
    Fraction &Fraction::operator++()
    {
        numerator += denominator;
        reduce();
        return *this;
    }

    // postfix increment operator
    Fraction Fraction::operator++(int)
    {
        Fraction temp(*this);
        ++(*this);
        return temp;
    }

    // prefix decrement operator
    Fraction &Fraction::operator--()
    {
        numerator -= denominator;
        reduce();
        return *this;
    }

    // postfix decrement operator
    Fraction Fraction::operator--(int)
    {
        Fraction temp(*this);
        --(*this);
        return temp;
    }

    Fraction Fraction::operator-() const
    {
        return Fraction(-numerator, denominator);
    }
    bool Fraction::operator==(const Fraction &other) const
    {
        double result1 = static_cast<double>(numerator) / denominator;
        double result2 = static_cast<double>(other.numerator) / other.denominator;
        return std::fabs(result1 - result2) < 0.0001; // or any other suitable tolerance value
    }

    bool operator==(double temp, const Fraction &fraction)
    {
        double result = static_cast<double>(fraction.getNumerator()) / fraction.getDenominator();
        return std::fabs(temp - result) < 0.0001; // or any other suitable tolerance value, i used 0.0001 for more accuracy
                                                  // could be any other value depending on the task. 
    }

    bool operator==(const Fraction &fraction, double temp)
    {
        double result = static_cast<double>(fraction.getNumerator()) / fraction.getDenominator();
        return std::fabs(temp - result) < 0.0001; // or any other suitable tolerance value
    }

    bool Fraction::operator>(const Fraction &other) const
    {
        return (numerator * other.denominator) > (denominator * other.numerator);
    }

    bool operator>(double temp, const Fraction &fraction)
    {
        return temp > fraction.toDouble();
    }

    bool operator>(const Fraction &fraction, double temp)
    {
        return fraction.toDouble() > temp;
    }

    bool Fraction::operator<(const Fraction &other) const
    {
        return (numerator * other.denominator) < (denominator * other.numerator);
    }

    bool operator<(double temp, const Fraction &fraction)
    {
        return temp < fraction.toDouble();
    }

    bool operator<(const Fraction &fraction, double temp)
    {
        return fraction.toDouble() < temp;
    }

    bool Fraction::operator<=(const Fraction &other) const
    {
        return (numerator * other.denominator) <= (denominator * other.numerator);
    }

    bool operator<=(double temp, const Fraction &fraction)
    {
        return temp <= fraction.toDouble();
    }

    bool operator<=(const Fraction &fraction, double temp)
    {
        return fraction.toDouble() <= temp;
    }

    bool Fraction::operator>=(const Fraction &other) const
    {
        return (numerator * other.denominator) >= (denominator * other.numerator);
    }

    bool operator>=(double temp, const Fraction &fraction)
    {
        return temp >= fraction.toDouble();
    }

    bool operator>=(const Fraction &fraction, double temp)
    {
        return fraction.toDouble() >= temp;
    }

    bool Fraction::operator!=(const Fraction &other) const
    {
        return numerator * other.denominator != other.numerator * denominator;
    }

    bool operator!=(double temp, const Fraction &fraction)
    {
        return Fraction(temp) != fraction;
    }

    bool operator!=(const Fraction &fraction, double temp)
    {
        return Fraction(temp) != fraction;
    }

    std::ostream &operator<<(std::ostream &os, Fraction &f)
    {
        return os << f.getNumerator() << '/' << f.getDenominator();
    }

    std::istream &operator>>(std::istream &is, Fraction &fraction)
    {    
        int num, den;
        if ((is >> num >> den) && den != 0)
        {
            int gcd = std::__gcd(num, den);
            fraction.setnumerator(num / gcd);
            fraction.setdenominator(den / gcd);
        }
        else
        {
            throw std::runtime_error("one input");
        }

        return is;
    }

    void Fraction::reduce()
    {   //finding the gcd and dividing the num and den by it.
        int gcd = std::__gcd(numerator, denominator);
        numerator /= gcd;
        denominator /= gcd;
        // taking care of the negative fractions
        if (denominator < 0)
        {
            numerator = -numerator;
            denominator = -denominator;
        }
        else if (denominator == 0)
        {
            throw std::invalid_argument("Denominator cannot be zero.");
        }
    }

    int Fraction::getNumerator() const
    {

        return numerator;
    }

    int Fraction::getDenominator() const
    {

        return denominator;
    }
    void Fraction::setnumerator(int num)
    {
        numerator = num;
    }

    void Fraction::setdenominator(int den)
    {
        denominator = den;
    }
    double Fraction::toDouble() const
    {
        //i've added 0.0005 to the decimal part so it rounds it to the nearest number not to 0.
        double quotient = static_cast<double>(numerator) / denominator;
        int integerPart = static_cast<int>(quotient);
        int decimalPart = static_cast<int>((quotient - integerPart + 0.0005) * 1000);
        double result = integerPart + static_cast<double>(decimalPart) / 1000.0;
        return result;
    }

}
