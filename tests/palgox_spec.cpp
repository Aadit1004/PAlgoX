#include <catch2/catch_test_macros.hpp>
#include "../src/palgox.h"


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
    }

    SECTION("Invalid PAlgoX_MatX Constructor Test - Empty Input Data") {
        const std::vector<std::vector<int>> test_input_data = {};
        palgox::palgox_matx* test_matx;
        CHECK_THROWS(test_matx = new palgox::palgox_matx(test_input_data));
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
    }

    SECTION("Invalid PAlgoX_MatX Add Test - Different sizes") {
        auto* test_matx_one = new palgox::palgox_matx(test_input_data_one);
        auto* test_matx_two = new palgox::palgox_matx(test_output_data_diffSize);
        CHECK_THROWS(test_matx_one->addMatx(test_matx_two));
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
    }

    SECTION("Invalid PAlgoX_MatX Sub Test - Different sizes") {
        auto* test_matx_one = new palgox::palgox_matx(test_input_data_one);
        auto* test_matx_two = new palgox::palgox_matx(test_output_data_diffSize);
        CHECK_THROWS(test_matx_one->subMatx(test_matx_two));
    }
}

TEST_CASE("PAlgoX_MatX Transpose and Multiplication Tests", "[single-file]") {
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
            {5, -1, 2},
            {3, 9, 7},
            {8, 4, 3},
        };
        auto* test_matx = new palgox::palgox_matx(test_input_data_one);
        palgox::palgox_matx* transposed_matx;
        CHECK_NOTHROW(transposed_matx = test_matx->getTranspose());
        auto* expected_matx = new palgox::palgox_matx(test_output_data);
        REQUIRE(transposed_matx->isEqual(expected_matx));
    }

    SECTION("Transpose m x n Size") {
        const std::vector<std::vector<int>> test_output_data = {
            {5, -1, 2},
            {3, 9, 7},
            {8, 4, 3},
            {2, 1, 2},
        };
        auto* test_matx = new palgox::palgox_matx(test_input_data_two);
        palgox::palgox_matx* transposed_matx;
        CHECK_NOTHROW(transposed_matx = test_matx->getTranspose());
        auto* expected_matx = new palgox::palgox_matx(test_output_data);
        REQUIRE(transposed_matx->isEqual(expected_matx));
    }

    SECTION("Multiplication valid dimensions") {
        // to implement
    }

    SECTION("Multiplication invalid dimensions") {
        // To fix
        auto* test_matx_one = new palgox::palgox_matx(test_input_data_one);
        auto* test_matx_two = new palgox::palgox_matx(test_input_data_two);
        CHECK_THROWS(test_matx_two->mulMatx(test_matx_one));
    }
}