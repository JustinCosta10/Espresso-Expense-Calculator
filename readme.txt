//ESPRESSO EXPENSE CALCULATOR//

Welcome to the Espresso Expense Calculator, a handy tool designed to simplify the management of coffee orders and expenses within groups or teams. 
Whether you're organizing office coffee runs or tracking coffee expenses among friends, this application streamlines the process for you.
The algorithm dynamically tracks participants' spending on other people's coffee orders and selects the individual who has spent the least on others as the next coffee buyer.
Coffee orders prices and spending are saved so the program can be used repeatedly while retaining all information.


Data is saved in /data in the file orderdata.csv. The program reads and writes from this file to store the coffee orders and spending.
If needed, data can be directly modified in data/orderdata.csv. Also, to reset the programs data replace the data in orderdata.csv with the data in orderdata_original.csv.
However the program is able to modify the .csv drinks and prices within itself.

The program can run with more or less people by modifying orderdata.csv, but adding people after orders have been placed will not work as intended.


The assumptions made while creating the program are as follows: 
It is ran with 7 employees that do not change. Removing an employee from the sorting or adding a new one would unbalance the entire system.
There is not a specific ending point of the coffee tab and it continues infinitely.

Getting Started

The build process is nothing out of the ordinary for a C++ application:

Clone the Repository: Clone the repository to your local machine using the following command:

git clone https://github.com/JustinCosta10/Espresso-Expense-Calculator

Build the Application: Build the application using your preferred C++ compiler. For example, using clang:

clang++ main.cpp -std=c++17 CoffeeTracking.cpp -o EspressoExpense

Run the Program: Execute the compiled binary to launch the Espresso Expense Calculator:

./EspressoExpense