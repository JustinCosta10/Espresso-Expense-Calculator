#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include "CoffeeTracking.hpp"

CoffeeTracking::CoffeeTracking() {}

void CoffeeTracking::ReadData() // reads all data from orderdata.csv and loads it into Orders, a list of all of the coffee order information
{
    std::ifstream orderDataRead;
    std::string tempLine;

    Orders.clear();

    orderDataRead.open("data/orderdata.csv", std::ios::in);

    if (!orderDataRead.is_open())
    {
        std::cout << "Error opening orderdata.csv. Coffee order data will not read or write. Exiting...\n";
        exit(1);
    }

    while (getline(orderDataRead, tempLine))
    {
        CoffeeOrder order;
        std::stringstream line(tempLine);
        std::getline(line, order.name, ',');
        std::getline(line, order.coffeeChoice, ',');
        std::getline(line, order.stringCostPerOrder, ',');
        order.orderCost = stof(order.stringCostPerOrder);
        std::getline(line, order.stringtotalMoneySpent, ',');
        order.totalMoneySpent = stof(order.stringtotalMoneySpent);
        std::getline(line, order.stringmoneySpentOnOthers, ',');
        order.moneySpentOnOthers = stof(order.stringmoneySpentOnOthers);
        Orders.push_back(order);
    }
}
void CoffeeTracking::WriteData() // writes data from Orders to orderdata.csv
{
    std::ofstream orderDataWrite;
    std::string tempLine;

    orderDataWrite.open("data/orderdata.csv", std::ios::out);

    if (!orderDataWrite.is_open())
    {
        std::cout << "Error opening orderdata.csv. Coffee order data will not read or write. Exiting...\n";
        exit(1);
    }
    for (int i = 0; i < Orders.size(); i++)
    {
        orderDataWrite << Orders[i].name << ","
                       << Orders[i].coffeeChoice << ","
                       << Orders[i].orderCost << ","
                       << Orders[i].totalMoneySpent << ","
                       << Orders[i].moneySpentOnOthers
                       << "\n";
    }
    Orders.clear();
}

void CoffeeTracking::EditCoffeeOrder() // Allows user to modify the name and price of any of the coffee orders.
{
    int userChoice;
    std::string newDrink;
    float newDrinkPrice;
    std::cout << "Choose a coffee order to edit by entering the corresponding number: ";

    std::cin >> userChoice;
    while (userChoice > Orders.size() || userChoice <= 0 || std::cin.fail())
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Please enter a valid option.\n";
        std::cout << "Select a numerical option: ";
        std::cin >> userChoice;
    }
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "Enter the name of the new drink for the order: ";
    std::getline(std::cin, newDrink);

    Orders[userChoice - 1].coffeeChoice = newDrink;

    std::cout << "Enter the price of the new drink (ex. 2.56): ";
    std::cin >> newDrinkPrice;
    while (std::cin.fail())
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Please enter a number for the price.";
        std::cout << "Enter the price of the new drink (ex. 2.56): ";
        std::cin >> newDrinkPrice;
    }
    Orders[userChoice - 1].orderCost = newDrinkPrice;
    WriteData();
}
void CoffeeTracking::DisplayOrders() // shows all current orders, what each person has paid and how much they have paid for other people.
{

    std::cout << std::left << std::setw(23) << "   Name"
              << "   "
              << std::setw(20) << "Coffee Order"
              << "   "
              << std::setw(14) << "Price"
              << "  "
              << std::setw(20) << "Spending"
              << std::setw(20) << "Paid For Others"
              << "\n\n";
    for (int i = 0; i < 7; i++)
    {
        std::cout << std::left << i + 1 << ". " << std::setw(20) << Orders[i].name << "   "
                  << std::setw(20) << Orders[i].coffeeChoice << "   $"
                  << std::setw(11) << std::fixed << std::setprecision(2) << Orders[i].orderCost << " "
                  << std::setw(5) << "   $" << std::setprecision(2) << Orders[i].totalMoneySpent << " "
                  << std::setw(13) << std::fixed << std::setprecision(2) << std::setw(2) << "             $"  << Orders[i].moneySpentOnOthers
                  << std::endl;
    }
}
void CoffeeTracking::OrderCoffee() // orders coffee, updates the value for spending and sorts by lowest spent on others.
{
    float totalOrderCost = 0;

    float groupMoneySpent = 0;

    ReadData();

    for (int i = 0; i < Orders.size(); i++)
    {
        totalOrderCost = totalOrderCost + Orders[i].orderCost;
    }

    SortingVector = Orders;

    for (int i = 0; i < Orders.size(); i++)
    {
        groupMoneySpent = groupMoneySpent + Orders[i].totalMoneySpent;
    }
    if (groupMoneySpent == 0)
    {
        std::cout << "\nNobody has bought any coffee yet! Most expensive order buys first.\n";

        for (int i = 0; i < SortingVector.size() - 1; ++i)
        {
            for (int j = 0; j < SortingVector.size() - i - 1; ++j)
            {
                if (SortingVector[j].orderCost < SortingVector[j + 1].orderCost) // Change the comparison logic
                {
                    std::swap(SortingVector[j], SortingVector[j + 1]);
                }
            }
        }
        std::cout << SortingVector[0].name << " buys the first order!";
        std::cout << " It costs $" << totalOrderCost << ".\n";

        SortingVector[0].totalMoneySpent = totalOrderCost;
        SortingVector[0].moneySpentOnOthers =  SortingVector[0].moneySpentOnOthers + (totalOrderCost - SortingVector[0].orderCost);

        for (int i = 0; i < SortingVector.size() - 1; ++i)
        {
            for (int j = 0; j < SortingVector.size() - i - 1; ++j)
            {
                if (SortingVector[j].moneySpentOnOthers > SortingVector[j + 1].moneySpentOnOthers)
                {
                    std::swap(SortingVector[j], SortingVector[j + 1]);
                }
            }
        }
        Orders = SortingVector;

        WriteData();
    }
    else
    {
        SortingVector = Orders;
        for (int i = 0; i < SortingVector.size() - 1; ++i)
        {
            for (int j = 0; j < SortingVector.size() - i - 1; ++j)
            {
                if (SortingVector[j].moneySpentOnOthers > SortingVector[j + 1].moneySpentOnOthers)
                {
                    std::swap(SortingVector[j], SortingVector[j + 1]);
                }
            }
        }
        std::cout << "\n" << SortingVector[0].name << " buys today!\n";
        std::cout << "It costs $" << totalOrderCost << ".\n";

        SortingVector[0].totalMoneySpent = SortingVector[0].totalMoneySpent + totalOrderCost;
        SortingVector[0].moneySpentOnOthers =  SortingVector[0].moneySpentOnOthers + (totalOrderCost - SortingVector[0].orderCost);
        for (int i = 0; i < SortingVector.size() - 1; ++i)
        {
            for (int j = 0; j < SortingVector.size() - i - 1; ++j)
            {
                if (SortingVector[j].moneySpentOnOthers > SortingVector[j + 1].moneySpentOnOthers)
                {
                    std::swap(SortingVector[j], SortingVector[j + 1]);
                }
            }
        }
        Orders = SortingVector;

        WriteData();
    }
}
