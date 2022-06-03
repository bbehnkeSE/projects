// sorting oranges
// converting vectors to multimaps
// Mikhail Nesterenko, Brian Behnke
// 10/06/2021


#include <iostream>
#include <ctime>
#include <cstdlib>
#include <string>
#include <vector>
#include <map>

enum class Variety { orange, pear, apple };
std::vector<std::string> colors = { "red", "green", "yellow" };


int main() {
   srand(time(nullptr));
   std::multimap<Variety, std::string> tree;
   int rando = rand() % 100 + 1;

   for(int i = 1; i <= rando; ++i) {
       tree.emplace(static_cast<Variety>(rand() % 3), colors[rand() % 3]);
   }
 
   std::cout << "Colors of the oranges: ";
   for(auto it = tree.lower_bound(Variety::orange); it != tree.upper_bound(Variety::orange); ++it) {
        std::cout << it->second << ", ";
   }
   std::cout << std::endl;

    return 0;
}