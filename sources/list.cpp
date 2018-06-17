#include <list.hpp>
#include <iostream>
#include <limits>
using namespace List;

auto ForwardList::Add(Node *&curr, int val) -> void {
  if (curr == nullptr)
    curr = new Node{val, nullptr};
  else {
    Add(curr->next, val);
  }
}

auto ForwardList::insert(int val) -> void { Add(first, val); }

auto change_color(col c) -> void {
#ifdef _WIN32
  HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
#endif
  switch (c) {
    case col::BLUE:  // blue color
#if defined(__gnu_linux__) || (defined(__APPLE__) && defined(__MACH__))
      std::cout << "\033[34m";
#endif
#ifdef _WIN32
      SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 3));
#endif
      break;
    case col::GREEN:  // green
#if defined(__gnu_linux__) || (defined(__APPLE__) && defined(__MACH__))
      std::cout << "\033[32m";
#endif
#ifdef _WIN32
      SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 10));
#endif
      break;
    case col::WHITE:  // white
#if defined(__gnu_linux__) || (defined(__APPLE__) && defined(__MACH__))
      std::cout << "\033[39;49m";
#endif
#ifdef _WIN32
      SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 15));
#endif
      break;
    case col::RED:  // red
#if defined(__gnu_linux__) || (defined(__APPLE__) && defined(__MACH__))
      std::cout << "\033[31m";
#endif
#ifdef _WIN32
      SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 4));
#endif
      break;
    case col::CYAN:
#if defined(__gnu_linux__) || (defined(__APPLE__) && defined(__MACH__))
      std::cout << "\033[36m";
#endif
#ifdef _WIN32
      SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 11));
#endif
  }
}

auto ForwardList::empty() -> bool {
  if (first == nullptr)
    return true;
  else
    return false;
}

auto ForwardList::Remove(int val) -> bool {
  Node *curr = first;
  Node *ptr = curr;

  if (curr->data == val) {
    curr = first->next;
    delete first;
    first = curr;
    return true;
  }

  curr = curr->next;

  while (curr != nullptr) {
    if (curr->data == val) {
      ptr->next = curr->next;
      delete curr;
      curr = ptr->next;
      return true;
    } else {
      ptr = ptr->next;
      curr = curr->next;
    }
  }
  return false;
}

auto ForwardList::print() const -> void {
  Node *curr = first;
  while (1) {
    if (curr != first) std::cout << " -> ";
    std::cout << curr->data;
    if (curr->next == nullptr) break;
    curr = curr->next;
  }
}

auto ForwardList::item_position(int val) -> bool {
  Node *curr = first;
  bool flag = false;
  int position = 0;
  while (curr != nullptr) {
    if (curr->data == val) {
      change_color(col::BLUE);
      std::cout << position << " ";
      ++position;
      curr = curr->next;
      flag = true;
    } else {
      curr = curr->next;
      ++position;
    }
  }
  if (flag) {
    std::cout << std::endl;
    return true;
  } else
    return false;
}

auto ForwardList::item_replacement(int item_position, int val) -> bool {
  Node *curr = first;
  bool flag = false;
  int position = 0;
  while (curr != nullptr) {
    if (position == item_position) {
      curr->data = val;
      flag = true;
      break;
    } else {
      curr = curr->next;
      ++position;
    }
  }
  if (flag) {
    return true;
  } else
    return false;
}

auto quick_sort(int *mass, int n) -> void {
  int i = 0, j = n, p = mass[n >> 1];
  do {
    while (mass[i] < p) ++i;
    while (mass[j] > p) --j;

    if (i <= j) {
      std::swap(mass[i], mass[j]);
      ++i;
      --j;
    }
  } while (i <= j);

  if (j > 0) quick_sort(mass, j);
  if (n > i) quick_sort(mass + i, n - i);
}

auto ForwardList::items_sort() -> void {
  int k = 0;
  Node *curr = new Node{0, nullptr};
  curr = first;
  while (curr != nullptr) {
    ++k;
    curr = curr->next;
  }

  curr = first;

  int *Massiv = new int[k];

  k = 0;

  while (curr != nullptr) {
    Massiv[k] = curr->data;
    ++k;
    curr = curr->next;
  }
  quick_sort(Massiv, --k);
  curr = first;
  k = 0;
  while (curr != nullptr) {
    curr->data = Massiv[k];
    ++k;
    curr = curr->next;
  }
  delete[] Massiv;
}

ForwardList::~ForwardList() {
  while (first != nullptr) {
    Node *temp = first->next;
    delete first;
    first = temp;
  }
}
