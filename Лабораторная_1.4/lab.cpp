#include "lab.hpp"

#if !defined(__i386__) && !defined(__x86_64__) && !defined(_M_IX86) && !defined(_M_X64)
#error "Эта лабораторная использует Intel SSE и должна собираться для x86/x86_64."
#endif

#include <immintrin.h>

LabStatus multiply_by_constant_sse(
    const float* input,
    float constant,
    float* output,
    std::size_t size)
{
    if (size == 0) {
        return LabStatus::invalid_size;
    }
    if (input == nullptr || output == nullptr) {
        return LabStatus::null_pointer;
    }

    const __m128 constant_register = _mm_set1_ps(constant);
    std::size_t index = 0;

    for (; index + 4 <= size; index += 4) {
        const __m128 values = _mm_loadu_ps(input + index);
        _mm_storeu_ps(output + index, _mm_mul_ps(values, constant_register));
    }

    if (index < size) {
        alignas(16) float tail_input[4] = {};
        alignas(16) float tail_output[4] = {};
        const std::size_t tail_size = size - index;

        for (std::size_t lane = 0; lane < tail_size; ++lane) {
            tail_input[lane] = input[index + lane];
        }

        const __m128 result = _mm_mul_ps(_mm_load_ps(tail_input), constant_register);
        _mm_store_ps(tail_output, result);

        for (std::size_t lane = 0; lane < tail_size; ++lane) {
            output[index + lane] = tail_output[lane];
        }
    }

    return LabStatus::ok;
}

