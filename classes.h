#include <iostream>
using namespace std;   
//account classes
class account{
    private:
        string accountName;
        int accountNumber; 
        int amountOfMoney;
    public:
    //setter
    void setAccountName(string inputAccountName){
        accountName = inputAccountName;
    }
    void setAccountNumber(int inputAccountNumber){
        accountNumber = inputAccountNumber;
    }
    void setAmountOfMoney(int inputAmountOfMoney){
        amountOfMoney = inputAmountOfMoney;
    }
    //getter
    string getAccountName(){
        return accountName;
    }
    int getAccountNumber(){
        return accountNumber;
    }
    int getAmountOfMoney(){
        return amountOfMoney;
    }
};
class deposit : private account{
    private:
        int depositAmount;
    public:
        //setter
        void setDepositAmount(int inputDepositAmount){
            depositAmount = inputDepositAmount; 
        }
        //updates amount of money
        void performDeposit() {
        setAmountOfMoney(getAmountOfMoney() + depositAmount);
        }
};
class withdraw : public account{
    private:
        int withdrawAmount;
    public:
        //setter
        void setWithdrawAmount(int inputWithdrawAmount){
            withdrawAmount = inputWithdrawAmount;
        }
        //updates amount of money
        void performWithdraw() {
            setAmountOfMoney(getAmountOfMoney() - withdrawAmount);
        }
};
