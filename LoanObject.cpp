#include "LoanObject.h"
#include<string>


void LoanObject::setMonthlyPayment(double payment) {
    //monthlyPayment = payment;
    double * point = &monthlyPayment;
    *point = payment;
}

void LoanObject::setName(string loanName) {
    name = loanName;
}

void LoanObject::setLoanAmount(double loanAmount) {
    initialAmount = loanAmount;
    workingAmount = loanAmount;
}

void LoanObject::setRate(double rate) {
    rateInPercent = rate;
}

double LoanObject::getWorkingAmount() {
    return workingAmount;
}

string LoanObject::getName() {
    return name;
}

double LoanObject::getMonthlyPayment() {
    return monthlyPayment;
}

double LoanObject::getRate() {
    return rateInPercent;
}

void LoanObject::setWorkingAmount(double loanWorkingAmount)
{
    double * point = &workingAmount;
    *point = loanWorkingAmount;
}



void LoanObject::iterate() {
    
    double workingRate = rateInPercent * .01;

    setWorkingAmount(getWorkingAmount() + (getWorkingAmount() * workingRate / 12));
    
    setWorkingAmount(getWorkingAmount() - monthlyPayment);
   
}

string LoanObject::toString() {


    string formattedName = name;
    string formattedRate = std::to_string(rateInPercent);
    string formattedAmount = std::to_string(workingAmount);
    string formattedPayment = std::to_string(monthlyPayment);
 
    formattedName.resize(17, ' ');
    formattedRate.resize(17, ' ');
    formattedAmount.resize(17, ' ');
    formattedPayment.resize(17, ' ');

    string representation = formattedName + "|" + formattedRate + "|" + formattedPayment + "|" + formattedAmount + "|\n";
    return representation;
} 

void LoanObject::reset() {
    workingAmount = initialAmount;
}
LoanObject::LoanObject(string loanName, double loanAmount, double loanRateInPercent, double loanMonthlyPayment) {
    setName(loanName);
    setMonthlyPayment(loanMonthlyPayment);
    setLoanAmount(loanAmount);
    setRate(loanRateInPercent);
    setMonthlyPayment(loanMonthlyPayment);
}
