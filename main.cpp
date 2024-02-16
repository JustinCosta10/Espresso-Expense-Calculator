#include <iostream>
#include "CoffeeTracking.hpp"
#include <fstream>

/*
//ESPRESSO EXPENSE CALCULATOR//

Welcome to the Espresso Expense Calculator, a handy tool designed to simplify the management of coffee orders and expenses within groups or teams. 
Whether you're organizing office coffee runs or tracking coffee expenses among friends, this application streamlines the process for you.

The algorithm dynamically tracks participants' spending on other people's coffee orders and selects the individual who has spent the least on others as the next coffee buyer.


Getting Started

The build process is nothing out of the ordinary for a C++ application:

Clone the Repository: Clone the repository to your local machine using the following command:

git clone https://github.com/JustinCosta10/Espresso-Expense-Calculator

Build the Application: Build the application using your preferred C++ compiler. For example, using clang:

clang++ main.cpp -std=c++17 CoffeeTracking.cpp -o EspressoExpense

Run the Program: Execute the compiled binary to launch the Espresso Expense Calculator:

./EspressoExpense

*/


int MainMenuChoice();

int main()
{
    bool programActive = true; //used to exit program safely.
    CoffeeTracking coffeeTime; //creates object of the class CoffeeTracking that allows reading,writing and sorting of the coffee orders.

    do
    {
        std::cout << "\n\nESPRESSO EXPENSE CALCULATOR\n\n";
        coffeeTime.ReadData();
        coffeeTime.DisplayOrders();
        switch (MainMenuChoice())
        {
        case 'a':
            coffeeTime.EditCoffeeOrder(); // Allows user to edit the order, coffee name and price. Writes to orderdata.csv

            break;
        case 'b':
            coffeeTime.OrderCoffee(); //Orders coffee and keeps track of who has spent what. Sorts by amount spent on the other people's orders.
            break;
        case 'c':
            std::cout << "Exiting...\n\n"; // exits program
            programActive = false;
            break;
        }
        coffeeTime.Orders.clear();
    } while (programActive);
} // end main

int MainMenuChoice() // displays initial menu options and validates user input of a valid character.
{
    char userMenuChoice;
    const int MENU_OPTIONS = 4;

    std::cout << "\n\na. Edit a Coffee Order\n";
    std::cout << "b. Order Coffee\n";
    std::cout << "c. Exit\n\n";

    std::cout << "Select a letter option (a, b, or c): ";

    std::cin >> userMenuChoice;

    while (userMenuChoice < 'a' || userMenuChoice > 'c' || std::cin.fail())
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Please enter a valid option.\n";
        std::cout << "Select a letter option (a, b, or c): ";
        std::cin >> userMenuChoice;
    }
    return userMenuChoice;
}