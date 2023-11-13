#include <iostream>
#include <cstdlib>
#include <ctime>
#include <random>
#include <complex>
#include <cmath>
#include <iomanip>

template <typename T>
class Vector {
private:
    T* _data;
    int _size;

public:
    // Конструктор с параметрами: размерность вектора и значение для заполнения
    Vector(int dimension, T value) : _size(dimension) {
        _data = new T[dimension];
        for (int i = 0; i < dimension; ++i) {
            _data[i] = value;
        }
    }

    // Конструктор, заполняющий вектор случайными значениями
    Vector(int dimension) : _size(dimension) {
        if (dimension <= 0) {
            throw std::invalid_argument("Vector dimension must be greater than 0");
        }
        _data = new T[dimension];
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<double> dis(0.0, 100.0);
        for (int i = 0; i < dimension; ++i) {
            _data[i] = static_cast<T>(dis(gen));
        }
    }

    // Конструктор копирования
    Vector(const Vector<T>& other) : _size(other._size) {
        _data = new T[_size];
        std::copy(other._data, other._data + _size, _data);
    }

    // Оператор присваивания
    Vector<T>& operator=(const Vector<T>& other) {
        if (this != &other) {
            delete[] _data; // Release existing resources
            _size = other._size;
            _data = new T[_size];
            std::copy(other._data, other._data + _size, _data);
        }
        return *this;
    }

    // Деструктор
    ~Vector() {
        delete[] _data;
    }

    // Метод для получения размерности вектора
    int get_size() const{
        return _size;
    }

    // Метод для доступа к элементам вектора по индексу
    T& operator[](int index) {
        if (index < 0 || index >= _size) {
            throw std::out_of_range("Index out of range");
        }
        return _data[index];
    }

    const T& operator[](int index) const{
        if (index < 0 || index >= _size) {
            throw std::out_of_range("Index out of range");
        }
        return _data[index];
    }

    // Оператор сложения векторов
    Vector<T> operator+(const Vector<T>& other) const {
        if (_size != other._size) {
            throw std::invalid_argument("Vectors must have the same dimension");
        }

        Vector<T> result(_size);
        for (int i = 0; i < _size; ++i) {
            result[i] = _data[i] + other[i];
        }
        return result;
    }

    // Оператор вычитания векторов
    Vector<T> operator-(const Vector<T>& other) const {
        if (_size != other._size) {
            throw std::invalid_argument("Vectors must have the same dimension");
        }

        Vector<T> result(_size);
        for (int i = 0; i < _size; ++i) {
            result[i] = _data[i] - other[i];
        }
        return result;
    }

    // Оператор умножения, выполняющий скалярное произведение векторов
    T operator*(const Vector<T>& other) const {
        if (_size != other._size) {
            throw std::invalid_argument("Vectors must have the same dimension");
        }

        T result = 0;
        for (int i = 0; i < _size; ++i) {
            result += _data[i] * other[i];
        }
        return result;
    }

    // Оператор умножения вектора на скаляр (коммутативный)
    Vector<T> operator*(const T& scalar) const {
        Vector<T> result(_size);
        for (int i = 0; i < _size; ++i) {
            result[i] = _data[i] * scalar;
        }
        return result;
    }

    // Дружественная функция для обеспечения коммутативности
    friend Vector<T> operator*(const T& scalar, const Vector<T>& vector) {
        return vector * scalar;
    }

    // Оператор деления вектора на скаляр
    Vector<T> operator/(const T& scalar) const {
        if (scalar == 0) {
            throw std::invalid_argument("Division by zero");
        }

        Vector<T> result(_size);
        for (int i = 0; i < _size; ++i) {
            result[i] = _data[i] / scalar;
        }
        return result;
    }

    // Вывод вектора
    friend std::ostream& operator<<(std::ostream& os, const Vector<T>& vector) {
        os << "(";
        for (int i = 0; i < vector._size; ++i) {
            os << vector[i];
            if (i < vector._size - 1) {
                os << ", ";
            }
        }
        os << ")";
        return os;
    }

    Vector<T> normalize() const{
        T magnitude = std::sqrt((*this) * (*this));  // Длина вектора
        return (*this) / magnitude;
    }
};

template <typename T>
class Vector<std::complex<T>> {
private:
    std::complex<T>* _data;
    int _size;

public:
    Vector(int dimension, const std::complex<T>& value) : _size(dimension) {
        _data = new std::complex<T>[dimension];
        for (int i = 0; i < dimension; ++i) {
            _data[i] = value;
        }
    }

    Vector(int dimension) : _size(dimension) {
        if (dimension <= 0) {
            throw std::invalid_argument("Vector dimension must be greater than 0");
        }
        _data = new std::complex<T>[dimension];
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<T> dis(-1.0, 1.0);
        for (int i = 0; i < dimension; ++i) {
            T realPart = dis(gen);
            T imagPart = dis(gen);
            _data[i] = std::complex<T>(realPart, imagPart);
        }
    }

    // Конструктор копирования
    Vector(const Vector <std::complex<T>>& other) : _size(other._size) {
        _data = new std::complex<T>[_size];
        std::copy(other._data, other._data + _size, _data);
    }

    // Оператор присваивания
    Vector <std::complex <T>>& operator=(const Vector <std::complex<T>>& other) {
        if (this != &other) {
            delete[] _data; // Release existing resources
            _size = other._size;
            _data = new std::complex<T>[_size];
            std::copy(other._data, other._data + _size, _data);
        }
        return *this;
    }

    ~Vector() {
        delete[] _data;
    }

    int get_size() const {
        return _size;
    }

    std::complex<T>& operator[](int index) {
        if (index < 0 || index >= _size) {
            throw std::out_of_range("Index out of range");
        }
        return _data[index];
    }

    const std::complex<T>& operator[](int index) const{
        if (index < 0 || index >= _size) {
            throw std::out_of_range("Index out of range");
        }
        return _data[index];
    }

    // Оператор сложения векторов
    Vector<std::complex<T>> operator+(const Vector<std::complex<T>>& other) const {
        if (_size != other._size) {
            throw std::invalid_argument("Vectors must have the same dimension for addition");
        }

        Vector<std::complex<T>> result(_size);
        for (int i = 0; i < _size; ++i) {
            result[i] = _data[i] + other[i];
        }
        return result;
    }

    // Оператор вычитания векторов
    Vector<std::complex<T>> operator-(const Vector<std::complex<T>>& other) const {
        if (_size != other._size) {
            throw std::invalid_argument("Vectors must have the same dimension for subtraction");
        }

        Vector<std::complex<T>> result(_size);
        for (int i = 0; i < _size; ++i) {
            result[i] = _data[i] - other[i];
        }
        return result;
    }

    // Оператор умножения для скалярного произведения векторов
    std::complex<T> operator*(const Vector<std::complex<T>>& other) const {
        if (_size != other._size) {
            throw std::invalid_argument("Vectors must have the same dimension for scalar product");
        }

        std::complex<T> result(0, 0);
        for (int i = 0; i < _size; ++i) {
            result += _data[i] * (std::conj(other[i]));
        }
        return result;
    }

    // Оператор умножения вектора на скаляр (коммутативный)
    Vector<std::complex<T>> operator*(const std::complex<T>& scalar) const {
        Vector<std::complex<T>> result(_size);
        for (int i = 0; i < _size; ++i) {
            result[i] = _data[i] * scalar;
        }
        return result;
    }

    // Дружественная функция для обеспечения коммутативности умножения вектора на скаляр
    friend Vector<std::complex<T>> operator*(const std::complex<T>& scalar, const Vector<std::complex<T>>& vector) {
        return vector * scalar;
    }

    // Оператор деления вектора на скаляр
    Vector<std::complex<T>> operator/(const T& scalar) const {
        if (scalar == 0) {
            throw std::invalid_argument("Division by zero");
        }

        Vector<std::complex<T>> result(_size);
        for (int i = 0; i < _size; ++i) {
            result[i] = _data[i] / scalar;
        }
        return result;
    }

    // Вывод вектора
    friend std::ostream& operator<<(std::ostream& os, const Vector<std::complex<T>>& vector) {
        os << "(";
        for (int i = 0; i < vector._size; ++i) {
            os << vector[i];
            if (i < vector._size - 1) {
                os << ", ";
            }
        }
        os << ")";
        return os;
    }

    Vector<std::complex<T>> normalize() {
        T magnitude = std::sqrt((*this) * (*this)).real();  // Длина вектора
        return (*this) / magnitude;
    }
};

template <typename T>
Vector<T> findPerpendicularUnitVector(const Vector<T>& v) {
    if (v.get_size() < 2) {
        throw std::invalid_argument("Vector dimension must be at least 2");
    }

    Vector<T> u_perpendicular(v.get_size(), 0);

    u_perpendicular[0] = -v[1];
    u_perpendicular[1] = v[0];

    return u_perpendicular.normalize();
}

template <typename T>
Vector<std::complex<T>> findPerpendicularUnitVector(const Vector<std::complex<T>>& v) {
    if (v.get_size() < 2) {
        throw std::invalid_argument("Vector dimension must be at least 2");
    }

    Vector<std::complex<T>> u_perpendicular(v.get_size(), std::complex<T>(0,0));

    u_perpendicular[0] = -v[1];
    u_perpendicular[1] = v[0];

    return u_perpendicular.normalize();
}



int main() {
    srand(time(0));
  
    // Заданный вектор
    Vector<double> v(2);

    // Перпендикулярный единичный вектор
    Vector<double> perpendicular = findPerpendicularUnitVector(v);

    // Выводим результаты
    std::cout << "Original Vector: " << v << std::endl;
    std::cout << "Perpendicular Unit Vector: " << perpendicular << std::endl;

    std::cout << std::endl;

    // Заданный комплексный вектор
    Vector<std::complex<double>> complex_v(2);

    // Перпендикулярный единичный вектор
    Vector<std::complex<double>> complex_perpendicular = findPerpendicularUnitVector(complex_v);

    // Выводим результаты
    std::cout << "Original Complex Vector: " << complex_v << std::endl;
    std::cout << "Perpendicular Unit Vector: " << complex_perpendicular << std::endl;

    return 0;
}
