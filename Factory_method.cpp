#include <iostream>
#include <memory>
#include <string>

struct Logger {
    virtual void log(const std::string& msg) const = 0;
    virtual ~Logger() = default;
};

struct ConsoleLogger : public Logger {
    void log(const std::string& msg) const override {
        std::cout << "[Console] " << msg << '\n';
    }
};

struct FileLogger : public Logger {
    void log(const std::string& msg) const override {
        std::cout << "[File] " << msg << '\n';
    }
};

class LoggerFactory {
public:
    virtual std::shared_ptr<Logger> createLogger() const = 0;
    virtual ~LoggerFactory() = default;
};

class ConsoleLoggerFactory : public LoggerFactory {
public:
    std::shared_ptr<Logger> createLogger() const override {
        return std::make_shared<ConsoleLogger>();
    }
};

class FileLoggerFactory : public LoggerFactory {
public:
    std::shared_ptr<Logger> createLogger() const override {
        return std::make_shared<FileLogger>();
    }
};

constexpr bool useFileLogger = false;

int main() {
    std::shared_ptr<LoggerFactory> factory;

    if constexpr (useFileLogger)
        factory = std::make_shared<FileLoggerFactory>();
    else
        factory = std::make_shared<ConsoleLoggerFactory>();

    auto logger = factory->createLogger();
    logger->log("Factory Method with constexpr choice!");
}
