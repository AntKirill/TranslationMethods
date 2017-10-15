//
// Created by kirant on 11.10.17.
//

#ifndef LAB2_PARSER_H
#define LAB2_PARSER_H

#include <string>
#include <memory>
#include <vector>
#include "lexical_analyzer.h"

class parser {

    std::shared_ptr<lexical_analyzer> lexer_ptr;

    struct node {
        std::string state_name;
        std::vector<std::shared_ptr<node>> children{};

        void add_children(std::shared_ptr<node> &v) {
            children.push_back(v);
        }

        explicit node(const std::string &state_name) noexcept : state_name(std::move(state_name)) {}
    };

    std::shared_ptr<node> S();

    std::shared_ptr<node> A();

    std::shared_ptr<node> APrime();

    std::shared_ptr<node> B();

    std::shared_ptr<node> C();

    std::shared_ptr<node> D();

public:

    struct iterator;

    parser::iterator parse(std::string file_name);

};

struct parser::iterator {
    std::string get_name() const;

    std::vector<iterator> get_all_children() const;

    friend iterator parser::parse(std::string);

private:
    std::shared_ptr<node> v;

    explicit iterator(std::shared_ptr<node> &x) noexcept : v(x) {}

    explicit iterator(std::shared_ptr<node> &&x) noexcept : v(std::move(x)) {}
};


#endif //LAB2_PARSER_H
