#include <iostream>
#include <vector>
#include <stdexcept>
#include <cstdlib> // Для використання функції rand()

class IntegerMultiset {
private:
    unsigned int* set;
    unsigned int beg;
    unsigned int end;
    mutable int state; // Mutable дозволяє змінювати state у const методах

public:
    // Конструктори
    IntegerMultiset() : beg(0), end(100), state(0) {
        try {
            set = new unsigned int[end - beg]();
            for (unsigned int i = 0; i < end - beg; ++i) {
                set[i] = rand() % (end - beg) + beg; // Генеруємо випадкове число від beg до end
            }
        }
        catch (std::bad_alloc& e) {
            state = -1;
            std::cerr << "Error: Memory allocation failed." << std::endl;
        }
    }

    IntegerMultiset(unsigned int end) : beg(0), end(end), state(0) {
        try {
            set = new unsigned int[end - beg]();
            for (unsigned int i = 0; i < end - beg; ++i) {
                set[i] = rand() % (end - beg) + beg; // Генеруємо випадкове число від beg до end
            }
        }
        catch (std::bad_alloc& e) {
            state = -1;
            std::cerr << "Error: Memory allocation failed." << std::endl;
        }
    }

    IntegerMultiset(unsigned int beg, unsigned int end) : beg(beg), end(end), state(0) {
        try {
            set = new unsigned int[end - beg]();
            for (unsigned int i = 0; i < end - beg; ++i) {
                set[i] = rand() % (end - beg) + beg; // Генеруємо випадкове число від beg до end
            }
        }
        catch (std::bad_alloc& e) {
            state = -1;
            std::cerr << "Error: Memory allocation failed." << std::endl;
        }
    }

    IntegerMultiset(unsigned int beg, unsigned int end, unsigned int value) : beg(beg), end(end), state(0) {
        try {
            set = new unsigned int[end - beg];
            for (unsigned int i = 0; i < end - beg; ++i) {
                set[i] = value;
            }
        }
        catch (std::bad_alloc& e) {
            state = -1;
            std::cerr << "Error: Memory allocation failed." << std::endl;
        }
    }

    // Конструктор копій та операція присвоєння
    IntegerMultiset(const IntegerMultiset& other) : beg(other.beg), end(other.end), state(other.state) {
        try {
            set = new unsigned int[end - beg];
            for (unsigned int i = 0; i < end - beg; ++i) {
                set[i] = other.set[i];
            }
        }
        catch (std::bad_alloc& e) {
            state = -1;
            std::cerr << "Error: Memory allocation failed." << std::endl;
        }
    }

    IntegerMultiset& operator=(const IntegerMultiset& other) {
        if (this != &other) {
            delete[] set;
            beg = other.beg;
            end = other.end;
            state = other.state;
            try {
                set = new unsigned int[end - beg];
                for (unsigned int i = 0; i < end - beg; ++i) {
                    set[i] = other.set[i];
                }
            }
            catch (std::bad_alloc& e) {
                state = -1;
                std::cerr << "Error: Memory allocation failed." << std::endl;
            }
        }
        return *this;
    }

    // Деструктор
    ~IntegerMultiset() {
        delete[] set;
    }

    // Функції для установки та отримання елементу
    void setValue(unsigned int index, unsigned int value) {
        if (index >= end - beg) {
            state = -2;
            std::cerr << "Error: Index out of bounds." << std::endl;
            return;
        }
        set[index] = value;
    }

    unsigned int getValue(unsigned int index) const {
        if (index >= end - beg) {
            state = -2;
            std::cerr << "Error: Index out of bounds." << std::endl;
            return 0;
        }
        return set[index];
    }

    // Функція, що повертає кількість повторень елементу множини
    unsigned int getCount(unsigned int value) const {
        unsigned int count = 0;
        for (unsigned int i = 0; i < end - beg; ++i) {
            if (set[i] == value) {
                ++count;
            }
        }
        return count;
    }

    // Функції для об'єднання, перетину та різниці
    IntegerMultiset unionSet(const IntegerMultiset& other) const {
        unsigned int newBeg = std::min(beg, other.beg);
        unsigned int newEnd = std::max(end, other.end);
        IntegerMultiset result(newBeg, newEnd);
        for (unsigned int i = newBeg; i < newEnd; ++i) {
            result.setValue(i - newBeg, std::max(getCount(i), other.getCount(i)));
        }
        return result;
    }

    IntegerMultiset intersectionSet(const IntegerMultiset& other) const {
        unsigned int newBeg = std::max(beg, other.beg);
        unsigned int newEnd = std::min(end, other.end);
        IntegerMultiset result(newBeg, newEnd);
        for (unsigned int i = newBeg; i < newEnd; ++i) {
            result.setValue(i - newBeg, std::min(getCount(i), other.getCount(i)));
        }
        return result;
    }

    IntegerMultiset differenceSet(const IntegerMultiset& other) const {
        unsigned int newBeg = std::min(beg, other.beg);
        unsigned int newEnd = std::max(end, other.end);
        IntegerMultiset result(newBeg, newEnd);
        for (unsigned int i = newBeg; i < newEnd; ++i) {
            result.setValue(i - newBeg, getCount(i) - other.getCount(i));
        }
        return result;
    }

    // Функції порівняння
    bool operator==(const IntegerMultiset& other) const {
        if (beg != other.beg || end != other.end) {
            return false;
        }
        for (unsigned int i = 0; i < end - beg; ++i) {
            if (set[i] != other.set[i]) {
                return false;
            }
        }
        return true;
    }

    bool operator!=(const IntegerMultiset& other) const {
        return !(*this == other);
    }

    bool operator<(const IntegerMultiset& other) const {
        if (beg != other.beg || end != other.end) {
            return false;
        }
        for (unsigned int i = 0; i < end - beg; ++i) {
            if (set[i] >= other.set[i]) {
                return false;
            }
        }
        return true;
    }

    bool operator<=(const IntegerMultiset& other) const {
        return *this == other || *this < other;
    }

    bool operator>(const IntegerMultiset& other) const {
        return !(*this <= other);
    }

    bool operator>=(const IntegerMultiset& other) const {
        return !(*this < other);
    }

    // Функція друку
    void print() const {
        std::cout << "Multiset Information:" << std::endl;
        std::cout << "Range: [" << beg << ", " << end << "]" << std::endl;
        std::cout << "Elements:" << std::endl;
        for (unsigned int i = 0; i < end - beg; ++i) {
            std::cout << beg + i << ": " << set[i] << std::endl;
        }
    }

    // Функція для отримання стану
    int getState() const {
        return state;
    }

    // Функція для підрахунку числа об'єктів даного типу
    static int getCountOfObjects() {
        // Тут можна використати статичну змінну для підрахунку об'єктів
        // Наприклад:
        // static int count = 0;
        // return count;
    }
};

int main() {
    // Тестування класу "Множина з повторенням діапазону цілих чисел"
    IntegerMultiset set1; // використання конструктора без параметрів
    set1.print();

    IntegerMultiset set2(50); // використання конструктора з одним параметром
    set2.print();

    IntegerMultiset set3(10, 30); // використання конструктора з двома параметрами
    set3.print();

    IntegerMultiset set4(5, 15, 3); // використання конструктора з трьома параметрами
    set4.print();

    // Тестування функцій об'єднання, перетину та різниці
    IntegerMultiset unionSet = set3.unionSet(set4);
    unionSet.print();

    IntegerMultiset intersectionSet = set3.intersectionSet(set4);
    intersectionSet.print();

    IntegerMultiset differenceSet = set3.differenceSet(set4);
    differenceSet.print();

    return 0;
}