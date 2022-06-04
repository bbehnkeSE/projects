// traversing genealogical tree using Composite and Visitors
// Mikhail Nesterenko, Brian Behnke
// 12/1/2021

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using std::cout; using std::endl;
using std::string; 
using std::vector;


class Person    // component
{
public:
    Person(string firstName, Person *spouse, Person *father, Person *mother):
        firstName_(firstName), spouse_(spouse), father_(father), mother_(mother) {}

    const string&  getFirstName() { return firstName_; }
    Person        *getSpouse()    { return spouse_; }
    Person        *getFather()    { return father_; }
    virtual bool   traversed() = 0;

    void          setSpouse(Person *spouse) { spouse_=spouse; }
    virtual void  accept(class PersonVisitor *) = 0;
    virtual void  setTraversed(bool) = 0;
    virtual      ~Person() {}

private:
    const string firstName_;
    Person *spouse_;
    Person *father_;
    Person *mother_;
};


// leaf
// man has a last name 
class Man: public Person
{
public:
    Man(string lastName, string firstName, Person *spouse, 
        Person *father, Person *mother, bool traversed = false): 
            lastName_(lastName), Person(firstName, spouse, father, mother), traversed_(traversed) {}

    const string& getLastName()        { return lastName_; }
    bool          traversed() override { return traversed_; }

    void setTraversed  (bool t)                       override { traversed_ = t; }
    void accept        (class PersonVisitor *visitor) override;

private:
    const string lastName_;
    bool traversed_;
};


// composite
// woman has a list of children
class Woman: public Person
{
public: 
    Woman(vector<Person *> children, string firstName, Person *spouse, Person *father, Person *mother, bool traversed = false): 
        children_(children), Person(firstName, spouse, father, mother), traversed_(traversed) {}

    const vector<Person *>& getChildren() { return children_; }
    bool traversed() override { return traversed_; }

    void setTraversed(bool t) override { traversed_ = t; }
    void setChildren(const vector<Person *> &children) { children_ = children;}
    void accept(class PersonVisitor *visitor) override;

private:
    vector<Person*> children_;
    bool traversed_;
};


// abstract visitor
class PersonVisitor
{
public:
    virtual void visit(Man*) = 0;
    virtual void visit(Woman*) = 0;
    virtual ~PersonVisitor() {}
};


// composite methods that define traversal
void Man::accept(PersonVisitor *visitor) 
{
    if(!this->traversed())
    {
        visitor->visit(this);
        this->setTraversed(true);
    }
    if(this->getSpouse() != nullptr && !this->getSpouse()->traversed())
        this->getSpouse()->accept(visitor);
}


void Woman::accept(PersonVisitor *visitor)
{ 
    if(!this->traversed())
    {
        visitor->visit(this);
        this->setTraversed(true);
    }
    if(this->getSpouse() != nullptr && !this->getSpouse()->traversed())
        this->getSpouse()->accept(visitor);

    // traversing descendants
    for(auto child : children_)
        child->accept(visitor);
}


// concrete visitors
// the last name for a man is stored in object
// the last name for a woman is determined by her 
// spouse if she is married
// or by her father if she is not
class NamePrinter: public PersonVisitor
{
public:
    void visit(Man *m) override 
    {
        cout << m->getFirstName() << " " << m->getLastName() << endl;
    }
    void visit(Woman *w) override 
    {
        cout << w->getFirstName() << " ";
        if (w->getSpouse() != nullptr)
            cout << static_cast<Man *>(w->getSpouse())->getLastName();

        else if (w->getFather() != nullptr)
            cout << static_cast<Man *> (w->getFather())->getLastName();

        else
            cout << "Doe";

        cout << endl;
    }
};


class ChildrenPrinter: public PersonVisitor
{
public:
    void visit(Man *m) override 
    {
        Woman *spouse = static_cast<Woman *>(m->getSpouse());

        if(spouse != nullptr) 
        {
            std::cout << m->getFirstName() << " & " << spouse->getFirstName() << ": ";
            printNames(spouse->getChildren());
            cout << endl;
        }
    }
    void visit(Woman *w) override 
    {
        // cout << w->getFirstName() << ": ";
        // printNames(w->getChildren());
        // cout << endl;
    }

private:
    void printNames(const vector<Person *> &children)
    {
        for(const auto c: children)
            cout << c->getFirstName() << ", ";
    }
};


class MaidenName: public PersonVisitor
{
public:
    void visit(Man* m)   override {}
    void visit(Woman* w) override
    {
        std::cout << w->getFirstName() << ": ";
        if(w->getFather() != nullptr)
            std::cout << static_cast<Man*>(w->getFather())->getLastName();
        else
            std::cout << "Doe";

        std::cout << std::endl;
    }
};


class CheckRelation: public PersonVisitor
{
public:
    CheckRelation(std::string candidate1, std::string candidate2, Person* p1 = nullptr, Person* p2 = nullptr): 
        candidate1_(candidate1), candidate2_(candidate2), p1_(p1), p2_(p2) {}

    void visit(Man* m) override 
    {
        std::string name = m->getFirstName() + " " + m->getLastName();
        if(name == candidate1_)
            p1_ = m;
        if(name == candidate2_)
            p2_ = m;
    }
    void visit(Woman* w) override
    {
        std::string name = w->getFirstName();
        if(w->getSpouse() != nullptr)
            name += " " + static_cast<Man *>(w->getSpouse())->getLastName();
        else if(w->getFather() != nullptr)
            name += " " + static_cast<Man *>(w->getFather())->getLastName();
        else
            name += " Doe";

        if(name == candidate1_)
            p1_ = w;
        if(name == candidate2_)
            p2_ = w;
    }

    void printRelation()
    {
        // One or both candidates are not found in the tree
        if(p1_ == nullptr || p2_ == nullptr)
            std::cout << "They are just friends (one or both not found).\n";

        // Both candidates are the same person
        else if(p1_ == p2_)
            std::cout << "They are close relatives (same person)\n";

        // One is the other's parent
        else if(hasFather(p1_) && ((p2_ == p1_->getFather() || p2_ == p1_->getFather()->getSpouse())) ||
                hasFather(p2_) && ((p1_ == p2_->getFather() || p1_ == p2_->getFather()->getSpouse())))
            std::cout << "They are close relatives (parent/child)\n";

        // One is the other's sibling
        else if(searchSiblings(p1_, p2_) || searchSiblings(p2_, p1_))
            std::cout << "They are close relatives (siblings).\n";

        // Aunts/Uncles
        else if((hasFather(p1_) && (searchSiblings(p1_->getFather(), p2_) || searchSiblings(p1_->getFather()->getSpouse(), p2_)) ||
                (hasFather(p2_) && (searchSiblings(p2_->getFather(), p1_) || searchSiblings(p2_->getFather()->getSpouse(), p1_)))))
            std::cout << "They are close relatives (aunt/uncle).\n";

        else
            std::cout << "They are just friends.\n";
    }

private:
    bool hasFather(Person* p) { return p->getFather() != nullptr; }
    bool searchSiblings(Person* p1, Person* p2)
    {
        if(hasFather(p1))
        {
            std::vector<Person*> children = static_cast<Woman*>(p1->getFather()->getSpouse())->getChildren();
            auto result = std::find_if(children.begin(), children.end(), [&](Person* p) { return p2 == p; });
            return result != children.end();
        }
        return false;
    }

private:
    std::string candidate1_;
    std::string candidate2_;

    Person* p1_;
    Person* p2_;
};


// demonstrating the operation
int main()
{
    // setting up the genealogical tree      
    // the tree is as follows
    //    
    //
    //     James Smith     <--spouse--> Mary 
    //	                                  |
    //	                               children ------------------------
    //	                                  |             |              |
    //	                                  |             |              |
    //	   William Johnson <--spouse-> Patricia     Robert Smith     Linda
    //                                    |
    //	                               children-------------
    //	                                  |                |
    //                                    |                |
    //	    Jennifer  <--spouse-->  Michael Johnson     Barbara
    //	       |
    //	    children
    //	       |
    //         |
    //	     Susan


    std::vector<Person*> people;    // Vector used to reset traversed status of each person.

    // first generation
    Man *js = new Man("Smith", "James", nullptr, nullptr, nullptr);
    Woman *ms = new Woman({}, "Mary", nullptr, nullptr, nullptr);
    ms->setSpouse(js); js->setSpouse(ms);
    people.push_back(js); people.push_back(ms);

    // second generation
    Woman *ps = new Woman({}, "Patricia",  nullptr, js, ms);
    Man *wj = new Man("Johnson", "William", nullptr, nullptr, nullptr);
    ps->setSpouse(wj); wj->setSpouse(ps);
    people.push_back(wj); people.push_back(ps);

    vector<Person *> marysKids = { ps,
        new Man("Smith", "Robert", nullptr, js, ms),
        new Woman({}, "Linda", nullptr, js, ms) };
    ms->setChildren(marysKids);
    for(auto kid: marysKids) { people.push_back(kid); }

    // third generation
    Man *mj = new Man("Johnson", "Michael", nullptr, wj, ps);
    vector<Person *> patsKids = { mj, new Woman({}, "Barbara", nullptr, wj, ps) }; 
    ps->setChildren(patsKids);
    people.push_back(mj);
    for(auto kid: patsKids) { people.push_back(kid); }

    Woman *jj = new Woman({}, "Jennifer", nullptr, nullptr, nullptr);
    vector<Person *> jensKids = { new Woman({}, "Susan", nullptr, mj ,jj) };
    people.push_back(jj);
    for(auto kid: jensKids) { people.push_back(kid); }

    jj->setSpouse(mj); mj->setSpouse(jj);
    jj->setChildren(jensKids);

    // defining visitors
    ChildrenPrinter *cp = new ChildrenPrinter;
    NamePrinter     *np = new NamePrinter;
    MaidenName      *mn = new MaidenName;

    // executing the traversal with the composite
    // and the specific visitor

    cout << "\nNAME LIST\n";
    ms->accept(np);
    cout << endl;
    for(auto person: people) { person->setTraversed(false); }

    cout << "CHILDREN LIST\n";
    ms->accept(cp);
    for(auto person: people) { person->setTraversed(false); }

    // cout << "\nJAMES' CHILDREN\n";
    // js->accept(cp);

    std::cout << "\nMAIDEN NAMES\n";
    ms->accept(mn);
    for(auto person: people) { person->setTraversed(false); }

    // Checking relation
    std::cout << "\nEnter first candidate: ";
    std::string first, last, candidate1, candidate2; 
    std::cin >> first >> last;
    candidate1 = first + " " + last;

    std::cout << "Enter second candidate: ";
    std::cin >> first >> last;
    candidate2 = first + " " + last;
    CheckRelation *cr = new CheckRelation(candidate1, candidate2);

    std::cout << "\nRELATION\n";
    js->accept(cr);
    cr->printRelation();

    return 0;
}