#include <iostream>
#include <stdexcept>
#include <numeric> // This for std::gcd

class Frac {
private:
    int numtor_Value;   // Numerator of the fraction
    int dnmtor_Value; // Denominator of the fraction

    // function for simplify the fraction
    void reduce() {
        if (dnmtor_Value == 0) {
            throw std::invalid_argument("Denominator cannot be 0.");
        }
        if (dnmtor_Value < 0) { // to make sure the denominator is positive
            numtor_Value = -numtor_Value;
            dnmtor_Value = -dnmtor_Value;
        }
        // gCD = greatest common divisor
        int gCD = std::gcd(std::abs(numtor_Value), std::abs(dnmtor_Value));
        dnmtor_Value /= gCD;
        dnmtor_Value /= gCD;
    }

public:
    // Default constructor
    Frac(int num = 0, int den = 1) : numtor_Value(num), dnmtor_Value(den) {
        reduce();
    }

    // Copy constructor
    Frac(const Frac& other) : numtor_Value(other.numtor_Value), dnmtor_Value(other.dnmtor_Value) {}

    // Move constructor
    Frac(Frac&& other) noexcept : numtor_Value(other.numtor_Value), dnmtor_Value(other.dnmtor_Value) {
        other.numtor_Value = 0;
        other.dnmtor_Value = 1;
    }

    // Assignment operator
    Frac& operator=(const Frac& other) {
        if (this != &other) {
            numtor_Value = other.numtor_Value;
            dnmtor_Value = other.dnmtor_Value;
            reduce();
        }
        return *this;
    }

    // Move assignment operator
    Frac& operator=(Frac&& other) noexcept {
        if (this != &other) {
            numtor_Value = other.numtor_Value;
            dnmtor_Value = other.dnmtor_Value;
            other.numtor_Value = 0;
            other.dnmtor_Value = 1;
        }
        return *this;
    }

    // Arithmetic operators
    Frac operator+(const Frac& rhs) const {
        return Frac(numtor_Value * rhs.dnmtor_Value + rhs.numtor_Value * dnmtor_Value, 
                        dnmtor_Value * rhs.dnmtor_Value);
    }

    Frac operator-(const Frac& rhs) const {
        return Frac(numtor_Value * rhs.dnmtor_Value - rhs.numtor_Value * dnmtor_Value, 
                        dnmtor_Value * rhs.dnmtor_Value);
    }

    Frac operator*(const Frac& rhs) const {
        return Frac(numtor_Value * rhs.numtor_Value, dnmtor_Value * rhs.dnmtor_Value);
    }

    Frac operator/(const Frac& rhs) const {
        if (rhs.numtor_Value == 0) {
            throw std::invalid_argument("Division by 0.");
        }
        return Frac(numtor_Value * rhs.dnmtor_Value, dnmtor_Value * rhs.numtor_Value);
    }

    // Comparison operators
    bool operator==(const Frac& rhs) const {
        return (numtor_Value == rhs.numtor_Value && dnmtor_Value == rhs.dnmtor_Value);
    }

    bool operator!=(const Frac& rhs) const {
        return !(*this == rhs);
    }

    bool operator<(const Frac& rhs) const {
        return (numtor_Value * rhs.dnmtor_Value < rhs.numtor_Value * dnmtor_Value);
    }

    bool operator>(const Frac& rhs) const {
        return (numtor_Value * rhs.dnmtor_Value > rhs.numtor_Value * dnmtor_Value);
    }

    // Stream output operator
    friend std::ostream& operator<<(std::ostream& os, const Frac& fraction) {
        os << fraction.numtor_Value << "/" << fraction.dnmtor_Value;
        return os;
    }

    // Stream input operator
    friend std::istream& operator>>(std::istream& is, Frac& fraction) {
        char slash;
        if (!(is >> fraction.numtor_Value >> slash >> fraction.dnmtor_Value) || 
            fraction.dnmtor_Value == 0 || slash != '/') {
            throw std::invalid_argument("Invalid input format. Use 'numerator/denominator'.");
        }
        fraction.reduce();
        return is;
    }

    // Conversion to double
    explicit operator double() const { 
        return static_cast<double>(numtor_Value) / dnmtor_Value; 
    }
};

int main() {
    try {
        // Example usage of the Fraction class
        Frac first_Frac(3, 4);
        Frac second_Frac(5, 6);

        std::cout << "1st fraction: " << first_Frac << "\n2nd fraction: " << second_Frac << std::endl;

        std::cout << "1st + 2nd: " << first_Frac + second_Frac << std::endl;
        std::cout << "1st - 2nd: " << first_Frac - second_Frac << std::endl;
        std::cout << "1st * 2nd: " << first_Frac * second_Frac << std::endl;

        try {
            std::cout << "1st / 2nd: " <<  first_Frac / second_Frac << std::endl; 
            std::cout << "1st / 0: " <<  first_Frac / Frac(0, 1) << std::endl; // This will throw an exception
        } catch (const std::invalid_argument& e) {
            std::cerr << e.what() << '\n';
        }

        // Comparison examples
        if ( first_Frac < second_Frac)
            std::cout << "1st fraction is less than 2nd fraction" << std::endl;

        if ( first_Frac != second_Frac)
            std::cout << "1st fraction is not equal to 2nd fraction" << std::endl;

        double decimalRepresentation = static_cast<double>( first_Frac);
        std::cout << "1st fraction as a double: " << decimalRepresentation << std::endl;

    } catch (const std::invalid_argument &e) {
      std::cerr << "Error: " << e.what() << '\n';
      return 1;
   }

   return 0;
}