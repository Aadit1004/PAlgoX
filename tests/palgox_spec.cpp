#include <catch2/catch_test_macros.hpp>
#include "../src/palgox.h"


TEST_CASE( "Matrix Constructor Tests", "[single-file]" ) {

    SECTION("Valid PAlgoX_MatX Constructor Test")
    {
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

    SECTION("Invalid PAlgoX_MatX Constructor Test - Inconsistent Columns")
    {
        const std::vector<std::vector<int>> test_input_data = {
            {5, 3, 8, -2, 7},
            {-1, 9, 4, 6, 0},
            {2, 7, 3, -8},
            {8, -2, 5, -3, 7}
        };
        palgox::palgox_matx* test_matx;
        CHECK_THROWS(test_matx = new palgox::palgox_matx(test_input_data));
    }

    SECTION("Invalid PAlgoX_MatX Constructor Test - Empty Input Data")
    {
        const std::vector<std::vector<int>> test_input_data = {};
        palgox::palgox_matx* test_matx;
        CHECK_THROWS(test_matx = new palgox::palgox_matx(test_input_data));
    }
}