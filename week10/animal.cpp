#include <iostream>
#include <string>


class Animal {
protected:
    std::string name;
    int age;
    
public:
    Animal(const std::string& n, int a) : name(n), age(a) {}
    
    void eat() {
        std::cout << name << " is eating." << std::endl;
    }
    
    void eat(const std::string& food) {
        std::cout << name << " is eating " << food << "." << std::endl;
    }
    
    void sleep() {
        std::cout << name << " is sleeping." << std::endl;
    }
    
    virtual void makeSound() {
        std::cout << name << " makes a sound." << std::endl;
    }
    
    virtual void move() {
        std::cout << name << " is moving." << std::endl;
    }
    
    void showInfo() {
        std::cout << "Name: " << name << ", Age: " << age << std::endl;
    }
};


class Dog : public Animal {
private:
    std::string breed;
    
public:
    Dog(const std::string& n, int a, const std::string& b) 
        : Animal(n, a), breed(b) {}
    
    void bark() {
        std::cout << name << " barks: Woof! Woof!" << std::endl;
    }
    
    void bark(int times) {
        std::cout << name << " barks " << times << " times!" << std::endl;
    }
    
    void makeSound() override {
        std::cout << name << " barks loudly!" << std::endl;
    }
    
    void move() override {
        std::cout << name << " runs on four legs." << std::endl;
    }
    
    void fetch() {
        std::cout << name << " is fetching the ball." << std::endl;
    }
    
    void showDogInfo() {
        showInfo();
        std::cout << "Breed: " << breed << std::endl;
    }
};

int main() {
    Animal animal("Generic Animal", 5);
    animal.eat();
    animal.eat("grass");
    animal.makeSound();
    animal.move();
    animal.showInfo();
    
    std::cout << "\n--- Dog Example ---\n";
    
    Dog dog("Buddy", 3, "Golden Retriever");
    dog.eat();
    dog.eat("dog food");
    dog.sleep();
    dog.bark();
    dog.bark(3);
    dog.makeSound();
    dog.move();
    dog.fetch();
    dog.showDogInfo();
    
    std::cout << "\n--- Polymorphism ---\n";
    Animal* ptr = &dog;
    ptr->makeSound();
    ptr->move();
    
    return 0;
}
