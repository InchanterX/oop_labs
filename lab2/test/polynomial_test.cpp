#include "lab02/polynomial.hpp"

#include <cmath>
#include <cstdint>
#include <limits>
#include <sstream>
#include <stdexcept>
#include <string>
#include <utility>

#include <gtest/gtest.h>

namespace lab02 {
namespace {

std::string ToStr(const Polynomial& p) {
    std::ostringstream out;
    p.print(out);
    return out.str();
}

void ExpectCoefficients(const Polynomial& p, const double* expected, std::int32_t size) {
    ASSERT_EQ(p.degree(), size - 1);
    for (std::int32_t power = 0; power < size; ++power) {
        EXPECT_DOUBLE_EQ(p.coefficient(power), expected[power]) << "power " << power;
    }
}

TEST(PolynomialTest, DefaultIsZero) {
    const Polynomial p;
    ExpectCoefficients(p, nullptr, 0);
}

TEST(PolynomialTest, ConstructCommon) {
    const double coeffs[]{1.0, 2.0, 3.0};
    const Polynomial p(coeffs, 2);
    const double expected[]{1.0, 2.0, 3.0};
    ExpectCoefficients(p, expected, 3);
}

TEST(PolynomialTest, ConstructConstant) {
    const double coeffs[]{5.0};
    const Polynomial p(coeffs, 0);
    const double expected[]{5.0};
    ExpectCoefficients(p, expected, 1);
}

TEST(PolynomialTest, ConstructTrailingZeros) {
    const double coeffs[]{1.0, 0.0, 0.0};
    const Polynomial p(coeffs, 2);
    const double expected[]{1.0};
    ExpectCoefficients(p, expected, 1);
}

TEST(PolynomialTest, ConstructAllZeros) {
    const double coeffs[]{0.0, 0.0, 0.0};
    const Polynomial p(coeffs, 2);
    ExpectCoefficients(p, nullptr, 0);
}

TEST(PolynomialTest_Fail, ConstructNull) {
    const Polynomial p(nullptr, 3);
    ExpectCoefficients(p, nullptr, 0);
}

TEST(PolynomialTest_Fail, ConstructNegativeDegree) {
    const double coeffs[]{1.0};
    const Polynomial p(coeffs, -5);
    ExpectCoefficients(p, nullptr, 0);
}

TEST(PolynomialTest, CoefficientOutOfRangeIsZero) {
    const double coeffs[]{1.0, 2.0};
    const Polynomial p(coeffs, 1);
    EXPECT_DOUBLE_EQ(p.coefficient(-1), 0.0);
    EXPECT_DOUBLE_EQ(p.coefficient(2), 0.0);
    EXPECT_DOUBLE_EQ(Polynomial().coefficient(0), 0.0);
}

TEST(PolynomialTest, CopyIsDeep) {
    const double coeffs[]{1.0, 2.0};
    Polynomial a(coeffs, 1);
    Polynomial b(a);
    b.add(a);
    const double expected_a[]{1.0, 2.0};
    const double expected_b[]{2.0, 4.0};
    ExpectCoefficients(a, expected_a, 2);
    ExpectCoefficients(b, expected_b, 2);
}

TEST(PolynomialTest, CopyZero) {
    const Polynomial a;
    const Polynomial b(a);
    ExpectCoefficients(b, nullptr, 0);
}

TEST(PolynomialTest, MoveCommon) {
    const double coeffs[]{1.0, 2.0};
    Polynomial a(coeffs, 1);
    const Polynomial b(std::move(a));
    const double expected[]{1.0, 2.0};
    ExpectCoefficients(b, expected, 2);
    ExpectCoefficients(a, nullptr, 0);
}

TEST(PolynomialTest, AssignCopy) {
    const double coeffs[]{1.0, 2.0};
    const Polynomial a(coeffs, 1);
    Polynomial b;
    b = a;
    const double expected[]{1.0, 2.0};
    ExpectCoefficients(b, expected, 2);
    ExpectCoefficients(a, expected, 2);
}

TEST(PolynomialTest, AssignMove) {
    const double coeffs[]{1.0, 2.0};
    Polynomial a(coeffs, 1);
    Polynomial b;
    b = std::move(a);
    const double expected[]{1.0, 2.0};
    ExpectCoefficients(b, expected, 2);
    ExpectCoefficients(a, nullptr, 0);
}

TEST(PolynomialTest, AssignSelf) {
    const double coeffs[]{1.0, 2.0};
    Polynomial a(coeffs, 1);
    Polynomial& ref = a;
    a = ref;
    const double expected[]{1.0, 2.0};
    ExpectCoefficients(a, expected, 2);
}

TEST(PolynomialTest, AddCommon) {
    const double c1[]{1.0, 2.0};
    const double c2[]{0.0, 1.0, 1.0};
    Polynomial a(c1, 1);
    const Polynomial b(c2, 2);
    a.add(b);
    const double expected[]{1.0, 3.0, 1.0};
    ExpectCoefficients(a, expected, 3);
}

TEST(PolynomialTest, AddToZero) {
    const double coeffs[]{1.0, 2.0};
    const Polynomial a(coeffs, 1);
    Polynomial zero;
    zero.add(a);
    const double expected[]{1.0, 2.0};
    ExpectCoefficients(zero, expected, 2);
}

TEST(PolynomialTest, AddZero) {
    const double coeffs[]{1.0, 2.0};
    Polynomial a(coeffs, 1);
    a.add(Polynomial());
    const double expected[]{1.0, 2.0};
    ExpectCoefficients(a, expected, 2);
}

TEST(PolynomialTest, AddCancelLeading) {
    const double c1[]{1.0, 0.0, 1.0};
    const double c2[]{0.0, 0.0, -1.0};
    Polynomial a(c1, 2);
    a.add(Polynomial(c2, 2));
    const double expected[]{1.0};
    ExpectCoefficients(a, expected, 1);
}

TEST(PolynomialTest, AddCancelAll) {
    const double c1[]{1.0, 2.0};
    const double c2[]{-1.0, -2.0};
    Polynomial a(c1, 1);
    a.add(Polynomial(c2, 1));
    ExpectCoefficients(a, nullptr, 0);
}

TEST(PolynomialTest, AddSelf) {
    const double coeffs[]{1.0, 2.0};
    Polynomial a(coeffs, 1);
    a.add(a);
    const double expected[]{2.0, 4.0};
    ExpectCoefficients(a, expected, 2);
}

TEST(PolynomialTest, MulCommon) {
    const double c1[]{1.0, 2.0};
    const double c2[]{0.0, 1.0, 1.0};
    Polynomial a(c1, 1);
    a.mul(Polynomial(c2, 2));
    const double expected[]{0.0, 1.0, 3.0, 2.0};
    ExpectCoefficients(a, expected, 4);
}

TEST(PolynomialTest, MulByZero) {
    const double coeffs[]{1.0, 2.0};
    Polynomial a(coeffs, 1);
    a.mul(Polynomial());
    ExpectCoefficients(a, nullptr, 0);
}

TEST(PolynomialTest, MulZero) {
    const double coeffs[]{1.0, 2.0};
    Polynomial zero;
    zero.mul(Polynomial(coeffs, 1));
    ExpectCoefficients(zero, nullptr, 0);
}

TEST(PolynomialTest, MulSelf) {
    const double coeffs[]{1.0, 1.0};
    Polynomial a(coeffs, 1);
    a.mul(a);
    const double expected[]{1.0, 2.0, 1.0};
    ExpectCoefficients(a, expected, 3);
}

TEST(PolynomialTest, EvaluateCommon) {
    const double coeffs[]{1.0, 3.0, 1.0};
    const Polynomial p(coeffs, 2);
    EXPECT_DOUBLE_EQ(p.evaluate(2.0), 11.0);
}

TEST(PolynomialTest, EvaluateAtZero) {
    const double coeffs[]{7.0, 3.0, 1.0};
    const Polynomial p(coeffs, 2);
    EXPECT_DOUBLE_EQ(p.evaluate(0.0), 7.0);
}

TEST(PolynomialTest, EvaluateZero) {
    const Polynomial p;
    EXPECT_DOUBLE_EQ(p.evaluate(42.0), 0.0);
}

TEST(PolynomialTest, PrintZero) {
    const Polynomial p;
    EXPECT_EQ(ToStr(p), "0");
}

TEST(PolynomialTest, PrintCommon) {
    const double coeffs[]{1.0, 2.0, 3.0};
    const Polynomial p(coeffs, 2);
    EXPECT_EQ(ToStr(p), "1 + 2x + 3x^2");
}

TEST(PolynomialTest, PrintNegative) {
    const double coeffs[]{-1.0, 0.0, -1.0};
    const Polynomial p(coeffs, 2);
    EXPECT_EQ(ToStr(p), "-1 - x^2");
}

TEST(PolynomialTest, PrintFractional) {
    const double coeffs[]{0.0, 2.5};
    const Polynomial p(coeffs, 1);
    EXPECT_EQ(ToStr(p), "2.5x");
}

TEST(PolynomialTest, PrintOperator) {
    const double coeffs[]{0.0, 1.0};
    const Polynomial p(coeffs, 1);
    std::ostringstream out;
    out << p;
    EXPECT_EQ(out.str(), "x");
}

TEST(PolynomialTest, FindRootCommon) {
    const double coeffs[]{-2.0, 0.0, 1.0};
    const Polynomial p(coeffs, 2);
    const double root = p.find_root(1.0, 2.0);
    EXPECT_NEAR(root, std::sqrt(2.0), 1e-9);
    EXPECT_LT(std::abs(p.evaluate(root)), 1e-9);
}

TEST(PolynomialTest, FindRootReversedBounds) {
    const double coeffs[]{-2.0, 0.0, 1.0};
    const Polynomial p(coeffs, 2);
    EXPECT_NEAR(p.find_root(2.0, 1.0), std::sqrt(2.0), 1e-9);
}

TEST(PolynomialTest, FindRootAtBound) {
    const double coeffs[]{-1.0, 1.0};
    const Polynomial p(coeffs, 1);
    EXPECT_DOUBLE_EQ(p.find_root(1.0, 3.0), 1.0);
}

TEST(PolynomialTest_Throw, FindRootSameSigns) {
    const double coeffs[]{-2.0, 0.0, 1.0};
    const Polynomial p(coeffs, 2);
    EXPECT_THROW(p.find_root(2.0, 3.0), std::invalid_argument);
}

TEST(PolynomialTest_Throw, FindRootConstant) {
    const double coeffs[]{5.0};
    const Polynomial p(coeffs, 0);
    EXPECT_THROW(p.find_root(-1.0, 1.0), std::invalid_argument);
}

TEST(PolynomialTest_Throw, FindRootInfiniteBound) {
    const double coeffs[]{-2.0, 0.0, 1.0};
    const Polynomial p(coeffs, 2);
    EXPECT_THROW(p.find_root(0.0, std::numeric_limits<double>::infinity()), std::invalid_argument);
}

TEST(PolynomialTest_Throw, FindRootNanBound) {
    const double coeffs[]{-2.0, 0.0, 1.0};
    const Polynomial p(coeffs, 2);
    EXPECT_THROW(p.find_root(std::numeric_limits<double>::quiet_NaN(), 2.0), std::invalid_argument);
}

}  // namespace
}  // namespace lab02
