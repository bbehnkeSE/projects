// Reads text from file and tallys and sorts by word occurances
// Brian Behnke
// 9/09/2021

#include "WordList.hpp"

int main(int argc, char* argv[]) {
    // Makes sure enough files are provided.
    if(argc < 2) {
        std::cerr << "Not enough files provided. Exiting...\n";
        return 1;
    }

    // Creates ifstream object and opens file.
    std::ifstream file;
    file.open(argv[1]);

    if(file.is_open()) {
        std::string word;
        WordList words;

        while(file >> word) {
            // Removes non-alphanumeric characters and capitalizes all characters to remove case sensitivity.
            for(int i = 0; i < word.length(); ++i) {
                if(isalnum(word[i]) == 0 && word[i] != '\'') {
                    word.erase(std::remove(word.begin(), word.end(), word[i]));
                }
                word[i] = toupper(word[i]);
            }
            words.addWord(word);
        }
        sortArray(words);
        words.print();
        file.close();
    }
    else {
        std::cerr << "Could not open file. Exiting...\n";
        return 1;
    }
    return 0;
}