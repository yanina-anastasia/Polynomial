#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using std::vector;
using std::string;

template<class T>
Polynomial<T>::Polynomial(const T& coef) {
    coefficients.push_back(coef);
    degree = 0;
}

template<class T>
template<class IterType>
Polynomial<T>::Polynomial(IterType begin, IterType end) {
    degree = std::distance(begin, end) - 1;
    IterType iter = end - 1;
    for(iter; iter != begin; --iter) {
        coefficients.push_back(*iter);
    }
    coefficients.push_back(*iter);
}

template<class T>
bool Polynomial<T>::operator ==(const Polynomial<T>& other) const {
    return coefficients == other.coefficients;
}

template<class T>
bool Polynomial<T>::operator !=(const Polynomial<T>& other) const {
    return !(*this == other);
}

template<class T>
void Polynomial<T>::RecountDegree() {
    while (coefficients.size() > 1 && coefficients.back() == T()) {
            coefficients.pop_back();
        }

    degree = coefficients.size() - 1;
}

template<class T>
Polynomial<T>& Polynomial<T>::operator +=(const Polynomial<T>& other) {
    size_t my_degree = Degree();
    size_t other_degree = other.Degree();

    if (my_degree < other_degree) {
        coefficients.resize(other_degree + 1);
        degree = other_degree;
    }

    for (int index = 0; index <= other_degree; ++index) {
        coefficients[index] += other.coefficients[index];
    }

    RecountDegree();

    return *this;
}

template<class T>
Polynomial<T>& Polynomial<T>::operator -=(const Polynomial<T>& other) {
    if (degree < other.degree) {
        coefficients.resize(other.degree + 1);
        degree = other.degree;
    }

    for (int index = 0; index <= other.degree; ++index) {
        coefficients[index] -= other.coefficients[index];
    }

    RecountDegree();

    return *this;
}

template<class T>
Polynomial<T>& Polynomial<T>::operator *=(const Polynomial<T>& other) {
    size_t my_degree = Degree();
    size_t other_degree = other.Degree();

    vector<T> temp_coefficients(degree + other_degree + 1);

    for(int index = 0; index <= my_degree; ++index) {
        for(int other_index = 0; other_index <= other_degree; ++other_index) {
            temp_coefficients[index + other_index] += coefficients[index] * other.coefficients[other_index];
        }
    }

    coefficients = temp_coefficients;
    degree += other_degree;

    return *this;
}

template<class T>
bool Polynomial<T>::operator <(const Polynomial<T>& other) const {
    size_t my_degree = Degree();
    size_t other_degree = other.Degree();

    if (my_degree != other_degree) {
        return degree < other_degree;
    }

    return coefficients < other.coefficients;
}

template<class T>
bool Polynomial<T>::operator >(const Polynomial<T>& other) const {
    return !(*this < other) && (*this != other);
}

template<class T>
bool Polynomial<T>::operator <=(const Polynomial<T>& other) const {
    return !(*this > other);
}

template<class T>
bool Polynomial<T>::operator >=(const Polynomial<T>& other) const {
    return !(*this < other);
}

template<class T>
const T& Polynomial<T>::operator[](size_t index) const {
    size_t my_degree = Degree();

    if (index > my_degree) {
        throw std::out_of_range("Out of range, object is constant");
    }
    return coefficients[index];
}

template<class T>
T& Polynomial<T>::operator[](size_t index) {
    size_t my_degree = Degree();

    if (index > my_degree) {
        degree = index;
        coefficients.resize(degree + 1);
    }
    return coefficients[index];
}

template<class T>
T Polynomial<T>::operator()(const T arg) const {
    T value = T();
    T arg_pow = 1;

    for (typename vector<T>::const_iterator iter = coefficients.begin(); iter != coefficients.end(); ++iter) {
        value += *iter * arg_pow;
        arg_pow *= arg;
    }

    return value;
}

template<class T>
void Polynomial<T>::Shift(size_t shift) {
    if (shift == 0) {
        return;
    }

    vector<T> temp(shift);
    for(int i = 0; i <= degree; ++i) {
        temp.push_back(coefficients[i]);
    }

    coefficients = temp;
    degree += shift;
}

template<class T>
void Polynomial<T>::RawDivide(const Polynomial<T>& rhs,
                              Polynomial<T>& quotient, Polynomial<T>& mod) const {

    size_t my_degree = Degree();
    size_t rhs_degree = rhs.Degree();

    if (rhs_degree == 0 && rhs[0] == 0) {
        throw std::overflow_error("Divide by zero");
    }

    if (my_degree < rhs_degree) {
        quotient = Polynomial<T>();
        mod = rhs;
        return;
    }

    mod = *this;
    while(mod.Degree() >= rhs_degree && !(mod[0] == 0 && mod.Degree() == 0)) {
        T coef = mod[mod.Degree()] / rhs[rhs_degree];
        if (coef == 0) {
            break;
        }
        int degree_diff = mod.Degree() - rhs_degree;
        Polynomial<T> temp(coef);
        temp.Shift(degree_diff);
        quotient += temp;
        mod -= temp * rhs;
    }
}

template<class T>
int Polynomial<T>::Degree() const {
    Polynomial<T> * non_const = const_cast<Polynomial<T>*>(this);
    non_const->RecountDegree();
    return degree;
}

template<class T>
typename vector<T>::iterator Polynomial<T>::begin() {
    return coefficients.begin();
}

template<class T>
typename vector<T>::const_iterator Polynomial<T>::begin() const {
    return coefficients.begin();
}

template<class T>
typename vector<T>::iterator Polynomial<T>::end() {
    return coefficients.end() - 1;
}

template<class T>
typename vector<T>::const_iterator Polynomial<T>::end() const {
    return coefficients.end() - 1;
}

template<class T>
void AddMonomial(T coef, int degree, std::ostream& stream, bool isFirst) {
    if (coef == T() && degree == 0 && isFirst) {
        stream << coef;
    }

    if (coef == T()) {
        return;
    }

    if (coef < T()) {
        stream << " - ";
    }

    if (coef > T() && !isFirst) {
        stream << " + ";
    }

    if (degree == 0) {
        stream << std::abs(coef);
        return;
    }

    if (coef != 1 && coef != -1) {
        stream << std::abs(coef);
    }

    stream << "x";
    if (degree != 1) {
        stream << "^" << degree;
    }
}

template<class T>
std::ostream& operator <<(std::ostream& stream, const Polynomial<T>& polynomial) {
    size_t my_degree = polynomial.Degree();
    AddMonomial(polynomial[my_degree], my_degree, stream, true);
    for (int index = my_degree - 1; index >= 0; --index) {
        AddMonomial(polynomial[index], index, stream, false);
    }

    return stream;
}
