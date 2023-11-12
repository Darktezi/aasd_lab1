#include <iostream>
#include <cstdlib>
#include <ctime>
#include <random>
#include <complex>

template <typename T>
class Vector {
private:
    T* _data;
    int _size;

public:
    //  онструктор с параметрами: размерность вектора и значение дл€ заполнени€
    Vector(int dimension, T value) : _size(dimension) {
        _data = new T[dimension];
        for (int i = 0; i < dimension; ++i) {
            _data[i] = value;
        }
    }

    //  онструктор, заполн€ющий вектор случайными значени€ми
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

    // ƒеструктор
    ~Vector() {
        delete[] _data;
    }

    // ћетод дл€ получени€ размерности вектора
    int get_size() {
        return _size;
    }

    // ћетод дл€ доступа к элементам вектора по индексу
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

    // ќператор сложени€ векторов
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

    // ќператор вычитани€ векторов
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

    // ќператор умножени€, выполн€ющий скал€рное произведение векторов
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

    // ќператор умножени€ вектора на скал€р (коммутативный)
    Vector<T> operator*(const T& scalar) const {
        Vector<T> result(_size);
        for (int i = 0; i < _size; ++i) {
            result[i] = _data[i] * scalar;
        }
        return result;
    }

    // ƒружественна€ функци€ дл€ обеспечени€ коммутативности
    friend Vector<T> operator*(const T& scalar, const Vector<T>& vector) {
        return vector * scalar;
    }

    // ќператор делени€ вектора на скал€р
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

    // ќператор сложени€ векторов
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

    // ќператор вычитани€ векторов
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

    // ќператор умножени€ дл€ скал€рного произведени€ векторов
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

    // ќператор умножени€ вектора на скал€р (коммутативный)
    Vector<std::complex<T>> operator*(const T& scalar) const {
        Vector<std::complex<T>> result(_size);
        for (int i = 0; i < _size; ++i) {
            result[i] = _data[i] * scalar;
        }
        return result;
    }

    // ƒружественна€ функци€ дл€ обеспечени€ коммутативности умножени€ вектора на скал€р
    friend Vector<std::complex<T>> operator*(const T& scalar, const Vector<std::complex<T>>& vector) {
        return vector * scalar;
    }

    // ќператор делени€ вектора на скал€р
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
};

int main() {
    srand(time(0));

    return 0;
}
