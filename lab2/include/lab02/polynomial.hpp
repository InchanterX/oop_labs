#pragma once

#include <cstdint>
#include <iosfwd>

namespace lab02 {

class Polynomial {
public:
    Polynomial();

    Polynomial(const double* coeffs, std::int32_t degree);

    Polynomial(const Polynomial& other);

    Polynomial(Polynomial&& other) noexcept;

    Polynomial& operator=(Polynomial other);

    ~Polynomial();

    std::int32_t degree() const;

    double coefficient(std::int32_t power) const;

    void add(const Polynomial& other);

    void mul(const Polynomial& other);

    double evaluate(double x) const;

    void print(std::ostream& os) const;

    double find_root(double a, double b) const;

private:
    void trim();

    void swap(Polynomial& other) noexcept;

    std::int32_t degree_;
    double* coeffs_;
};

std::ostream& operator<<(std::ostream& os, const Polynomial& p);

}  // namespace lab02
