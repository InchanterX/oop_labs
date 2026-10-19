#include "lab02/polynomial.hpp"

#include <cmath>
#include <sstream>
#include <stdexcept>
#include <string>
#include <utility>

#include <gtest/gtest.h>

static std::string to_str(const Polynomial& p) {
    std::ostringstream out;
    p.print(out);
    return out.str();
}

TEST(PolynomialTest, DefaultIsZero) {
    const Polynomial p;
    EXPECT_EQ(to_str(p), "0");
}

TEST(PolynomialTest, ConstructCommon) {
    const double coeffs[]{1.0, 2.0, 3.0};
    const Polynomial p(coeffs, 2);
    EXPECT_EQ(to_str(p), "1 + 2x + 3x^2");
}

TEST(PolynomialTest, ConstructConstant) {
    const double coeffs[]{5.0};
    const Polynomial p(coeffs, 0);
    EXPECT_EQ(to_str(p), "5");
}

TEST(PolynomialTest, ConstructTrailingZeros) {
    const double coeffs[]{1.0, 0.0, 0.0};
    const Polynomial p(coeffs, 2);
    EXPECT_EQ(to_str(p), "1");
}

TEST(PolynomialTest, ConstructAllZeros) {
    const double coeffs[]{0.0, 0.0, 0.0};
    const Polynomial p(coeffs, 2);
    EXPECT_EQ(to_str(p), "0");
}

TEST(PolynomialTest_Fail, ConstructNull) {
    const Polynomial p(nullptr, 3);
    EXPECT_EQ(to_str(p), "0");
}

TEST(PolynomialTest_Fail, ConstructNegativeDegree) {
    const double coeffs[]{1.0};
    const Polynomial p(coeffs, -5);
    EXPECT_EQ(to_str(p), "0");
}

TEST(PolynomialTest, CopyIsDeep) {
    const double coeffs[]{1.0, 2.0};
    Polynomial a(coeffs, 1);
    Polynomial b(a);
    b.add(a);
    EXPECT_EQ(to_str(a), "1 + 2x");
    EXPECT_EQ(to_str(b), "2 + 4x");
}

TEST(PolynomialTest, CopyZero) {
    const Polynomial a;
    const Polynomial b(a);
    EXPECT_EQ(to_str(b), "0");
}

TEST(PolynomialTest, MoveCommon) {
    const double coeffs[]{1.0, 2.0};
    Polynomial a(coeffs, 1);
    const Polynomial b(std::move(a));
    EXPECT_EQ(to_str(b), "1 + 2x");
    EXPECT_EQ(to_str(a), "0");
}

TEST(PolynomialTest, AssignCopy) {
    const double coeffs[]{1.0, 2.0};
    const Polynomial a(coeffs, 1);
    Polynomial b;
    b = a;
    EXPECT_EQ(to_str(b), "1 + 2x");
    EXPECT_EQ(to_str(a), "1 + 2x");
}

TEST(PolynomialTest, AssignMove) {
    const double coeffs[]{1.0, 2.0};
    Polynomial a(coeffs, 1);
    Polynomial b;
    b = std::move(a);
    EXPECT_EQ(to_str(b), "1 + 2x");
    EXPECT_EQ(to_str(a), "0");
}

TEST(PolynomialTest, AssignSelf) {
    const double coeffs[]{1.0, 2.0};
    Polynomial a(coeffs, 1);
    Polynomial& ref = a;
    a = ref;
    EXPECT_EQ(to_str(a), "1 + 2x");
}

TEST(PolynomialTest, AddCommon) {
    const double c1[]{1.0, 2.0};
    const double c2[]{0.0, 1.0, 1.0};
    Polynomial a(c1, 1);
    const Polynomial b(c2, 2);
    a.add(b);
    EXPECT_EQ(to_str(a), "1 + 3x + x^2");
}

TEST(PolynomialTest, AddToZero) {
    const double coeffs[]{1.0, 2.0};
    const Polynomial a(coeffs, 1);
    Polynomial zero;
    zero.add(a);
    EXPECT_EQ(to_str(zero), "1 + 2x");
}

TEST(PolynomialTest, AddZero) {
    const double coeffs[]{1.0, 2.0};
    Polynomial a(coeffs, 1);
    a.add(Polynomial());
    EXPECT_EQ(to_str(a), "1 + 2x");
}

TEST(PolynomialTest, AddCancelLeading) {
    const double c1[]{1.0, 0.0, 1.0};
    const double c2[]{0.0, 0.0, -1.0};
    Polynomial a(c1, 2);
    a.add(Polynomial(c2, 2));
    EXPECT_EQ(to_str(a), "1");
}

TEST(PolynomialTest, AddCancelAll) {
    const double c1[]{1.0, 2.0};
    const double c2[]{-1.0, -2.0};
    Polynomial a(c1, 1);
    a.add(Polynomial(c2, 1));
    EXPECT_EQ(to_str(a), "0");
}

TEST(PolynomialTest, AddSelf) {
    const double coeffs[]{1.0, 2.0};
    Polynomial a(coeffs, 1);
    a.add(a);
    EXPECT_EQ(to_str(a), "2 + 4x");
}

TEST(PolynomialTest, MulCommon) {
    const double c1[]{1.0, 2.0};
    const double c2[]{0.0, 1.0, 1.0};
    Polynomial a(c1, 1);
    a.mul(Polynomial(c2, 2));
    EXPECT_EQ(to_str(a), "x + 3x^2 + 2x^3");
}

TEST(PolynomialTest, MulByZero) {
    const double coeffs[]{1.0, 2.0};
    Polynomial a(coeffs, 1);
    a.mul(Polynomial());
    EXPECT_EQ(to_str(a), "0");
}

TEST(PolynomialTest, MulZero) {
    const double coeffs[]{1.0, 2.0};
    Polynomial zero;
    zero.mul(Polynomial(coeffs, 1));
    EXPECT_EQ(to_str(zero), "0");
}

TEST(PolynomialTest, MulSelf) {
    const double coeffs[]{1.0, 1.0};
    Polynomial a(coeffs, 1);
    a.mul(a);
    EXPECT_EQ(to_str(a), "1 + 2x + x^2");
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

TEST(PolynomialTest, PrintNegative) {
    const double coeffs[]{-1.0, 0.0, -1.0};
    const Polynomial p(coeffs, 2);
    EXPECT_EQ(to_str(p), "-1 - x^2");
}

TEST(PolynomialTest, PrintFractional) {
    const double coeffs[]{0.0, 2.5};
    const Polynomial p(coeffs, 1);
    EXPECT_EQ(to_str(p), "2.5x");
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

TEST(PolynomialTest_Fail, FindRootSameSigns) {
    const double coeffs[]{-2.0, 0.0, 1.0};
    const Polynomial p(coeffs, 2);
    EXPECT_THROW(p.find_root(2.0, 3.0), std::invalid_argument);
}

TEST(PolynomialTest_Fail, FindRootConstant) {
    const double coeffs[]{5.0};
    const Polynomial p(coeffs, 0);
    EXPECT_THROW(p.find_root(-1.0, 1.0), std::invalid_argument);
}

TEST(PolynomialTest_Fail, FindRootInfiniteBound) {
    const double coeffs[]{-2.0, 0.0, 1.0};
    const Polynomial p(coeffs, 2);
    EXPECT_THROW(p.find_root(0.0, INFINITY), std::invalid_argument);
}
