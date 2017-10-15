#include <iostream>
#include "paskal_function_header/parser.h"
#include "visualizator.h"

using namespace std;

int main() {
    parser p;
    try {
        parser::iterator tree_it = p.parse("input.txt");
        try {
            png_from_tree(tree_it, "output");
            if (system("xdg-open output.png")) {
                cerr << "Unable to open picture of the tree" << endl;
            }
        } catch (...) {
            cerr << "Parsed successfully, but unable to visualize tree" << endl;
        }
    } catch (exception &e) {
        cerr << e.what() << endl;
        cerr << "Unable to handle such header" << endl;
    }
    return 0;
}