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
    // Конструктор с параметрами: размерность вектора и значение для заполнения
    Vector(int dimension, T value) : size(dimension) {
        data = new T[dimension];
        for (int i = 0; i < dimension; i++) {
            data[i] = value;
        }
    }

    // Конструктор, заполняющий вектор случайными значениями
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

    // Деструктор
    ~Vector() {
        delete[] data;
    }

    // Метод для получения размерности вектора
    int getSize() {
        return size;
    }

    // Метод для доступа к элементам вектора по индексу
    T& operator[](int index) {
        if (index < 0 || index >= size) {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }

    const T& operator[](int index) const{
        if (index < 0 || index >= size) {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }

    // Оператор сложения векторов
    Vector<T> operator+(const Vector<T>& other) const {
        if (size != other.size) {
            throw std::invalid_argument("Vectors must have the same dimension");
        }

        Vector<T> result(size);
        for (int i = 0; i < size; i++) {
            result[i] = data[i] + other[i];
        }
        return result;
    }

    // Оператор вычитания векторов
    Vector<T> operator-(const Vector<T>& other) const {
        if (size != other.size) {
            throw std::invalid_argument("Vectors must have the same dimension");
        }

        Vector<T> result(size);
        for (int i = 0; i < size; i++) {
            result[i] = data[i] - other[i];
        }
        return result;
    }

    // Оператор умножения, выполняющий скалярное произведение векторов
    T operator*(const Vector<T>& other) const {
        if (size != other.size) {
            throw std::invalid_argument("Vectors must have the same dimension");
        }

        T result = 0;
        for (int i = 0; i < size; i++) {
            result += data[i] * other[i];
        }
        return result;
    }

    // Оператор умножения вектора на скаляр (коммутативный)
    Vector<T> operator*(const T& scalar) const {
        Vector<T> result(size);
        for (int i = 0; i < size; i++) {
            result[i] = data[i] * scalar;
        }
        return result;
    }

    // Дружественная функция для обеспечения коммутативности
    friend Vector<T> operator*(const T& scalar, const Vector<T>& vector) {
        return vector * scalar;
    }
};

int main() {
    srand(time(0));

    Vector<int> intVector(3, 2);
    Vector<int> intResult = intVector * 3;
    Vector<int> intResultComm = 3 * intVector;

    Vector<float> floatVector(3, 1.5f);
    Vector<float> floatResult = floatVector * 2.0f;
    Vector<float> floatResultComm = 2.0f * floatVector;

    Vector<double> doubleVector(3, 1.234);
    Vector<double> doubleResult = doubleVector * 1.5;
    Vector<double> doubleResultComm = 1.5 * doubleVector;

    // Вывод результатов
    std::cout << "intResult: ";
    for (int i = 0; i < intResult.getSize(); i++) {
        std::cout << intResult[i] << " ";
    }
    std::cout << std::endl;

    std::cout << "intResultComm: ";
    for (int i = 0; i < intResultComm.getSize(); i++) {
        std::cout << intResultComm[i] << " ";
    }
    std::cout << std::endl;

    std::cout << "floatResult: ";
    for (int i = 0; i < floatResult.getSize(); i++) {
        std::cout << floatResult[i] << " ";
    }
    std::cout << std::endl;

    std::cout << "floatResultComm: ";
    for (int i = 0; i < floatResultComm.getSize(); i++) {
        std::cout << floatResultComm[i] << " ";
    }
    std::cout << std::endl;

    std::cout << "doubleResult: ";
    for (int i = 0; i < doubleResult.getSize(); i++) {
        std::cout << doubleResult[i] << " ";
    }
    std::cout << std::endl;

    std::cout << "doubleResultComm: ";
    for (int i = 0; i < doubleResultComm.getSize(); i++) {
        std::cout << doubleResultComm[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}
