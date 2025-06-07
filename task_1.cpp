#include <iostream>
#include <string>
#include <numeric>
#include <cmath>
#include <stdexcept>
#include <sstream>

using namespace std;

class Fraction {
private:
    long long numerator;
    long long denominator;

    void reduce() {
        if (numerator == 0) {
            denominator = 1;
            return;
        }

        long long common_divisor = std::gcd(std::abs(numerator), std::abs(denominator));

        if (common_divisor != 0) {
             numerator /= common_divisor;
             denominator /= common_divisor;
        }

        if (denominator < 0) {
            numerator = -numerator;
            denominator = -denominator;
        }
    }

public:
    Fraction(long long num = 0, long long den = 1) : numerator(num), denominator(den) {
        if (den == 0) {
            throw std::invalid_argument("Знаменник нуль? Ти серйозно?!");
        }
        reduce();
    }

    string toString() {
        stringstream ss;
        int num_abs = abs(numerator);
        int den_abs = abs(denominator);

        if (numerator == 0) {
            return "0";
        }

        bool is_negative = numerator < 0;
        int whole_part = num_abs / den_abs;
        int remainder_num = num_abs % den_abs;

        if (is_negative) {
            ss << "-";
        }

        if (whole_part != 0) {
            ss << whole_part;
            if (remainder_num != 0) {
                ss << " ";
            }
        }

        if (remainder_num != 0) {
            ss << remainder_num << "/" << den_abs;
        }

        return ss.str();
    }

    double toDouble() const {
        return static_cast<double>(numerator) / denominator;
    }

    string getRawString() const {
         return std::to_string(numerator) + "/" + std::to_string(denominator);
     }

    Fraction plus(const Fraction& that) const {
        long long new_num = numerator * that.denominator + that.numerator * denominator;
        long long new_den = denominator * that.denominator;
        return Fraction(new_num, new_den);
    }

    Fraction minus(const Fraction& that) const {
        long long new_num = numerator * that.denominator - that.numerator * denominator;
        long long new_den = denominator * that.denominator;
        return Fraction(new_num, new_den);
    }

    Fraction times(const Fraction& that) const {
        long long new_num = numerator * that.numerator;
        long long new_den = denominator * that.denominator;
        return Fraction(new_num, new_den);
    }

    Fraction by(const Fraction& that) const {
        if (that.numerator == 0) {
            throw std::invalid_argument("Ділити на нуль?! Геть звідси!");
        }
        long long new_num = numerator * that.denominator;
        long long new_den = denominator * that.numerator;
        return Fraction(new_num, new_den);
    }
};

int main() {
    long long num1, den1, num2, den2;
    char slash;

    cout << "Введи перший дріб (типу 5/8): ";
    cin >> num1 >> slash >> den1;

    cout << "Тепер другий дріб (типу 1/4): ";
    cin >> num2 >> slash >> den2;

    Fraction f1(num1, den1);
    Fraction f2(num2, den2);

    cout << "\nТи ввів: " << f1.getRawString() << " та " << f2.getRawString() << endl;
    cout << "Зараз магія почнеться...\n" << endl;

    Fraction sum = f1.plus(f2);
    Fraction diff = f1.minus(f2);
    Fraction prod = f1.times(f2);
    Fraction quot = f1.by(f2);

    cout << f1.getRawString() << " + " << f2.getRawString() << " = " << sum.toString() << endl;
    cout << f1.getRawString() << " - " << f2.getRawString() << " = " << diff.toString() << endl;
    cout << f1.getRawString() << " * " << f2.getRawString() << " = " << prod.toString() << endl;
    cout << f1.getRawString() << " / " << f2.getRawString() << " = " << quot.toString() << endl;

    return 0;
}
