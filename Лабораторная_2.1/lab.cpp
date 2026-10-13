#include "lab.hpp"

#if !defined(__i386__) && !defined(__x86_64__) && !defined(_M_IX86) && !defined(_M_X64)
#error "Эта лабораторная использует Intel SSE и должна собираться для x86/x86_64."
#endif

#include <immintrin.h>

LabStatus sum_array_sse(const float* input, float& sum, std::size_t size)
{
    if (size == 0) {
        return LabStatus::invalid_size;
    }
    if (input == nullptr) {
        return LabStatus::null_pointer;
    }

    __m128 accumulator = _mm_setzero_ps();
    std::size_t index = 0;

    for (; index + 4 <= size; index += 4) {
        accumulator = _mm_add_ps(accumulator, _mm_loadu_ps(input + index));
    }

    if (index < size) {
        alignas(16) float tail[4] = {};
        const std::size_t tail_size = size - index;
        for (std::size_t lane = 0; lane < tail_size; ++lane) {
            tail[lane] = input[index + lane];
        }
        accumulator = _mm_add_ps(accumulator, _mm_load_ps(tail));
    }

    accumulator = _mm_hadd_ps(accumulator, accumulator);
    accumulator = _mm_hadd_ps(accumulator, accumulator);
    _mm_store_ss(&sum, accumulator);
    return LabStatus::ok;
}

