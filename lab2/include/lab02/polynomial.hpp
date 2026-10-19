#pragma once

#include <cstdint>
#include <ostream>

class Polynomial {
    std::int32_t degree_;
    double* coeffs_;

    void trim();

    void swap(Polynomial& other) noexcept;

public:
    // base constructor
    Polynomial();

    // constructor from array
    Polynomial(const double* coeffs, std::int32_t degree);

    // copy constructor
    Polynomial(const Polynomial& other);

    // move constructor
    Polynomial(Polynomial&& other) noexcept;

    // copy and swap
    Polynomial& operator=(Polynomial other);

    // destructor
    ~Polynomial();

    void add(const Polynomial& other);

    void mul(const Polynomial& other);

    double evaluate(double x) const;

    void print(std::ostream& os) const;

    double find_root(double a, double b) const;
};

std::ostream& operator<<(std::ostream& os, const Polynomial& p);
