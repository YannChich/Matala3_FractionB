#include "Fraction.hpp"
#include <cstdlib>  // function abs()
using namespace std;
using namespace ariel;


// Constructors

   //Default
    Fraction::Fraction(){
        this->numerator = 0;
        this->denominator = 1;
    }
    //Parameterized
    Fraction::Fraction(int num,int den): numerator(num),denominator(den){
        if(this->denominator==0){
            throw invalid_argument("The denominator cannot be 0");
        }else{
            Min_Form(this->numerator,this->denominator);
            if(this->denominator < 0){
                this->numerator *= -1;
                this->denominator *= -1;
            }
        }
    }
/*
To convert a float we can multiply the number by 10 until his decimal part is equal to 0
EX : 0.44 --> 1 : den = 10 nun = 4.4
              2 : den = 100 num = 44
              0.44 = 44/100 and we apply the Min_form() ----> 11/25
Why using round : if we get the number 2.782 the row 34 going to round our number *1000
EX : round(2.782*1000) ---> round(2782.0) 
*/
    Fraction::Fraction(double num){
    int numerator = static_cast<int>(round(num * 1000));
    int denominator = 1000;
    Min_Form(numerator, denominator);
    this->numerator = numerator;
    this->denominator = denominator;
    }

    //Copy
    Fraction::Fraction(const Fraction& other) : numerator(other.numerator), denominator(other.denominator) {}
    // Move Constructor
    // https://en.cppreference.com/w/cpp/language/move_assignment
    Fraction::Fraction(Fraction&& other) noexcept : numerator(move(other.numerator)), denominator(move(other.denominator)) {
        other.numerator = 0;
        other.denominator = 1;
    }

// Destructor 
    Fraction::~Fraction(){}

// Function to change the function to the min form : exemple : 2/6 = 1/3
    int Fraction::pgcd(int varA, int varB) {
        if (varB == 0) {
            return varA;
        } 
        else {
            return pgcd(varB, varA % varB);
        }
    }

    void Fraction::Min_Form(int& num, int& den) {
        int diviseur = abs(pgcd(num, den));
        num /= diviseur;
        den /= diviseur;
    }

    /*For each arithmetic operation we are goind to check an Overflow of a Interget 
    The biggest number is : 2¹⁶ * 2¹⁶ = 2³² need to work with long to check with the max int : 2¹⁶
    https://www.tutorialspoint.com/check-for-integer-overflow-on-multiplication-in-cplusplus
    */


    // operator : [+] f1+f2 / f1+number / number+f1
    /*
    EX : 1/2 + 1/4 = We need to multiply (1/2)*4 and (1/4)*2 = 4/8 + 2/8 = 6/8 and after apply the function Min_Form = 3/4
    */
    const Fraction Fraction:: operator+(const Fraction& frac2) const{
        long num = static_cast<long>((this->numerator * frac2.denominator)) + static_cast<long>((this->denominator * frac2.numerator));
        if(num > numeric_limits<int>::max() || num < numeric_limits<int>::min()){
            throw overflow_error("Overflow from the numerator");
        }
        long den = static_cast<long>((this->denominator * frac2.denominator));
        if(den > numeric_limits<int>::max() || den < numeric_limits<int>::min()){
            throw overflow_error("Overflow from the denominator");
        }
        Fraction frac = Fraction(num,den);
        return frac;
    }
    const Fraction Fraction:: operator+(const float& number){
        Fraction frac2 = Fraction(number);
        cout << frac2 << endl;
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
        long num = static_cast<long>((this->numerator * frac2.denominator)) - static_cast<long>((this->denominator * frac2.numerator));
        if(num > numeric_limits<int>::max() || num < numeric_limits<int>::min()){
            throw overflow_error("Overflow from the numerator");
        }
        long den = static_cast<long>((this->denominator * frac2.denominator));
        if(den > numeric_limits<int>::max() || den < numeric_limits<int>::min()){
            throw overflow_error("Overflow from the denominator");
        }
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
        long num = static_cast<long>(this->numerator) * static_cast<long>(frac2.numerator);
        if(num > numeric_limits<int>::max() || num < numeric_limits<int>::min()){
            throw overflow_error("Overflow from the numerator");
        }
        long den = static_cast<long>(this->denominator) * static_cast<long>(frac2.denominator);
        if(den > numeric_limits<int>::max() || den < numeric_limits<int>::min()){
            throw overflow_error("Overflow from the denominator");
        }
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
    We can use the operator *
    */
    const Fraction Fraction:: operator/(const Fraction& frac2) const{
        if(frac2 == 0){
            throw runtime_error("Cannot divide by 0");
        }
        // Inverse the fraction in the argument
        Fraction frac = Fraction(frac2.denominator,frac2.numerator);
        return *this*frac;
    }
    const Fraction Fraction:: operator/(const float& number) const{
        if(number == 0){
            throw runtime_error("Cannot divise by 0");
        }
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
        if(this->numerator == 0 && frac2.numerator == 0){
            return true;
        }
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
        if(this == &other){
            return *this;
        }
        numerator = move(other.numerator);
        denominator = move(other.denominator);
        other.numerator = 0;
        other.denominator =1;
        return *this;
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

    ostream& ariel::operator<<(ostream& output,const Fraction& frac){
        return output << frac.numerator << "/" << frac.denominator;
    }

    istream& ariel::operator>>(istream& input, Fraction& frac){
        char chr = 0;
        input >> frac.numerator >> frac.denominator;
        if(frac.denominator < 0){
            frac.denominator *= -1;
            frac.numerator *= -1;
        }
        if(frac.denominator == 0){
            throw runtime_error("Wrong input denominator == 0.");
        }
        //Help on : https://stackoverflow.com/questions/4206816/ifstream-check-if-opened-successfully
        //        : https://web.physics.utah.edu/~detar/phys6720/handouts/iomethods/iomethods/node2.html
        if(input.fail()){
            throw runtime_error("Wrong input, the standard input is : Fraction(number1 number2).");
        }
        return input;
    }

    // ----------------------------------- TRAINING EXAM ------------------------------

    // Operator !=
    const bool Fraction::operator!=(const Fraction& frac) const{
        return !(*this==frac);

    }
    const bool Fraction::operator!=(const float& number) const{
        return !(*this==number);
    }
    const bool ariel::operator!=(const float& num,const Fraction& frac){
        return !(num==frac);
    }

    // Operator += , toute les opération serons sur this
    // 1/3 += 1/2 ---> 1/3 + 1/2 donc je dois multiplier les dénominteur ensemble et ensuite ajouter les numérateur
    // 1/3 + 1/2 = 1*2 / 3*2  +  1*3 / 3*2  = 2/6 + 3/6 = 5/6
    Fraction& Fraction::operator+=(const Fraction& fon2){
        this->numerator = (this->numerator * fon2.denominator) + (fon2.numerator * this->denominator);
        this->denominator = this->denominator * fon2.denominator;
        Min_Form(this->numerator,this->denominator);
        return *this;
    }
    Fraction& Fraction::operator+=(const float& number){
        Fraction frac = Fraction(number);
        return *this+=frac;
    }

    // Function Pow
    Fraction Fraction::pow(int pow) const {
        int num =1;
        int deno =1;
        if(pow ==0){
            return Fraction(1,1); 
        }
        else if(pow > 0){
            for(int i=0;i<pow;i++){
                num *= this->numerator;
                deno *= this->denominator;
            }
        }
        else {
            // la puissance est negatif donc je dois faire par exemple : (2/5)^-3 = (5^3 / 2^3)
            for(int i=0;i<abs(pow);i++){
                num *= this->denominator;
                deno *= this->numerator;
            }
        }
        return Fraction(num,deno);
    }

    int& Fraction::operator[](int index){
        if(index > 1 || index < 0){
            throw out_of_range("Invalid index : usage : index=0 || index=1");
        }
        if(index == 0) return this->numerator;
        return this->denominator;
    }


    double Fraction::operator()() const {
        double result = static_cast<double>(this->numerator) / this->denominator;
        result = round(result * 1000) / 1000;
        return result;
    }
