// Dipen Thapa

#include <iostream>
#include <string>
#include <fstream>
using std ::cin;
using std::cout;
using std::endl;
using std::ofstream;
using std ::string;

class Logger
{
public:
    static Logger &instance()
    {
        static Logger log;
        return log;
    }

    void report(const string &);

private:
    Logger();
    ofstream fout;

    ~Logger()
    {
        fout.close();
    }
    Logger(const Logger &) {}
    Logger &operator=(const Logger &) { return *this; }
    // Logger(const Logger &) = delete;
};

Logger::Logger()
{
    fout.open("log.txt", std::fstream::out);
}

void Logger::report(const string &text)

{
    fout << text << endl;
}

void funcOne()
{
    Logger::instance().report("Hi I am Dipen");
}

void funcTwo()
{
    Logger::instance().report("I am studying CS III");
}

int main()
{
    funcOne();
    funcTwo();
    Logger::instance().report("Dipen says Hi in main");
    Logger::instance().report("Test 123");
}