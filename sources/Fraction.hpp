#pragma once
#include <iostream>
#include <stdexcept>
#include <string>
#include <cmath>
#include <sstream>
#include <fstream>
using namespace std;

namespace ariel {
class Fraction
{
private:
// Data for a franction of Integer
    int numerator;
    int denominator;
    
public:
// Constructor
    //Default
    Fraction();
    //Parameterized
    Fraction(int num,int den);
// Constructor to convert a float to the fraction : 0.333 = 333/1000. it's taking only 3 decimal number
    Fraction(double num);
    //Copy
    Fraction(const Fraction& other);
    // Move Constructor
    Fraction(Fraction&& other) noexcept;

// Destructor 
    ~Fraction();

// Function to change the function to the min form : exemple : 2/6 = 1/3
    void Min_Form(int& num, int& den);
    int pgcd(int varA,int varB);    

// Getter and Setter
    int getNumerator() const{ return this->numerator;}
    int getDenominator() const{ return this->denominator;}
    void setNumerator(int n){ this->numerator = n;}
    void setDenominator(int n){ this->denominator = n;}

//Overloading of Operators
    // operator : [+] f1+f2 / f1+number / number+f1
    const Fraction operator+(const Fraction& fon2) const;
    const Fraction operator+(const float& number);
    friend const Fraction operator+(const float& num,const Fraction& fon);

    // operator : [-] f1-f2 / f1-number / number-f1
    const Fraction operator-(const Fraction& fon2) const;
    const Fraction operator-(const float& number) const;
    friend const Fraction operator-(const float& num,const Fraction& fon);

    // operator : [*] f1*f2 / f1*number / number*f1
    const Fraction operator*(const Fraction& fon2) const;
    const Fraction operator*(const float& number);
    friend const Fraction operator*(const float& num,const Fraction& fon);

    // operator : [/] f1/f2 ; f1/number ; number/f1
    const Fraction operator/(const Fraction& fon2) const;
    const Fraction operator/(const float& number) const;
    friend const Fraction operator/(const float& num,const Fraction& fon);

    // operator : [==]  f1==f2
    const bool operator==(const Fraction& fon2) const;
    const bool operator==(const float& number) const;
    friend bool operator==(const float& number, const Fraction& fon);

    // operator : [=] f1 = f2
    Fraction& operator=(const Fraction& other); 
    Fraction& operator=(Fraction&& other) noexcept;

    // operator : [>] f1 > f2 / f1 > number / number > f1
    const bool operator>(const Fraction& fon2) const;
    const bool operator>(const float& number) const;
    friend const bool operator>(const float& num,const Fraction& fon1);

    // operator : [>=] f1 >= f2 / f1 >= number / number >= f1
    const bool operator>=(const Fraction& fon2) const;
    const bool operator>=(const float& number) const;
    friend const bool operator>=(const float& num,const Fraction& fon1);

    // operator : [<] f1 < f2 / f1 < number / number < f1
    const bool operator<(const Fraction& fon2) const;
    const bool operator<(const float& number) const;
    friend const bool operator<(const float& num,const Fraction& fon1);    

    // operator : [<=] f1 <= f2 / f1 <= number / number <= f1
    const bool operator<=(const Fraction& fon2) const;
    const bool operator<=(const float& number) const;
    friend const bool operator<=(const float& num,const Fraction& fon1);

    // operator : ++ 
        // prefix
    Fraction& operator++();
        //postfix
    const Fraction operator++(int flag);

    // operator : --
        // prefix
    Fraction& operator--();
        //postfix
    const Fraction operator--(int flag);

    // IO operator : friend methods
        // <<
    friend ostream& operator<<(ostream& output,const Fraction& frac);
        // >>
    friend istream& operator>>(istream& input, Fraction& frac);

    // ---------------------------- TRAINING OPERATOR -----------------------------------

    // Operator !=
    const bool operator!=(const Fraction& frac) const;
    const bool operator!=(const float& number) const;
    friend const bool operator!=(const float& num,const Fraction& frac);

    // Operator +=
    Fraction& operator+=(const Fraction& fon2);
    Fraction& operator+=(const float& number);

    // Function Pow
    Fraction pow(int pow) const;

    // Operator [] , [0] renvoie numérateur et [1] renvoie dénominateur
    int& operator[](int index);

    // Operator () renvoie la valeur décimal de la fraction
    double operator()() const;

    };
}