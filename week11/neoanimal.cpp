#include <iostream>
#include <string>

class Label {
private:
    char color[20];
public:
    Label(const char* c) {
        strcpy(color, c);
        std::cout << "Label constructor: " << color << std::endl;
    }
    ~Label() {
        std::cout << "Label destructor: " << color << std::endl;
    }
};

class Animal {
protected:
    std::string name;
    int age;
    Label label;
    
public:
    Animal(const std::string& n, int a, const char* c) 
        : name(n), age(a), label(c) {
        std::cout << "Animal constructor: " << name << std::endl;
    }
    
    virtual ~Animal() {
        std::cout << "Animal destructor: " << name << std::endl;
    }
    
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
    Label tag;
    
public:
    Dog(const std::string& n, int a, const char* c, const std::string& b, const char* t) 
        : Animal(n, a, c), breed(b), tag(t) {
        std::cout << "Dog constructor: " << name << std::endl;
    }
    
    ~Dog() {
        std::cout << "Dog destructor: " << name << std::endl;
    }
    
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
    Animal animal("Generic Animal", 5, "red");
    std::cout << std::endl;
    
    Dog dog("Buddy", 3, "blue", "Golden Retriever", "yellow");
    std::cout << std::endl;
    
    Animal* ptr = &dog;
    ptr->makeSound();
    ptr->move();
    std::cout << std::endl;
    
    dog.eat();
    dog.sleep();
    std::cout << std::endl;
    
    return 0;
}
