#include <iostream>
#include <string>
#include <Windows.h>
using namespace std;

class BankAccount 
{
private:
    int accountNumber;
    double balance;
    double interestRate;
public:
    BankAccount(int accauntNumber, double initialBalance) 
    {
        this->balance = initialBalance;
        this->interestRate = 0;
    }

    void deposit(double amount)
    {
        if (amount <= 0) 
        {
           cout << "Некорректная сумма внесения.";
        }
        balance += amount;
        cout << "Средства успешно внесены.\nОстаток на счете: " << balance << endl;
    }

    void withdraw(double amount)
    {
        if (amount <= 0) 
        {
            cout << "Некорректная сумма снятия.";
        }
        if (amount > balance) 
        {
            cout << "Некорректная сумма снятия.";
        }

        if (balance - amount < 0) 
        {
             cout << "Упс! Баланс не может быть отрицательным.";
        }
        else
        {
             balance -= amount;
             cout << "Средства успешно сняты.\nОстаток на счете: " << balance << endl;
        }
    }

    double getBalance() 
    {
        return balance;
    }

    double getInterest() 
    {
        return balance * interestRate / 100.0 * (1.0 / 12.0);
    }

    void setInterestRate(double Rate) 
    {
        interestRate = Rate;
    }

    double getInterestRate() 
    {
        return interestRate;
    }

    int getAccountNumber() 
    {
        return accountNumber;
    }
    friend bool transfer(BankAccount& from, BankAccount& to, double amount);
};


bool transfer(BankAccount& from, BankAccount& to, double amount) 
{
    if (amount <= 0) 
    {
        throw invalid_argument("Некоректная сумма перевода");
    }
    if (from.balance >= amount) 
    {
        from.balance -= amount;
        to.balance += amount;
        cout << "Операция прошла успешно!" << endl;
        return true;
    }
    else 
    {
        cout << "Увы! Не достаточно средств!" << endl;
        return false;
    }
}

int main()
{
    SetConsoleCP(1251);
    setlocale(LC_ALL, "Rus");

    BankAccount numberOne(1, 0);
    BankAccount numberTwo(2, 0);

    double amount;
    int choice;
    bool pobeda;

    do
    {
        cout << "====================================\n";
        cout << "===== Добро пожаловать в БАНК ======\n";
        cout << "В этом банке Вы можете:\n 1. Пополнить счет\n 2. Вывести средства\n 3. Изменить процентную ставку\n 4. Перевод средств\n 5. Узнать текущую процентную ставку\n 6. Выйти из программы\n";

        cout << "Выберете действие которое хотите произвести: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "Введите сумму которую хотите внести для пополнения: ";
            cin >> amount;
            numberOne.deposit(amount);
            break;
        case 2:
            cout << "Введите сумму для вывода средств: ";
            cin >> amount;
            numberOne.withdraw(amount);
            break;
        case 3:
            cout << "Введите новую процентную ставку: ";
            cin >> amount;
            numberOne.setInterestRate(amount);
            cout << "Процентная ставка обновлена!\n";
            break;
        case 4:
            cout << "Введите сумму для перевода средств: ";
            cin >> amount;
            pobeda = transfer(numberOne, numberTwo, amount);
            if (pobeda)
            {
                cout << "Баланс первого счета: " << numberOne.getBalance() << endl;
                cout << "Баланс второго счета: " << numberTwo.getBalance() << endl;
            }
            break;
        case 5:
            cout << "Процентная ставка: " << numberOne.getInterestRate() << "%" << endl;
            break;
        case 6:
            cout << "Пока-пока." << endl;
            return 0;
        default:
            cout << "Пожалуйста, выберите доступное действие." << endl;
        }
    } while (choice != 6);

    return 0;
}
