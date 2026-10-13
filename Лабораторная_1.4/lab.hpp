#pragma once

#include <cstddef>

enum class LabStatus : int {
    ok = 0,
    null_pointer = 1,
    invalid_size = 2,
};

LabStatus multiply_by_constant_sse(
    const float* input,
    float constant,
    float* output,
    std::size_t size);

