// Games, Template Method example
// Mikhail Nesterenko, Brian Behnke
// 2/4/2014

#include <ctime>
#include <cstdlib>
#include <iostream>

using std::cout; using std::endl;

// template for any game where players take 
// turns to make moves
// and there is a winner
class Game{
public:
    Game():playersCount_(0), movesCount_(0), playerWon_(noWinner){}

    // template method
    void playGame(const int playersCount = 0) {
        playersCount_ = playersCount;
        movesCount_=0;

        initializeGame();

        for(int i=0; !endOfGame(); i = (i+1) % playersCount_ ){
            makeMove(i);
            if (i==playersCount_-1) 
                ++movesCount_; 
        }
        printWinner();
    }

    virtual ~Game(){}

protected:
    // primitive operations
    virtual void initializeGame() = 0;
    virtual void makeMove(int player) = 0;
    virtual void printWinner() = 0;
    virtual bool endOfGame() { return playerWon_ != noWinner;}  // this is a hook
                                                                // returns true if winner is decided
    static const int noWinner=-1;

    int playersCount_;
    int movesCount_;
    int playerWon_;
};

// Monopoly - a concrete game implementing primitive 
// operations for the template method
class Monopoly: public Game {
public:  
    // implementing concrete methods
    void initializeGame(){
        playersCount_ = rand() % numPlayers_ + 1 ; // initialize players
    }

    void makeMove(int player) {
        if (movesCount_ > minMoves_){ 
            const int chance = minMoves_ + rand() % (maxMoves_ - minMoves_);
            if (chance < movesCount_) playerWon_= player;
        }
    }

    void printWinner(){
        cout << "Monopoly, player "<< playerWon_<< " won in "
        << movesCount_<< " moves." << endl;
    }

private:
    static const int numPlayers_ = 8;   // max number of players
    static const int minMoves_ = 20;    // nobody wins before minMoves_
    static const int maxMoves_ = 200;   // somebody wins before maxMoves_
};

// Chess - another game implementing
// primitive operations
class Chess: public Game {
public:
    void initializeGame(){
        playersCount_ = numPlayers_; // initalize players
        for(int i=0; i < numPlayers_; ++i) 
            experience_[i] = rand() % maxExperience_ + 1 ; 
    }

    void makeMove(int player){
        if (movesCount_ > minMoves_){
            const int chance = (rand() % maxMoves_) / experience_[player];
            if (chance < movesCount_) playerWon_= player;
        }
    }

    void printWinner(){
        cout << "Chess, player " << playerWon_ 
        << " with experience " << experience_[playerWon_]
        << " won in "<< movesCount_ << " moves over"
        << " player with experience " << experience_[playerWon_== 0 ? 1:0] 
        << endl;
    }

private:
    static const int numPlayers_ = 2;
    static const int minMoves_ = 2;         // nobody wins before minMoves_
    static const int maxMoves_ = 100;       // somebody wins before maxMoves_
    static const int maxExperience_ = 5;    // player's experience
                                            // the higher, the greater probability of winning
    int experience_[numPlayers_]; 
};


class Dice: public Game {
public:
    void initializeGame() { playersCount_ = numPlayers_; }

    void makeMove(int player) {
        if(player == 1 && hPass_) {    // Human, passed
            std::cout << "You passed, your highest score = " << h_hScore << std::endl;
            ++turnCounter;
        }
        if(player == 0 && cPass_) {    // Computer, passed
            std::cout << "Computer passed, computer's highest score = " << c_hScore << std::endl;
            ++turnCounter;
        }
        if(player == 0 && !cPass_) {    // Computer, not passed
            std::cout << "Computer ";
            int roll_ = roll();
            if(c_hScore < roll_) {
                c_hScore = roll_;
            }
            std::cout << "computer's highest score = " << c_hScore << std::endl;
            ++turnCounter;
        }
        if(player == 1 && !hPass_) {   // Human, not passed
            std::cout << "You ";
            int roll_ = roll();
            if(h_hScore < roll_) {
                h_hScore = roll_;
            }
            std::cout << "your highest score = " << h_hScore << std::endl;
            rollAgain();
            ++turnCounter;
        }
        if(cPass()) {
            cPass_ = true;
        }

        if((turnCounter / 2) >= maxMoves_ || (cPass_ && hPass_)) {
            if(c_hScore >= h_hScore) { playerWon_ = 0; }
            if(h_hScore > c_hScore)  { playerWon_ = 1; }
        }
        
    }

    void printWinner() {
        if(playerWon_ == 1) { std::cout << "You won" << std::endl; }
        else { std::cout << "You lose"; }
    }

private:
    bool cPass() { return rand() % 2; }     // Coin flip to see if the computer passes

    int roll() {
        int total = 0;
        int roll = 0;
        std::cout << "rolled: ";
        for(int i = 1; i <= maxDice_; ++i) {
            roll = (rand() % dSides_ + 1);
            std::cout << roll << " ";
            total += roll;
        }
        std::cout << "= " << total << ", ";
        return total;
    }

    void rollAgain() {
        char answer;
        while(answer != 'y' && answer != 'n') {
            std::cout << "Roll again? [y/n] ";
            std::cin >> answer;
        }
        if(answer == 'n') {
            hPass_ = true;
        }
    }

private:
    static const int numPlayers_ = 2;
    static const int minMoves_ = 1;
    static const int maxMoves_ = 3;
    static const int maxDice_ = 5;  // Number of dice to be rolled
    static const int dSides_ = 6;   // Number of sides on a die
    
    int turnCounter = 1;
    int c_hScore = 0;   // Computer's high score
    int h_hScore = 0;   // Human's high score

    bool cPass_ = false;
    bool hPass_ = false;

};


int main() {
    srand(time(nullptr));

    Game* gp = nullptr;

    // play chess 10 times
    for (int i = 0; i < 10; ++i){ 
        gp = new Chess;
        gp->playGame(); 
        delete gp;
    }
    std::cout << std::endl;
        

    // play monopoly 8 times
    for (int i = 0; i < 8; ++i){
        gp = new Monopoly;
        gp->playGame(); 
        delete gp;
    }
    std::cout << std::endl;


    // play dice
    gp = new Dice;
    gp->playGame();
    delete gp;
}