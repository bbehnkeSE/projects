// Three state process model using State and Prototype design patters
// Brian Behnke
// 11/8/2021

#ifndef PROCESS_HPP_
#define PROCESS_HPP_

#include <iostream>
#include <string>

class State;

class Process
{
public:
    Process(int);

    void interrupt();
    void schedulerDispatch();
    void eventCompletion();
    void eventWait();
    void exit();
    void print() { std::cout << report(); }

    Process* clone() { return new Process(++id_); }

    std::string report();

    void changeState(State* state) { state_ = state; }
private:
    State* state_;
    int id_ = 0;
};
//int Process::id_ = 0;


class State 
{
public:
    virtual void interrupt(Process*) {}
    virtual void schedulerDispatch(Process*) {}
    virtual void eventCompletion(Process*) {}
    virtual void eventWait(Process*) {}
    virtual void exit(Process*) {}

    virtual std::string report() = 0;

    void changeState(Process* p, State* s) { p -> changeState(s); }
};


class Ready: public State
{
public:
    static State* instance()
    {
        static State* s = new Ready;
        return s;
    }
    void schedulerDispatch(Process*) override;

    std::string report() override { return "ready"; }

private:
    Ready() {}
    Ready(const Ready&) = delete;
    Ready& operator=(const Ready&);
};


class Running: public State
{
public:
    static State* instance()
    {    
        static State* s = new Running;
        return s;
    }
    void eventWait(Process*) override;
    void interrupt(Process*) override;
    void exit     (Process*) override;

    std::string report() override { return "running"; }

private:
    Running() {}
    Running(const Running&) = delete;
    Running& operator=(const Running&);
};


class Waiting: public State
{
public:
    static State* instance()
    {
        static State* s = new Waiting;
        return s;
    }
    void eventCompletion(Process* p) override { changeState(p, Ready::instance()); }

    std::string report() override { return "waiting"; }

private:
    Waiting() {}
    Waiting(const Waiting&) = delete;
    Waiting& operator=(const Waiting&);
};


class Terminated: public State
{
public:
    static State* instance()
    {
        static State* s = new Terminated;
        return s;
    }
    std::string report() override { return "terminated"; }

private:
    Terminated() {}
    Terminated(const Terminated&) = delete;
    Terminated& operator=(const Terminated&);
};


// Process
// Admit new process
Process::Process(int id) 
{
    state_ = Ready::instance();
    id_ = id; 
}

// Behaviors
void Process::interrupt()         { state_->interrupt(this); }
void Process::schedulerDispatch() { state_->schedulerDispatch(this); }
void Process::eventCompletion()   { state_->eventCompletion(this); }
void Process::eventWait()         { state_->eventWait(this); }
void Process::exit()              { state_->exit(this); }
std::string Process::report()     
{
    return "process " + std::to_string(id_) + " is " + state_->report() + "\n";
}

// Ready
void Ready::schedulerDispatch(Process* p) { changeState(p, Running::instance()); }

// Running
void Running::eventWait(Process* p) { changeState(p, Waiting::instance()); }
void Running::interrupt(Process* p) { changeState(p, Ready::instance()); }
void Running::exit     (Process* p) { changeState(p, Terminated::instance()); }


#endif  // PROCESS_HPP_