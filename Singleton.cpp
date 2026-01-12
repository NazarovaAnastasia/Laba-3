#include <iostream>
#include <memory>
#include <mutex>

class Singleton {
private:
    static std::shared_ptr<Singleton> instance;
    static std::once_flag initFlag;

    Singleton() {
        std::cout << "Singleton created\n";
    }

public:
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;

    static std::shared_ptr<Singleton> getInstance() {
        std::call_once(initFlag, []() {
            instance = std::shared_ptr<Singleton>(new Singleton());
        });
        return instance;
    }

    void doSomething() const {
        std::cout << "Singleton is working\n";
    }
};

std::shared_ptr<Singleton> Singleton::instance = nullptr;
std::once_flag Singleton::initFlag;

int main() {
    auto s1 = Singleton::getInstance();
    auto s2 = Singleton::getInstance();
    s1->doSomething();
    std::cout << "Same instance: " << std::boolalpha << (s1 == s2) << "\n";
}
