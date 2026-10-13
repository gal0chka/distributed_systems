#pragma once

#include <algorithm>
#include <cctype>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <limits>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

inline std::string trim(std::string value)
{
    const auto not_space = [](unsigned char c) { return !std::isspace(c); };
    value.erase(value.begin(), std::find_if(value.begin(), value.end(), not_space));
    value.erase(std::find_if(value.rbegin(), value.rend(), not_space).base(), value.end());
    return value;
}

inline float parse_float(std::string text)
{
    text = trim(std::move(text));
    std::replace(text.begin(), text.end(), ',', '.');
    std::size_t used = 0;
    float value = 0.0F;
    try {
        value = std::stof(text, &used);
    } catch (const std::exception&) {
        throw std::runtime_error("Некорректное число: " + text);
    }
    if (used != text.size() || !std::isfinite(value)) {
        throw std::runtime_error("Некорректное число: " + text);
    }
    return value;
}

inline std::size_t parse_size(const std::string& text)
{
    std::size_t used = 0;
    unsigned long long value = 0;
    try {
        value = std::stoull(text, &used);
    } catch (const std::exception&) {
        throw std::runtime_error("Некорректный размер массива: " + text);
    }
    if (used != text.size() || value == 0 || value > std::numeric_limits<std::size_t>::max()) {
        throw std::runtime_error("Размер массива должен быть положительным целым числом");
    }
    return static_cast<std::size_t>(value);
}

inline std::vector<float> read_input(const std::string& path)
{
    std::ifstream input(path);
    if (!input) {
        throw std::runtime_error("Не удалось открыть файл: " + path);
    }

    std::string size_line;
    if (!std::getline(input, size_line)) {
        throw std::runtime_error("В файле отсутствует размер массива");
    }
    const std::size_t size = parse_size(trim(size_line));

    std::ostringstream buffer;
    buffer << input.rdbuf();
    std::string text = buffer.str();
    std::replace(text.begin(), text.end(), '\n', ';');
    std::replace(text.begin(), text.end(), '\r', ';');

    std::vector<float> values;
    values.reserve(size);
    std::istringstream tokens(text);
    std::string token;
    while (std::getline(tokens, token, ';')) {
        token = trim(std::move(token));
        if (!token.empty()) {
            values.push_back(parse_float(token));
        }
    }
    if (values.size() != size) {
        throw std::runtime_error(
            "Ожидалось элементов: " + std::to_string(size) +
            ", прочитано: " + std::to_string(values.size()));
    }
    return values;
}

inline std::string format_float(float value)
{
    std::ostringstream output;
    output << std::setprecision(9) << value;
    std::string text = output.str();
    std::replace(text.begin(), text.end(), '.', ',');
    return text;
}

inline void write_result(const std::string& path, float value)
{
    std::ofstream output(path);
    if (!output) {
        throw std::runtime_error("Не удалось создать файл результата: " + path);
    }
    output << format_float(value) << '\n';
}

