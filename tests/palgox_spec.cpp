#include <cmath>
#include <catch2/catch_test_macros.hpp>
#include "../src/palgox.h"

/*
 * PAlgoX_VecX unit tests
 */
TEST_CASE( "PAlgoX_VecX Constructor Tests", "[single-file]" ) {

    SECTION("Valid PAlgoX_VecX Constructor 1 Test") {
        const std::vector<int> test_input_data = {5, 3, 8, -2, 7};
        const palgox::palgox_vecx* test_vecx = nullptr;
        CHECK_NOTHROW(test_vecx = new palgox::palgox_vecx(test_input_data));
        REQUIRE(test_vecx->getNumElems() == 5);
        delete test_vecx;
    }

    SECTION("Invalid PAlgoX_VecX Constructor 1 Test - Empty Input Data") {
        const std::vector<int> test_input_data = {};
        const palgox::palgox_vecx* test_vecx = nullptr;
        CHECK_THROWS(test_vecx = new palgox::palgox_vecx(test_input_data));
        delete test_vecx;
    }

    SECTION("Valid PAlgoX_VecX Constructor 2 Test") {
        int size = 5;
        const palgox::palgox_vecx* test_vecx = nullptr;
        const std::vector<int> expected_data = {1, 3, 5, 7, 9};
        auto* expected_vecx = new palgox::palgox_vecx(expected_data);
        CHECK_NOTHROW(test_vecx = new palgox::palgox_vecx(size, [](const int num){return (2 * num) + 1;}));
        REQUIRE(test_vecx->getNumElems() == 5);
        REQUIRE(test_vecx->isEqual(expected_vecx));
        delete test_vecx;
        delete expected_vecx;
    }

    SECTION("Invalid PAlgoX_VecX Constructor 2 Test - Invalid Size Parameter") {
        constexpr int size = -3;
        const palgox::palgox_vecx* test_vecx = nullptr;
        CHECK_THROWS(test_vecx = new palgox::palgox_vecx(size, [](const int num){return (2 * num) + 1;}));
        delete test_vecx;
    }
}

TEST_CASE("PAlgoX_VecX applyOperation/ addVecx/ subVecx Tests", "[single-file]") {
    const std::vector<int> test_input_data_one = {1, -2, 3, -4, 5, -6};
    const std::vector<int> test_input_data_two = {-7, 8, -9, 10, -11, 12};
    const std::vector<int> test_invalid_data = {1, 2, 3};

    SECTION("Valid PAlgoX_VecX applyOperation Test") {
        auto* test_vecx = new palgox::palgox_vecx(test_input_data_one);
        const std::vector<int> expected_data = {1, 2, 3, 4, 5, 6};
        const auto* expected_vecx = new palgox::palgox_vecx(expected_data);
        CHECK_NOTHROW(test_vecx->applyOperation([](const int num){return std::abs(num);}));
        REQUIRE(test_vecx->isEqual(expected_vecx));
        delete test_vecx;
        delete expected_vecx;
    }

    SECTION("Valid PAlgoX_VecX addVecx Test") {
        auto* test_vecx_one = new palgox::palgox_vecx(test_input_data_one);
        auto* test_vecx_two = new palgox::palgox_vecx(test_input_data_two);
        const std::vector<int> expected_data = {-6, 6, -6, 6, -6, 6};
        const auto* expected_vecx = new palgox::palgox_vecx(expected_data);
        CHECK_NOTHROW(test_vecx_one->addVecx(test_vecx_two));
        REQUIRE(test_vecx_one->isEqual(expected_vecx));
        delete test_vecx_one;
        delete test_vecx_two;
        delete expected_vecx;
    }

    SECTION("Invalid PAlgoX_VecX addVecx Test") {
        auto* test_vecx_one = new palgox::palgox_vecx(test_input_data_one);
        auto* test_vecx_invalid = new palgox::palgox_vecx(test_invalid_data);
        CHECK_THROWS(test_vecx_one->addVecx(test_vecx_invalid));
        delete test_vecx_one;
        delete test_vecx_invalid;
    }

    SECTION("Valid PAlgoX_VecX subVecx Test") {
        auto* test_vecx_one = new palgox::palgox_vecx(test_input_data_one);
        auto* test_vecx_two = new palgox::palgox_vecx(test_input_data_two);
        const std::vector<int> expected_data = {8, -10, 12, -14, 16, -18};
        const auto* expected_vecx = new palgox::palgox_vecx(expected_data);
        CHECK_NOTHROW(test_vecx_one->subVecx(test_vecx_two));
        REQUIRE(test_vecx_one->isEqual(expected_vecx));
        delete test_vecx_one;
        delete test_vecx_two;
        delete expected_vecx;
    }

    SECTION("Invalid PAlgoX_VecX subVecx Test") {
        auto* test_vecx_one = new palgox::palgox_vecx(test_input_data_one);
        auto* test_vecx_invalid = new palgox::palgox_vecx(test_invalid_data);
        CHECK_THROWS(test_vecx_one->subVecx(test_vecx_invalid));
        delete test_vecx_one;
        delete test_vecx_invalid;
    }

}

TEST_CASE("PAlgoX_VecX search/ quickSort/ mergeSort Tests", "[single-file]") {
    const std::vector<int> test_input_data = {-6, 44, 728, -3, -17, 131};

    SECTION("Valid PAlgoX_VecX search Test - value exists") {
        const auto* test_vecx = new palgox::palgox_vecx(test_input_data);
        int result;
        CHECK_NOTHROW(result = test_vecx->search(-3));
        REQUIRE(result == 3);
        delete test_vecx;
    }

    SECTION("Valid PAlgoX_VecX search Test - value doesn't exist") {
        const auto* test_vecx = new palgox::palgox_vecx(test_input_data);
        int result;
        CHECK_NOTHROW(result = test_vecx->search(10));
        REQUIRE(result == -1);
        delete test_vecx;
    }

    SECTION("Valid PAlgoX_VecX quickSort Test") {
        auto* test_vecx = new palgox::palgox_vecx(test_input_data);
        auto* expected_vecx = new palgox::palgox_vecx({-17, -6, -3, 44, 131, 728});
        CHECK_NOTHROW(test_vecx->quickSort());
        REQUIRE(test_vecx->isEqual(expected_vecx));
        delete test_vecx;
        delete expected_vecx;
    }

    SECTION("Valid PAlgoX_VecX mergeSort Test") {
        auto* test_vecx = new palgox::palgox_vecx(test_input_data);
        auto* expected_vecx = new palgox::palgox_vecx({-17, -6, -3, 44, 131, 728});
        CHECK_NOTHROW(test_vecx->mergeSort());
        REQUIRE(test_vecx->isEqual(expected_vecx));
        delete test_vecx;
        delete expected_vecx;
    }

}

TEST_CASE("PAlgoX_VecX filter/ andMap/ orMap Tests", "[single-file]") {
    const std::vector<int> test_input_data = {1, 2, 3, 4, 5};

    SECTION("Valid PAlgoX_VecX filter Test - value exists") {
        const auto* test_vecx = new palgox::palgox_vecx(test_input_data);
        const auto* expected_vecx = new palgox::palgox_vecx({3, 4, 5});
        const palgox::palgox_vecx* output_vecx = nullptr;
        CHECK_NOTHROW(output_vecx = test_vecx->filter([](const int num){return num > 2;}));
        REQUIRE(output_vecx->getNumElems() == 3);
        REQUIRE(output_vecx->isEqual(expected_vecx));
        delete test_vecx;
        delete expected_vecx;
        delete output_vecx;
    }

    SECTION("Invalid PAlgoX_VecX filter Test") {
        const auto* test_vecx = new palgox::palgox_vecx(test_input_data);
        CHECK_THROWS(test_vecx->filter([](const int num){return num > 6;}));
        delete test_vecx;
    }

    SECTION("Valid PAlgoX_VecX andMap True Case") {
        const auto* test_vecx = new palgox::palgox_vecx(test_input_data);
        REQUIRE(test_vecx->andMap([](const int num){return num > 0;}));
        delete test_vecx;
    }

    SECTION("Valid PAlgoX_VecX andMap False Case") {
        const auto* test_vecx = new palgox::palgox_vecx(test_input_data);
        REQUIRE_FALSE(test_vecx->andMap([](const int num){return num > 4;}));
        delete test_vecx;
    }

    SECTION("Valid PAlgoX_VecX orMap True Case") {
        const auto* test_vecx = new palgox::palgox_vecx(test_input_data);
        REQUIRE(test_vecx->orMap([](const int num){return num > 4;}));
        delete test_vecx;
    }

    SECTION("Valid PAlgoX_VecX orMap False Case") {
        const auto* test_vecx = new palgox::palgox_vecx(test_input_data);
        REQUIRE_FALSE(test_vecx->orMap([](const int num){return num < 0;}));
        delete test_vecx;
    }
}

TEST_CASE("PAlgoX_VecX reduceLeft/ reduceRight/ findMin/ findMax Tests", "[single-file]") {
    const std::vector test_input_data = {1, 2, 3, 4, 5};

    SECTION("Valid PAlgoX_VecX reduceLeft Test") {
        const auto* test_vecx = new palgox::palgox_vecx(test_input_data);
        int result;
        CHECK_NOTHROW(result = test_vecx->reduceLeft(10, [](const int a, const int b){return a + b;}));
        REQUIRE(result == 25);
        delete test_vecx;
    }

    SECTION("Valid PAlgoX_VecX reduceRight Test") {
        const auto* test_vecx = new palgox::palgox_vecx(test_input_data);
        int result;
        CHECK_NOTHROW(result = test_vecx->reduceRight(400, [](const int a, const int b){return a / b;}));
        REQUIRE(result == 3);
        delete test_vecx;
    }

    SECTION("Valid PAlgoX_VecX findMin Test") {
        const auto* test_vecx = new palgox::palgox_vecx(test_input_data);
        int result;
        CHECK_NOTHROW(result = test_vecx->findMin());
        REQUIRE(result == 1);
        delete test_vecx;
    }

    SECTION("Valid PAlgoX_VecX findMax Test") {
        const auto* test_vecx = new palgox::palgox_vecx(test_input_data);
        int result;
        CHECK_NOTHROW(result = test_vecx->findMax());
        REQUIRE(result == 5);
        delete test_vecx;
    }
}

TEST_CASE("PAlgoX_VecX prefixSum/ suffixSum Tests", "[single-file]") {
    const std::vector test_input_data = {1, 2, 3, 4, 5};

    SECTION("Valid PAlgoX_VecX prefixSum Test") {
        const auto* test_vecx = new palgox::palgox_vecx(test_input_data);
        const auto* expected_vecx = new palgox::palgox_vecx({1, 3, 6, 10, 15});
        const palgox::palgox_vecx* output_vecx = nullptr;
        CHECK_NOTHROW(output_vecx = test_vecx->prefixSum());
        REQUIRE(output_vecx->getNumElems() == 5);
        REQUIRE(output_vecx->isEqual(expected_vecx));
        delete test_vecx;
        delete expected_vecx;
        delete output_vecx;
    }

    SECTION("Valid PAlgoX_VecX suffixSum Test") {
        const auto* test_vecx = new palgox::palgox_vecx(test_input_data);
        const auto* expected_vecx = new palgox::palgox_vecx({15, 14, 12, 9, 5});
        const palgox::palgox_vecx* output_vecx = nullptr;
        CHECK_NOTHROW(output_vecx = test_vecx->suffixSum());
        REQUIRE(output_vecx->getNumElems() == 5);
        REQUIRE(output_vecx->isEqual(expected_vecx));
        delete test_vecx;
        delete expected_vecx;
        delete output_vecx;
    }
}

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
        delete test_matx;
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
        delete test_matx;
    }

    SECTION("Invalid PAlgoX_MatX Constructor Test - Empty Input Data") {
        const std::vector<std::vector<int>> test_input_data = {};
        palgox::palgox_matx* test_matx;
        CHECK_THROWS(test_matx = new palgox::palgox_matx(test_input_data));
        delete test_matx;
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
        delete test_matx_one;
        delete test_matx_two;
        delete test_matx_output;
    }

    SECTION("Invalid PAlgoX_MatX Add Test - Different sizes") {
        auto* test_matx_one = new palgox::palgox_matx(test_input_data_one);
        auto* test_matx_two = new palgox::palgox_matx(test_output_data_diffSize);
        CHECK_THROWS(test_matx_one->addMatx(test_matx_two));
        delete test_matx_one;
        delete test_matx_two;
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
        delete test_matx_one;
        delete test_matx_two;
        delete test_matx_output;
    }

    SECTION("Invalid PAlgoX_MatX Sub Test - Different sizes") {
        auto* test_matx_one = new palgox::palgox_matx(test_input_data_one);
        auto* test_matx_two = new palgox::palgox_matx(test_output_data_diffSize);
        CHECK_THROWS(test_matx_one->subMatx(test_matx_two));
        delete test_matx_one;
        delete test_matx_two;
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
        delete test_matx;
        delete transposed_matx;
        delete expected_matx;

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
        delete test_matx;
        delete transposed_matx;
        delete expected_matx;
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
        const palgox::palgox_matx* output_matx = nullptr;
        CHECK_NOTHROW(output_matx = test_matx_one->mulMatx(test_matx_two));
        const auto* expected_matx = new palgox::palgox_matx(test_expected_data);
        REQUIRE(output_matx->isEqual(expected_matx));
        delete test_matx_one;
        delete test_matx_two;
        delete output_matx;
        delete expected_matx;
    }

    SECTION("Multiplication invalid dimensions") {
        const auto* test_matx_one = new palgox::palgox_matx(test_input_data_one);
        const auto* test_matx_two = new palgox::palgox_matx(test_input_data_two);
        CHECK_THROWS(test_matx_two->mulMatx(test_matx_one));
        delete test_matx_one;
        delete test_matx_two;
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
        delete test_matx;
    }

    SECTION("andMap False Case") {
        const auto* test_matx = new palgox::palgox_matx(test_input_data);
        REQUIRE_FALSE(test_matx->andMap([](const int a) {return a > 0;}));
        delete test_matx;
    }

    SECTION("orMap True Case") {
        const auto* test_matx = new palgox::palgox_matx(test_input_data);
        REQUIRE(test_matx->orMap([](const int a) {return a > 3;}));
        delete test_matx;
    }

    SECTION("orMap False Case") {
        const auto* test_matx = new palgox::palgox_matx(test_input_data);
        REQUIRE_FALSE(test_matx->orMap([](const int a) {return a < -10;}));
        delete test_matx;
    }
}

/*
 * PAlgoX_GraphX unit tests
 */
TEST_CASE( "PAlgoX_GraphX Constructor Tests", "[single-file]" ) {

    SECTION("Valid PAlgoX_GraphX Constructor Test") {
        palgox::palgox_graphx* test_graph;
        CHECK_NOTHROW(test_graph = new palgox::palgox_graphx(5));
        REQUIRE(test_graph->getNumVertices() == 5);
        delete test_graph;
    }

    SECTION("Invalid PAlgoX_GraphX Constructor Test - Nonpositive Param") {
        palgox::palgox_graphx* test_graph;
        CHECK_THROWS(test_graph = new palgox::palgox_graphx(-10));
    }
}

TEST_CASE( "PAlgoX_GraphX isEqual Tests", "[single-file]" ) {

    SECTION("Valid PAlgoX_GraphX isEqual Test - True Case") {
        auto* test_graph = new palgox::palgox_graphx(4);
        auto* test_graph_two = new palgox::palgox_graphx(4);
        test_graph->addEdge(1, 2);
        test_graph->addEdge(0, 3);
        test_graph->addEdge(3, 2);
        test_graph->addEdge(2, 2);
        test_graph_two->addEdge(1, 2);
        test_graph_two->addEdge(0, 3);
        test_graph_two->addEdge(3, 2);
        test_graph_two->addEdge(2, 2);
        REQUIRE(test_graph->isEqual(test_graph_two));
        delete test_graph;
        delete test_graph_two;
    }

    SECTION("Valid PAlgoX_GraphX isEqual Test - False Case") {
        auto* test_graph = new palgox::palgox_graphx(4);
        auto* test_graph_two = new palgox::palgox_graphx(4);
        test_graph->addEdge(1, 2);
        test_graph->addEdge(0, 3);
        test_graph->addEdge(3, 2);
        test_graph->addEdge(2, 2);
        test_graph_two->addEdge(1, 2);
        test_graph_two->addEdge(1, 3);
        test_graph_two->addEdge(3, 2);
        test_graph_two->addEdge(2, 2);
        REQUIRE_FALSE(test_graph->isEqual(test_graph_two));
        delete test_graph;
        delete test_graph_two;
    }
}

TEST_CASE( "PAlgoX_GraphX hasCyle Tests", "[single-file]" ) {

    SECTION("Valid PAlgoX_GraphX hasCyle Test - True Case") {
        auto* test_graph = new palgox::palgox_graphx(4);
        test_graph->addEdge(0, 1);
        test_graph->addEdge(1, 2);
        test_graph->addEdge(2, 0);
        test_graph->addEdge(2, 3);
        REQUIRE(test_graph->hasCycle());
        delete test_graph;
    }

    SECTION("Valid PAlgoX_GraphX hasCyle Test - False Case") {
        auto* test_graph = new palgox::palgox_graphx(5);
        test_graph->addEdge(0, 1);
        test_graph->addEdge(1, 2);
        test_graph->addEdge(2, 3);
        test_graph->addEdge(3, 4);
        REQUIRE_FALSE(test_graph->hasCycle());
        delete test_graph;
    }

    SECTION("Valid PAlgoX_GraphX hasCyle Test - No Edges") {
        auto* test_graph = new palgox::palgox_graphx(4);
        REQUIRE_FALSE(test_graph->hasCycle());
        delete test_graph;
    }
}

/*
 * PAlgoX_MathX unit tests
 */
TEST_CASE( "PAlgoX_MathX All Util Methods Tests", "[single-file]" ) {

    SECTION("PAlgoX_MathX computePowers Test") {
        std::vector<int> bases = {2, 3, 4};
        std::vector<int> exponents = {3, 2, 1};
        std::vector<int> expected_results = {8, 9, 4};
        std::vector<int> results = palgox::palgox_mathx::computePowers(bases, exponents);
        REQUIRE(results.size() == expected_results.size());
        for (size_t i = 0; i < results.size(); ++i) {
            REQUIRE(results[i] == expected_results[i]);
        }
    }

    SECTION("PAlgoX_MathX factorial Test") {
        REQUIRE(palgox::palgox_mathx::factorial(0) == 1);
        REQUIRE(palgox::palgox_mathx::factorial(1) == 1);
        REQUIRE(palgox::palgox_mathx::factorial(5) == 120);
        REQUIRE(palgox::palgox_mathx::factorial(10) == 3628800);
        REQUIRE(palgox::palgox_mathx::factorial(12) == 479001600);
    }

    SECTION("PAlgoX_MathX generatePrimes Test") {
        // up to 10
        std::vector<bool> expected_primes_10 = {false, false, true, true, false, true, false, true, false, false, false};
        std::vector<bool> primes_10 = palgox::palgox_mathx::generatePrimes(10);
        REQUIRE(primes_10.size() == expected_primes_10.size());
        for (size_t i = 0; i < primes_10.size(); ++i) {
            REQUIRE(primes_10[i] == expected_primes_10[i]);
        }
        // up to 100 (checks random)
        std::vector<bool> primes_100 = palgox::palgox_mathx::generatePrimes(100);
        REQUIRE(primes_100[2] == true);
        REQUIRE(primes_100[3] == true);
        REQUIRE(primes_100[4] == false);
        REQUIRE(primes_100[59] == true);
        REQUIRE(primes_100[83] == true);
        REQUIRE(primes_100[97] == true);
        REQUIRE(primes_100[100] == false);
    }
}