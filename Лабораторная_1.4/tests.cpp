#include "lab.hpp"

#include <cmath>
#include <cstddef>
#include <iostream>
#include <vector>

bool almost_equal(float left, float right)
{
    const float scale = std::fmax(1.0F, std::fmax(std::fabs(left), std::fabs(right)));
    return std::fabs(left - right) <= 1.0e-5F * scale;
}

int main()
{
    for (const std::size_t size : {1U, 2U, 3U, 4U, 5U, 7U, 8U, 9U, 100U}) {
        std::vector<float> input(size);
        std::vector<float> output(size);
        for (std::size_t i = 0; i < size; ++i) {
            input[i] = static_cast<float>(i) * 1.25F - 3.5F;
        }
        if (multiply_by_constant_sse(input.data(), 2.5F, output.data(), size) != LabStatus::ok) {
            return 1;
        }
        for (std::size_t i = 0; i < size; ++i) {
            if (!almost_equal(output[i], input[i] * 2.5F)) {
                return 1;
            }
        }
    }

    float value = 0.0F;
    if (multiply_by_constant_sse(nullptr, 2.0F, &value, 1) != LabStatus::null_pointer ||
        multiply_by_constant_sse(&value, 2.0F, nullptr, 1) != LabStatus::null_pointer ||
        multiply_by_constant_sse(&value, 2.0F, &value, 0) != LabStatus::invalid_size) {
        return 1;
    }

    std::cout << "Тесты лабораторной 1.4 пройдены\n";
    return 0;
}

