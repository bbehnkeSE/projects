// Three state process model using State and Prototype design patters
// Brian Behnke
// 11/8/2021

#include "process.hpp"

#include <queue>
#include <ctime>


int main()
{
    srand(time(nullptr));
    Process prototype(0);
    const int maxSize = 4;
    int rando;

    std::queue<Process*> ready, waiting;

    // Fill queue with processes
    for(int i = 0; i < maxSize; ++i) 
    {
        ready.push(prototype.clone());
    }

    while(!ready.empty() || !waiting.empty()) 
    {
        rando = rand() % 3;     // Determines what occurs
        if(!ready.empty())
        {
            std::cout << "Schedule new process: ";
            ready.front()->schedulerDispatch();
            ready.front()->print();
        
            if(rando == 0)
            {
                std::cout << "Process completed:    ";
                ready.front()->exit();
                ready.front()->print();
                ready.pop();
            }
            if(rando == 1)
            {
                std::cout << "Process interrupted:  ";
                ready.front()->interrupt();
                ready.front()->print();
                ready.push(ready.front());
                ready.pop();
            }
            if(rando == 2)
            {
                std::cout << "Waiting for I/O:      ";
                ready.front()->eventWait();
                ready.front()->print();
                waiting.push(ready.front());
                ready.pop();
            }
        }
        if(!waiting.empty() && rando / 2 != 1)
        {
            std::cout << "I/O complete:         ";
            ready.push(waiting.front());
            waiting.pop();
            ready.back()->eventCompletion();
            ready.back()->print();
        } 
    }

    return 0;
}