//
//  main.cpp
//  drobi
//
//  Created by Valeria Dudinova on 12.09.2024.
//

#include <iostream>
using namespace std;

class Fraction
{
private:
    int numerator;
    int denominator;

    int gcd(int a, int b) const
    {
        while (b != 0)
        {
            int temp = b;
            b = a % b;
            a = temp;
        }
        return a;
    }

    void simplify()
    {
        int gcd_value = gcd(numerator, denominator);
        numerator /= gcd_value;
        denominator /= gcd_value;

        if (denominator < 0)
        {
            numerator = -numerator;
            denominator = -denominator;
        }
    }

public:
    Fraction() : numerator(0), denominator(1) {}

    Fraction(int num, int den) : numerator(num), denominator(den)
    {
        if (den == 0) {
            throw invalid_argument("Denominator cannot be zero");
        }
        simplify();
    }

    void input()
    {
        cout << "Enter numerator: ";
        cin >> numerator;
        cout << "Enter denominator: ";
        cin >> denominator;
        if (denominator == 0)
        {
            throw invalid_argument("Denominator cannot be zero");
        }
        simplify();
    }

    void output() const
    {
        cout << numerator << "/" << denominator << endl;
    }

    Fraction operator+(const Fraction& other) const
    {
        int num = numerator * other.denominator + other.numerator * denominator;
        int den = denominator * other.denominator;
        return Fraction(num, den);
    }

    Fraction operator-(const Fraction& other) const
    {
        int num = numerator * other.denominator - other.numerator * denominator;
        int den = denominator * other.denominator;
        return Fraction(num, den);
    }

    Fraction operator*(const Fraction& other) const
    {
        int num = numerator * other.numerator;
        int den = denominator * other.denominator;
        return Fraction(num, den);
    }

    Fraction operator/(const Fraction& other) const
    {
        if (other.numerator == 0)
        {
            throw invalid_argument("Cannot divide by zero");
        }
        int num = numerator * other.denominator;
        int den = denominator * other.numerator;
        return Fraction(num, den);
    }

    bool operator==(const Fraction& other) const
    {
        return numerator == other.numerator && denominator == other.denominator;
    }

    bool operator!=(const Fraction& other) const
    {
        return !(*this == other);
    }

    friend ostream& operator<<(ostream& os, const Fraction& frac)
    {
        os << frac.numerator << '/' << frac.denominator;
        return os;
    }

    friend istream& operator>>(istream& is, Fraction& frac)
    {
        is >> frac.numerator;
        is.ignore();
        is >> frac.denominator;
        if (frac.denominator == 0)
        {
            throw invalid_argument("Denominator cannot be zero");
        }
        frac.simplify();
        return is;
    }
};

int main()
{
    try
    {
        Fraction frac1, frac2;
        cout << "Enter first fraction:" << endl;
        frac1.input();
        cout << "Enter second fraction:" << endl;
        frac2.input();

        Fraction result;

        result = frac1 + frac2;
        cout << "Sum: " << result << endl;

        result = frac1 - frac2;
        cout << "Difference: " << result << endl;

        result = frac1 * frac2;
        cout << "Product: " << result << endl;

        result = frac1 / frac2;
        cout << "Quotient: " << result << endl;
    }
    catch (const exception& e)
    {
        cerr << e.what() << endl;
    }

    return 0;
}

