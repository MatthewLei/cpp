#include <iostream>
#include <fstream>

using namespace std;

/**
 *  check_input_str - checks for PNG extension
 *  @param input User input string
 *  @return True if input has PNG extension
 */
bool is_png(string input) {
    const int TERM_CHAR = 1; //1 byte for terminating \0
    int len = input.size();
    int ext_len = sizeof(".png") - TERM_CHAR;
    if (len < ext_len || input.find(".png", len - ext_len) == string::npos) {
	cout << input << " does not have .png extension\n";
	return false;
    } else {
	return true;
    }
}

void get_file_name(string &fileName) {
    cout << "PNG file name: ";
    cin >> fileName;
    while (!is_png(fileName)) {
	cout << fileName << " does not have .png extension. Try again: ";
	cin >> fileName;
    }
}

int main(int argc, char** argv) {
    string fileName;
    ifstream file;
    if (argc > 2) {
	cout << "usage: ./prog <img_name.png>\n";
	exit(0);
    } else if (argc > 1) {
	if (is_png(string(argv[1]))) {
	    fileName = string(argv[1]);
	} else {
	    exit(0);
	}
    } else {
	get_file_name(fileName);
    }

    file.open(fileName);
    while (!file.good()) {
	cout << "File does not exist, try again.\n";
	get_file_name(fileName);
	file.open(fileName);
    }
}
