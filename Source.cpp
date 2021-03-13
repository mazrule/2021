#include <iostream>
#include <iomanip>
#include <math.h>
#include <string>
#include <fstream>
#include <vector>
#include <locale>
using namespace std;

int main(int argc, char* argv[])
{
    double loanAmount;
    double annualInterestRate;
    int numberOfYears, numberOfMonths;
    double additionalPPerMonth;

    string fileNameToWrite;

    cout << "\nEnter Loan amount (0-9999999), for example 300000.90: ";
    while (!(std::cin >> loanAmount) || loanAmount > 9999999 || loanAmount <= 0)
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Error: That is not a valid input. Enter a number between 0 and 9999999: ";
    }
    cout << "\nEnter annual interest rate(0-30), for example 4.25 meaning 4.25%: ";
    while (!(std::cin >> annualInterestRate) || annualInterestRate > 30 || annualInterestRate <= 0)
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Error: That is not a valid input. Enter a number between 0 and 30: ";
    }

    cout << "\nEnter no. of years as integer(1-99), for example 30: ";

    while (!(std::cin >> numberOfYears) || numberOfYears > 99 || numberOfYears < 1)
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Error: That is not a valid input. Enter a number between 1 and 99: ";
    }

    numberOfMonths = numberOfYears * 12;
    cout << "\nEnter additional principle per month (0-9999999), for example 300: ";

    while (!(std::cin >> additionalPPerMonth) || additionalPPerMonth > 9999999 || additionalPPerMonth < 0)
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Error: That is not a valid input. Enter a number between 0 and 9999999: ";
    }

    cout << "\nSend the mortgage amortization table to a file (enter file name): ";

    cin >> fileNameToWrite;

    ofstream outFile;

    outFile.open(fileNameToWrite);

    outFile.imbue(std::locale(""));

    double monthlyPayment = (loanAmount * annualInterestRate / 100 / 12) / (1 -
        1 / pow(1 + annualInterestRate / 100 / 12, numberOfYears * 12));
    double actualPayment = monthlyPayment + additionalPPerMonth;

    outFile << "\t\t"
        << "MORTGAGE AMORTIZATION TABLE";

    outFile << std::setw(25) << "\n\nAmount:\t\t\t" << std::fixed << std::setprecision(2) << std::internal << "$" << std::setw(12) << loanAmount;
    outFile << std::setw(25) << "\nInterest Rate:\t\t" << std::setprecision(3) << annualInterestRate << "%";
    outFile << std::setw(25) << "\nTerms(Years): \t\t" << numberOfYears;
    outFile << std::setw(25) << "\nMonthly Payment:\t" << std::setprecision(2) << std::internal << "$" << std::setw(12) << monthlyPayment;
    outFile << std::setw(25) << "\nAdditional Payment:\t" << std::setprecision(2) << std::internal << "$" << std::setw(12) << additionalPPerMonth;
    outFile << std::setw(25) << "\nActual Payment:\t\t" << std::setprecision(2) << std::internal << "$" << std::setw(12) << actualPayment;
    outFile << std::setw(25) << "\n\n\t"<< std::right << std::setw(12)<<"Principle"
         << "\t\t"<< std::right << std::setw(12) << "Interest" << "\t\t"<< std::right << std::setw(12) << "Balance";

    double balance = loanAmount;
    double interest, principle;
    int i = 1;

    while (balance > 0) {
        interest = (balance * annualInterestRate / 12) / 100;
        if (actualPayment - interest > balance)
        {
            principle = balance;
        }
        else
        {
            principle = actualPayment - interest;
        }
        balance = balance - principle;
        if (balance < 0) {

            balance = 0;
        }
        if (i == 1)
        {
            outFile << "\n" << i
                << "\t" << std::fixed << std::setprecision(2) << std::internal << "$" << std::setw(12) << principle
                << "\t\t" << std::fixed << std::setprecision(2) << std::internal << "$" << std::setw(12) << interest
                << "\t\t" << std::fixed << std::setprecision(2) << std::internal << "$" << std::setw(12) << balance;
            i += 1;
        }
        else
        {
            outFile << "\n" << i
                << "\t" << std::fixed << std::setprecision(2) << std::internal << " " << std::setw(12) << principle
                << "\t\t" << std::fixed << std::setprecision(2) << std::internal << " " << std::setw(12) << interest
                << "\t\t" << std::fixed << std::setprecision(2) << std::internal << " " << std::setw(12) << balance;
            i += 1;
        }
    }
    outFile.close();
}
