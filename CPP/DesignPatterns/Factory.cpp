// DesignPatterns.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <map>
#include <memory>
#include <functional>

class operation
{
    virtual uint32_t result() = 0;
    virtual std::string name() = 0;
    virtual std::string symbol() = 0;
};

class add : public operation
{
    uint32_t num1, num2;
public:
    std::shared_ptr<operation> operator()(uint32_t n1, uint32_t n2) { return std::make_shared<add>(n1, n2); }
    add(uint32_t n1, uint32_t n2) :num1(n1), num2(n2) {}
    virtual uint32_t result() { return num1 + num2; }
    virtual std::string name() { return std::string("add"); }
    virtual std::string symbol() { return std::string("a"); }
};

class sqrt : public operation
{
    uint32_t num;
public:
    std::shared_ptr<operation> operator()(uint32_t n) { return std::make_shared<sqrt>(n); }
    sqrt(uint32_t n) :num(n) {}
    virtual uint32_t result() { return num * num; }
    virtual std::string name() { return std::string("sqrt"); }
    virtual std::string symbol() { return std::string("s"); }
};

class calculator
{
    std::function< std::shared_ptr<operation>()> creator;
    static std::map<std::string, std::pair<std::string, std::shared_ptr<operation>>> registry;

public:
    static void add(const std::string& symbol, const std::string& name, std::shared_ptr<operation> creator)
    {
        registry.insert({ symbol, {name, creator} });
    }

    void showOperations()
    {
        for (const auto& e : registry)
        {
            std::cout << "operation: " << e.second.first << ", symbol: " << e.first << std::endl;
        }
    }

    std::string selectOperation()
    {
        std::string selection;
        std::cout << "Enter Symbol: " << std::endl;
        std::cin >> selection;
        return selection;
    }

    void performOperation(const std::string& symbol)
    {
        auto result = registry.find(symbol);
        if (result == registry.end())
        {
            std::cout << "Operation not found." << std::endl;
            return;
        }

        //deliberately taking input here
        if (symbol == "a")
        {
            int a, b;
            std::cin >> a >> b;
            *(result->second.second)(a, b);
        }
        else if (symbol == "s")
        {

        }
    }
};

int main()
{
    calculator calc;
    calc.showOperations();
    std::string op = calc.selectOperation();
    calc.performOperation(op);
}
