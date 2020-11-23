#ifndef SJTU_MATRIX_HPP
#define SJTU_MATRIX_HPP

#include <cstddef>
#include <initializer_list>
#include <utility>
#include <iterator>

using std::size_t;

namespace sjtu {

    template<class T>
    class Matrix {
    private:
        // your private member variables here.
        const std::pair<size_t, std::size_t> init_size={0,0};
        std::pair<size_t, std::size_t> size_Matrix=init_size;
        T *Core = nullptr;
        size_t len = 0,true_len=0;
    public:
        template<class T1,class U>
        friend auto operator*(const Matrix<T1> &mat, const U &x);

        template<class T1,class U>
        friend auto operator*(const U &x, const Matrix<T1> &mat);

        template<class U, class V>
        friend auto operator*(const Matrix<U> &a, const Matrix<V> &b);

        template<class U, class V>
        friend auto operator+(const Matrix<U> &a, const Matrix<V> &b);

        template<class U, class V>
        friend auto operator-(const Matrix<U> &a, const Matrix<V> &b);

        Matrix() = default;

        Matrix(size_t n, size_t m, T _init = T()) {
            size_Matrix.first = n;
            size_Matrix.second = m;
            true_len=len = n * m;
            Core = new T[len];
            for (int i = 0; i < len; ++i) Core[i] = _init;
        }

        explicit Matrix(std::pair<size_t, size_t> sz, T _init = T()) {
            size_Matrix = sz;
            true_len=len = sz.first * sz.second;
            Core = new T[len];
            for (int i = 0; i < len; ++i) Core[i] = _init;
        }

        Matrix(const Matrix &o) {
            size_Matrix = o.size_Matrix;
            true_len=len = o.len;
            Core = new T[len];
            for (int i = 0; i < len; ++i) Core[i] = o.Core[i];
        }

        template<class U>
        Matrix(const Matrix<U> &o) {
            std::pair<size_t, std::size_t> sz=o.size();
            size_Matrix = sz;
            true_len=len = sz.second*sz.first;
            Core = new T[len];
            for (int i = 0; i < sz.first; ++i)
                for (int j=0;j<sz.second;++j)
                    Core[i*sz.second+j] =static_cast<T>(o(i,j));
        }

        Matrix &operator=(const Matrix &o) {
            if (this==&o) return *this;
            delete[] Core;
            true_len=len = o.len;
            size_Matrix = o.size_Matrix;
            Core = new T[len];
            for (int i = 0; i < len; ++i) Core[i] = o.Core[i];
            return *this;
        }

        template<class U>
        Matrix &operator=(const Matrix<U> &o) {
            delete [] Core;
            std::pair<size_t, std::size_t> sz=o.size();
            true_len=len=sz.first*sz.second;
            size_Matrix = sz;
            Core=new T[len];
            for (int i=0;i<sz.first;++i)
                for (int j=0;j<sz.second;++j)
                    Core[i*sz.second+j]=static_cast<T>(o(i,j));
            return *this;
        }

        Matrix(Matrix &&o) noexcept {
            Core = o.Core;
            size_Matrix = o.size_Matrix;
            true_len=len = o.len;
            o.Core = nullptr;
        }

        Matrix &operator=(Matrix &&o) noexcept {
            if (this==&o) return *this;
            Core = o.Core;
            size_Matrix = o.size_Matrix;
            true_len=len = o.len;
            o.Core = nullptr;
            return *this;
        }

        ~Matrix() {
            delete[] Core;
        }

        Matrix(std::initializer_list<std::initializer_list<T>> il) {
            size_Matrix.first=il.size();
            size_Matrix.second=(*std::begin(il)).size();
            true_len=len=size_Matrix.first*size_Matrix.second;
            Core=new T [len];
            int i=-1;
            for (auto it_i=std::begin(il);it_i!=std::end(il);++it_i){
                for (auto it_j=std::begin(*it_i);it_j!=std::end(*it_i);++it_j){
                    Core[++i]=*it_j;
                }
            }
        }

    public:
        size_t rowLength() const {
            return size_Matrix.first;
        }

        size_t columnLength() const {
            return size_Matrix.second;
        }

        void resize(size_t _n, size_t _m, T _init = T()) {
            if (_n*_m==len){
                size_Matrix={_n,_m};
            }else {
                T* tmp=new T [_n*_m];
                int cnt=-1;
                for (int i=0;i<_n && i<size_Matrix.first;++i)
                    for (int j=0;j<_m && j<size_Matrix.second;++j)
                            tmp[++cnt]=Core[i*size_Matrix.second+j];
                for (int i=cnt+1;i<_n*_m;++i) tmp[i]=_init;
                T* _tmp=Core;
                Core=tmp;
                delete [] _tmp;
                size_Matrix={_n,_m};
                true_len=len=_n*_m;
            }
        }

        void resize(std::pair<size_t, size_t> sz, T _init = T()) {
            std::size_t _n=sz.first,_m=sz.second;
            if (_n*_m==len){
                size_Matrix={_n,_m};
            }else {
                T* tmp=new T [_n*_m];
                int cnt=-1;
                for (int i=0;i<_n && i<size_Matrix.first;++i)
                    for (int j=0;j<_m && j<size_Matrix.second;++j)
                        tmp[++cnt]=Core[i*size_Matrix.second+j];
                for (int i=cnt+1;i<_n*_m;++i) tmp[i]=_init;
                T* _tmp=Core;
                Core=tmp;
                delete [] _tmp;
                size_Matrix={_n,_m};
                true_len=len=_n*_m;
            }
        }

        std::pair<size_t, size_t> size() const {
            return size_Matrix;
        };

        void clear() {
            delete[] Core;
            Core = nullptr;
            true_len=len = 0;
            size_Matrix=init_size;
        }

    public:
        const T &operator()(size_t i, size_t j) const {
            return Core[i*size_Matrix.second+j];
        }

        T &operator()(size_t i, size_t j) {
            return Core[i*size_Matrix.second+j];
        }

        Matrix<T> row(size_t i) const {
            Matrix<T> res;
            res.size_Matrix={1,size_Matrix.second};
            res.true_len=res.len=size_Matrix.second;
            res.Core=new T [res.len];
            for (int j=0;j<res.len;++j) res.Core[j]=Core[i*size_Matrix.second+j];
            return res;
        }

        Matrix<T> column(size_t i) const {
            Matrix<T> res;
            res.size_Matrix={size_Matrix.first,1};
            res.true_len=res.len=size_Matrix.first;
            res.Core=new T [res.len];
            for (int j=0;j<res.len;++j) res.Core[j]=Core[j*size_Matrix.second+i];
            return res;
        }


    public:
        template<class U>
        bool operator==(const Matrix<U> &o) const {
            if (size_Matrix!=o.size()) return 0;
            for (int i=0;i<size_Matrix.first;++i)
                for (int j=0;j<size_Matrix.second;++j)
                    if (Core[i*size_Matrix.second+j]!=o(i,j)) return 0;
            return 1;
        }

        template<class U>
        bool operator!=(const Matrix<U> &o) const {
            if (size_Matrix!=o.size()) return 1;
            for (int i=0;i<size_Matrix.first;++i)
                for (int j=0;j<size_Matrix.second;++j)
                if (Core[i*size_Matrix.second+j]!=o(i,j)) return 1;
            return 0;
        }

        Matrix operator-() const {
            Matrix<T> res;
            res.size_Matrix=size_Matrix;
            res.true_len=res.len=len;
            res.Core=new T [len];
            for (int i=0;i<len;++i) res.Core[i]=-Core[i];
            return res;
        }

        template<class U>
        Matrix &operator+=(const Matrix<U> &o) {
            for (int i=0;i<size_Matrix.first;++i)
                for (int j=0;j<size_Matrix.second;++j)
                    Core[i*size_Matrix.second+j]+=static_cast<T>(o(i,j));
//            for (int i=0;i<len;++i) Core[i]+=static_cast<T>(o.Core[i]);
            return *this;
        }

        template<class U>
        Matrix &operator-=(const Matrix<U> &o) {
            for (int i=0;i<size_Matrix.first;++i)
                for (int j=0;j<size_Matrix.second;++j)
                    Core[i*size_Matrix.second+j]-=static_cast<T>(o(i,j));
//            for (int i=0;i<len;++i) Core[i]-=static_cast<T>(o.Core[i]);
            return *this;
        }

        template<class U>
        Matrix &operator*=(const U &x) {
            for (int i=0;i<len;++i) Core[i]*=static_cast<T>(x);
            return *this;
        }

        Matrix tran() const {
            Matrix<T> res;
            res.size_Matrix={size_Matrix.second,size_Matrix.first};
            res.true_len=res.len=len;
            res.Core=new T [len];
            for (int i=0;i<size_Matrix.second;++i)
                for (int j=0;j<size_Matrix.first;++j)
                    res.Core[i*size_Matrix.first+j]=Core[j*size_Matrix.second+i];
            return res;
        }

    public: // iterator
        class iterator {
        public:
            using iterator_category = std::random_access_iterator_tag;
            using value_type = T;
            using pointer = T *;
            using reference = T &;
            using size_type = size_t;
            using difference_type = std::ptrdiff_t;

            iterator() = default;

            iterator(const iterator &) = default;

            iterator &operator=(const iterator &) = default;

        private:
            T* ptr;
            int now,len;
            friend class Matrix;
        public:
            difference_type operator-(const iterator &o) {
                return now-o.now;
            }
            //0 <-> end
            iterator &operator+=(difference_type offset) {
                int tmp=now+offset;
                T* tmp_ptr;
                if (tmp<0) tmp+=len+1;
                if (tmp>len) tmp-=len+1;
                tmp_ptr=ptr-now;
                now=tmp;
                ptr=tmp_ptr+now;
                return *this;
            }

            iterator operator+(difference_type offset) const {
                iterator res;
                res.len=len;
                res.ptr=ptr-now;
                int tmp=now+offset;
                if (tmp<0) tmp+=len+1;
                if (tmp>len) tmp-=len+1;
                res.now=tmp;
                res.ptr=res.ptr+res.now;
                return res;
            }

            iterator &operator-=(difference_type offset) {
                int tmp=now-offset;
                T* tmp_ptr;
                if (tmp<0) tmp+=len+1;
                if (tmp>len) tmp-=len+1;
                tmp_ptr=ptr-now;
                now=tmp;
                ptr=tmp_ptr+now;
                return *this;
            }

            iterator operator-(difference_type offset) const {
                iterator res;
                res.len=len;
                res.ptr=ptr-now;
                int tmp=now-offset;
                if (tmp<0) tmp+=len+1;
                if (tmp>len) tmp-=len+1;
                res.now=tmp;
                res.ptr=res.ptr+res.now;
                return res;
            }

            iterator &operator++() {
                ++ptr;
                ++now;
                if (now>len) {
                    ptr-=now;
                    now = 0;
                }
                return *this;
            }

            iterator operator++(int) {
                iterator res;
                res.len=len;
                res.now=now;
                res.ptr=ptr;
                ++ptr;
                ++now;
                if (now>len) {
                    ptr-=now;
                    now = 0;
                }
                return res;
            }

            iterator &operator--() {
                --ptr;
                --now;
                if (now<0) {
                    ptr+=len+1;
                    now = len;
                }
                return *this;
            }

            iterator operator--(int) {
                iterator res;
                res.len=len;
                res.now=now;
                res.ptr=ptr;
                --ptr;
                --now;
                if (now<0) {
                    ptr+=len+1;
                    now = len;
                }
                return res;
            }

            reference operator*() const {
                return *ptr;
            }

            pointer operator->() const {
                return ptr;
            }

            bool operator==(const iterator &o) const {
                return (ptr==o.ptr);
            }

            bool operator!=(const iterator &o) const {
                return (ptr!=o.ptr);
            }
        };

        iterator begin() {
            iterator res;
            res.ptr=Core;
            res.now=0;
            res.len=len;
            return res;
        }

        iterator end() {
            iterator res;
            res.ptr=Core+len;
            res.now=len;
            res.len=len;
            return res;
        }

        std::pair<iterator, iterator> subMatrix(std::pair<size_t, size_t> l, std::pair<size_t, size_t> r) {

        }
    };

}

//
namespace sjtu {
    template<class T, class U>
    auto operator*(const Matrix<T> &mat, const U &x) {
        std::pair<size_t,size_t> size_=mat.size_Matrix;
        Matrix<decltype(mat.Core[0]*x)> res(size_);
        for (int i=0;i<size_.first;++i)
            for (int j=0;j<size_.second;++j)
                res.Core[i*size_.second+j]=mat.Core[i*size_.second+j]*x;
        return res;
    }

    template<class T, class U>
    auto operator*(const U &x, const Matrix<T> &mat) {
        std::pair<size_t,size_t> size_=mat.size_Matrix;
        Matrix<decltype(mat.Core[0]*x)> res(size_);
        for (int i=0;i<size_.first;++i)
            for (int j=0;j<size_.second;++j)
                res.Core[i*size_.second+j]=mat.Core[i*size_.second+j]*x;
        return res;
    }

    template<class U, class V>
    auto operator*(const Matrix<U> &a, const Matrix<V> &b) {
        std::pair<size_t,size_t> size_={a.size_Matrix.first,b.size_Matrix.second};
        Matrix<decltype(a.Core[0]*b.Core[0])> res(size_,0);
        for (int i=0;i<a.size_Matrix.first;++i)
            for (int j=0;j<b.size_Matrix.second;++j)
                for (int k=0;k<a.size_Matrix.second;++k)
                    res.Core[i*size_.second+j]+=a.Core[i*a.size_Matrix.second+k]*b.Core[k*b.size_Matrix.second+j];
        return res;
    }

    template<class U, class V>
    auto operator+(const Matrix<U> &a, const Matrix<V> &b) {
        std::pair<size_t,size_t> size_={a.size_Matrix.first,a.size_Matrix.second};
        Matrix<decltype(a.Core[0]+b.Core[0])> res(size_,0);
        for (int i=0;i<a.size_Matrix.first;++i)
            for (int j=0;j<a.size_Matrix.second;++j)
                    res.Core[i*size_.second+j]=a.Core[i*size_.second+j]+b.Core[i*size_.second+j];
        return res;
    }

    template<class U, class V>
    auto operator-(const Matrix<U> &a, const Matrix<V> &b) {
        std::pair<size_t,size_t> size_={a.size_Matrix.first,a.size_Matrix.second};
        Matrix<decltype(a.Core[0]-b.Core[0])> res(size_,0);
        for (int i=0;i<a.size_Matrix.first;++i)
            for (int j=0;j<a.size_Matrix.second;++j)
                res.Core[i*size_.second+j]=a.Core[i*size_.second+j]-b.Core[i*size_.second+j];
        return res;
    }
}

#endif //SJTU_MATRIX_HPP

