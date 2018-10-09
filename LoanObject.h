#ifndef LOANOBJECT_H
#define LOANOBJECT_H
#include<string>
using namespace std;
class LoanObject {

private:
    string name;
    double initialAmount;
    double workingAmount;
    double rateInPercent;
    double monthlyPayment;

public:
LoanObject(string loanName, double loanAmount, double loanRateInPercent, double loanMonthlyPayment);


void setName(string loanName);

void setLoanAmount(double loanAmount);

void setRate(double rate);

void setWorkingAmount(double loanWorkingAmount);

void setMonthlyPayment(double payment);

double getMonthlyPayment();

double getRate();

double getWorkingAmount();

string getName();

void iterate();

string toString();

void reset();

};
#endif