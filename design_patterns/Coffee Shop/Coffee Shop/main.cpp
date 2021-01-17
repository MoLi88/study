//
//  main.cpp
//  Coffee Shop
//
//  Created by Mo Li on 1/16/21.
//

#include <iostream>

class Beverage {
public:
    std::string description = "Unknown Beverage ";
    virtual std::string getDescription() {
        return description;
    }
    virtual double cost() = 0;
};

class CondimentDecorator : public Beverage {
public:
    virtual std::string getDescription() = 0;
};

class Espresso : public Beverage {
public:
    Espresso() {
        description = "Espresso ";
    }
    double cost() {
        return 1.99;
    }
};

class HouseBlend : public Beverage {
public:
    HouseBlend() {
        description = "House Blend Coffee ";
    }
    double cost() {
        return 0.89;
    }
};

class DarkRoast : public Beverage {
public:
    DarkRoast() {
        description = "Dark Roast Coffee ";
    }
    double cost() {
        return 0.99;
    }
};

class Mocha : public CondimentDecorator {
    Beverage* beverage;
public:
    Mocha(Beverage* beverage) {
        this->beverage = beverage;
    }
    std::string getDescription() {
        return beverage->getDescription() + ", Mocha ";
    }
    double cost() {
        return 0.2 + beverage->cost();
    }
};

class Whip : public CondimentDecorator {
    Beverage* beverage;
public:
    Whip(Beverage* beverage) {
        this->beverage = beverage;
    }
    std::string getDescription() {
        return beverage->getDescription() + ", Whip ";
    }
    double cost() {
        return 0.1 + beverage->cost();
    }
};

class Soy : public CondimentDecorator {
    Beverage* beverage;
public:
    Soy(Beverage* beverage) {
        this->beverage = beverage;
    }
    std::string getDescription() {
        return beverage->getDescription() + ", Soy ";
    }
    double cost() {
        return 0.15 + beverage->cost();
    }
};

int main(int argc, const char * argv[]) {
    Beverage* beverage = new Espresso();
    std::cout << beverage->getDescription() << "$" << beverage->cost() << std::endl;
    
    Beverage* beverage2 = new DarkRoast();
    beverage2 = new Mocha(beverage2);
    beverage2 = new Mocha(beverage2);
    beverage2 = new Whip(beverage2);
    std::cout << beverage2->getDescription() << "$" << beverage2->cost() << std::endl;
    
    Beverage* beverage3 = new HouseBlend();
    beverage3 = new Soy(beverage3);
    beverage3 = new Mocha(beverage3);
    beverage3 = new Whip(beverage3);
    std::cout << beverage3->getDescription() << "$" << beverage3->cost() << std::endl;
    
    return 0;
}
