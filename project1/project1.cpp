/**
 * @file project1.cpp
 * @author Md Arifuzzaman Faisal
 * @date 29 January, 2025
 * @brief Program to approximate integrals using the midpoint rectangle method.
 */

#include <iostream>
using namespace std;

// Constants
const int MAX_RECTANGLES = 100; // Maximum number of rectangles for precision check
const int CHOICE_FIRST = 1;
const int CHOICE_SECOND = 2;
const int CHOICE_THIRD = 3;

// Function Prototypes
/**
 * @brief Prints the menu options for the user.
 */
void printMenu();
/**
 * @brief Raises a value to a specified power.
 * @param val The base value.
 * @param power The exponent value.
 * @return The result of val raised to the power.
 */
double toThePower(const double val, const int power);
/**
 * @brief Evaluates the function y = ax^3 + bx^2 + cx + d at a given x.
 * @param aCoeff Coefficient for x^3.
 * @param bCoeff Coefficient for x^2.
 * @param cCoeff Coefficient for x.
 * @param dCoeff Constant term.
 * @param xValue The value at which the function is evaluated.
 * @param resultVal Reference parameter to store the result.
 * @return True if the result is non-negative, false otherwise.
 */
bool evaluateCubicFormula(const double aCoeff, const double bCoeff, const double cCoeff, 
                        const double dCoeff, const double xValue, double &resultVal);
                        /**
 * @brief Approximates the area under the curve using rectangles.
 * @param aCoeff Coefficient for x^3.
 * @param bCoeff Coefficient for x^2.
 * @param cCoeff Coefficient for x.
 * @param dCoeff Constant term.
 * @param startX Start of the integration range.
 * @param endX End of the integration range.
 * @param numRects Number of rectangles to use.
 * @return The approximate area under the curve.
 */
double approximateAreaWithRectangles(const double aCoeff, const double bCoeff, const double cCoeff, 
                        const double dCoeff, const double startX, const double endX, const int numRects);

#ifdef ANDREW_TEST
#include "andrewTest.h"
#else
int main() 
{
    int userChoice;
    double coeffA, coeffB, coeffC, coeffD;
    double startX, endX;
    int numRectangles;
    double correctValue, precision;
    bool isRunning = true;

    while (isRunning) 
    {
        printMenu();
        cout << "YOUR CHOICE: ";
        cin >> userChoice;

        if (userChoice == CHOICE_THIRD) 
        {
            cout << "Thanks for using this program"<<endl;
            isRunning = false;
        }
        else if (userChoice == CHOICE_FIRST || userChoice == CHOICE_SECOND) 
        {
            cout << "Enter (a b c d) for function y = a*x^3 + b*x^2 + c*x + d: ";
            cin >> coeffA >> coeffB >> coeffC >> coeffD;

            bool isValidRange = false;
            while (!isValidRange) 
            {
                cout << "Now enter x start and end values: ";
                cin >> startX >> endX;
                if (startX < endX) 
                {
                    isValidRange = true;
                }
                else 
                {
                    cout << "Invalid range entered\n";
                }
            }

            if (userChoice == CHOICE_FIRST) 
            {
                bool isValidRectangles = false;
                while (!isValidRectangles) 
                {
                    cout << "Enter the number of rectangles to use: ";
                    cin >> numRectangles;
                    if (numRectangles > 0) 
                    {
                        isValidRectangles = true;
                    }
                    else 
                    {
                        cout << "Invalid number of rectangles entered"<<endl;
                    }
                }
                double result = approximateAreaWithRectangles(coeffA, coeffB, coeffC, coeffD, startX, endX, numRectangles);
                cout << "Rectangle result is: " << result << endl;
            }
            else if (userChoice == CHOICE_SECOND) 
            {
                cout << "Enter correct answer: ";
                cin >> correctValue;
                cout << "Enter precision to reach: ";
                cin >> precision;

                int neededRectangles = 1;
                bool precisionReached = false;
                bool precisionNotFound = true;
                while (neededRectangles <= MAX_RECTANGLES && precisionNotFound) 
                {
                    double result = approximateAreaWithRectangles(coeffA, coeffB, coeffC, coeffD, startX, endX, neededRectangles);
                    double resultPrecision = result - correctValue;
                    if (resultPrecision < 0)
                    {
                        resultPrecision= -1.0*resultPrecision;
                    }
                    if (resultPrecision <= precision) 
                    {
                        precisionReached = true;
                        precisionNotFound = false;
                        --neededRectangles;
                    }
                    ++neededRectangles;
                }

                if (precisionReached) 
                {
                    cout << "Rectangles needed to reach precision: " << neededRectangles << endl;
                } 
                else 
                {
                    cout << "Tried " << MAX_RECTANGLES << " rectangles without reaching precision"<<endl;
                }
            }
        }
        else 
        {
            cout << "Invalid menu choice entered\n";
        }
    }

    return 0;
}
#endif

// Function Definitions
void printMenu() 
{
    cout << "1 Approximate Integral Using Rectangles"<<endl;
    cout << "2 Experiment With Rectangle Precision"<<endl;
    cout << "3 Quit The Program"<<endl;
}

double toThePower(const double val, const int power) 
{
    double result = 1.0;
    for (int i = 0; i < power; ++i) 
    {
        result *= val;
    }
    return result;
}

bool evaluateCubicFormula(const double aCoeff, const double bCoeff, const double cCoeff, 
                        const double dCoeff, const double xValue, double &resultVal) 
{
    resultVal = aCoeff * toThePower(xValue, 3) + bCoeff * toThePower(xValue, 2) + cCoeff * xValue + dCoeff;
    return (resultVal>0);
}

double approximateAreaWithRectangles(const double aCoeff, const double bCoeff, const double cCoeff, 
                                    const double dCoeff, const double startX, const double endX, const int numRects) 
{
    double width = (endX - startX) / numRects;
    double sum = 0.0;

    for (int i = 0; i < numRects; ++i) 
    {
        double midX = startX + (i + 0.5) * width;
        double yHeight;
        evaluateCubicFormula(aCoeff, bCoeff, cCoeff, dCoeff, midX, yHeight);
        // Return the absolute value of the function
        if (yHeight < 0)
        {
            yHeight = -1.0*yHeight;
        }
        sum += yHeight * width;
    }
    return sum;
}
