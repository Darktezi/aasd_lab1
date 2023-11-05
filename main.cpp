#include <iostream>
#include <cstdlib>
#include <ctime>
#include <random>

template <typename T>
class Vector {
private:
    T* data;
    int size;

public:
    //  онструктор с параметрами: размерность вектора и значение дл€ заполнени€
    Vector(int dimension, T value) : size(dimension) {
        data = new T[dimension];
        for (int i = 0; i < dimension; i++) {
            data[i] = value;
        }
    }

    //  онструктор, заполн€ющий вектор случайными значени€ми
    Vector(int dimension) : size(dimension) {
        if (dimension <= 0) {
            throw std::invalid_argument("Vector dimension must be greater than 0");
        }
        data = new T[dimension];
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<double> dis(0.0, 100.0);
        for (int i = 0; i < dimension; i++) {
            data[i] = static_cast<T>(dis(gen));
        }
    }

    // ƒеструктор
    ~Vector() {
        delete[] data;
    }

    // ћетод дл€ получени€ размерности вектора
    int getSize() {
        return size;
    }

    // ћетод дл€ доступа к элементам вектора по индексу
    T& operator[](int index) {
        if (index < 0 || index >= size) {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }
};

int main() {
    srand(time(0));

    Vector<int> intVector(5, 42);
    Vector<float> floatVector(3, 3.14f);
    Vector<double> doubleVector(4, 2.71828);

    // ѕример использовани€
    for (int i = 0; i < intVector.getSize(); i++) {
        std::cout << intVector[i] << " ";
    }
    std::cout << std::endl;

    for (int i = 0; i < floatVector.getSize(); i++) {
        std::cout << floatVector[i] << " ";
    }
    std::cout << std::endl;

    for (int i = 0; i < doubleVector.getSize(); i++) {
        std::cout << doubleVector[i] << " ";
    }
    std::cout << std::endl;

    Vector<int> randomIntVector(3);
    for (int i = 0; i < randomIntVector.getSize(); i++) {
        std::cout << randomIntVector[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}
