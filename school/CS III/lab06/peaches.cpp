// jamming peaches
// non STL-algorithm code to be replaced by algorthms
// Mikhail Nesterenko, Brian Behnke
// 10/10/2021


#include <numeric>
#include <functional>
#include <algorithm>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <deque>


struct Peaches {
    double weight; // oz
    bool ripe;  // ripe or not
    void print() const { std::cout << (ripe?"ripe":"green") << ", " <<  weight << std::endl; }
};


class Jammers {
public:
    Jammers() { mWeight_ = 0; sum_ = 0; }
    double operator() (double x, Peaches peach, double mWeight) {
        mWeight_ = mWeight;
        if(peach.weight < mWeight_) {
            sum_ += peach.weight;
            return sum_;
        }
        return 0;
    }
private:
    double mWeight_, sum_;
};


int main() {
    srand(time(nullptr));
    const double minWeight = 8.;
    const double maxWeight = 3.;

    std::cout << "Input basket size: ";
    int size;
    std::cin >> size;

    std::vector <Peaches> basket(size);

    
    //DONE
    // assign random weight and ripeness peaches in the basket
    // replace with generate()
    std::generate(basket.begin(), basket.end(), [&](){
        Peaches peach;
        peach.weight = minWeight + static_cast<double>(rand())/RAND_MAX*(maxWeight - minWeight);
        peach.ripe   = rand() % 2;
        return peach;
    });


    //DONE
    // for_each() possibly
    std::cout << "All peaches:\n";
    std::for_each(basket.begin(), basket.end(), [](Peaches peach){ peach.print(); });
    std::cout << std::endl;


    //DONE?
    // moving all the ripe peaches from basket to peck
    // remove_copy_if() with back_inserter()/front_inserter() or equivalents
    std::deque<Peaches> peck;
    std::remove_copy_if(basket.begin(), basket.end(), std::back_inserter(peck), [](Peaches peach){ return !peach.ripe; });
    basket.erase(std::remove_if(basket.begin(), basket.end(), [](Peaches peach){ return peach.ripe; }), basket.end());


    //DONE
    // for_each() possibly
    std::cout << "peaches remaining in the basket"<< std::endl;
    std::for_each(basket.begin(), basket.end(), [](Peaches peach){ peach.print(); });
    std::cout << std::endl;


    //DONE
    // for_each() possibly
    std::cout << "peaches moved to the peck"<< std::endl;
    std::for_each(peck.begin(), peck.end(), [](Peaches peach){ peach.print(); });


    // prints every "space" peach in the peck
    // 
    const int space = 3; 
    std::cout << "\nevery " << space << "\'d peach in the peck"<< std::endl;


    //DONE
    // replace with advance()/next()/distance()
    // no iterator arithmetic
    auto it = std::next(peck.begin(), space - 1);
    it->print();
    while(std::distance(it, peck.end()) > space) {
        std::advance(it, space);
        it->print();
    }

    // 
    // putting all small ripe peaches in a jam
    // use a binder to create a functor with configurable max weight
    // accumulate() or count_if() then remove_if()
    const double weightToJam = 10;
    Jammers jammer;
    double jamWeight = std::accumulate(peck.begin(), peck.end(), 0, std::bind(jammer, std::placeholders::_1, std::placeholders::_2, weightToJam));
    peck.erase(std::remove_if(peck.begin(), peck.end(), [&](Peaches peach){ return peach.weight < weightToJam; }), peck.end());
    

    std::cout << "Weight of jam is: " << jamWeight << std::endl;

    return 0;
}
