#include "../include/five.hpp"
#include <algorithm>
#include <cctype>
#include <cstddef>
#include <iostream>
#include <stdexcept>
#include <string>

Five::Five() : data(nullptr), size(0) {}

// Создание массива размера n, заполненый элементами defaultValue
Five::Five(const size_t &n, unsigned char defaultValue) {
    if (defaultValue > 4) {
        throw std::invalid_argument("Digit must be in [0..4]");
    }

    size = n;
    data = new unsigned char[size];
    std::fill(data, data + size, defaultValue);
}

// Инициализация массива из списка (arr{1, 2, 3})
Five::Five(const std::initializer_list<unsigned char> &initList) {
    size = initList.size();
    data = new unsigned char[size];

    size_t i = 0;
    for (unsigned char value : initList) {
        if (value > 4) {
            throw std::invalid_argument("Digit must be in [0..4]");
        }
        
        data[i++] = value;
    }
}

// Инициализация из строки
Five::Five(const std::string &initString) {
    size = initString.size();
    data = new unsigned char[size];

    for (size_t i = 0; i < size; ++i) {
        char c = initString[i];

        if (!std::isdigit(c) || c < '0' || c > '4') {
            throw std::invalid_argument("Invalid char for base-5");
        }

        data[i] = c - '0'; // Отнимаем код '0' в ASCII, что бы получить литерал числа (НЕТ, ЭТО ПИШЕТ НЕ ИИ) 
    }
}

// Копирование данных другого экземпляра
Five::Five(const Five &other) {
    size = other.size;
    data = new unsigned char[size];

    // Идем от 1 элемента other.data до элемента other.data + size (не включительно) и записываем в data
    std::copy(other.data, other.data + size, data); 
}

// Перемещение данных из other в новый экземпляр
Five::Five(Five &&other) noexcept : data(other.data), size(other.size) {
  other.data = nullptr;
  other.size = 0;
}

// Оператор присваивания
Five &Five::operator=(const Five &other) {
  if (this != &other) {
    delete[] data;
    size = other.size;
    data = new unsigned char[size];
    std::copy(other.data, other.data + size, data);
  }

  return *this;
}

// Присваиванее (с перемещением)
Five &Five::operator=(Five &&other) noexcept {
  if (this != &other) {
    delete[] data;
    data = other.data;
    size = other.size;
    other.data = nullptr;
    other.size = 0;
  }

  return *this;
}

// Делитер
Five::~Five() noexcept {
  delete[] data;
  data = nullptr;
  size = 0;
}

Five Five::operator+(const Five &other) const {
  size_t maxSize = std::max(size, other.size);
  size_t resultSize = maxSize + 1;
  unsigned char *resultData = new unsigned char[resultSize]();
  unsigned char carry = 0;

  for (size_t i = 0; i < maxSize; ++i) {
    unsigned char a = (i < size) ? data[i] : 0;
    unsigned char b = (i < other.size) ? other.data[i] : 0;
    unsigned char sum = a + b + carry;

    resultData[i] = sum % 5;
    carry = sum / 5;
  }
  resultData[maxSize] = carry;

  while (resultSize > 1 && resultData[resultSize - 1] == 0)
    --resultSize;

  Five result;

  result.size = resultSize;
  result.data = new unsigned char[resultSize];
  std::copy(resultData, resultData + resultSize, result.data);

  delete[] resultData;

  return result;
}

Five Five::operator-(const Five &other) const {
  if (!(*this >= other))
    throw std::invalid_argument("Subtraction would result in negative number");

  size_t resultSize = size;
  unsigned char *resultData = new unsigned char[resultSize]();
  int borrow = 0;

  for (size_t i = 0; i < resultSize; ++i) {
    int a = (i < size) ? data[i] : 0;
    int b = (i < other.size) ? other.data[i] : 0;
    a -= borrow;

    if (a < b) {
      a += 5;
      borrow = 1;
    } else
      borrow = 0;

    resultData[i] = a - b;
  }

  while (resultSize > 1 && resultData[resultSize - 1] == 0)
    --resultSize;

  Five result;

  result.size = resultSize;
  result.data = new unsigned char[resultSize];
  std::copy(resultData, resultData + resultSize, result.data);

  delete[] resultData;

  return result;
}

bool Five::operator==(const Five &other) const {
  if (size != other.size)
    return false;

  for (size_t i = 0; i < size; ++i)
    if (data[i] != other.data[i])
      return false;

  return true;
}

bool Five::operator>=(const Five &other) const {
  if (size > other.size)
    return true;

  if (size < other.size)
    return false;

  for (size_t i = size; i > 0; --i) {
    if (data[i - 1] > other.data[i - 1])
      return true;

    if (data[i - 1] < other.data[i - 1])
      return false;
  }

  return true;
}

std::ostream &operator<<(std::ostream &os, const Five &f) {
  if (f.size == 0) {
    os << '0';

    return os;
  }

  for (size_t i = f.size; i > 0; --i)
    os << static_cast<int>(f.data[i - 1]);

  return os;
}