#include <cstdlib>
#include <ctime>
#include <limits>
#include <iostream>
#include <cmath>

class Point2D {
private:
    int x;
    int y;
public:
    Point2D(int x, int y) : x(x), y(y) {}
    int getX() const { return x; }
    int getY() const { return y; }
    void setX(int newX) { x = newX; }
    void setY(int newY) { y = newY; }
    void move(int deltaX, int deltaY) {
        x += deltaX;
        y += deltaY;
    }
};

class Character {
protected:
    Point2D position;

public:
    std::string shown;
    Character(int x, int y) : position(x, y) {}
    Point2D getPosition() const {
        return position;
    }
    virtual void move(int deltaX, int deltaY) = 0;
};

class Prey : public Character {
public:
    Prey(int x, int y) : Character(x, y) { shown = "()"; }

    void move(int deltaX, int deltaY) override {
        position.move(deltaX, deltaY);
    }
};

class Predator : public Character {
public:
    Predator(int x, int y) : Character(x, y) { shown = "**"; }

    void move(int deltaX, int deltaY) override {
        position.move(deltaX, deltaY);
    }
};

class Arena {
private:
    static const int size = 30;
    static const int point_width = 2;
    char arena[3 + size][size * point_width + 4];

public:
    Arena() {
        for (int i = 0; i < 3 + size; ++i) {
            for (int j = 0; j < size * point_width + 4; ++j) {
                arena[i][j] = ' ';
            }
        }

        for (int i = 0; i < size * point_width; ++i) {
            arena[0][4 + i] = '~';
        }
        for (int i = 1; i < size + 1; ++i) {
            arena[i][0] = char(i / 10 + '0');
            arena[i][1] = char(i % 10 + '0');
            arena[i][2] = '|';
            arena[i][size * point_width + 3] = '|';
        }
        for (int i = 0; i < size * point_width; ++i) {
            arena[size + 1][4 + i] = '~';
        }
        for (int i = 0; i < size; ++i) {
            if (i > 9) {
                arena[size + 2][2 + 2 * i] = char(i / 10 + '0');
            }
            else {
                arena[size + 2][2 + 2 * i] = ' ';
            }
            arena[size + 2][3 + 2 * i] = char(i % 10 + '0');
        }
    }

    void stand(const Character& character) {
        Point2D pos = character.getPosition();
        for (int i = 0; i < character.shown.size(); ++i) {
            arena[1 + pos.getX()][3 + pos.getY() * point_width + i] = character.shown[i];
        }
    }

    void display() const {
        for (int i = 0; i < 3 + size; ++i) {
            for (int j = 0; j < size * point_width + 4; ++j) {
                std::cout << arena[i][j];
            }
            std::cout << std::endl;
        }
    }

    bool isIn(int x, int y) const {
        return x >= 0 && x < size && y >= 0 && y < size;
    }

    void clearPosition(int x, int y) {
        if (isIn(x, y)) {
            arena[1 + x][3 + y * point_width] = ' ';
            arena[1 + x][3 + y * point_width + 1] = ' ';
        }
    }
};

void MakeStep(Arena& arena, Character& unit_, int predatorX, int predatorY, int newPredatorX, int newPredatorY) {
    if (arena.isIn(newPredatorX, newPredatorY)) {
        arena.clearPosition(predatorX, predatorY);
        unit_.move(newPredatorX - predatorX, newPredatorY - predatorY);
        arena.stand(unit_);
    }
}

int sgn(int a) {
    if (a > 0) {
        return 1;
    }
    else if (a < 0) {
        return -1;
    }
    return 0;
}
int main() {
    setlocale(LC_ALL, "rus");
    int character;
    std::cout << "Выберите персонажа:\n1 - Хищник\n2 - Жертва\n";
    std::cin >> character;
    while (character != 1 && character != 2) {
        std::cout << "Некорректный выбор персонажа. Выберите:\n1 - Хищник\n2 - Жертва\n";
        std::cin >> character;
    }
    Arena arena;
    Prey prey(10, 10);
    Predator predator(20, 20);
    arena.stand(prey);
    arena.stand(predator);

    if (character == 1) {
        std::cout << "Вы выбрали Хищника\n";
    }
    else {
        std::cout << "Вы выбрали Жертву\n";
    }

    if (character == 1) {
        int flag = 0;

        while (true) {
            arena.display();

            if (flag == 1) {
                std::cout << "Некорректное направление хода или число шагов\n";
            }
            flag = 0;
            int moveDirection;
            std::cout << "Выберите направление хода:\n1 - Влево\n2 - Вниз\n3 - Вправо\n4 - Вверх\n";
            std::cin >> moveDirection;

            int moveSteps;
            std::cout << "Выберите количество шагов от 1 до 3\n";
            std::cin >> moveSteps;

            int deltaX = 0, deltaY = 0;
            if (moveSteps <= 3) {
                if (moveDirection == 1) { deltaY = -moveSteps; }
                else if (moveDirection == 2) { deltaX = moveSteps; }
                else if (moveDirection == 3) { deltaY = moveSteps; }
                else if (moveDirection == 4) { deltaX = -moveSteps; }
                else {
                    flag = 1;
                    system("clear");
                    continue;
                }
            }
            else {
                flag = 1;
                system("clear");
                continue;
            }

            int newPredatorX = predator.getPosition().getX() + deltaX;
            int newPredatorY = predator.getPosition().getY() + deltaY;
            MakeStep(arena, predator, predator.getPosition().getX(), predator.getPosition().getY(), newPredatorX, newPredatorY);
            if (prey.getPosition().getX() == predator.getPosition().getX() && prey.getPosition().getY() == predator.getPosition().getY()) {
                std::cout << "Хищник поймал жертву! Конец игры.\n";
                break;
            }
            deltaX = 0, deltaY = 0;
            deltaX = sgn(predator.getPosition().getX() - prey.getPosition().getX());
            deltaY = sgn(predator.getPosition().getY() - prey.getPosition().getY());
            while (deltaX == 0 && deltaY == 0) {
                deltaX = rand() % 3 - 1;
                deltaY = rand() % 3 - 1;
            }
            int newPreyX = prey.getPosition().getX() + deltaX;
            int newPreyY = prey.getPosition().getY() + deltaY;
            MakeStep(arena, prey, prey.getPosition().getX(), prey.getPosition().getY(), newPreyX, newPreyY);
            if (prey.getPosition().getX() == predator.getPosition().getX() && prey.getPosition().getY() == predator.getPosition().getY()) {
                std::cout << "Жертва пришла к охотнику! Конец игры.\n";
                break;
            }
            system("clear");
        }
    }
    int flag = 0;
    if (character == 2) {
        while (true) {
            arena.display();
            if (flag == 1) {
                std::cout << "Некорректное направление хода.\n";
            }
            flag = 0;
            int moveDirection;
            std::cout << "Выберите направление хода:\n1 - Влево\n2 - Вниз\n3 - Вправо\n4 - Вверх\n5 - Влево-вниз\n6 - Влево-вверх\n7 - Вправо-вниз\n8 - Вправо-вверх\n";
            std::cin >> moveDirection;
            int deltaX = 0, deltaY = 0;
            if (moveDirection == 1) { deltaY = -1; }
            else if (moveDirection == 2) { deltaX = 1; }
            else if (moveDirection == 3) { deltaY = 1; }
            else if (moveDirection == 4) { deltaX = -1; }
            else if (moveDirection == 5) { deltaY = -1; deltaX = 1; }
            else if (moveDirection == 6) { deltaY = -1; deltaX = -1; }
            else if (moveDirection == 7) { deltaY = 1; deltaX = 1; }
            else if (moveDirection == 8) { deltaY = 1; deltaX = -1; }
            else {
                std::cin.clear();
                flag = 1;
                system("clear");
                continue;
            }
            int newPreyX = prey.getPosition().getX() + deltaX;
            int newPreyY = prey.getPosition().getY() + deltaY;
            MakeStep(arena, prey, prey.getPosition().getX(), prey.getPosition().getY(), newPreyX, newPreyY);
            int predatorX = predator.getPosition().getX();
            int predatorY = predator.getPosition().getY();
            int preyX = prey.getPosition().getX();
            int preyY = prey.getPosition().getY();
            deltaX = 0, deltaY = 0;
            if (abs(predatorX - preyX) > abs(predatorY - preyY)) {
                deltaX = preyX - predatorX;
                if (abs(deltaX) > 3) {
                    deltaX = 3 * (deltaX / abs(deltaX));
                }
            }
            else {
                deltaY = preyY - predatorY;
                if (abs(deltaY) > 3) {
                    deltaY = 3 * (deltaY / abs(deltaY));
                }
            }
            int newPredatorX = predatorX + deltaX;
            int newPredatorY = predatorY + deltaY;
            MakeStep(arena, predator, predatorX, predatorY, newPredatorX, newPredatorY);
            if (prey.getPosition().getX() == predator.getPosition().getX() && prey.getPosition().getY() == predator.getPosition().getY()) {
                std::cout << "Хищник поймал жертву! Конец игры.\n";
                break;
            }
            system("clear");
        }
    }
    return 0;
}
