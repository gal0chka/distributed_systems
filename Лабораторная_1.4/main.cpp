#include "input_reader.hpp"
#include "lab.hpp"

#include <iostream>
#include <string>
#include <vector>

int main(int argc, char* argv[])
{
    if (argc < 2 || argc > 3) {
        std::cerr << "Использование: " << argv[0]
                  << " <input_const.txt> [result.txt]\n";
        return 1;
    }

    try {
        const InputData input = read_input(argv[1]);
        std::vector<float> result(input.values.size());

        const LabStatus status = multiply_by_constant_sse(
            input.values.data(), input.constant, result.data(), result.size());
        if (status != LabStatus::ok) {
            std::cerr << "Ошибка функции, статус: " << static_cast<int>(status) << '\n';
            return static_cast<int>(status);
        }

        const std::string output_path = argc == 3 ? argv[2] : "lab_1_4_result.txt";
        write_result(output_path, result);
        std::cout << "Лабораторная 1.4 выполнена. Элементов: " << result.size()
                  << ", результат: " << output_path << '\n';
        return 0;
    } catch (const std::exception& error) {
        std::cerr << "Ошибка: " << error.what() << '\n';
        return 1;
    }
}

