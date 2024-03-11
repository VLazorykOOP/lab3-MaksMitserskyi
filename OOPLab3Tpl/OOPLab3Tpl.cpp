#include <iostream>
#include <cmath>
#include <string>
using namespace std;
const double M_PI = 3.14;
class Cube 
{
private:
    double side;
    string color;
public:
    // конструктор за замовч
    Cube() : side(0.0), color("white") {}
    // конструктор з параметрами
    Cube(double s, const string& c) : side(s), color(c) {}
    // ф-ції обчисл площі поверхні, об’єму, довжини діагоналі та об’єму вписаної сфери
    double surfaceArea() const {
        return 6 * side * side;
    }
    double volume() const {
        return side * side * side;
    }
    double diagonalLength() const {
        return sqrt(3) * side;
    }
    double inscribedSphereVolume() const {
        return (4.0 / 3.0) * M_PI * pow(side / 2, 3);
    }
    // ф-ції встановлення значення сторони та кольору
    void setSide(double s) {
        if (s > 0) {
            side = s;
        }
        else {
            cerr << "Помилка: сторона повинна бути більною ніж 0." << endl;
        }
    }
    void setColor(const string& c) {
        color = c;
    }
    // ф-ції що повертають значення полів
    double getSide() const {
        return side;
    }
    string getColor() const {
        return color;
    }
    // ф-ція друку
    void print() const {
        cout << "Сторона: " << side << endl;
        cout << "Колiр: " << color << endl;
        cout << "Площа: " << surfaceArea() << endl;
        cout << "Об*єм: " << volume() << endl;
        cout << "Довжина дiагоналi: " << diagonalLength() << endl;
        cout << "Об*єм вписаної сфери: " << inscribedSphereVolume() << endl;
    }
};
int main() {
    setlocale(LC_CTYPE, "Ukr");
    // тест класу 
    cout << "Тест 1(Конструктор зв замовчуванням): " << endl;
    Cube cube1; // використання конструктора за замовчуванням
    cube1.print();
    cout << "Тест 2(Конструктор з параметром 1): " << endl;
    Cube cube2(3.0, "blue"); // використання конструктора з параметрами
    cube2.print();
    // зміна знач полів та тестування функцій
    cout << "Тест 3(Конструктор з параметром 2): " << endl;
    cube2.setSide(5.0);
    cube2.setColor("green");
    cube2.print();
    return 0;
}
