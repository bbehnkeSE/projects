// sorting apples
// non STL-algorithm code to be replaced by algorthms
// Mikhail Nesterenko, Brian Behnke
// 10/09/2021


//#include <numeric>
#include <algorithm>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <string>


struct Apples{
   double weight; // oz
   std::string color;  // red or green
   void print() const { std::cout << color << ", " <<  weight << std::endl; }
};


bool wComp(Apples lhs, Apples rhs) { return lhs.weight < rhs.weight; }


int main(){
    srand(time(nullptr));
    const double minWeight = 8.;
    const double maxWeight = 3.;

    std::cout << "Input crate size: ";
    int size;
    std::cin >> size;

    std::vector <Apples> crate(size);


    //DONE
    // assign random weight and color to apples in the crate
    // replace with generate()
    std::generate(crate.begin(), crate.end(), [&](){ 
        Apples apple; 
        apple.weight = minWeight + static_cast<double>(rand())/RAND_MAX*(maxWeight - minWeight);
        apple.color = rand() % 2 == 1 ? "green" : "red";
        return apple;
    });

    // DONE
    // for_each() possibly
    std::cout << "all apples"<< std::endl;
    std::for_each(crate.begin(), crate.end(), [](const Apples& apple){ apple.print(); });
    std::cout << "Enter weight to find: ";
    double toFind;
    std::cin >> toFind;


    // DONE
    // count_if()
    int cnt = count_if(crate.begin(), crate.end(), [&](const Apples& apple){ return toFind < apple.weight; });
    std::cout << "There are " << cnt << " apples heavier than " << toFind << " oz" <<  std::endl;


    //DONE
    // find_if()
    std::cout << "at positions ";
    auto i = std::find_if(crate.begin(), crate.end(), [&](Apples apple){ return apple.weight > toFind; });
    if(i != crate.end()) {
        do {
            std::cout << i - crate.begin() << ", ";
            i = std::find_if(++i, crate.end(), [&](Apples apple){ return apple.weight > toFind; });
        }
        while(i != crate.end());
    }
    std::cout << std::endl;


    //DONE
    // max_element()
    auto it = std::max_element(crate.begin(), crate.end(), wComp);
    double heaviest = it->weight;
    std::cout << "Heaviest apple weighs: " << heaviest << " oz" << std::endl;


    //DONE
    // for_each() or accumulate()
    double sum = 0;
    std::for_each(crate.begin(), crate.end(), [&](const Apples& apple){ sum += apple.weight; });
    std::cout << "Total apple weight is: " << sum << " oz" << std::endl;


    //DONE
    // transform();
    std::cout << "How much should they grow: ";
    double toGrow;
    std::cin >> toGrow;
    std::transform(crate.begin(), crate.end(), crate.begin(), [&](Apples apple){ apple.weight += toGrow; return apple; });


    //DONE
    // remove_if()
    std::cout << "Input minimum acceptable weight: ";
    double minAccept;
    std::cin >> minAccept;
    crate.erase(std::remove_if(crate.begin(), crate.end(), [&](const Apples& apple){ return apple.weight < minAccept; }), crate.end());
    std::cout << "removed " << size - crate.size() << " elements" << std::endl;


    //DONE
    // bubble sort, replace with sort()
    std::sort(crate.begin(), crate.end(), wComp);


    //DONE
    // for_each() possibly
    std::cout << "sorted remaining apples"<< std::endl;
    std::for_each(crate.begin(), crate.end(), [](const Apples& apple){ apple.print(); });

    return 0;
}
