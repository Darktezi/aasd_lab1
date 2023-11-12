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
    // ����������� � �����������: ����������� ������� � �������� ��� ����������
    Vector(int dimension, T value) : size(dimension) {
        data = new T[dimension];
        for (int i = 0; i < dimension; i++) {
            data[i] = value;
        }
    }

    // �����������, ����������� ������ ���������� ����������
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

    // ����������
    ~Vector() {
        delete[] data;
    }

    // ����� ��� ��������� ����������� �������
    int getSize() {
        return size;
    }

    // ����� ��� ������� � ��������� ������� �� �������
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
};

int main() {
    srand(time(0));

    // ������ �������������

    Vector<float> floatVector1(3, 1.5f);
    Vector<float> floatVector2(3, 2.5f);
    Vector<float> floatResult = floatVector1 + floatVector2;

    // ����� �����������

    std::cout << "floatResult: ";
    for (int i = 0; i < floatResult.getSize(); i++) {
        std::cout << floatResult[i] << " ";
    }
    std::cout << std::endl;


    return 0;
}
