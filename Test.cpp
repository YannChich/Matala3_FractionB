#include "doctest.h"
#include "sources/Fraction.hpp"
#include <stdexcept>
#include <iostream>
#include <string>
using namespace std;
using namespace ariel;


Fraction ConvertFloat(float num){
        int denominator = 1;
        // If my number got a decimal part it's always execute the while.
        while(num != floor(num)){
            denominator *=10;
            num*=10;
        }
        int numerator = static_cast<int>(num);

        return Fraction(numerator,denominator);
    }

TEST_CASE("Creation of a fraction"){
    Fraction frac1 = Fraction(1,2);
    Fraction frac2 = Fraction(8,2);

    CHECK_THROWS_AS(Fraction(3, 0),invalid_argument);
    CHECK_NOTHROW(Fraction(4,7));
    CHECK(frac1.getDenominator() == 2);
    CHECK(frac1.getNumerator() == 1);
    CHECK(frac2.getDenominator() == 1);
    CHECK(frac2.getNumerator() == 4);   
    
}

TEST_CASE("Float to Fraction"){
    float num = 1.43;
    Fraction frac = Fraction(num);
    CHECK(frac == Fraction(143,100));
    float num1 = 0.66;
    Fraction frac1 = Fraction(num1);
    CHECK(frac1 == Fraction(33,50));

}

TEST_CASE("Operator +"){
    Fraction frac(1,2);
    Fraction frac1(2,7);
    CHECK((frac+frac1) == Fraction(11,14));
    float num = 0.5;
    CHECK((frac1+num) == Fraction(11,14));
    Fraction frac2 = frac+frac1;
    CHECK((frac2+num) == Fraction(9,7));
}

TEST_CASE("Operator -"){
    Fraction frac(4,5);
    Fraction frac1(13,7);
    CHECK((frac-frac1) == Fraction(-37,35));
    float num = 1.76;
    CHECK((frac1+num) == Fraction(633,175));
    Fraction frac2 = frac+frac1;
    CHECK((frac2-num) == Fraction(157,175));
}

TEST_CASE("Operator *"){
    Fraction frac(1,2);
    Fraction frac1(2,7);
    CHECK((frac*frac1) == Fraction(1,7));
    float num = 0.5;
    CHECK((frac1*num) == Fraction(1,7));
    Fraction frac2 = frac+frac1;
    CHECK((frac2*num) == Fraction(11,28));
}

TEST_CASE("Operator /"){
    Fraction frac(5,9);
    Fraction frac1(2,7);
    CHECK((frac/frac1) == Fraction(35,18));
    float num = 0.8;
    CHECK((frac1/num) == Fraction(5,14));
    Fraction frac2 = frac*frac1;
    CHECK((frac2/num) == Fraction(25,126));
}

TEST_CASE("Operator =="){
    Fraction f1(2, 4);
    Fraction f2(1, 2);
    Fraction f3(3, 6);
    Fraction f4(5, 15);
    Fraction f5(7, 3);
    float num1 = 0.5;
    float num2 = 2.333333;
    CHECK(f1 == f2);
    CHECK(f1 == f3);
    CHECK(f2 == f3);
    CHECK_FALSE(f3 == f4);

    CHECK_FALSE(f1 == f5);
    CHECK_FALSE(f2 == f5);
    CHECK_FALSE(f3 == f5);
    CHECK_FALSE(f4 == f5);

    CHECK(f1 == num1);
    CHECK(f2 == num1);
    CHECK(f3 == num1);
    CHECK_FALSE(f4 == num1);

    CHECK_FALSE(f1 == num2);
    CHECK_FALSE(f2 == num2);
    CHECK_FALSE(f3 == num2);
    CHECK_FALSE(f4 == num2);
    CHECK_FALSE(f5 == num2);
}

TEST_CASE("Operator =") {
    ariel::Fraction frac1(2, 4);
    ariel::Fraction frac2(1, 2);

    Fraction frac3, frac4;

   
    frac3 = frac1;
    CHECK(frac3 == frac1);
    CHECK(frac3.getNumerator() == 1);
    CHECK(frac3.getDenominator() == 2);

    frac4 = frac2;
    CHECK(frac4 == frac2);
    CHECK(frac4.getNumerator() == 1);
    CHECK(frac4.getDenominator() == 2);


    frac2 = frac2;
    CHECK(frac2.getNumerator() == 1);
    CHECK(frac2.getDenominator() == 2);
}

TEST_CASE("Operator <") {
    Fraction frac1(1, 2);
    Fraction frac2(1, 3);
    CHECK(frac2 < frac1);
}

TEST_CASE("Operator >") {
    Fraction frac1(1, 2);
    Fraction frac2(1, 3);
    CHECK(frac1 > frac2);
}

TEST_CASE("Operator <=") {
    Fraction frac1(1, 2);
    Fraction frac2(1, 3);
    Fraction frac3(1, 2);
    CHECK(frac2 <= frac1);
    CHECK(frac1 <= frac3);
}

TEST_CASE("Operator >=") {
    Fraction frac1(1, 2);
    Fraction frac2(1, 3);
    Fraction frac3(1, 2);
    CHECK(frac1 >= frac2);
    CHECK(frac1 >= frac3);
}

TEST_CASE("Operator ++ and --"){
    Fraction f1(1, 2);

    Fraction f2 = ++f1;
    CHECK(f1.getNumerator() == 3);
    CHECK(f1.getDenominator() == 2);
    CHECK(f2.getNumerator() == 3);
    CHECK(f2.getDenominator() == 2);

    Fraction f5 = f1--;
    CHECK(f1.getNumerator() == 1);
    CHECK(f1.getDenominator() == 2);
    CHECK(f5.getNumerator() == 3);
    CHECK(f5.getDenominator() == 2);
}

TEST_CASE("Operator << and >>"){
    Fraction f1(3,4);
    ostringstream ss;
    ss << f1;
    CHECK(ss.str() == "3/4");

    istringstream iss("5 6");
    Fraction f2;
    iss >> f2;
    CHECK(f2.getNumerator() == 5);
    CHECK(f2.getDenominator() == 6);
}

TEST_CASE("Operator !="){
    Fraction f1(2,3);
    Fraction f2(4,6);

    CHECK_FALSE(f1!=f2);
    Fraction f3(1,2);
    CHECK(f1!=f3);

    Fraction f4(10,2);
    float num = 5;
    CHECK_FALSE(f4!=5);
    float num2 = 4;
    CHECK(f4!=num2);

    Fraction f5(100,2);
    float num3 = 50.1;
    CHECK(num3!=f5);
    float num4=50;
    CHECK_FALSE(num4!=f5);
}

TEST_CASE("Operator +="){
    Fraction f1{1,2};
    Fraction f2{1,3};
    Fraction f3{5,6};
    CHECK((f1+=f2) == f3);
    
    Fraction f4{2,4};
    float num = 0.25;
    Fraction f5{3,4};
    CHECK((f4+=num) == f5);
}

TEST_CASE("Testing pow method") {
    ariel::Fraction f1(2, 3);

    SUBCASE("Positive power") {
        ariel::Fraction result = f1.pow(2);
        CHECK(result.getNumerator() == 4);
        CHECK(result.getDenominator() == 9);
    }

    SUBCASE("Zero power") {
        ariel::Fraction result = f1.pow(0);
        CHECK(result.getNumerator() == 1);
        CHECK(result.getDenominator() == 1);
    }

    SUBCASE("Negative power") {
        ariel::Fraction result = f1.pow(-2);
        CHECK(result.getNumerator() == 9);
        CHECK(result.getDenominator() == 4);
    }
}

TEST_CASE("Operator []"){
    Fraction f1{11,13};
    CHECK(f1[0] == 11);
    CHECK(f1[1] == 13);
    CHECK_THROWS(f1[8]);
}

TEST_CASE("Operator ()"){
    Fraction f1{27,6};
    CHECK(f1() == 4.5);
    Fraction f2{-8,13};
    CHECK(f2() == -0.615);
}



