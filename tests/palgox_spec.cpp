#include <cmath>
#include <catch2/catch_test_macros.hpp>
#include "../src/palgox.h"

/*
 * PAlgoX_MatX unit tests
 */
TEST_CASE( "PAlgoX_MatX Constructor Tests", "[single-file]" ) {

    SECTION("Valid PAlgoX_MatX Constructor Test") {
        const std::vector<std::vector<int>> test_input_data = {
            {5, 3, 8, -2, 7},
            {-1, 9, 4, 6, 0},
            {2, 7, 3, -8, -5},
            {8, -2, 5, -3, 7}
        };
        palgox::palgox_matx* test_matx;
        CHECK_NOTHROW(test_matx = new palgox::palgox_matx(test_input_data));
        REQUIRE(test_matx->getNumRows() == 4);
        REQUIRE(test_matx->getNumCols() == 5);
        delete(test_matx);
    }

    SECTION("Invalid PAlgoX_MatX Constructor Test - Inconsistent Columns") {
        const std::vector<std::vector<int>> test_input_data = {
            {5, 3, 8, -2, 7},
            {-1, 9, 4, 6, 0},
            {2, 7, 3, -8},
            {8, -2, 5, -3, 7}
        };
        palgox::palgox_matx* test_matx;
        CHECK_THROWS(test_matx = new palgox::palgox_matx(test_input_data));
        delete(test_matx);
    }

    SECTION("Invalid PAlgoX_MatX Constructor Test - Empty Input Data") {
        const std::vector<std::vector<int>> test_input_data = {};
        palgox::palgox_matx* test_matx;
        CHECK_THROWS(test_matx = new palgox::palgox_matx(test_input_data));
        delete(test_matx);
    }
}

TEST_CASE("PAlgoX_MatX Add and Sub Tests", "[single-file]") {
    const std::vector<std::vector<int>> test_input_data_one = {
        {5, 3, 8},
        {-1, 9, 4},
    };
    const std::vector<std::vector<int>> test_input_data_two = {
        {5, 3, 8},
        {-1, 9, 4},
    };
    const std::vector<std::vector<int>> test_output_data_diffSize = {
        {10, 6, 16, -4, 14},
        {-2, 18, 8, 12, 0},
    };
    SECTION("Valid PAlgoX_MatX Add Test") {
        const std::vector<std::vector<int>> test_output_data_add = {
            {10, 6, 16},
            {-2, 18, 8},
        };
        auto* test_matx_one = new palgox::palgox_matx(test_input_data_one);
        auto* test_matx_two = new palgox::palgox_matx(test_input_data_two);
        auto* test_matx_output = new palgox::palgox_matx(test_output_data_add);
        CHECK_NOTHROW(test_matx_one->addMatx(test_matx_two));
        REQUIRE(test_matx_one->isEqual(test_matx_output));
        delete(test_matx_one);
        delete(test_matx_two);
        delete(test_matx_output);
    }

    SECTION("Invalid PAlgoX_MatX Add Test - Different sizes") {
        auto* test_matx_one = new palgox::palgox_matx(test_input_data_one);
        auto* test_matx_two = new palgox::palgox_matx(test_output_data_diffSize);
        CHECK_THROWS(test_matx_one->addMatx(test_matx_two));
        delete(test_matx_one);
        delete(test_matx_two);
    }

    SECTION("Valid PAlgoX_MatX Sub Test") {
        const std::vector<std::vector<int>> test_output_data_sub = {
            {0, 0, 0},
            {0, 0, 0},
        };
        auto* test_matx_one = new palgox::palgox_matx(test_input_data_one);
        auto* test_matx_two = new palgox::palgox_matx(test_input_data_two);
        auto* test_matx_output = new palgox::palgox_matx(test_output_data_sub);
        CHECK_NOTHROW(test_matx_one->subMatx(test_matx_two));
        REQUIRE(test_matx_one->isEqual(test_matx_output));
        delete(test_matx_one);
        delete(test_matx_two);
        delete(test_matx_output);
    }

    SECTION("Invalid PAlgoX_MatX Sub Test - Different sizes") {
        auto* test_matx_one = new palgox::palgox_matx(test_input_data_one);
        auto* test_matx_two = new palgox::palgox_matx(test_output_data_diffSize);
        CHECK_THROWS(test_matx_one->subMatx(test_matx_two));
        delete(test_matx_one);
        delete(test_matx_two);
    }
}

TEST_CASE("PAlgoX_MatX Transpose Tests", "[single-file]") {
    const std::vector<std::vector<int>> test_input_data_one = { // 2 x 2
        {5, 3},
        {-1, 9},
    };
    const std::vector<std::vector<int>> test_input_data_two = { // 2 x 3
        {5, 3, 8},
        {-1, 9, 4},
    };
    SECTION("Transpose n x n Size") {
        const std::vector<std::vector<int>> test_output_data = {
            {5, -1},
            {3, 9},
        };
        auto* test_matx = new palgox::palgox_matx(test_input_data_one);
        palgox::palgox_matx* transposed_matx;
        CHECK_NOTHROW(transposed_matx = test_matx->getTranspose());
        auto* expected_matx = new palgox::palgox_matx(test_output_data);
        REQUIRE(transposed_matx->isEqual(expected_matx));
        delete(test_matx);
        delete(transposed_matx);
        delete(expected_matx);

    }

    SECTION("Transpose m x n Size") {
        const std::vector<std::vector<int>> test_output_data = {
            {5, -1},
            {3, 9},
            {8, 4},
        };
        auto* test_matx = new palgox::palgox_matx(test_input_data_two);
        palgox::palgox_matx* transposed_matx;
        CHECK_NOTHROW(transposed_matx = test_matx->getTranspose());
        auto* expected_matx = new palgox::palgox_matx(test_output_data);
        REQUIRE(transposed_matx->isEqual(expected_matx));
        delete(test_matx);
        delete(transposed_matx);
        delete(expected_matx);
    }
}

TEST_CASE("PAlgoX_MatX Multiplication Tests", "[single-file]") {
    const std::vector<std::vector<int>> test_input_data_one = { // 2 x 2
        {5, 3},
        {-1, 9},
    };
    const std::vector<std::vector<int>> test_input_data_two = { // 2 x 3
        {5, 3, 8},
        {-1, 9, 4},
    };
    SECTION("Multiplication valid dimensions") {
        const std::vector<std::vector<int>> test_expected_data = { // 2 x 3
            {22, 42, 52},
            {-14, 78, 28},
        };
        const auto* test_matx_one = new palgox::palgox_matx(test_input_data_one);
        const auto* test_matx_two = new palgox::palgox_matx(test_input_data_two);
        palgox::palgox_matx* output_matx;
        CHECK_NOTHROW(output_matx = test_matx_one->mulMatx(test_matx_two));
        const auto* expected_matx = new palgox::palgox_matx(test_expected_data);
        REQUIRE(output_matx->isEqual(expected_matx));
        delete(test_matx_one);
        delete(test_matx_two);
        delete(output_matx);
        delete(expected_matx);
    }

    SECTION("Multiplication invalid dimensions") {
        const auto* test_matx_one = new palgox::palgox_matx(test_input_data_one);
        const auto* test_matx_two = new palgox::palgox_matx(test_input_data_two);
        CHECK_THROWS(test_matx_two->mulMatx(test_matx_one));
        delete(test_matx_one);
        delete(test_matx_two);
    }
}

TEST_CASE("PAlgoX_MatX andMap and orMap Tests", "[single-file]") {
    const std::vector<std::vector<int>> test_input_data = {
        {5, 3},
        {-1, 9},
    };

    SECTION("andMap True Case") {
        const auto* test_matx = new palgox::palgox_matx(test_input_data);
        REQUIRE(test_matx->andMap([](const int a) {return a > -5;}));
        delete(test_matx);
    }

    SECTION("andMap False Case") {
        const auto* test_matx = new palgox::palgox_matx(test_input_data);
        REQUIRE_FALSE(test_matx->andMap([](const int a) {return a > 0;}));
        delete(test_matx);
    }

    SECTION("orMap True Case") {
        const auto* test_matx = new palgox::palgox_matx(test_input_data);
        REQUIRE(test_matx->orMap([](const int a) {return a > 3;}));
        delete(test_matx);
    }

    SECTION("orMap False Case") {
        const auto* test_matx = new palgox::palgox_matx(test_input_data);
        REQUIRE_FALSE(test_matx->orMap([](const int a) {return a < -10;}));
        delete(test_matx);
    }
}

/*
 * PAlgoX_VecX unit tests
 */