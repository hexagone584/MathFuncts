#include <iostream>
#include <cmath>

const int taylorUpperLimit = 7;
const double derivativeH = 5e-7;
const double PI = 3.1415926;


int factorial(int num) {
    int returnValue = num;
    for (int i = num-1; i > 0; i--) {
        returnValue *= i;
    }
    return returnValue;
}

double sin(double x) {
    double newX = x;
    int sign = 1;
    //flip those negatives!
    if (x < 0) {
        newX *= -1;
        sign *= -1;
    }

    //TODO: look up fmod
    //converting to [0,2pi] range
    while (newX >= 2 * PI) {
        newX -= 2 * PI;
    }

    //ok now onto PI, sign retains our output sign b/c we're shortening to pi/2 range
    if (newX > PI) {
        sign *= -1;
        newX -= PI;
    }
    //ideal range is pi/2, so that's what we're doing
    if (newX > PI/2) {
        newX = PI - newX;
    }

    double returnVal = 0;
    for (int i = 0; i < taylorUpperLimit; i++) {
        returnVal += (pow(-1,i) * pow(newX,2*i+1)) / factorial(2*i+1);
    }

    return returnVal * sign;
}

double cos(double x) {
    return sin(x + PI/2);
}

//tan might cause me some trouble
double tan(double x) {
    double denom = cos(x);
    return denom == 0 ? NAN : sin(x)/denom;
}

//cotan might cause me some trouble
double cot(double x) {
    double denom = sin(x);
    return denom == 0 ? NAN : cos(x)/denom;
}

double sec(double x) {
    double denom = cos(x);
    return denom == 0 ? NAN : cos(x)/denom;
}

double csc(double x) {
    double denom = sin(x);
    return denom == 0 ? NAN : sin(x)/denom;
}

int main() {
    double target = 86.5;
    double current = 0.0;
    double cosinefactor = 1;
    double xVal = 1;
    double yVal = 0;

    for (int i = 0; i < 5; i++) {
        double rotation = std::atan(std::pow(2,-i)) * 180 / PI; //is it rly PI that messes me up?
        cosinefactor *= std::cos(std::atan(std::pow(2,-i)));

        if (current < target) {
            current += rotation;
        } else {
            current -= rotation;
        }

        //this needs to be done before tan is updated
        //I needed temporary values because doing the operation on x would screw up on y
        double tempX = xVal;
        double tempY = yVal;
        //we're doing powers of 2 cuz our special angles have tan(t)=powers of 2
        xVal = xVal - std::pow(2,-i) * tempY;
        yVal = yVal + std::pow(2,-i) * tempX;
    }
    std::cout << "target: " << target << std::endl << "current: " << current << std::endl;
    std::cout << "cosine factor: "<< cosinefactor << std::endl;
    std::cout << "x value: " << xVal << std::endl << "y value: "<< yVal;
    return 0;
}