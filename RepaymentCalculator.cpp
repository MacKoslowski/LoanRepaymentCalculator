#include<iostream>
#include<string>
#include<vector>
#include<set>
#include<algorithm>
#include "LoanObject.h"






LoanObject createLoan(set<string> nameSet) {
    

    string name;
    string amountString;
    string rateInPercentString;
    string monthlyPaymentString;
    double amount;
    double rateInPercent;
    double monthlyPayment;

    bool nameFound = false;
    
    while(!nameFound) {
        
        std::cout << "Enter a name for the loan:\n";

        std::getline(std::cin, name);

        set<string>::iterator iterator = nameSet.find(name);

        if (iterator != nameSet.end()) {
            std::cout << "Name already in use. Enter another name.\n";
            
        } else {
            nameFound = true;
        }

    }

   
    std::cout << "Enter an amount for the loan:\n";

    std::getline(std::cin, amountString);

    std::cout << "Enter the rate in percent for the loan (ex: 28.7):\n";

    std::getline(std::cin, rateInPercentString);

    std::cout << "Enter a monthly payment for the loan:\n";

    std::getline(std::cin, monthlyPaymentString);

    amount = atof(amountString.c_str());

    rateInPercent = atof(rateInPercentString.c_str());

    monthlyPayment = atof(monthlyPaymentString.c_str());

    LoanObject loan(name, amount, rateInPercent, monthlyPayment);
    nameSet.insert(name);
   
    return loan;
    
}

string queryForLoan(bool afterFirst) {
    string choice;
    
    if(afterFirst) {
        std::cout << "Would you like to enter another loan (y/n)?\n";
        
    } else {
        std::cout << "Would you like to enter a loan (y/n)?\n";
        afterFirst = true;
    }
        
   
    std::getline(std::cin, choice);
    
    return choice;
}

int queryAction() {
    std::cout << "Press 1 to iterate loans until repayment completed. Press 2 to step through repayment manually.\n";
    std::cout << "Press 3 to change payments. Press q to quit.\n";

    string input;
    int returnInt;

    std::getline(std::cin, input);


    if(input == "1") {
        returnInt = 1;
    } else if (input == "2"){
        returnInt = 2;
    } else if (input == "3"){
        returnInt = 3;
    } else if(input == "q"){
        exit(EXIT_SUCCESS);

    }else {
        std::cout << "Input invalid, enter 1, 2, or 3 to proceed. Press q to quit.";
        returnInt = queryAction();

    }

    return returnInt;
}



void iterateToCompletion(vector<LoanObject> & loansVector) {

    int months = 0;
    double maxAmount = - std::numeric_limits<double>::infinity();
    double * maxAmountPointer  = &maxAmount;
    bool zeroReached = false;

    while(!zeroReached) {
        std::cout << "Month: " + std::to_string(months) + "\n";
        std::cout << "Name             |Rate In Percent  |Monthly Payment  |Current Balance  |\n";
        for(LoanObject & object: loansVector) {
            
            object.iterate();

            maxAmountPointer = & (double) std::max(object.getWorkingAmount(), maxAmount);
            std::cout << object.toString();
        }         
        
        ++months;
        if(*maxAmountPointer <= 0) {
            zeroReached = true;
        }
    }

    
}

double oneStep(vector<LoanObject> & loansVector, double & maxAmount) {
    double returnAmount;

    
    
    for(LoanObject & object: loansVector) {
        object.iterate();
       
        returnAmount = std::max(object.getWorkingAmount(), maxAmount);
        std::cout << object.toString();
    }

    return returnAmount;
    
}

void stepThroughIteration(vector<LoanObject> loansVector) {
    int months = 0;
    double maxAmount = - std::numeric_limits<double>::infinity();
    double * maxAmountPointer  = &maxAmount;

    bool endReached = false;
    
    
    std::cout << "Press enter to step through. Press another key at any time to quit. \n";

    while(!endReached) {
        //string input;

        //std::cin >> input;

        if(cin.get() == '\n') {
            std::cout << "Month: " + std::to_string(months) + "\n";
            std::cout << "Name             |Rate In Percent  |Monthly Payment  |Current Balance  |\n";
            ++months;
            double newMax = oneStep(loansVector, maxAmount);
            maxAmountPointer = & newMax;
        } else {
            endReached = true;
        }

        if(*maxAmountPointer <= 0) {
            endReached = true;
        }   
    }

}

void changePayments(vector<LoanObject> & loanVector) {
    std::cout << "Loan names: \n";
    for(LoanObject loan: loanVector) {
        std::cout << loan.getName() << endl;
    }
    
    std::cout << "Enter name of loan to change (case-sensitive)\n";
    string name;

    std::getline(std::cin, name);

    bool found = false;

    for(LoanObject & loan: loanVector) {
        if(loan.getName() == name) {
            found = true;

            std::cout << "Enter new payment amount\n";

            string newPaymentString;

            std::getline(std::cin, newPaymentString);

            double newPayment = atof(newPaymentString.c_str());

            loan.setMonthlyPayment(newPayment);
        }
    }

    if(!found) {
        std::cout << "No loan with that name found. Returning.";
    }

}

void reset(vector<LoanObject> & loansVector) {
     for(LoanObject & loan: loansVector) {
        loan.reset();
    }
}

void main() {
    
    
    std::cout << "Welcome to the loan repayment calculator!\n";
    
    bool afterFirst = false;
    vector<LoanObject> loansVector;
    set<string> nameSet;
    
    bool anotherLoan = true;

    while(anotherLoan) {
        string queryChoice = queryForLoan(afterFirst);


        if(queryChoice == "y") {
            
            LoanObject object = createLoan(nameSet);
            loansVector.push_back(object);
            

        } else if (queryChoice == "n") {
            anotherLoan = false;
        } else {
            std::cout << "Incorrect input. Please enter either 'y' or 'n'.\n";
           
        }

    }

    bool terminate = false;

    while(!terminate) {

        int queryResult = queryAction();

        if(queryResult == 1) {
            iterateToCompletion(loansVector);
            reset(loansVector);
        } else if(queryResult == 2){
            stepThroughIteration(loansVector);
            reset(loansVector);
        } else {
            changePayments(loansVector);
        }
    }

    

   
}


