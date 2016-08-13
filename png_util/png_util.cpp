//written by: Matthew Lei
//png chunk specifications: https://www.w3.org/TR/PNG-Chunks.html
//png file structure spec:  

#include <iostream>
#include <fstream>

using namespace std;

static const int SIG_SZ = 8;
static const int PNG_SIG[SIG_SZ] = {137, 80, 78, 71, 13, 10, 26, 10};

typedef struct Ihdr {
    unsigned int width;      /// 4 bytes
    unsigned int height;     /// 4 bytes
    int8_t bit_depth;        /// 1 byte
    int8_t color_type;       /// 1 byte
    int8_t compression;      /// 1 byte
    int8_t filter;           /// 1 byte
    int8_t interlace;        /// 1 byte
}Ihdr;

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


unsigned int read_4byte_uint(ifstream &fs) {
    char b1, b2, b3, b4;
    fs.get(b1);
    fs.get(b2);
    fs.get(b3);
    fs.get(b4);
    return (unsigned int) ((int) b1 + (int) b2 + (int) b3 + (int) b4);
}

/** @brief Checks for PNG file signiture
 *
 *  Checks first 8 bytes of the file for PNG
 *  file signature according to PNG specifications.
 *  sig (dec): 137, 80, 78, 71, 13, 10, 26, 10
 *  sig (ascii): \211 P N G \r \n \032 \n
 *  ref: http://www.libpng.org/pub/png/spec/1.2/PNG-Structure.html
 *
 *  @param fs File stream
 *  @return True if file has valid PNG signature
 */
bool png_check_sig(ifstream &fs) {
    char byte;
    unsigned char ubyte;
    int cur;

    cur = fs.tellg();
    fs.seekg(fs.beg);
    for (int i = 0; i < SIG_SZ; ++i) {
	fs.get(byte);
	ubyte = (unsigned char) byte;
	if ((int) ubyte != PNG_SIG[i]) {
	    cout << "file is not a PNG image or corrupted.\n";
	    return false;
	}
    }
    fs.seekg(cur);
    return true;
}

Ihdr get_ihdr_chunk(ifstream &fs) {
    Ihdr ihdr;
    char a, b, c, d;
    fs.get(a); cout << a;
    fs.get(a); cout << a;
    fs.get(a); cout << a;
    fs.get(a); cout << a;
    cout << read_4byte_uint(fs);
    /*
    fs.get(a);
    fs.get(b);
    fs.get(c);
    fs.get(d);
    cout << a << " " << b << " " << c << " " << d << endl;
    cout << (int) a << " " << (int) b << " " << (int) c << " " << (int) d << endl;
    */
    return ihdr;
}

/***************************************************************************/

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
    png_check_sig(file);
    //get_ihdr_chunk(file);
}
