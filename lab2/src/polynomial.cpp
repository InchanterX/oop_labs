#include "lab02/polynomial.hpp"

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <ostream>
#include <stdexcept>
#include <utility>

namespace lab02 {
namespace {

constexpr int kMaxIterations{200};

}  // namespace

void Polynomial::trim() {
    if (!coeffs_) {
        return;
    }
    std::int32_t length = degree_ + 1;
    std::int32_t pos = length - 1;
    while (pos >= 0 && coeffs_[pos] == 0) {
        --pos;
    }
    if (pos < 0) {
        delete[] coeffs_;
        coeffs_ = nullptr;
        degree_ = -1;
    } else if (pos == degree_) {
        return;
    } else {
        double* new_coeffs = new double[pos + 1];
        std::copy(coeffs_, coeffs_ + pos + 1, new_coeffs);
        delete[] coeffs_;
        coeffs_ = new_coeffs;
        degree_ = pos;
    }
}

Polynomial::Polynomial() : degree_(-1), coeffs_(nullptr) {}

Polynomial::Polynomial(const double* coeffs, std::int32_t degree) : degree_(degree), coeffs_(nullptr) {
    if (degree < 0 || !coeffs) {
        degree_ = -1;
    } else {
        coeffs_ = new double[degree + 1];
        std::copy(coeffs, coeffs + degree + 1, coeffs_);
        trim();
    }
}

Polynomial::Polynomial(const Polynomial& other) : degree_(other.degree_), coeffs_(nullptr) {
    if (other.coeffs_) {
        coeffs_ = new double[degree_ + 1];
        std::copy(other.coeffs_, other.coeffs_ + other.degree_ + 1, coeffs_);
    }
}

Polynomial::Polynomial(Polynomial&& other) noexcept : degree_(other.degree_), coeffs_(other.coeffs_) {
    other.coeffs_ = nullptr;
    other.degree_ = -1;
}

void Polynomial::swap(Polynomial& other) noexcept {
    std::swap(degree_, other.degree_);
    std::swap(coeffs_, other.coeffs_);
}

Polynomial& Polynomial::operator=(Polynomial other) {
    swap(other);
    return *this;
}

Polynomial::~Polynomial() {
    delete[] coeffs_;
}

std::int32_t Polynomial::degree() const {
    return degree_;
}

double Polynomial::coefficient(std::int32_t power) const {
    if (power < 0 || power > degree_) {
        return 0.0;
    }
    return coeffs_[power];
}

void Polynomial::add(const Polynomial& other) {
    if (!other.coeffs_) {
        return;
    }
    std::int32_t max_length = std::max(degree_, other.degree_) + 1;
    double* new_coeffs = new double[max_length];
    for (std::int32_t i = 0; i < max_length; ++i) {
        double el1{0.0};
        double el2{0.0};
        if (i <= degree_) {
            el1 = coeffs_[i];
        }
        if (i <= other.degree_) {
            el2 = other.coeffs_[i];
        }
        new_coeffs[i] = el1 + el2;
    }
    delete[] coeffs_;
    coeffs_ = new_coeffs;
    degree_ = max_length - 1;
    trim();
}

void Polynomial::mul(const Polynomial& other) {
    if (!coeffs_) {
        return;
    } else if (!other.coeffs_) {
        *this = Polynomial();
        return;
    }
    std::int32_t new_degree = degree_ + other.degree_;
    double* new_coeffs = new double[new_degree + 1]();
    for (std::int32_t i = 0; i <= degree_; ++i) {
        for (std::int32_t j = 0; j <= other.degree_; ++j) {
            new_coeffs[i + j] += coeffs_[i] * other.coeffs_[j];
        }
    }
    delete[] coeffs_;
    coeffs_ = new_coeffs;
    degree_ = new_degree;
    trim();
}

double Polynomial::evaluate(double x) const {
    double result{0.0};
    for (std::int32_t i = degree_; i >= 0; --i) {
        result = result * x + coeffs_[i];
    }
    return result;
}

void Polynomial::print(std::ostream& os) const {
    if (degree_ < 0) {
        os << 0;
        return;
    }
    bool first = true;
    for (std::int32_t i = 0; i <= degree_; ++i) {
        double c = coeffs_[i];
        if (c == 0.0) {
            continue;
        }
        if (first) {
            if (c < 0) {
                os << '-';
            }
        } else {
            if (c < 0) {
                os << " - ";
            } else {
                os << " + ";
            }
        }
        double abs_c = std::abs(c);
        if (abs_c != 1.0 || i == 0) {
            os << abs_c;
        }
        if (i >= 1) {
            os << 'x';
        }
        if (i >= 2) {
            os << '^' << i;
        }
        first = false;
    }
}

std::ostream& operator<<(std::ostream& os, const Polynomial& p) {
    p.print(os);
    return os;
}

double Polynomial::find_root(double a, double b) const {
    if (!std::isfinite(a) || !std::isfinite(b)) {
        throw std::invalid_argument("find_root a and b must be finite!");
    }
    if (a > b) {
        std::swap(a, b);
    }
    double f_a = evaluate(a);
    const double f_b = evaluate(b);
    if (f_a == 0.0) {
        return a;
    }
    if (f_b == 0.0) {
        return b;
    }
    if ((f_a < 0) == (f_b < 0)) {
        throw std::invalid_argument("find_root f(a) and f(b) must have different signs!");
    }
    for (int i = 0; i < kMaxIterations; ++i) {
        double m = a + (b - a) / 2;
        double f_m = evaluate(m);
        if (f_m == 0.0 || m == a || m == b) {
            return m;
        } else if ((f_m < 0) == (f_a < 0)) {
            a = m;
            f_a = f_m;
        } else {
            b = m;
        }
    }
    return a + (b - a) / 2;
}

}  // namespace lab02
