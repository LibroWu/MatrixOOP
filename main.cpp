//#define operator*
#define init_list
#include <iostream>
#include "matrix.hpp"

using namespace sjtu;

template <typename T>
void print(Matrix<T> a){
    auto size_=a.size();
    for (int i=0;i<size_.first;++i){
        for (int j=0;j<size_.second;++j) std::cout<<a(i,j)<<' ';
        std::cout<<'\n';
    }
}

int main() {
#ifdef operator*
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
#endif
#ifdef init_list
    Matrix<int> a={{1,2,3,4},{5,6,7,8},{9,10,11,12}};
    print(a*3);
    print(a.tran());
    print(a);
#endif
    return 0;
}
