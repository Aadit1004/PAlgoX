#include <catch2/catch_test_macros.hpp>
#include "../src/palgox.h"


TEST_CASE( "Matrix Constructor Tests", "[single-file]" ) {

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

TEST_CASE("Matrix Add and Sub Tests", "[single-file]") {
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