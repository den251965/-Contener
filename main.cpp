#include <algorithm>
#include <iostream>
#include <list>
#include <ostream>
#include <vector>

// Печать
template <typename T, template <typename ELEM, typename ALLOC = std::allocator<T>> class Cont>
std::ostream& operator<<(std::ostream& out, const Cont<T>& conteiner) {
  for (auto& t : conteiner) {
    out << t << " ";
  }
  out << "\n";
  return out;
}

template <
    typename T,
    template <typename ELEM, typename ALLOC = std::allocator<std::pair<T, T>>> class Cont>
std::ostream& operator<<(std::ostream& out, const Cont<std::pair<T, T>>& conteiner) {
  for (auto& [f, s] : conteiner) {
    out << "[ " << f << " , " << s << " ] ";
  }
  out << "\n";
  return out;
}

template <typename Cont>
void Print(std::string comment, std::string name_cont, Cont con) {
  std::cout << comment << " name conteiner - " << name_cont << " : ";
  std::cout << con << "\n";
}

#define Printered(text, x) Print(text, #x, x);

// Рандом у нас идет от 0 и до 50 , чтоб глаза не мазолить
int random() {
  return std::rand() % 51;
}

bool correct(size_t x, const std::vector<int>& v) {
  return x <= v.size();
}

#define MessErrRangeV(x) \
  std::cout << "Invalid " << #x << " = " << x << " out of range std::vector<int> v\n";

// Перемещение элементов вектора с конца в лист
template <typename T>
std::list<T> VectorMoveList(std::vector<T>& v, size_t ln) {
  std::list<T> list;
  std::move(v.begin() + v.size() - ln, v.end(), std::back_inserter(list));
  v.resize(v.size() - ln);  // 6
  return list;
}

template <typename T>
std::vector<std::pair<T, T>> UnionPair(const std::vector<T>& v_min, const std::vector<T>& v_max) {
  std::vector<std::pair<int, int>> v4;
  //v4.resize(v_min.size());
  std::transform(
      v_min.begin(),
      v_min.end(),
      v_max.begin(),
      std::back_inserter(v4),
      [](int a, int b) { return std::make_pair(a, b); }
  );
  return v4;
}

int main() {
  // 1
  std::vector<int> v;

enter_n:
  std::cout << "insert size vector (limits 500(min) - 1000(max)): ";
  size_t n;
  std::cin >> n;
  if (n < 500 || n > 1000) {
    std::cout << "Invalid n = " << n << " goes beyond limits 500(min) - 1000(max)\n";
    goto enter_n;
  }

  v.resize(n, 0);
  std::generate(v.begin(), v.end(), random);  // забиваем его рандомным числом

  Printered("1. Vector", v);

  // копируем из одного вектора в другой или 200 элементов или от b до e
  // 2.1

  std::vector<int> v2(v.rbegin(), v.rbegin() + 200);  // тк условие разворот вектора не
                                                      // запрещено
  Printered("2.1. Vector(size = 200)", v2);

  // 2.2
  size_t b, e;
enter_b:
  std::cout << "insert begin copy b : ";
  std::cin >> b;
  if (!correct(b, v)) {
    MessErrRangeV(b);
    goto enter_b;
  }

enter_e:
  std::cout << "insert end copy e : ";
  std::cin >> e;
  if (!correct(e, v)) {
    MessErrRangeV(e);
    goto enter_e;
  }

  if (b > e)
    std::swap(b, e);

  std::vector<int> v2_1(v.begin() + b, v.begin() + e);
  Printered("2.2. Vector", v2_1);

  // 3.	Сформировать список list1, поместив в него первые n (от 20 до 50) наибольших элементов
  // вектора v1 (указанные элементы должны быть отсортированы до помещения их в список).
  std::sort(v.begin(), v.end());  // от меньшего к большему
  Printered("Sorted vector", v);

  // рандомное число для list 1
  size_t ln = 20 + std::rand() % 31;
  std::cout << "list1.size =" << ln << "\n ";
  std::list<int> list1(VectorMoveList(v, ln));
  Printered("3.", list1);

  // 4.	Сформировать список list2, поместив в него последние n (от 20 до 50) наименьших элементов
  // вектора v2, порядок элементов не важен.
  std::sort(v2.begin(), v2.end(), [](int l, int r) { return l > r; });  // от большего к меньшему
  Printered("Sorted vector", v2);

  // рандомное число для list 2
  ln = 20 + std::rand() % 31;
  std::cout << "4. list2.size =" << ln << "\n ";
  std::list<int> list2(VectorMoveList(v2, ln));
  Printered("", list2);

  // 5.	Удалить из векторов v1 и v2 перемещенные элементы. Скорректируйте размеры векторов после
  // удаления из них элементов.
  Printered("5.1. v -> list1", v);

  Printered("5.2. v2 -> list2", v2);

  // 6.	Для списка list1 найти элемент со средним значением. Перегруппировать элементы списка так,
  // чтобы в начале оказались все элементы, большие среднего значения.

  std::reverse(list1.begin(), list1.end());
  Printered("6. reverse", list1);

  // 7.	Удалите из списка list2 все нечётные элементы (или используйте другой критерий,
  // который однозначно делит экземпляры вашего класса на два непересекающихся множества).

  auto new_end = std::remove_if(list2.begin(), list2.end(), [](auto n) { return n % 2 != 0; });
  list2.erase(new_end, list2.end());
  Printered("7. del nechet", list2);

  // 8. Создайте вектор v3 из элементов, которые присутствуют и в векторе v1 и в векторе v2.
  std::vector<int> v3(v.begin(), v.end());
  v3.reserve(v.size() + v2.size());
  v3.insert(v3.cend(), v.cbegin(), v.cend());
  v3.insert(v3.cend(), v2.cbegin(), v2.cend());

  Printered("8. Vector", v3);

  // 9. Для списков list1 и list2 из списка с большим числом элементов удалите первые n так, чтобы
  // оба списка имели бы одинаковый размер. Сформируйте из них список list3, который будет хранить
  // пары <первый элемент списка list1, первый элемент списка list2>, <второй элемент списка list1,
  // второй элемент списка list2>  и т. д.

  size_t k = std::min(list1.size(), list2.size());
  if (list1.size() > k)
    list1.resize(k);
  else if (list2.size() > k)
    list2.resize(k);
  std::list<std::pair<int, int>> list3;
  std::transform(
      list1.begin(),
      list1.end(),
      list2.begin(),
      std::back_inserter(list3),
      [](int a, int b) { return std::make_pair(a, b); }
  );

  // вывод результатов
  Printered("9. ", list3);

  // 10. Решите предыдущую задачу для векторов v1 и v2 без предварительного приведения векторов к
  // одному размеру. Пар с пустыми значениями быть не должно.

  std::vector<std::pair<int, int>> v4 = v.size() < v2.size() ? UnionPair(v, v2) : UnionPair(v2, v);

  // вывод результатов
  Printered("10. ", v4);

  std::cout << "Success !!!";

  return 0;
}
