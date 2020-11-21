#include <iostream>
#include "matrix.hpp"

using namespace sjtu;
int main() {
    int n,m,k;
    std::cin>>n>>m>>k;
    Matrix<int> a(n,m),b(m,k);
    for (int i=0;i<n;++i)
        for (int j=0;j<m;++j) std::cin>>a(i,j);
    for (int i=0;i<m;++i)
        for (int j=0;j<k;++j) std::cin>>b(i,j);
    Matrix<int> c=a*b;
    c=-c;
    for (int i=0;i<n;++i) {
        for (int j = 0; j < k; ++j) std::cout << c(i, j) << ' ';
        std::cout<<'\n';
    }
    return 0;
}
