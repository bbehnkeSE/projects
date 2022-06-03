// implements command history 
// (multiple undos)
// demonstrates command pattern
// Mikhail Nesterenko, Brian Behnke
// 12/1/2021

#include <iostream>
#include <vector>
#include <string>
#include <stack>

using std::vector; using std::string;
using std::cout; using std::cin; using std::endl;


// receiver
class Document 
{
public:
    Document(const vector <string> & lines={}): lines_(lines) {}

    // actions
    void insert(int line, const string &str) 
    {
        const int index = line-1;
        if (index <= lines_.size())
            lines_.insert(lines_.begin() + index, str); 
        else
            cout << "line out of range" << endl; 
    }

    string remove(int line) 
    {
        const int index = line-1;
        string deletedLine="";
        if(index < lines_.size())
        {
            deletedLine = lines_[index];
            lines_.erase(lines_.begin() + index); 
        }
        else
            cout << "line out of range" << endl; 

        return deletedLine;
    } 

    void show() 
    {
        for(int i = 0; i < lines_.size(); ++i)
            cout << i + 1 << ". " << lines_[i] << endl; 
    }

private:
    vector<string> lines_; 
};


// abstract command
class Command
{
public:
    Command(Document *doc, std::string com = "") : doc_(doc), com_(com) {}

    virtual void execute()   = 0; 
    virtual void unexecute() = 0; 
    virtual     ~Command() {}

    virtual std::string show() = 0;

protected:
    Document *doc_;
    std::string com_;
}; 


// two concrete commands
class InsertCommand : public Command 
{
public:
    InsertCommand(Document *doc, int line, const string &str): 
        Command(doc, "insert"), line_(line),  str_(str) {}

    void        execute()   override { doc_->insert(line_, str_); }
    void        unexecute() override { doc_->remove(line_); }
    std::string show()      override
    {
        std::string result = com_ + " \"" + str_ + "\" at line " + std::to_string(line_);
        return result;
    }

private:
    int line_; 
    string str_; 
}; 


class EraseCommand : public Command 
{
public:
    EraseCommand(Document *doc, int line): 
        Command(doc, "erase"), line_(line), str_("") {}

    void        execute()   override { str_ = doc_->remove(line_); }
    void        unexecute() override { doc_-> insert(line_, str_); }
    std::string show()      override
    {
        std::string result = com_ + " line " + std::to_string(line_);
        return result;
    }

private:
    int line_;
    string str_;
};


// client
class DocumentWithHistory
{
public:
    DocumentWithHistory(const vector<string> & text = {}) : doc_(text) {}

    void insert(int line, string str) 
    {
        Command *com = new InsertCommand(&doc_, line, str); 
        com->execute(); 
        doneCommands_.push(com); 
    }

    void erase(int line)
    {
        Command *com = new EraseCommand(&doc_, line);
        com->execute();
        doneCommands_.push(com);
    }

    void undo() 
    {
        if(doneCommands_.size() != 0) 
        {
            Command *com = doneCommands_.top(); 
            doneCommands_.pop(); 
            com->unexecute();
            delete com; // don't forget to delete command
        }
        else
            cout << "no commands to undo" << endl; 
    }

    class Memento* createMemento() const;

    void history();
    void rollBack(class Memento*);
    void show() { doc_.show(); }
    void redo(const int&);

private:
    Document doc_;
    std::stack<Command*> doneCommands_;
};


class Memento
{
public:
    Memento(const DocumentWithHistory& doc): doc_(doc) {}
    const DocumentWithHistory& getState() const { return doc_; }

private:
    const DocumentWithHistory doc_;
};



Memento* DocumentWithHistory::createMemento() const
{
    return new Memento(*this);
}


void DocumentWithHistory::history()
{
    if(!doneCommands_.empty())
    {
        std::stack<Command*> tmp = doneCommands_;
        int size = tmp.size();
        for(int i = 0; i < size; ++i)
        {
            std::cout << i + 1 << ". " << tmp.top()->show() << std::endl;
            tmp.pop();
        }
    }
    else
        std::cout << "\nNo previous commands." << std::endl;
}


void DocumentWithHistory::redo(const int& num)
{
    if(!doneCommands_.empty())
    {
        std::stack<Command*> tmp = doneCommands_;
        for(int i = 1; i < num; ++i)
        {
            tmp.pop();
        }
        tmp.top()->execute();
        doneCommands_.push(tmp.top());
    }
    else
        std::cout << "\nNo commands to redo.\n" << std::endl;
}


void DocumentWithHistory::rollBack(Memento* m)
{
    *this = m->getState();
}


// invoker
int main() 
{
    DocumentWithHistory his({
        "Lorem Ipsum is simply dummy text of the printing and typesetting",
        "industry. Lorem Ipsum has been the industry's standard dummy text",
        "ever since the 1500s, when an unknown printer took a galley of",
        "type and scrambled it to make a type specimen book. It has",
        "survived five centuries."
    }); 

    Memento* checkpoint = nullptr;
    char option;
    do
    {
        his.show(); 
        cout << endl;

        cout << "Enter option "
             << "(i)nsert line, "
             << "(e)rase line, "
             << "(u)ndo last command, "
             << "(c)heckpoint, "
             << "roll(b)ack, "
             << "(h)istory, "
             << "(r)edo: ";
        cin >> option; 

        int line, cmd; string str; 
        switch(option)
        {
            case 'i':
                cout << "line number to insert: "; 
                cin >> line; 
                cout << "line to insert: "; 
                cin.get();  // removes end-of-line character so getline() works correctly
                getline(cin, str); 
                his.insert(line, str); 
                break;

            case 'e':
                cout << "line number to remove: ";
                cin >> line;
                his.erase(line);
                break;

            case 'u':
                his.undo(); 
                break;
            
            case 'c':
                checkpoint = his.createMemento();
                break;
            
            case 'b':
                if(checkpoint != nullptr)
                {
                    his.rollBack(checkpoint);
                    delete checkpoint;
                    checkpoint = nullptr;
                }
                break;

            case 'h':
                std::cout << "\nCommand history:\n\n";
                his.history();
                std::cout << std::endl;
                break;

            case 'r':
                std::cout << "Command number to redo: ";
                std::cin >> cmd;
                his.redo(cmd);
                break;
        }

    } while(option == 'i' || 
            option == 'e' || 
            option == 'u' || 
            option == 'c' || 
            option == 'b' ||
            option == 'h' ||
            option == 'r');

    return 0;
}