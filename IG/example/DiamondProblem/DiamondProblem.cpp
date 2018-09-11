#include <iostream>

class LivingThing {
protected:
    virtual void breathe() {}
};

class Animal : protected LivingThing {
protected:
    void breathe() {
        std::cout << "I'm breathing as an animal." << std::endl;
    }
};

class Reptile : protected LivingThing {
public:
    void crawl() {
        std::cout << "I'm crawling as a reptile." << std::endl;
    }
};

class Snake : public Animal, public Reptile {

};

int main() {
    Snake snake;

    snake.breathe();
    snake.crawl();

    return 0;
}
