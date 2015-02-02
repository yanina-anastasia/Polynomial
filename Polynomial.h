#pragma once
#include <iostream>
#include <vector>


template<class T>
class Polynomial {
private:
    std::vector<T> coefficients;
    int degree;

public:
    Polynomial(const T& coef = T());

    template <class IterType>
    Polynomial(IterType, IterType);

    bool operator ==(const Polynomial<T>&) const;
    bool operator !=(const Polynomial<T>&) const;
    bool operator <(const Polynomial<T>&) const;
    bool operator >(const Polynomial<T>&) const;
    bool operator <=(const Polynomial<T>&) const;
    bool operator >=(const Polynomial<T>&) const;

    Polynomial<T>& operator +=(const Polynomial<T>&);
    Polynomial<T>& operator -=(const Polynomial<T>&);
    Polynomial<T>& operator *=(const Polynomial<T>&);

    const T& operator[](size_t) const;
    T& operator[](size_t);

    T operator()(const T) const;

    int Degree() const;

    typename std::vector<T>::iterator begin();
    typename std::vector<T>::const_iterator begin() const;
    typename std::vector<T>::iterator end();
    typename std::vector<T>::const_iterator end() const;

    void RawDivide(const Polynomial<T>& rhs, Polynomial<T>& quotient, Polynomial<T>& mod) const;

    void Shift(size_t shift);

    void RecountDegree();

    friend Polynomial operator +(const Polynomial& lhs, const Polynomial& rhs)
    {
        Polynomial temp(lhs);
        temp += rhs;
        return temp;
    }
    
    friend Polynomial operator -(const Polynomial& lhs, const Polynomial& rhs)
    {
        Polynomial temp(lhs);
        temp -= rhs;
        return temp;
    }

    friend Polynomial operator *(const Polynomial& lhs, const Polynomial& rhs)
    {
        Polynomial temp(lhs);
        temp *= rhs;
        return temp;
    }

    friend Polynomial operator /(const Polynomial& lhs, const Polynomial& rhs)
    {
        Polynomial quotient;
        Polynomial mod;
        lhs.RawDivide(rhs, quotient, mod);
        return quotient;
    }

    friend Polynomial operator %(const Polynomial& lhs, const Polynomial& rhs)
    {
        Polynomial quotient;
        Polynomial mod;
        lhs.RawDivide(rhs, quotient, mod);
        return mod;
    }

    friend Polynomial operator ,(const Polynomial& lhs, const Polynomial& rhs)
    {
        Polynomial quotient, mod;
        if (lhs > rhs) {
            quotient = lhs;
            mod = rhs;
        } else {
            quotient  = rhs;
            mod = lhs;
        }

        while (!(mod.degree == 0 && mod[0] == 0)) {
            Polynomial temp(mod);
            mod = quotient % mod;
            quotient = temp;
        }
        return quotient;
    }
};


template <class T>
std::ostream& operator <<(std::ostream&, const Polynomial<T>&);

#include "Polynomial.hpp"
