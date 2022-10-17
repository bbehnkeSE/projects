/* 
 * Brian Behnke
 * CS43105 - Data Mining Techniques
 * 10/14/2022
 *
 * Demonstrates Apriori algorithm for pruning dataets
 * Usage: myapriori file.txt frequency%
 * Ex. myapriori data.txt 20
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <map>

typedef std::map<std::string, float> Map;

Map         join       (const std::vector<std::string>&, int);
Map&        prune      (Map&, const float&);
void        printMap   (const Map&, const float&);
std::string removeSpace(const std::string&);


int main(int argc, char* argv[])
{
    // Check for correct amount of arguments
    if(argc != 3)
    {
        std::cout << "Usage: myapriori file.txt frequency%\n"
                  << "Please include a file and a desired frequency.\n";
        return EXIT_FAILURE;
    }

    // Create and open file stream
    std::ifstream data;
    data.open(argv[1]);
    if(!data.is_open())
    {
        std::cout << "Failed to open " << argv[1] << ". Exiting...\n";
        return EXIT_FAILURE;
    }

    // Read itemsets into memory
    std::string              set;
    std::vector<std::string> sets;
    while(getline(data, set))
        sets.push_back(set);

    // Close the file
    data.close();

    float total = sets.size();

    // Convert frequency percentage from CLA to float percentage
    float       minsup = 0.;
    std::string minSupString(argv[2]);
    for(int i = 0; i < minSupString.length(); ++i)
        minsup = minsup * 10. + (minSupString[i] - '0');

    minsup = (minsup / 100) * total;

    // Generate single-item sets with support counts
    Map frequents, result;
    std::string tmp, tmp2;
    for(auto it: sets)
    {
        tmp = removeSpace(it);
        for(auto itt: tmp)
        {
            tmp2 = itt;             // Convert char to str to store in map
            frequents[tmp2] += 1;
        }
    }

    // Remove sets that don't meet the minimum support requirement
    frequents = prune(frequents, minsup);
    result.insert(frequents.begin(), frequents.end());

    if(frequents.empty())
    {
        std::cout << "No items meet the minimum support value.\n";
        return EXIT_SUCCESS;
    }

    // Main loop
    // K represents the number of items each set should have
    int k = 2;
    while(!frequents.empty())
    {
        frequents = join(sets, k);
        frequents = prune(frequents, minsup);
        result.insert(frequents.begin(), frequents.end());
        ++k;
    }
    printMap(result, total);

    return EXIT_SUCCESS;
}


// Should generate C_k+1 from L_k, but currently does not
Map join(const std::vector<std::string>& sets, int k)
{
    int start, end;
    Map candidates;
    std::string tmp = "";
    std::string spacelessSet;
    for(auto set: sets)
    {
        start = 0;
        end   = k - 1;
        set   = removeSpace(set);
        while((start + k - 1) < set.length())
        {
            while(start + end < set.length())
            {
                for(int i = start; i < (start + k - 1); ++i)
                    tmp += set[i];
                
                tmp += set[start + end++];
                candidates[tmp] += 1;
                tmp.clear();
            }
            ++start;
            end = (k - 1);
        }
    }
    return candidates;
}


Map& prune(Map& sets, const float& minsup)
{
    if(!sets.empty())
    {
        auto it = sets.begin();
        while(it != sets.end())
        {
            if(it->second < minsup)
                it = sets.erase(it);
            else
                ++it;
        }
    }
    return sets;
}


void printMap(const Map& sets, const float& total)
{
    bool printComma = true;
    int commaCounter;

    for(auto it: sets)
    {
        std::cout << "{";
        commaCounter = 0;
        for(const auto& c: it.first)
        {
            if(printComma)
                printComma = false;
            else
            {
                std::cout << ", ";
                ++commaCounter;
            }
            std::cout << c;
        }
        std::cout << "}" << std::right << std::setw(25 - (it.first.length() + commaCounter)) << "\t: " << it.second << "\t| " << it.second/total * 100 << "\%\n";
        printComma = true;
    }
}


std::string removeSpace(const std::string& str)
{
    std::string result = "";
    for(int i = 0; i < str.length(); ++i)
        if(str[i] != ' ')
            result += str[i];

    return result;
}