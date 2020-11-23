//#define operator
//#define init_list
#define emm
#include <iostream>
#include "matrix.hpp"

using namespace sjtu;
struct Int{
    int num;
};
template <typename T>
void print(Matrix<T> a){
    auto size_=a.size();
    for (int i=0;i<size_.first;++i){
        for (int j=0;j<size_.second;++j) std::cout<<a(i,j)<<' ';
        std::cout<<'\n';
    }
    std::cout<<'\n';
}

int main() {
#ifdef emm
    std::initializer_list<std::initializer_list<int>> intIl = {{ 0, 1, 2, 3 },
                                                               { 1, 2, 3, 4 },
                                                               { 2, 3, 4, 5 }};
    Matrix<int> a = intIl;
    auto b = a;
    b += a;

    if (b != 2 * a)
        std::cout<<"wa\n";
    b-=a;
    if (b != a)
        std::cout<<"wa\n";
#endif
#ifdef operator
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
    auto z=a;
    z+=a;
    Matrix<int> y=2*a;
    if (y!=2*a) std::cout<<"yes\n";
    print(z);
    print(a*3);
    print(a.tran());
    if (a==a) print(a-a);
    a.resize(6,6,3);
    print(a);
    a.resize(4,4,1);
    print(a);
    Matrix<Int> b(2, 2,{3});
    b(0, 0).num = 124;
    if (b.begin()->num != 123)
        std::cout<<"wa\n"<<b.begin()->num<<'\n';
    Matrix<Int>::iterator it;
    it=b.begin();
    Int tmp=*++it;
    std::cout<<tmp.num<<' '<<it->num;
#endif
    return 0;
}
