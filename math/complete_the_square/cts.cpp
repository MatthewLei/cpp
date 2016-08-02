/**
 *  written by: Matthew Lei
 *  credit/reference: http://www.regentsprep.org/regents/math/algtrig/ate12/completesqlesson.htm
 *  Program for forcing a quadratic expression into a perfect square
 */
#include <iostream>
#include <tuple>
#include <cmath>
#include <string>

using namespace std;

/** 
 *  @brief read float from stdin (loop)
 *  @param dst Destination of read float
 *  @param prompt Prompt for user input
 *  @return Void
 */
void num_read(float* dst, string prompt) {
    bool cont = false;
    string input;

    do {
	cout << prompt;
	cin >> input;
	try {
	    *dst = stof(input);
	    cont = false;
	}
	catch (const std::invalid_argument& ia) {
	    cout << "must enter a number, try again\n";
	    cont = true;
	}
    } while (cont == true);
}

/**
 *  @brief complete the square (cts) function
 *  @param a The coefficient of x^2
 *  @param b The coefficient of x
 *  @param c Constant on quadratic side of the equation
 *  @param d Constant value of quadratic expression
 *  @return Void
 *
 *  Quadratic equation takes the form of a(x^2) + b(x) + c = d
 */
void cts(float a, float b, float c, float d) {
    /// step 1 - divide by highest degree coefficient
    if (a != 1) {
	b /= a;
	c /= a;
	d /= a;
	a /= a; /// a = 1
    }

    /// step 2 - subtract c
    if (c != 0) {
	d += (-1) * c;
	c += (-1) * c; /// c = 0
    }

    /// step 3 - balance both sides with (b/2)^2
    c += (b/2) * (b/2);
    d += (b/2) * (b/2);

    /// step 4 - factor perfect square
    float square_val = sqrt(c);
    cout << "completed square: (x";
    if (b < 0) {
	cout << " - ";
    } else {
	cout << " + ";
    }
    cout << square_val << ")^2 = " << d << endl;
}

int main(int argc, char** argv) {
    cout << "Completing The Square\n";
    cout << "form: A(x^2) + B(x) + C = D\n";
    bool cont = false;
    bool in_err = false;
    bool no_factor = false;
    float a, b, c, d;
    string input;
    do {
	a = 0;
	num_read(&a, "input value of A: ");
	if (a == 0) {
	    cout << "Cannot complete the square if non quadratic\n";
	    break;
	}
	b = 0;
	num_read(&b, "input value of B: ");
	c = 0;
	num_read(&c, "input value of C: ");
	d = 0;
	num_read(&d, "input value of D: ");

	/// Calculate
	cts(a, b, c, d);

	do {
	    in_err = false;
	    cout << "again? [y/n]: ";
	    cin >> input;
	    if (input == "y") {
		cont = true;
	    } else if (input == "n") {
		cont = false;
	    } else {
		in_err = true;
		cout << "please enter y or n\n";
		cin.ignore();
	    }
	} while (in_err == true);
    } while (cont == true);
    cout << "Program successfully exited\n";
}
