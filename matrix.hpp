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
        size_t len = 0;
    public:
        Matrix() = default;

        Matrix(size_t n, size_t m, T _init = T()) {
            size_Matrix.first = n;
            size_Matrix.second = m;
            len = n * m;
            Core = new T[len];
            for (int i = 0; i < len; ++i) Core[i] = _init;
        }

        explicit Matrix(std::pair<size_t, size_t> sz, T _init = T()) {
            size_Matrix = sz;
            len = sz.first * sz.second;
            Core = new T[len];
            for (int i = 0; i < len; ++i) Core[i] = _init;
        }

        Matrix(const Matrix &o) {
            size_Matrix = o.size_Matrix;
            len = o.len;
            Core = new T[len];
            for (int i = 0; i < len; ++i) Core[i] = o.Core[i];
        }

        template<class U>
        Matrix(const Matrix<U> &o) {
            size_Matrix = o.size_Matrix;
            len = o.len;
            Core = new T[len];
            for (int i = 0; i < len; ++i) Core[i] =static_cast<T>(o.Core[i]);
        }

        Matrix &operator=(const Matrix &o) {
            delete[] Core;
            len = o.len;
            size_Matrix = o.size_Matrix;
            Core = new T[len];
            for (int i = 0; i < len; ++i) Core[i] = o.Core[i];
            return *this;
        }

        template<class U>
        Matrix &operator=(const Matrix<U> &o) {
            delete [] Core;
            len=o.len;
            size_Matrix = o.size_Matrix;
            Core=new T[len];
            for (int i=0;i<len;++i) Core[i]=static_cast<T>(o.Core[i]);
            return *this;
        }

        Matrix(Matrix &&o) noexcept {
            Core = o.Core;
            size_Matrix = o.size_Matrix;
            len = o.len;
            o.Core = nullptr;
        }

        Matrix &operator=(Matrix &&o) noexcept {
            Core = o.Core;
            size_Matrix = o.size_Matrix;
            len = o.len;
            o.Core = nullptr;
            return *this;
        }

        ~Matrix() {
            delete[] Core;
        }

        Matrix(std::initializer_list<std::initializer_list<T>> il) {

        }

    public:
        size_t rowLength() const {
            return size_Matrix.first;
        }

        size_t columnLength() const {
            return size_Matrix.second;
        }

        void resize(size_t _n, size_t _m, T _init = T()) {

        }

        void resize(std::pair<size_t, size_t> sz, T _init = T()) {

        }

        std::pair<size_t, size_t> size() const {
            return size_Matrix;
        };

        void clear() {
            delete[] Core;
            Core = nullptr;
            len = 0;
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
            res.len=size_Matrix.second;
            res.Core=new T [res.len];
            for (int j=0;j<res.len;++j) res.Core[j]=i*size_Matrix.second+j;
            return res;
        }

        Matrix<T> column(size_t i) const {
            Matrix<T> res;
            res.size_Matrix={size_Matrix.first,1};
            res.len=size_Matrix.first;
            res.Core=new T [res.len];
            for (int j=0;j<res.len;++j) res.Core[j]=j*size_Matrix.second+i;
            return res;
        }


    public:
        template<class U>
        bool operator==(const Matrix<U> &o) const {
            if (size_Matrix!=o.size_Matrix) return 0;
            for (int i=0;i<len;++i)
                if (Core[i]!=static_cast<T>(o.Core[i])) return 0;
            return 1;
        }

        template<class U>
        bool operator!=(const Matrix<U> &o) const {
            if (size_Matrix!=o.size_Matrix) return 1;
            for (int i=0;i<len;++i)
                if (Core[i]!=static_cast<T>(o.Core[i])) return 1;
            return 0;
        }

        Matrix operator-() const {
            for (int i=0;i<len;++i) Core[i]=-Core[i];
            return *this;
        }

        template<class U>
        Matrix &operator+=(const Matrix<U> &o) {
            for (int i=0;i<len;++i) Core[i]+=static_cast<T>(o.Core[i]);
            return *this;
        }

        template<class U>
        Matrix &operator-=(const Matrix<U> &o) {
            for (int i=0;i<len;++i) Core[i]-=static_cast<T>(o.Core[i]);
            return *this;
        }

        template<class U>
        Matrix &operator*=(const U &x) {
            for (int i=0;i<len;++i) Core[i]+=static_cast<T>(x);
            return *this;
        }

        Matrix tran() const {
            Matrix<T> res;
            res.size_Matrix={size_Matrix.second,size_Matrix.first};
            res.len=len;
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


        public:
            difference_type operator-(const iterator &o) {

            }

            iterator &operator+=(difference_type offset) {

            }

            iterator operator+(difference_type offset) const {

            }

            iterator &operator-=(difference_type offset) {

            }

            iterator operator-(difference_type offset) const {

            }

            iterator &operator++() {

            }

            iterator operator++(int) {

            }

            iterator &operator--() {

            }

            iterator operator--(int) {

            }

            reference operator*() const {

            }

            pointer operator->() const {

            }

            bool operator==(const iterator &o) const {

            }

            bool operator!=(const iterator &o) const {

            }
        };

        iterator begin() {

        }

        iterator end() {

        }

        std::pair<iterator, iterator> subMatrix(std::pair<size_t, size_t> l, std::pair<size_t, size_t> r) {

        }
    };

}

//
namespace sjtu {
    template<class T, class U>
    auto operator*(const Matrix<T> &mat, const U &x) {
        std::pair<size_t,size_t> size_=mat.size();
        Matrix<decltype(mat(0,0)*x)> res(size_);
        for (int i=0;i<size_.first;++i)
            for (int j=0;j<size_.second;++j)
                res(i,j)=mat(i,j)*x;
        return res;
    }

    template<class T, class U>
    auto operator*(const U &x, const Matrix<T> &mat) {
        std::pair<size_t,size_t> size_=mat.size();
        Matrix<decltype(mat(0,0)*x)> res(size_);
        for (int i=0;i<size_.first;++i)
            for (int j=0;j<size_.second;++j)
                res(i,j)=mat(i,j)*x;
        return res;
    }

    template<class U, class V>
    auto operator*(const Matrix<U> &a, const Matrix<V> &b) {
        std::pair<size_t,size_t> size_={a.size().first,b.size().second};
        Matrix<decltype(a(0,0)*b(0,0))> res(size_,0);
        for (int i=0;i<a.size().first;++i)
            for (int j=0;j<b.size().second;++j)
                for (int k=0;k<a.size().second;++k)
                    res(i,j)+=a(i,k)*b(k,j);
        return res;
    }

    template<class U, class V>
    auto operator+(const Matrix<U> &a, const Matrix<V> &b) {
        std::pair<size_t,size_t> size_={a.size().first,a.size().second};
        Matrix<decltype(a(0,0)+b(0,0))> res(size_,0);
        for (int i=0;i<a.size().first;++i)
            for (int j=0;j<a.size().second;++j)
                    res(i,j)=a(i,j)+b(i,j);
        return res;
    }

    template<class U, class V>
    auto operator-(const Matrix<U> &a, const Matrix<V> &b) {
        std::pair<size_t,size_t> size_={a.size().first,a.size().second};
        Matrix<decltype(a(0,0)-b(0,0))> res(size_,0);
        for (int i=0;i<a.size().first;++i)
            for (int j=0;j<a.size().second;++j)
                res(i,j)=a(i,j)-b(i,j);
        return res;
    }
}

#endif //SJTU_MATRIX_HPP

