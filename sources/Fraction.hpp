#include <iostream>
#include <cmath>

namespace ariel {
    class Fraction {
        private:
            int numerator;
            int denominator;
        public:
           
            // constructor and destructor
            Fraction();
            ~Fraction();
            Fraction(int num, int den);
            Fraction(double number);
            Fraction(const Fraction& other);
            Fraction(Fraction&& other) noexcept;

            // assignment operators
            Fraction& operator=(const Fraction& other);
            Fraction& operator=(Fraction&& other) noexcept;
            
            // arithmetic operators
            Fraction operator+(const Fraction& other) const;
            friend Fraction operator+(double temp, const Fraction& fraction);
            friend Fraction operator+(const Fraction& fraction, double temp);
            
            Fraction operator-(const Fraction& other) const;
            friend Fraction operator-(double temp, const Fraction& fraction);
            friend Fraction operator-(const Fraction& fraction, double temp);

            Fraction operator*(const Fraction& other) const;
            friend Fraction operator*(double temp, const Fraction& fraction);
            friend Fraction operator*(const Fraction& fraction, double temp);

            Fraction operator/(const Fraction& other) const;
            friend Fraction operator/(double temp, const Fraction& fraction);
            friend Fraction operator/(const Fraction& fraction, double temp);


            // increment and decrement operators
            Fraction& operator++();
            Fraction operator++(int);
            Fraction& operator--();
            Fraction operator--(int);
            
            // unary minus operator
            Fraction operator-() const;
           
            // comparison operators
            bool operator==(const Fraction& other) const;
            friend bool operator==( double temp, const Fraction& fraction);
            friend bool operator==(const Fraction& fraction,  double temp);

            bool operator!=(const Fraction& other) const;
            friend bool operator!=(double temp, const Fraction& fraction);
            friend bool operator!=(const Fraction& fraction, double temp);

            bool operator<(const Fraction& other) const;
            friend bool operator<( double temp, const Fraction& fraction); 
            friend bool operator<(const Fraction& fraction,  double temp);

            bool operator>(const Fraction& other) const;
            friend bool operator>(double temp, const Fraction& fraction);
            friend bool operator>(const Fraction& fraction, double temp);

            bool operator<=(const Fraction& other) const;
            friend bool operator<=( double temp, const Fraction& fraction); 
            friend bool operator<=(const Fraction& fraction,  double temp);

            bool operator>=(const Fraction& other) const;
            friend bool operator>=(double temp, const Fraction& fraction); 
            friend bool operator>=(const Fraction& fraction, double temp);

            // input and output operators
            friend std::ostream& operator<<(std::ostream& oss, Fraction& fraction);
            friend std::istream& operator>>(std::istream& iss, Fraction& fraction);

            int getNumerator() const;
            int getDenominator() const;
            void setnumerator(int num);
            void setdenominator(int den);
            void reduce(); // helper function to reduce the fraction 
            double toDouble() const;


    };
}
