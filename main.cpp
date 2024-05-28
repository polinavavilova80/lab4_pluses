#include <cstdlib>
#include <ctime>
#include <limits>
#include <iostream>
#include <cmath>

// Определение класса для представления точки в двумерном пространстве
class Point2D {
private:
    int x; // Координата X точки
    int y; // Координата Y точки
public:
    Point2D(int x, int y) : x(x), y(y) {} // Конструктор для создания объекта Point2D
    int getX() const { return x; } // Получить значение координаты X
    int getY() const { return y; } // Получить значение координаты Y
    void setX(int newX) { x = newX; } // Установить новое значение координаты X
    void setY(int newY) { y = newY; } // Установить новое значение координаты Y
    void move(int deltaX, int deltaY) { // Переместить точку на заданное расстояние по оси X и Y
        x += deltaX;
        y += deltaY;
    }
};

// Базовый класс для персонажей игры
class Character {
protected:
    Point2D position; // Позиция персонажа
public:
    std::string shown; // Символ, который будет использоваться для отображения персонажа
    Character(int x, int y) : position(x, y) {} // Конструктор для создания объекта Character
    Point2D getPosition() const { return position; } // Получить текущую позицию персонажа
    virtual void move(int deltaX, int deltaY) = 0; // Абстрактная функция для перемещения персонажа
};

// Подкласс для жертвы
class Prey : public Character {
public:
    Prey(int x, int y) : Character(x, y) { shown = "()"; } // Конструктор для создания объекта Prey

    void move(int deltaX, int deltaY) override { // Переопределенная функция перемещения
        position.move(deltaX, deltaY);
    }
};

// Подкласс для хищника
class Predator : public Character {
public:
    Predator(int x, int y) : Character(x, y) { shown = "**"; } // Конструктор для создания объекта Predator

    void move(int deltaX, int deltaY) override { // Переопределенная функция перемещения
        position.move(deltaX, deltaY);
    }
};

// Класс для игрового поля
class Arena {
private:
    static const int size = 30; // Размер игрового поля
    static const int point_width = 2; // Ширина символа для отображения точки
    char arena[3 + size][size * point_width + 4]; // Массив для хранения состояния игрового поля

public:
    Arena() { // Конструктор для инициализации игрового поля
        // Инициализация игрового поля
    }

    void stand(const Character& character) { // Функция для размещения персонажа на игровом поле
        // Реализация функции
    }

    void display() const { // Функция для вывода игрового поля
        // Реализация функции
    }

    bool isIn(int x, int y) const { // Проверка, находится ли точка внутри игрового поля
        // Реализация функции
    }

    void clearPosition(int x, int y) { // Очистка позиции на игровом поле
        // Реализация функции
    }
};

// Функция для выполнения одного шага игры
void MakeStep(Arena& arena, Character& unit_, int predatorX, int predatorY, int newPredatorX, int newPredatorY) {
    // Реализация функции
}

// Функция для определения знака числа
int sgn(int a) {
    // Реализация функции
}

int main() {
    // Основной цикл игры
    return 0;
}
