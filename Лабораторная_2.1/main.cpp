#include "input_reader.hpp"
#include "lab.hpp"

#include <iostream>
#include <string>
#include <vector>

int main(int argc, char* argv[])
{
    if (argc < 2 || argc > 3) {
        std::cerr << "Использование: " << argv[0]
                  << " <input_one_array.txt> [result.txt]\n";
        return 1;
    }

    try {
        const std::vector<float> input = read_input(argv[1]);
        float sum = 0.0F;

        const LabStatus status = sum_array_sse(input.data(), sum, input.size());
        if (status != LabStatus::ok) {
            std::cerr << "Ошибка функции, статус: " << static_cast<int>(status) << '\n';
            return static_cast<int>(status);
        }

        const std::string output_path = argc == 3 ? argv[2] : "lab_2_1_result.txt";
        write_result(output_path, sum);
        std::cout << "Лабораторная 2.1 выполнена. Сумма: " << format_float(sum)
                  << ", результат: " << output_path << '\n';
        return 0;
    } catch (const std::exception& error) {
        std::cerr << "Ошибка: " << error.what() << '\n';
        return 1;
    }
}

