#include <iostream>
#include <cstring>
#include <stdlib.h>
#include <string>
#include <limits>
#include <list.hpp>
using namespace List;
using namespace std;
 
auto menu(ForwardList &) -> void;

auto change_color(col c) -> void;

int main(int argc, char *argv[]) {
  ForwardList list;

  unsigned int n = 1;
  if (argc == 2) {
    string mas_str = argv[1], mas_str_const = mas_str;
    unsigned j = 1, tmp = 0;

    for (unsigned i = 0; i < strlen(mas_str_const.c_str()); ++i) {
      if (mas_str[i] == ',') {
        ++j;
      }
    }
    int *Mass = new int[j];

    j = 0;

    Mass[j] = atoi(mas_str.c_str());
    ++j;

    for (unsigned int i = 0; i < strlen(mas_str_const.c_str()); ++i) {
      if (mas_str[0] != ',') {
        mas_str.erase(0, 1);
      } else {
        mas_str.erase(0, 1);
        Mass[j] = atoi(mas_str.c_str());
        ++j;
      }
    }

    for (unsigned int i = 0; i < j; ++i) {
      list.insert(Mass[i]);
    }

    menu(list);

    delete[] Mass;
  }
  if (argc > 2) {
    for (unsigned int i = 1; i < argc; ++i) {
      ++n;
    }

    int *Mass = new int[n];

    for (int i = 1; i < n; ++i) {
      Mass[i] = atoi(argv[i]);
    }
    for (unsigned int i = 1; i < n; ++i) {
      list.insert(Mass[i]);
    }
    menu(list);

    delete[] Mass;
  }
}

auto menu(ForwardList &list) -> void {
  while (1) {
    change_color(col::CYAN);
    cout << "Выберите одну из операций: " << endl;
    cout << "1. Распечатать список " << endl;
    cout << "2. Добавить элементы в список " << endl;
    cout << "3. Удалить элемент " << endl;
    cout << "4. Найти позиции элементов" << endl;
    cout << "5. Заменить элемент на другой" << endl;
    cout << "6. Отсортировать элементы списка" << endl;
    cout << "7. Завершить работу программы" << endl;
    change_color(col::GREEN);
    int choise = 0;
    cin >> choise;

    if (!cin) {
      cin.clear();
      while (cin.get() != '\n')
        ;
      cout << "Введено неверное значение!" << endl;
    }

    if ((list.empty()) && (choise != 2) && (choise != 7)) {
      change_color(col::RED);
      cout << "Список пуст" << endl;
    }

    else {
      switch (choise) {
        case 1: {
          change_color(col::BLUE);
          list.print();
          std::cout << endl;
        } break;
        case 2: {
          string values, values_const;
          unsigned int k = 1;
          change_color(col::CYAN);
          cout << "Введите элементы: ";
          change_color(col::GREEN);
          cin.ignore(numeric_limits<streamsize>::max(), '\n');
          getline(cin, values);
          while (!cin) {
            cin.clear();
            cout << "Введено неверное значение!" << endl;
            cin.get();
          }
          values_const = values;

          for (unsigned int i = 0; i < strlen(values_const.c_str()); ++i) {
            if ((values[i] == ' ') && (values[i + 1] != ' ')) {
              ++k;
            }
          }

          int *Massiv = new int[k];

          k = 0;

          Massiv[k] = atoi(values.c_str());
          if ((Massiv[k] == 0) && (values[0] != '0')) {
            cout << "Введено неверное значение!" << endl;
            continue;
          }
          ++k;

          for (unsigned int i = 0; i < strlen(values_const.c_str()); ++i) {
            if (values[0] != ' ') {
              values.erase(0, 1);
            } else if ((values[1] != ' ') &&
                       (i + 1 != strlen(values_const.c_str()))) {
              values.erase(0, 1);
              Massiv[k] = atoi(values.c_str());
              ++k;
            } else
              values.erase(1, 1);
          }

          for (unsigned int i = 0; i < k; ++i) {
            list.insert(Massiv[i]);
          }
          delete[] Massiv;
        } break;
        case 3: {
          int value;
          change_color(col::CYAN);
          cout << "Введите значение элемента: ";
          change_color(col::GREEN);
          cin >> value;
          if (!cin) {
            cin.clear();
            cout << "Введено неверное значение!" << endl;
            cin.get();
            break;
          } else {
            bool default_ = false;
            change_color(col::RED);
            default_ = list.Remove(value);
            if (!default_)
              std::cout << "Элемент " << value << " отсутствует" << std::endl;
          }
        } break;
        case 4: {
          int value;
          change_color(col::CYAN);
          cout << "Введите значение элемента: ";
          change_color(col::GREEN);
          cin >> value;
          if (!cin) {
            cin.clear();
            cout << "Введено неверное значение!" << endl;
            cin.get();
            break;
          }
          bool default_ = false;
          default_ = list.item_position(value);
          if (!default_) {
            change_color(col::RED);
            std::cout << "Элемент отсутствует" << std::endl;
          }
        } break;
        case 5: {
          string values, values_const;
          int val = 0;
          unsigned int position = 0;
          change_color(col::CYAN);
          cout << "Введите позицию и новое значение: ";
          change_color(col::GREEN);
          cin.ignore(numeric_limits<streamsize>::max(), '\n');
          getline(cin, values);
          values_const = values;
          position = atoi(values.c_str());

          for (unsigned int i = 0; i < strlen(values_const.c_str()); ++i) {
            if (values[0] != ' ') {
              values.erase(0, 1);
            } else {
              values.erase(0, 1);
              val = atoi(values.c_str());
            }
          }
          bool default_ = false;
          default_ = list.item_replacement(position, val);
          if (!default_) {
            change_color(col::RED);
            std::cout << "Элемент с позицией " << position << " не существует"
                      << std::endl;
          }
        } break;
        case 6: {
          list.items_sort();
        } break;
        case 7: {
          string prog_exit;
          change_color(col::RED);
          cout << "Вы уверены, что хотите выйти?(yes|no)" << endl;
          change_color(col::GREEN);
          cin >> prog_exit;
          if ((prog_exit == "yes") || (prog_exit == "YES") ||
              (prog_exit == "Yes") || (prog_exit == "y")) {
            cout << "До свидания !" << endl;
            return;
          }
        } break;
      }
    }
  }
}
