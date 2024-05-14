## **Documentation**
Documentation for all methods for the library. Currently supporting Integer data type.

## PAlgoX_MatX Class
Matrix Class for PAlgoX

### palgox::palgox_matx Constructor 

Parameters:
- input_data: 2-dimensional, non-empty vector of integers.

Throws Exception: ***Yes***

Example:
```cpp
int main() {
	const std::vector<std::vector<int>> test_input_data = {
            {5, 3, 8, -2, 7},
            {-1, 9, 4, 6, 0},
            {2, 7, 3, -8, -5},
            {8, -2, 5, -3, 7}
        };
        auto* test_matx = new palgox::palgox_matx(test_input_data);
}
```

### palgox::palgox_matx isEqual()

Parameters:
- other_matx: a palgox_matx to compare to *this* palgox_matx if all elements are equal.

Throws Exception: ***No***


Example:
```cpp
int main() {
	const std::vector<std::vector<int>> test_input_data_one = {
        {5, 3, 8},
        {-1, 9, 4},
    };
    const std::vector<std::vector<int>> test_input_data_two = {
        {5, 3, 8},
        {-1, 9, 4},
    };
    auto* test_matx_one = new palgox::palgox_matx(test_input_data_one);
    auto* test_matx_two = new palgox::palgox_matx(test_input_data_two);
    std::cout << test_matx_one->isEqual(test_matx_two) << std::endl // prints true
}
```