#include <iostream>
#include <string>

class Zoo {
private:
    std::string name;
    static int totalAnimals; 
    int animalCount;
    const int maxCapacity;  
    const static int roomPerAni = 10; 
    friend class ZooInspector;

public:
    Zoo(const std::string& n, int count, int capacity) 
        : name(n), animalCount(count), maxCapacity(capacity) {
        totalAnimals += animalCount; 
    }

    ~Zoo() {
        totalAnimals -= animalCount; 
    }

    int getAnimalCount() const {
        return animalCount;
    }

    std::string getName() const {
        return name;
    }

    int getMaxCapacity() const {
        return maxCapacity;
    }
    bool addAnimals(int count) {
        if (animalCount + count <= maxCapacity) {
            animalCount += count;
            totalAnimals += count;
            return true;
        }
        return false;
    }
    static int getSpacePerAnimal() {
        return roomPerAni;
    }

    static int getTotalAnimals() {
        return totalAnimals;
    }

    friend void printZooInfo(const Zoo& zoo);
};


int Zoo::totalAnimals = 0;

class ZooInspector {
public:
    void inspect(const Zoo& zoo) {

        std::cout << "insptect：" << zoo.name << " " 
                  << zoo.animalCount << " animals" << std::endl;
    }
};


void printZooInfo(const Zoo& zoo) {

    std::cout << zoo.name << "current：" << zoo.animalCount << "只" << std::endl;
}

int main() {
    std::cout << "SpacePerAnimal: " << Zoo::getSpacePerAnimal() << "个单位" << std::endl;
    std::cout << "total" << Zoo::getTotalAnimals() << std::endl;
    Zoo shanghaiZoo("sh", 500, 1000);
    Zoo beijingZoo("bj", 800, 1500);
    std::cout << "current" << shanghaiZoo.getAnimalCount() << std::endl;
    std::cout << "max" << shanghaiZoo.getMaxCapacity() << std::endl;

    if (shanghaiZoo.addAnimals(100)) {
        std::cout << "succed" << std::endl;
    } else {
        std::cout << "fail" << std::endl;
    }

    printZooInfo(shanghaiZoo);
    printZooInfo(beijingZoo);

    ZooInspector inspector;
    inspector.inspect(shanghaiZoo);
    inspector.inspect(beijingZoo);

    std::cout << "\ntotal" << Zoo::getTotalAnimals() << std::endl;

    return 0;
}