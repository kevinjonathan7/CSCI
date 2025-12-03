#include <iostream>
#include <iomanip> // For setw and setprecision

using namespace std;

// Template function to calibrate a value
template <typename S>
S calibrateValue(const S &x, char factor) {
    return x * (factor - '0'); // Convert char digit to numeric value
}

// Function to adjust a reading using pointer and default argument
void adjustReading(double *value, double offset = 1.25) {
    *value += offset; // Pointer used to modify value in-place
}

// Function to clamp a reading within 0 to 100
void clampReading(double &r) { // Reference used for in-place modification
    if (r < 0) r = 0;
    if (r > 100) r = 100;
}

// Function to compute difference
double computeDifference(int a, double b) {
    return a - b;
}

int main() {
    int intSensor;
    double doubleSensor;

    // Input sensor readings
    cout << "Enter integer sensor reading: ";
    cin >> intSensor;
    cout << "Enter double sensor reading: ";
    cin >> doubleSensor;

    // Step 1: Calibrate both readings by factor 2
    int calibratedInt = calibrateValue(intSensor, '2'); 
    double calibratedDouble = calibrateValue(doubleSensor, '2');

    cout << fixed << setprecision(4); // Set precision for floating-point output

    // Display calibrated values
    cout << setw(40) << left << "Calibrated integer sensor" << setw(10) << right << calibratedInt << endl;
    cout << setw(40) << left << "Calibrated double sensor" << setw(10) << right << calibratedDouble << endl;

    // Step 2: Convert integer to double
    double intAsDouble = static_cast<double>(calibratedInt);

    // Step 3: Adjust readings
    adjustReading(&intAsDouble);              // Using default offset 1.25
    adjustReading(&calibratedDouble, 3.4);   // Using specified offset 3.4

    // Display adjusted readings
    cout << setw(40) << left << "Adjusted integer sensor (double)" << setw(10) << right << intAsDouble << endl;
    cout << setw(40) << left << "Adjusted double sensor" << setw(10) << right << calibratedDouble << endl;

    // Step 4: Clamp readings to 0-100
    clampReading(intAsDouble);
    clampReading(calibratedDouble);

    // Display clamped readings
    cout << setw(40) << left << "Clamped integer sensor (double)" << setw(10) << right << intAsDouble << endl;
    cout << setw(40) << left << "Clamped double sensor" << setw(10) << right << calibratedDouble << endl;

    // Step 5: Convert adjusted integer back to int
    int finalInt = static_cast<int>(intAsDouble);
    cout << setw(40) << left << "Final integer sensor (after conversion)" << setw(10) << right << finalInt << endl;

    // Step 6: Compute difference between double and integer sensor readings
    double diff = computeDifference(finalInt, calibratedDouble);
    cout << setw(40) << left << "Difference between integer and double sensor" << setw(10) << right << diff << endl;

    return 0;
}
