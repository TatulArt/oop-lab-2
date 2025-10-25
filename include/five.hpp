#ifndef FIVE_H
#define FIVE_H

#include <cstddef>
#include <initializer_list>
#include <iosfwd>
#include <stdexcept>
#include <string>

class Five final {
public:
  Five(); // Инициализация пустого экземпляра
  Five(const size_t &n, unsigned char defaultValue = 0); // Создание массива размера n, заполненый элементами defaultValue
  Five(const std::initializer_list<unsigned char> &initList); // Инициализация массива из списка (arr{1, 2, 3})
  Five(const std::string &initString); // Инициализация из строки
  Five(const Five &other); // Копирование данных другого экземпляра
  Five(Five &&other) noexcept; // Перемещение данных из other в новый экземпляр

  Five &operator=(const Five &other); // Оператор присваивания
  Five &operator=(Five &&other) noexcept; // Оператор присваивания (перемещение)
  ~Five() noexcept; // Делитер

  Five operator+(const Five &other) const;
  Five operator-(const Five &other) const;
  bool operator==(const Five &other) const;
  bool operator>=(const Five &other) const;

  friend std::ostream &operator<<(std::ostream &os, const Five &f);

private:
  unsigned char *data;
  size_t size;
};

#endif // FIVE_H