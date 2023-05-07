#include "Fraction.hpp"
using namespace std;
using namespace ariel;


// Constructors

   //Default
    Fraction::Fraction(){
        this->numerator = 0;
        this->denominator = 1;
    }
    //Parameterized
    Fraction::Fraction(int num,int den): numerator(num), denominator(den) {
        if(denominator==0){
            throw invalid_argument("The denominator cannot be 0");
        }else{
            Min_Form(numerator,denominator);
        }
    }
/*
To convert a float we can multiply the number by 10 until his decimal part is equal to 0
EX : 0.44 --> 1 : den = 10 nun = 4.4
              2 : den = 100 num = 44
              0.44 = 44/100 and we apply the Min_form() ----> 11/25
*/
    Fraction::Fraction(double num){
        this->denominator = 1;
        int decimal_places = 0;
        int Max_decimal = 3;

        while (num != floor(num) && decimal_places < Max_decimal) {
            this->denominator *= 10;
            num *= 10;
            decimal_places++;
        }
        this->numerator = static_cast<int>(num);
        Min_Form(this->numerator,this->denominator);
    }

    //Copy
    Fraction::Fraction(const Fraction& other) {
    this->numerator = other.numerator;
    this->denominator = other.denominator;
    }
    // Move Constructor
    Fraction::Fraction(Fraction&& other) noexcept{}

// Destructor 
    Fraction::~Fraction(){}

// Function to change the function to the min form : exemple : 2/6 = 1/3
    int Fraction:: pgcd(int varA, int varB) {
    if (varB == 0) {
        return varA;
        } 
    else {
        return pgcd(varB, varA % varB);
        }
    }

    void Fraction:: Min_Form(int& num, int& den){
        int diviseur = pgcd(num, den);
        num /= diviseur;
        den /= diviseur;
    }

    // operator : [+] f1+f2 / f1+number / number+f1
    /*
    EX : 1/2 + 1/4 = We need to multiply (1/2)*4 and (1/4)*2 = 4/8 + 2/8 = 6/8 and after apply the function Min_Form = 3/4
    */
    const Fraction Fraction:: operator+(const Fraction& frac2) const{
        int num = (this->numerator * frac2.denominator) + (this->denominator * frac2.numerator);
        int den = (this->denominator * frac2.denominator);
        Fraction frac = Fraction(num,den);
        return frac;
    }
    const Fraction Fraction:: operator+(const float& number){
        Fraction frac2 = Fraction(number);
        return *this + frac2;
    }
    const  Fraction ariel::operator+(const float& num,const Fraction& frac){
        Fraction frac2 = Fraction(num);
        return frac2 + frac;
    }

    // operator : [-] f1-f2 / f1-number / number-f1
    /*
    EX : 1/4 - 1/2 = We need to multiply (1/4)*2 and (1/2)*4 = 2/8 - 4/8 = -2/8 and after apply the function Min_Form = -1/4
    */
    const Fraction Fraction:: operator-(const Fraction& frac2) const{
        int num = (this->numerator * frac2.denominator) - (this->denominator * frac2.numerator);
        int den = (this->denominator * frac2.denominator);
        Fraction frac = Fraction(num,den);
        return frac;
    }
    const Fraction Fraction:: operator-(const float& number) const{
        Fraction frac2 = Fraction(number);
        return *this - frac2;
    }
    const Fraction ariel::operator-(const float& num,const Fraction& frac){
        Fraction frac2 = Fraction(num);
        return frac2 - frac;
    }


    // operator : [*] f1*f2 / f1*number / number*f1
    /*
    EX : 1/4 * 1/2 = We need to multiply each numerators and denominator : num = 1*1 , den = 2*4 = 1/8 and apply Min_Form
    */
    const Fraction Fraction:: operator*(const Fraction& frac2) const{
        int num = this->numerator * frac2.numerator;
        int den = this->denominator * frac2.denominator;
        Fraction frac = Fraction(num,den);
        return frac;
    }
    const Fraction Fraction:: operator*(const float& number){
        Fraction frac2 = Fraction(number);
        return *this * frac2;
    }
    const Fraction ariel::operator*(const float& num,const Fraction& frac){
        Fraction frac2 = Fraction(num);
        return frac2 * frac;
    }

    // operator : [/] f1/f2 ; f1/number ; number/f1
    /*
    EX = 1/4 div 1/2. It's the same of 1/4 * 2/1 ; num = num1*den2 / den = den=den1*num2
    */
    const Fraction Fraction:: operator/(const Fraction& frac2) const{
        int num = this->numerator * frac2.denominator;
        int den = this->denominator * frac2.numerator;
        Fraction frac = Fraction(num,den);
        return frac;
    }
    const Fraction Fraction:: operator/(const float& number) const{
        Fraction frac = Fraction(number);
        return *this / frac;
    }
    const Fraction ariel::operator/(const float& num,const Fraction& frac){
        Fraction frac2 = Fraction(num);
        return frac2 / frac;
    }

    // operator : [==]  f1==f2 
    /*
    The two function is the min_Form because when we create a Func they call the function
    */
    const bool Fraction::operator==(const Fraction& frac2) const{
        return (this->numerator == frac2.numerator && this->denominator == frac2.denominator);
    }
    const bool Fraction::operator==(const float& number) const{
        Fraction frac = Fraction(number);
        return *this == frac;
    }
    bool ariel::operator==(const float& number, const Fraction& frac){
        Fraction frac2 = Fraction(number);
        return frac2 == frac;        
    }

    // operator : [=] f1 = f2
    // For the copie
    Fraction& Fraction::operator=(const Fraction& other){
        if(this != &other){ // Vérifier si les deux objets sont différents
            numerator = other.numerator;
            denominator = other.denominator;
        }
        return *this; // Renvoyer l'objet modifié
    }
    // For the move
    Fraction& Fraction::operator=(Fraction&& other) noexcept{
        if(this != &other){ // Vérifier si les deux objets sont différents
            numerator = move(other.numerator); // Utiliser std::move pour transférer les données de l'objet "other"
            denominator = move(other.denominator);
        }
        return *this; // Renvoyer l'objet modifié
    }

    // operator : [>] f1 > f2 / f1 > number / number > f1
    /*
    Each fonction is the min_Form.
    First : check if the numerator is the same and after check the numerator
    5/7 > 3/2 ?  5*2 = 10 / 3*7 = 21  So 3/2 bigger than 5/7
    */
    const bool Fraction:: operator>(const Fraction& frac2) const{
        if(this->denominator == frac2.denominator){
            return this->numerator > frac2.numerator;
        }else{
            return (this->numerator * frac2.denominator) > (this->denominator * frac2.numerator);
        }
    }
    const bool Fraction:: operator>(const float& number) const{
        Fraction frac = Fraction(number);
        return *this > frac;
    }
    const bool ariel::operator>(const float& num,const Fraction& frac){
        Fraction frac2 = Fraction(num);
        return frac2 > frac;
    }

    // operator : [>=] f1 >= f2 / f1 >= number / number >= f1
    const bool Fraction:: operator>=(const Fraction& frac2) const{
        if(this->denominator == frac2.denominator){
            return this->numerator >= frac2.numerator;
        }else{
            return (this->numerator * frac2.denominator) >= (this->denominator * frac2.numerator);
        }
    }
    const bool Fraction:: operator>=(const float& number) const{
        Fraction frac = Fraction(number);
        return *this >= frac;
    }
    const bool ariel::operator>=(const float& num,const Fraction& frac){
        Fraction frac2 = Fraction(num);
        return frac2 >= frac;
    }

    // operator : [<] f1 < f2 / f1 < number / number < f1
    const bool Fraction:: operator<(const Fraction& frac2) const{
        if(this->denominator == frac2.denominator){
            return this->numerator < frac2.numerator;
        }else{
            return (this->numerator * frac2.denominator) < (this->denominator * frac2.numerator);
        }
    }
    const bool Fraction:: operator<(const float& number) const{
        Fraction frac = Fraction(number);
        return *this < frac;
    }
    const bool ariel::operator<(const float& num, const Fraction& frac) {
        Fraction frac2 = Fraction(num);
        return frac2 < frac;
}


    // operator : [<=] f1 <= f2 / f1 <= number / number <= f1
    const bool Fraction:: operator<=(const Fraction& frac2) const{
        if(this->denominator == frac2.denominator){
            return this->numerator <= frac2.numerator;
        }else{
            return (this->numerator * frac2.denominator) <= (this->denominator * frac2.numerator);
        }
    }
    const bool Fraction:: operator<=(const float& number) const{
        Fraction frac = Fraction(number);
        return *this <= frac;
    }
    const bool ariel::operator<=(const float& num,const Fraction& frac){
        Fraction frac2 = Fraction(num);
        return frac2 <= frac;
    }

    // operator : ++ 
        // prefix
    Fraction& Fraction:: operator++(){
        numerator += denominator;
        Min_Form(numerator,denominator);
        return *this;
    }
        //postfix
    const Fraction Fraction:: operator++(int flag){
        Fraction old = *this;
        numerator += denominator;
        Min_Form(numerator,denominator);
        return old;
    }
     
    // operator : --
        // prefix
    Fraction& Fraction:: operator--(){
        numerator -= denominator;
        Min_Form(numerator,denominator);
        return *this;   
    }
        //postfix
    const Fraction Fraction:: operator--(int flag){
        Fraction old = *this;
        numerator -= denominator;
        Min_Form(numerator,denominator);
        return old;
    }
