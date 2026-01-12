#include <iostream>
#include <memory>
#include <string>

class Pizza {
    std::string dough;
    std::string sauce;
    std::string topping;

public:
    Pizza& setDough(std::string d) { dough = std::move(d); return *this; }
    Pizza& setSauce(std::string s) { sauce = std::move(s); return *this; }
    Pizza& setTopping(std::string t) { topping = std::move(t); return *this; }

    void show() const {
        std::cout << "Pizza with " << dough << " dough, "
                  << sauce << " sauce, and "
                  << topping << " topping.\n";
    }
};

class PizzaBuilder {
    std::shared_ptr<Pizza> pizza;
public:
    PizzaBuilder() : pizza(std::make_shared<Pizza>()) {}

    PizzaBuilder& buildDough(std::string d) {
        pizza->setDough(std::move(d));
        return *this;
    }
    PizzaBuilder& buildSauce(std::string s) {
        pizza->setSauce(std::move(s));
        return *this;
    }
    PizzaBuilder& buildTopping(std::string t) {
        pizza->setTopping(std::move(t));
        return *this;
    }

    std::shared_ptr<Pizza> getResult() const { return pizza; }
};

int main() {
    auto pizza = PizzaBuilder()
        .buildDough("thin")
        .buildSauce("tomato")
        .buildTopping("cheese + pepperoni")
        .getResult();

    pizza->show();
}
