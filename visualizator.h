//
// Created by kirant on 15.10.17.
//

#ifndef LAB2_VISUALIZATOR_H
#define LAB2_VISUALIZATOR_H


#include <cstdio>
#include "paskal_function_header/parser.h"

FILE *png_from_tree(const parser::iterator &, std::string file_name);

#endif //LAB2_VISUALIZATOR_H
