#include <iostream>
#include "paskal_function_header/parser.h"
#include "visualizator.h"

using namespace std;

void go(const std::string &test_file_name, const std::string &answer_file_name) {
    parser p;
    try {
        parser::iterator tree_it = p.parse(test_file_name);
        try {
            png_from_tree(tree_it, answer_file_name);
            if (test_file_name == "input.txt") {
                if (system("xdg-open output.png")) {
                    cerr << "Unable to open picture of the tree" << endl;
                }
            }
        } catch (...) {
            cerr << "Parsed successfully, but unable to visualize tree" << endl;
        }

    } catch (exception &e) {
        cerr << e.what() << endl;
        cerr << "Unable to handle such header" << endl;
        cerr << "Test " + test_file_name + " failed\n" << endl;
    }
}

int main() {
    const int K = 8; //amount of tests at folder tests/

    ifstream in;
    in.open("input.txt");
    string s;
    bool is = in.good();
    in.close();
    if (is) {
        go("input.txt", "output");
        return 0;
    } else {
        cerr << "input.txt not found" << endl;
        cerr << "testing on all tests of directory tests/\n" << endl;
    }

    for (int i = 1; i <= K; i++) {
        go("tests/t" + to_string(i) + ".txt", "t" + to_string(i) + "_ans");
    }
    return 0;
}