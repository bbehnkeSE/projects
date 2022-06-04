// Singleton logger
// Brian Behnke
// 10/26/2021

#include <fstream>
#include <string>
#include <iostream>

class Logger 
{
public:
    static Logger& instance() 
    { 
        static Logger lgr;
        return lgr; 
    }
    void report(const std::string& s_report) { Logger::instance().oLog << s_report << std::endl; };
    void open_oLog() { oLog.open("log.txt", std::fstream::out | std::fstream::app); }
    static void close_oLog();

private:
    Logger();
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&);

private:
    std::ofstream oLog;
};

Logger::Logger() 
{
    atexit(close_oLog);
    open_oLog();
}

void Logger::close_oLog() 
{
    std::cout << "Closing...\n";
    Logger::instance().oLog.flush();
    Logger::instance().oLog.close();
}


void func1() { Logger::instance().report("Report from func1."); }
void func2() { Logger::instance().report("Report from func2."); }


int main() 
{   
    func1();
    func2();

    std::cout << "End of main().\n";
    return 0;
}