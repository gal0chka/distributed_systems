#pragma once

#include <cstddef>

enum class LabStatus : int {
    ok = 0,
    null_pointer = 1,
    invalid_size = 2,
};

LabStatus sum_array_sse(const float* input, float& sum, std::size_t size);

