#include <iostream>
#include <memory>

struct Button {
    virtual void paint() const = 0;
    virtual ~Button() = default;
};

struct Checkbox {
    virtual void paint() const = 0;
    virtual ~Checkbox() = default;
};

struct WindowsButton : Button {
    void paint() const override { std::cout << "Windows Button\n"; }
};
struct WindowsCheckbox : Checkbox {
    void paint() const override { std::cout << "Windows Checkbox\n"; }
};

struct MacButton : Button {
    void paint() const override { std::cout << "Mac Button\n"; }
};
struct MacCheckbox : Checkbox {
    void paint() const override { std::cout << "Mac Checkbox\n"; }
};

struct GUIFactory {
    virtual std::shared_ptr<Button> createButton() const = 0;
    virtual std::shared_ptr<Checkbox> createCheckbox() const = 0;
    virtual ~GUIFactory() = default;
};

struct WindowsFactory : GUIFactory {
    std::shared_ptr<Button> createButton() const override { return std::make_shared<WindowsButton>(); }
    std::shared_ptr<Checkbox> createCheckbox() const override { return std::make_shared<WindowsCheckbox>(); }
};

struct MacFactory : GUIFactory {
    std::shared_ptr<Button> createButton() const override { return std::make_shared<MacButton>(); }
    std::shared_ptr<Checkbox> createCheckbox() const override { return std::make_shared<MacCheckbox>(); }
};

constexpr bool useMac = true;

class Application {
    std::shared_ptr<Button> button;
    std::shared_ptr<Checkbox> checkbox;

public:
    Application(std::shared_ptr<GUIFactory> factory) {
        button = factory->createButton();
        checkbox = factory->createCheckbox();
    }

    void paint() const {
        button->paint();
        checkbox->paint();
    }
};

int main() {
    std::shared_ptr<GUIFactory> factory;
    if constexpr (useMac)
        factory = std::make_shared<MacFactory>();
    else
        factory = std::make_shared<WindowsFactory>();

    Application app(factory);
    app.paint();
}
