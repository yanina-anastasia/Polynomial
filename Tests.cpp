#include <vector>

#include "Polynomial.h"

#define BOOST_TEST_MODULE MyTest
#include <boost\test\unit_test.hpp>

Polynomial<int> generate_polynom(int degree) {
    vector<int> seq;
    for (int i = 0; i < degree + 1; ++i) {
        seq.push_back(i + 1);
    }
    Polynomial<int> polynom(seq.begin(), seq.end());
    return polynom;
}


BOOST_AUTO_TEST_CASE(test_data) {
    Polynomial<int> polynomial = generate_polynom(5);
    BOOST_CHECK_EQUAL(polynomial[2], 4);

    polynomial[2] = 10;

    vector<int> req_seq;
    req_seq.push_back(1);
    req_seq.push_back(2);
    req_seq.push_back(3);
    req_seq.push_back(10);
    req_seq.push_back(5);
    req_seq.push_back(6);
    Polynomial<int> req_polynomial(req_seq.begin(), req_seq.end());
    BOOST_CHECK_EQUAL(polynomial, req_polynomial);
}

BOOST_AUTO_TEST_CASE(test_comparison) {
    Polynomial<int> polynomial_first = generate_polynom(1);
    Polynomial<int> polynomial_second = generate_polynom(2);
    BOOST_CHECK_LT(polynomial_first, polynomial_second);
    BOOST_CHECK_GT(polynomial_second, polynomial_first);
    BOOST_REQUIRE(polynomial_first != polynomial_second);
    polynomial_first[0] = 3;
    polynomial_first[1] = 2;
    polynomial_first[2] = 1;
    BOOST_CHECK_EQUAL(polynomial_first, polynomial_second);
}

BOOST_AUTO_TEST_CASE(test_polynom_value) {
    Polynomial<int> polynom = generate_polynom(2);
    BOOST_CHECK_EQUAL(polynom(3), 18);
    BOOST_CHECK_EQUAL(polynom(0), 3);
    polynom[0] = 5;
    BOOST_CHECK_EQUAL(polynom(0), 5);
    BOOST_CHECK_EQUAL(polynom(5), 40);
}

BOOST_AUTO_TEST_CASE(test_degree) {
    Polynomial<int> polynom = generate_polynom(5);
    BOOST_CHECK_EQUAL(polynom.Degree(), 5);
    polynom[6] = 6;
    polynom[7] = 7;
    BOOST_CHECK_EQUAL(polynom.Degree(), 7);
}

BOOST_AUTO_TEST_CASE(test_begin_iter) {
    Polynomial<int> polynom = generate_polynom(3);
    BOOST_CHECK_EQUAL(*polynom.begin(), 4);
    polynom[0] = 10;
    BOOST_CHECK_EQUAL(*polynom.begin(), 10);
}

BOOST_AUTO_TEST_CASE(test_end_iter) {
    Polynomial<int> polynom = generate_polynom(3);
    BOOST_CHECK_EQUAL(*polynom.end(), 1);
    polynom[3] = 10;
    BOOST_CHECK_EQUAL(*polynom.end(), 10);
}

BOOST_AUTO_TEST_CASE(test_resize_polynomial) {
    Polynomial<int> polynom = generate_polynom(3);
    BOOST_CHECK_EQUAL(polynom.Degree(), 3);
    polynom[5] = 100;
    BOOST_CHECK_EQUAL(*polynom.end(), 100);
    BOOST_CHECK_EQUAL(*(polynom.end() - 1), 0);
}

BOOST_AUTO_TEST_CASE(test_sum) {
    Polynomial<int> polynom = generate_polynom(3);
    Polynomial<int> summand = generate_polynom(0);
    Polynomial<int> sum = generate_polynom(3);
    sum[0] = polynom[0] + summand[0];
    polynom += summand;
    BOOST_CHECK_EQUAL(polynom, sum);
}

BOOST_AUTO_TEST_CASE(test_outer_sum) {
    Polynomial<int> polynom = generate_polynom(3);
    Polynomial<int> summand = generate_polynom(0);
    Polynomial<int> sum = generate_polynom(3);
    sum[0] = polynom[0] + summand[0];
    BOOST_CHECK_EQUAL(polynom + summand, sum);
}

BOOST_AUTO_TEST_CASE(test_degree_sum) {
    Polynomial<int> polynom = generate_polynom(3);
    Polynomial<int> summand = generate_polynom(3);
    summand[3] = -summand[3];
    summand[2] = -summand[2];
    summand[1] = -summand[1];
    Polynomial<int> sum_req = generate_polynom(0);
    sum_req[0] = polynom[0] + summand[0];
    Polynomial<int> sum = polynom + summand;
    BOOST_CHECK_EQUAL(sum, sum_req);
    BOOST_CHECK_EQUAL(sum.Degree(), 0);
}

BOOST_AUTO_TEST_CASE(test_subtraction) {
    Polynomial<int> polynom = generate_polynom(3);
    Polynomial<int> subtr = generate_polynom(0);
    Polynomial<int> diff = generate_polynom(3);
    diff[0] = polynom[0] - subtr[0];
    polynom -= subtr;
    BOOST_CHECK_EQUAL(polynom, diff);
}

BOOST_AUTO_TEST_CASE(test_outer_subtraction) {
    Polynomial<int> polynom = generate_polynom(3);
    Polynomial<int> subtr = generate_polynom(0);
    Polynomial<int> diff = generate_polynom(3);
    diff[0] = polynom[0] - subtr[0];
    BOOST_CHECK_EQUAL(polynom - subtr, diff);
}

BOOST_AUTO_TEST_CASE(test_degree_substraction) {
    Polynomial<int> polynom = generate_polynom(3);
    Polynomial<int> subtr = generate_polynom(3);
    subtr[0] = subtr[0] - 1;
    Polynomial<int> diff_req = Polynomial<int>(1);
    Polynomial<int> diff = polynom - subtr;
    BOOST_CHECK_EQUAL(diff, diff_req);
    BOOST_CHECK_EQUAL(diff.Degree(), 0);
}

BOOST_AUTO_TEST_CASE(test_mul_number) {
    Polynomial<int> polynom = generate_polynom(3);
    int multiplier = 3;
    Polynomial<int> product = generate_polynom(3);
    for (int i = 0; i <= product.Degree(); ++i) {
        product[i] *= multiplier;
    }
    polynom *= multiplier;
    BOOST_CHECK_EQUAL(polynom, product);
}

BOOST_AUTO_TEST_CASE(test_outer_mul_number) {
    Polynomial<int> polynom = generate_polynom(3);
    int multiplier = 3;
    Polynomial<int> product = generate_polynom(3);
    for (int i = 0; i <= product.Degree(); ++i) {
        product[i] *= multiplier;
    }
    BOOST_CHECK_EQUAL(polynom * multiplier, product);
}

BOOST_AUTO_TEST_CASE(test_mul_polynom) {
    Polynomial<int> polynom = generate_polynom(3);
    Polynomial<int> multiplier = generate_polynom(1);
    Polynomial<int> product = generate_polynom(4);
    product[0] = 8;
    product[1] = 10;
    product[2] = 7;
    product[3] = 4;
    product[4] = 1;
    polynom *= multiplier;
    BOOST_CHECK_EQUAL(polynom, product);
}

BOOST_AUTO_TEST_CASE(test_outer_mul_polynom) {
    Polynomial<int> polynom = generate_polynom(3);
    Polynomial<int> multiplier = generate_polynom(1);
    Polynomial<int> product = generate_polynom(4);
    product[0] = 8;
    product[1] = 10;
    product[2] = 7;
    product[3] = 4;
    product[4] = 1;
    BOOST_CHECK_EQUAL(polynom * multiplier, product);
}

BOOST_AUTO_TEST_CASE(test_outer_mul_extra) {
    Polynomial<int> polynom = generate_polynom(2);
    Polynomial<int> multiplier = generate_polynom(2);
    Polynomial<int> product = generate_polynom(4);
    product[0] = 9;
    product[1] = 12;
    product[2] = 10;
    product[3] = 4;
    product[4] = 1;
    BOOST_CHECK_EQUAL(polynom * multiplier, product);
}

BOOST_AUTO_TEST_CASE(stress_mult_test) {
    Polynomial<int> polynom = generate_polynom(1000);
    Polynomial<int> multiplier = generate_polynom(1000);
    Polynomial<int> product = generate_polynom(2000);
    product = polynom * multiplier;
    BOOST_CHECK_EQUAL(product[2000], 1);
    BOOST_CHECK_EQUAL(product[1999], 4);
    BOOST_CHECK_EQUAL(product[1998], 10);
    BOOST_CHECK_EQUAL(product[1997], 20);
    BOOST_CHECK_EQUAL(product[1996], 35);
    BOOST_CHECK_EQUAL(product[1995], 56);
    BOOST_CHECK_EQUAL(product[1994], 84);
    BOOST_CHECK_EQUAL(product[2], 2999998);
    BOOST_CHECK_EQUAL(product[1], 2002000);
    BOOST_CHECK_EQUAL(product[0], 1002001);
}

BOOST_AUTO_TEST_CASE(test_int_divide) {
    Polynomial<int> dividend = Polynomial<int>(-1);
    dividend[1] = 0;
    dividend[2] = 1;
    Polynomial<int> diviser = Polynomial<int>(1);
    diviser[1] = 1;
    Polynomial<int> quotient = Polynomial<int>(-1);
    quotient[1] = 1;
    BOOST_CHECK_EQUAL(dividend / diviser, quotient);
}

BOOST_AUTO_TEST_CASE(test_double_number_divide) {
    Polynomial<double> dividend = Polynomial<double>(1);
    dividend[1] = 1;
    double diviser = 2;
    Polynomial<double> quotient = Polynomial<double>(0.5);
    quotient[1] = 0.5;
    BOOST_CHECK_EQUAL(dividend / diviser, quotient);
    BOOST_CHECK_EQUAL(dividend % diviser, 0);
}

BOOST_AUTO_TEST_CASE(test_double_polynomial_divide) {
    Polynomial<double> dividend = Polynomial<double>(2);
    dividend[1] = -1;
    dividend[2] = 1;
    Polynomial<double> diviser = Polynomial<double>(-3);
    diviser[1] = 1;
    Polynomial<double> quotient = Polynomial<double>(2);
    quotient[1] = 1;
    BOOST_CHECK_EQUAL(dividend / diviser, quotient);
    BOOST_CHECK_EQUAL(dividend % diviser, 8);
}

BOOST_AUTO_TEST_CASE(test_double_polynomial_divide_extra) {
    Polynomial<double> dividend = Polynomial<double>(1);
    dividend[1] = -2;
    dividend[2] = 3.5;
    Polynomial<double> diviser = Polynomial<double>(5.5);
    diviser[1] = 1;
    Polynomial<double> quotient = Polynomial<double>(-21.25);
    quotient[1] = 3.5;
    BOOST_CHECK_EQUAL(dividend / diviser, quotient);
    BOOST_CHECK_EQUAL(dividend % diviser, 117.875);
}

BOOST_AUTO_TEST_CASE(test_divide_number_by_polynomial) {
    double dividend = 5;
    Polynomial<double> diviser = Polynomial<double>(5);
    diviser[1] = -2;
    diviser[2] = 1;
    BOOST_CHECK_EQUAL(dividend / diviser, 0);
    BOOST_CHECK_EQUAL(dividend % diviser, diviser);
}

BOOST_AUTO_TEST_CASE(test_simple_divide) {
    Polynomial<double> dividend = Polynomial<double>(5);
    dividend[1] = -2;
    dividend[2] = 1;
    BOOST_CHECK_EQUAL(dividend / 1, dividend);
    BOOST_CHECK_EQUAL(dividend % 1, 0);
}

BOOST_AUTO_TEST_CASE(stress_divide_test) {
    Polynomial<int> dividend = generate_polynom(1000);
    Polynomial<int> diviser = generate_polynom(10);
    Polynomial<int> quotient = dividend / diviser;
    BOOST_CHECK_EQUAL(quotient.Degree(), 990);
    BOOST_CHECK_EQUAL(quotient[990], 1);
    BOOST_CHECK_EQUAL(quotient[979], 12);
    BOOST_CHECK_EQUAL(quotient[978], -11);
}

BOOST_AUTO_TEST_CASE(test_divide_by_zero) {
    Polynomial<double> dividend = Polynomial<double>(5);
    dividend[1] = 1;
    BOOST_CHECK_THROW(dividend / 0, std::overflow_error);
    BOOST_CHECK_THROW(dividend % 0, std::overflow_error);
}

BOOST_AUTO_TEST_CASE(test_gcd) {
    Polynomial<double> polynom_first = Polynomial<double>(-1);
    polynom_first[1] = 0;
    polynom_first[2] = 1;
    Polynomial<double> polynom_second = Polynomial<double>(1);
    polynom_second[1] = 1;
    Polynomial<double> required_polynomial = Polynomial<double>(1);
    required_polynomial[1] = 1;
    BOOST_CHECK_EQUAL((polynom_first, polynom_second), required_polynomial);
}

BOOST_AUTO_TEST_CASE(test_simple_gcd) {
    Polynomial<double> polynom = Polynomial<double>(-1);
    polynom[1] = 0;
    polynom[2] = 1;
    BOOST_CHECK_EQUAL((polynom, 1), 1);
}

BOOST_AUTO_TEST_CASE(test_simple_gcd_extra) {
    Polynomial<double> polynom = Polynomial<double>(-5);
    polynom[1] = 25;
    polynom[2] = 5;
    BOOST_CHECK_EQUAL((5, polynom), 5);
}

BOOST_AUTO_TEST_CASE(test_gcd_extra) {
    Polynomial<double> polynom_first = Polynomial<double>(-5);
    polynom_first[1] = 2;
    Polynomial<double> polynom_second = Polynomial<double>(1);
    polynom_second[1] = 1;
    BOOST_CHECK_EQUAL((polynom_first, polynom_second), 3.5);
}

BOOST_AUTO_TEST_CASE(test_strange) {
    Polynomial<string> polynom_first = Polynomial<string>("One ");
    polynom_first[1] = "Two ";
    Polynomial<string> polynom_second = Polynomial<string>("Three ");
    BOOST_CHECK_EQUAL(polynom_first[0], "One ");
    BOOST_CHECK_EQUAL(polynom_first[1], "Two ");
    BOOST_CHECK_EQUAL(polynom_second[0], "Three ");
    BOOST_REQUIRE(polynom_first != polynom_second);
    BOOST_REQUIRE(polynom_first > polynom_second);
    polynom_second[1] = "Seven hundred ";
    BOOST_CHECK_EQUAL(polynom_second[1], "Seven hundred ");
    BOOST_REQUIRE(polynom_first < polynom_second);
    polynom_first += polynom_second;
    BOOST_CHECK_EQUAL(polynom_first[0], "One Three ");
}
