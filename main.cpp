#include <iostream>
#include "include/Bank.h"
#include "include/SavingsAccount.h"
#include "include/CheckingAccount.h"
#include "include/BusinessAccount.h"
#include <iomanip>


int main() {
    Bank bank;

    int numCustomers;
    std::cout << "Введите количество клиентов: ";
    std::cin >> numCustomers;

    for (int i = 0; i < numCustomers; ++i) {
        std::string name, id;
        std::cout << "Введите имя клиента #" << (i + 1) << ": ";
        std::cin >> name;

        do {
            std::cout << "Введите ID клиента #" << (i + 1) << " (ровно 9 чисел): ";
            std::cin >> id;
            if (!isValidId(id)) {
                std::cout << "Ошибка: ID должен состоять ровно из 9 цифр!" << std::endl;
            }
        } while (!isValidId(id));

        bank.AddCustomer(name, id);
    }

    int numAccounts;
    std::cout << "Введите количество аккаунтов: ";
    std::cin >> numAccounts;

    for (int i = 0; i < numAccounts; ++i) {
        double initialBalance;
        int accountType;

        std::cout << "Введите начальный баланс для аккаунта #" << (i + 1) << ": ";
        std::cin >> initialBalance;

        while (true) {
            std::cout << "Введите тип аккаунта (1-Сберегательный, 2-Расчетный, 3-Бизнес): ";
            std::cin >> accountType;

            if (accountType >= 1 && accountType <= 3) {
                break;
            }
            else {
                std::cout << "Такого варианта нет, попробуйте заново." << std::endl;
            }
        }

        if (accountType == 1) {
            double interestRate;
            std::cout << "Введите процентную ставку: ";
            std::cin >> interestRate;
            bank.AddAccount(std::make_shared<SavingsAccount>(initialBalance, interestRate));
        }
        else if (accountType == 2) {
            double overdraftLimit;
            std::cout << "Введите лимит овердрафта (максимальная сумма, на которую можно уходить в минус.): ";
            std::cin >> overdraftLimit;
            bank.AddAccount(std::make_shared<CheckingAccount>(initialBalance, overdraftLimit));
        }
        else if (accountType == 3) {
            bank.AddAccount(std::make_shared<BusinessAccount>(initialBalance));
        }

        std::cout << "Аккаунт #" << (i + 1) << " создан с балансом: " << std::fixed << std::setprecision(2) << initialBalance
            << " и типом: " << accountType << std::endl;
    }


    bank.ShowCustomers();
    bank.ShowAccounts();

    bank.DeleteCustomer(0);
    bank.DeleteAccount(0);


    bank.ShowAccounts();

    std::cout << "------------------------------------------------" << std::endl;
    std::cout << "Всего средств в банке: " << std::fixed << std::setprecision(2) << bank.CalculateTotalAssets() << std::endl;
    std::cout << "------------------------------------------------" << std::endl;
    bank.SortAccountsByBalance();


    bank.ShowAccounts();

    bank.ShowAccountInfo(0);
    bank.DepositToAccount(0, 1000);
    bank.WithdrawFromAccount(0, 500);
    bank.ApplyInterestToSavings();
    bank.UpdateOverdraftLimit(1, 500);
    bank.Transfer(0, 1, 200);


    bank.ShowAccounts();
    return 0;
}
