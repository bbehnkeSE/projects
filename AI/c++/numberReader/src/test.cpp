#include "headers/layers.hpp"

int main()
{
    // Convolutional test(3, 3, 3, 2, 2);

    // test.debugPrint();

    // std::vector<int> v1 = {1, 2, 3, 4, 5};
    // std::vector<int> v2 = {6, 7, 8, 9, 10};
    // std::vector<std::vector<int>> test;
    // test.push_back(v1);
    // test.push_back(v2);

    // std::cout << test[1][3] << std::endl;


    arma::mat* test = new arma::mat(3, 3, arma::fill::randu);

    std::cout << *test << std::endl;
    std::vector<arma::mat*>* v = new std::vector<arma::mat*>;
    v->push_back(test);
    std::vector<arma::mat*>::iterator it = v->begin();

    std::cout << **it << std::endl;

    std::vector<std::vector<arma::mat*>*> asdf;
    asdf.push_back(v);
    auto itt = asdf[0][0];

    std::cout << itt << std::endl;

    return 0;
}