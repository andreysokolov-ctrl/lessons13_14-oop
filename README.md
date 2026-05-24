# Вариант 25 — Контрольная точка 5

**Дисциплина:** Программирование на C++  
**Тема:** ООП — Классы, Наследование, Виртуальные функции, Шаблоны  

***

## Задание

### a) Класс однонаправленный список `List`
Перегруженные операции:
- `+` — добавить элемент в конец (`list + item`)
- `--` — удалить элемент из конца (`--list`)
- `!=` — проверка на неравенство

### b) Иерархия классов: Микроорганизмы
Базовый класс `Microorganism` и производные: `Bacterium`, `Virus`, `Protozoa`.  
Статический член: подсчёт **минимального размера** микроорганизма.  
Реализовано ≥ 2 виртуальных функций.

### c) Шаблонный класс
Класс `List<T>` из задачи a) является шаблонным.  
Демонстрация работы с `List<Microorganism*>` и `List<char>`.

***

## Структура проекта

```
lessons13_14-oop/
└── variant25_solution.cpp   
```

***

## Иерархия классов

```
Microorganism  (базовый)
├── virtual void info() const
├── virtual double getSize() const
├── static double minSize       ← минимальный размер
├── static int count            ← количество объектов
│
├── Bacterium   (форма клетки)
├── Virus       (тип вируса)
└── Protozoa    (наличие ядра)
```

***

## Шаблонный класс List\<T\>

```cpp
template <class T>
class List {
    List& operator+(T val);              // добавить в конец
    List& operator--();                  // удалить из конца
    bool  operator!=(const List& other); // проверка неравенства
    void  show() const;
};
```

Использование:
```cpp
List<char> charList;
charList + 'A';
charList + 'B';
--charList;          // удаляет 'B'

List<Microorganism*> bioList;
bioList + &bacterium;
bioList + &virus;
```

***

## Сборка и запуск

```bash
g++ -std=c++11 -o solution variant25_solution.cpp
./solution
```

### Ожидаемый вывод

```
=== List<char> ===
Initial list: [A -> B -> C -> D]
After --(remove last): [A -> B -> C]
charList != charList2: true
charList != charList3 (same): false

=== Hierarchy: Microorganisms ===
Bacterium: E.coli, size: 2 um, shape: rod
Virus: Influenza, size: 0.1 um, type: RNA
Protozoa: Amoeba, size: 500 um, nucleus: yes
Bacterium: Staphylococcus, size: 1 um, shape: sphere
Virus: SARS-CoV-2, size: 0.12 um, type: RNA

Total organisms created: 5
Minimum size: 0.1 um

=== List<Microorganism*> ===
List size: 4
After remove last, size: 3
bioList != bioList2 (should be false): false
```

***

## Ключевые концепции

| Концепция | Где используется |
|---|---|
| Шаблонный класс (`template<class T>`) | `List<T>` |
| Перегрузка операторов (`operator`) | `+`, `--`, `!=` у `List<T>` |
| Виртуальные функции (`virtual`) | `info()`, `getSize()` в `Microorganism` |
| Динамический полиморфизм | Вызов `->info()` через `Microorganism*` |
| Статические члены класса (`static`) | `minSize`, `count` в `Microorganism` |
| Наследование | `Bacterium`, `Virus`, `Protozoa` : `Microorganism` |

***

## Ограничения

- STL **не используется** (по условию задания)
- Список реализован вручную через узлы (`Node`)
