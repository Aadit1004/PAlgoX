## **PAlgoX_MatX Documentation**
Documentation for the PAlgoX MatX class methods. Currently supporting Integer data type.

### palgox::palgox_matx Constructor

Parameters:
- input_data: 2-dimensional, non-empty vector of integers.

Throws Exception: ***Yes***

Return Value: palgox_matx Object Instance

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

Return Value: Boolean

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

### palgox::palgox_matx addMatx()

Parameters:
- other_matx: a palgox_matx to add to *this* palgox_matx

Throws Exception: ***Yes***

Return Value: None

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
    test_matx_one->addMatx(test_matx_two);
    
    // test_matx_one values:
    // 10 6 16
    // -2 18 8
}
```

### palgox::palgox_matx subMatx()

Parameters:
- other_matx: a palgox_matx to subtract to *this* palgox_matx

Throws Exception: ***Yes***

Return Value: None

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
    test_matx_one->subMatx(test_matx_two);
    
    // test_matx_one values:
    // 0 0 0
    // 0 0 0
}
```

### palgox::palgox_matx getTranspose()

Parameters: None

Throws Exception: ***No***

Return Value: a palgox_matx with the transposed value of *this* palgox_matx

Example:
```cpp
int main() {
    const std::vector<std::vector<int>> test_input_data = { // 2 x 3
        {5, 3, 8},
        {-1, 9, 4},
    };
    auto* test_matx_input = new palgox::palgox_matx(test_input_data);
    auto* test_matx_transpose = test_matx_input->getTranspose();
    
    // test_matx_transpose values:
    // 5 -1
    // 3 9
    // 8 4
}
```

### palgox::palgox_matx mulMatx()

Parameters:
- other_matx: a palgox_matx to multiply to *this* palgox_matx

Throws Exception: ***Yes***

Return Value: a palgox_matx with the product of the two matrices

Example:
```cpp
int main() {
    const std::vector<std::vector<int>> test_input_data_one = { // 2 x 2
        {5, 3},
        {-1, 9},
    };
    const std::vector<std::vector<int>> test_input_data_two = { // 2 x 3
        {5, 3, 8},
        {-1, 9, 4},
    };
    const auto* test_matx_one = new palgox::palgox_matx(test_input_data_one);
    const auto* test_matx_two = new palgox::palgox_matx(test_input_data_two);
    palgox::palgox_matx* output_matx = test_matx_one->mulMatx(test_matx_two);
    
    // output_matx values:
    // 22 42 52
    // -14 78 28
}
```

### palgox::palgox_matx andMap()

Parameters:
- operation: a boolean function that takes in an integer

Throws Exception: ***No***

Return Value: True if the *AND* operation on all elements is true

Example:
```cpp
int main() {
    const std::vector<std::vector<int>> test_input_data = {
        {5, 3},
        {-1, 9},
    };
    const auto* test_matx = new palgox::palgox_matx(test_input_data);
    bool result = test_matx->andMap([](const int a) {return a > -5;});
    std::cout << result << std::endl; // prints true
}
```

### palgox::palgox_matx orMap()

Parameters:
- operation: a boolean function that takes in an integer

Throws Exception: ***No***

Return Value: True if the *OR* operation on all elements is true

Example:
```cpp
int main() {
    const std::vector<std::vector<int>> test_input_data = {
        {5, 3},
        {-1, 9},
    };
    const auto* test_matx = new palgox::palgox_matx(test_input_data);
    bool result = test_matx->orMap([](const int a) {return a > 3;});
    std::cout << result << std::endl; // prints true
}
```