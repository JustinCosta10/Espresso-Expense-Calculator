#pragma "CoffeeTracking.cpp"

class CoffeeTracking
{
    public:
    struct CoffeeOrder
    {
        std::string name;
        std::string coffeeChoice;
        float orderCost;
        float totalMoneySpent;
        float moneySpentOnOthers;
 

        std::string stringCostPerOrder;
        std::string stringtotalMoneySpent;
        std::string stringmoneySpentOnOthers;

    };
    std::vector<CoffeeOrder> Orders;
    std::vector<CoffeeOrder> SortingVector;
    CoffeeTracking();
    void ReadData();
    void WriteData();
    void EditCoffeeOrder();
    void DisplayOrders();
    void OrderCoffee();
};


// name, coffee choice, order cost, totalmoneyspent,moneyspentonothers, isBuyer