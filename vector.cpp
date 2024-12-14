#include <iostream>
#include <vector>

// Vector class definition
class Vector {
public:
    // // Constructor for size and initialize the vector with 0s
    Vector(size_t size) : data_(size, 0.0) {}

    // Function to get vector elements from user input
    void input_elements() {
        for (size_t i = 0; i < data_.size(); ++i) {
            std::cout << "Enter element " << i + 1 << ": ";
            std::cin >> data_[i];
        }
    }

    // Function to add another vector to this vector
    void add(const Vector& other) {
        for (size_t i = 0; i < data_.size(); ++i) {
            data_[i] += other.data_[i];
        }
    }

    // Function to subtract another vector from this vector
    void subtract(const Vector& other) {
        for (size_t i = 0; i < data_.size(); ++i) {
            data_[i] -= other.data_[i];
        }
    }

    // Function to multiply this vector by a scalar
    void Scalar_Multiply(double scalar) {
        for (size_t i = 0; i < data_.size(); ++i) {
            data_[i] *= scalar;
        }
    }

    // Function for dot product with another vector
    double dot_Product(const Vector& other) const {
        double result = 0;
        for (size_t i = 0; i < data_.size(); ++i) {
            result += data_[i] * other.data_[i];
        }
        return result;
    }

    // Function to display the vector
    void display() const {
        std::cout << "[ ";
        for (size_t i = 0; i < data_.size(); ++i) {
            std::cout << data_[i] << " ";
        }
        std::cout << "]\n";
    }

private:
    std::vector<double> data_;
};

// Function to get a vector from the user
Vector vector_from_user() {
    size_t size;
    std::cout << "Size of the vector: ";
    std::cin >> size;

    Vector v(size);
    std::cout << "***Enter the elements of the vector***\n";
    v.input_elements();
    return v;
}

int main() {
    // To get the first vector from the user
    std::cout << "**Tell me about your frist vector-(^_^)!!!\n";
    Vector v1 = vector_from_user();

    // To get the second vector from the user
    std::cout << "\n***Tell me about your second vector-(^_^)!!!\n";
    Vector v2 = vector_from_user();

    //Operations and display results
    std::cout << "\n--- Results of your Operations ---\n";
    
    std::cout << "\nv1: ";
    v1.display();

    std::cout << "v2: ";
    v2.display();

    // Addition of v2 to v1
    v1.add(v2);
    std::cout << "v1 + v2: ";
    v1.display();

    // Subtraction of v2 from v1
    v1.subtract(v2);
    std::cout << "v1 - v2: ";
    v1.display();

    // To get a scalar and multiply v1 by it
    double scalar;
    std::cout << "Give me a scalar value to multiply v1: ";
    std::cin >> scalar;
    v1.Scalar_Multiply(scalar);
    std::cout << "v1 * " << scalar << ": ";
    v1.display();

    // Dot product of v1 and v2
    double dot = v1.dot_Product(v2);
    std::cout << "Dot product of v1 and v2: " << dot << "\n";

    return 0;
}