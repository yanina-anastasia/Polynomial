#include "Polynomial.h"

void PolynomialSum() {
    vector<double> v1;
    v1.push_back(2);
    v1.push_back(0);
    v1.push_back(-2);
    vector<double> v2;
    v2.push_back(1);
    v2.push_back(1);
    Polynomial<double> polynomial(v1.begin(), v1.end());
    Polynomial<double> polynomial2(v2.begin(), v2.end());
    Polynomial<double> a = (polynomial , 2);
}
    
int main() {
    /*vector<double> v1;
    v1.push_back(2);
    v1.push_back(0);
    v1.push_back(-2);
    vector<double> v2;
    v2.push_back(1);
    v2.push_back(1);
    Polynomial<double> polynomial(v1.begin(), v1.end());
    Polynomial<double> polynomial2(v2.begin(), v2.end());
    Polynomial<double> a = (polynomial , 2);
    std::cout << a << std::endl;
    return 0;*/
}
