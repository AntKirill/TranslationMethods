//
// Created by kirant on 11.10.17.
//

#include <cassert>
#include "parser.h"
#include "parse_exception.h"

std::shared_ptr<parser::node> parser::S()  {
    node res("S");
    auto ch1 = std::make_shared<node>("function");
    std::shared_ptr<node> ch2;
    auto ch3 = std::make_shared<node>("(");
    std::shared_ptr<node> ch4;
    auto ch5 = std::make_shared<node>(")");
    auto ch6 = std::make_shared<node>(":");
    std::shared_ptr<node> ch7;
    auto ch8 = std::make_shared<node>(";");
    switch (lexer_ptr->get_cur_token()) {
        case token::FUNCTION :
            res.add_children(ch1);
            lexer_ptr->next_token();

            assert(lexer_ptr->get_cur_token() == token::NAME);
            ch2 = std::make_shared<node>(lexer_ptr->get_cur_attribute());
            res.add_children(ch2);
            lexer_ptr->next_token();

            assert(lexer_ptr->get_cur_token() == token::LBR);
            res.add_children(ch3);
            lexer_ptr->next_token();

            ch4 = A();
            res.add_children(ch4);

            assert(lexer_ptr->get_cur_token() == token::RBR);
            res.add_children(ch5);
            lexer_ptr->next_token();

            assert(lexer_ptr->get_cur_token() == token::DOTDOT);
            res.add_children(ch6);
            lexer_ptr->next_token();

            assert(lexer_ptr->get_cur_token() == token::NAME);
            ch7 = std::make_shared<node>(lexer_ptr->get_cur_attribute());
            res.add_children(ch7);
            lexer_ptr->next_token();

            assert(lexer_ptr->get_cur_token() == token::DOTCOMA);
            res.add_children(ch8);
            lexer_ptr->next_token();

            assert(lexer_ptr->get_cur_token() == token::END);
            break;
        case token::PROCEDURE :
            res.add_children(ch1);
            lexer_ptr->next_token();

            assert(lexer_ptr->get_cur_token() == token::NAME);
            ch2 = std::make_shared<node>(lexer_ptr->get_cur_attribute());
            res.add_children(ch2);
            lexer_ptr->next_token();

            assert(lexer_ptr->get_cur_token() == token::LBR);
            res.add_children(ch3);
            lexer_ptr->next_token();

            ch4 = A();
            res.add_children(ch4);

            assert(lexer_ptr->get_cur_token() == token::RBR);
            res.add_children(ch5);
            lexer_ptr->next_token();

            assert(lexer_ptr->get_cur_token() == token::DOTCOMA);
            res.add_children(ch6);
            lexer_ptr->next_token();

            assert(lexer_ptr->get_cur_token() == token::END);
            break;
        default:
            throw parse_exception("Unknown function/procedure declaration");
    }
    return std::make_shared<node>(res);
}

std::shared_ptr<parser::node> parser::A()  {
    node res("A");
    std::shared_ptr<node> ch;
    std::shared_ptr<node> ch1;
    switch (lexer_ptr->get_cur_token()) {
        case NAME :
            ch = B();
            res.add_children(ch);

            ch1 = APrime();
            res.add_children(ch1);
            break;
        case RBR:
            ch = std::make_shared<node>(")");
            break;
        default:
            throw parse_exception("Expected argument name, found smth other");
    }
    return std::make_shared<node>(res);
}

std::shared_ptr<parser::node> parser::APrime()  {
    node res("A'");
    auto ch = std::make_shared<node>(";");
    std::shared_ptr<node> ch1;
    std::shared_ptr<node> ch3;
    switch(lexer_ptr->get_cur_token()) {
        case token::DOTCOMA:
            res.add_children(ch);
            lexer_ptr->next_token();

            ch1 = B();
            res.add_children(ch1);

            ch3 = APrime();
            res.add_children(ch3);
            break;
        case token::RBR:
            break;
        default:
            throw parse_exception("; expected");
    }
    return std::make_shared<node>(res);
}

parser::iterator parser::parse(std::string file_name)  {
    lexer_ptr = std::make_shared<lexical_analyzer>(std::move(file_name));
    lexer_ptr->next_token();
    return parser::iterator(parser::S());
}

std::string parser::iterator::get_name() const {
    return v->state_name;
}

std::vector<parser::iterator> parser::iterator::get_all_children() const {
    std::vector<iterator> ans;
    for (auto ch: v->children) {
        ans.push_back(iterator(ch));
    }
    return ans;
}

std::shared_ptr<parser::node> parser::B()  {
    node res("B");
    std::shared_ptr<node> ch;
    auto ch1 = std::make_shared<node>(":");
    std::shared_ptr<node> ch2;
    switch(lexer_ptr->get_cur_token()) {
        case token::NAME:
            ch = C();
            res.add_children(ch);

            assert(lexer_ptr->get_cur_token() == token::DOTDOT);
            res.add_children(ch1);
            lexer_ptr->next_token();

            assert(lexer_ptr->get_cur_token() == token::NAME);
            ch2 = std::make_shared<node>(lexer_ptr->get_cur_attribute());
            res.add_children(ch2);
            lexer_ptr->next_token();
            break;
        default:
            throw parse_exception("expected function argument, found smth else");
    }
    return std::make_shared<node>(res);
}

std::shared_ptr<parser::node> parser::C()  {
    node res("C");
    std::shared_ptr<node> ch;
    std::shared_ptr<node> ch1;
    switch(lexer_ptr->get_cur_token()) {
        case token::NAME :
            ch = std::make_shared<node>(lexer_ptr->get_cur_attribute());
            res.add_children(ch);
            lexer_ptr->next_token();

            ch1 = D();
            res.add_children(ch1);
            break;
        default:
            throw parse_exception("expected function argument, found smth else");
    }
    return std::make_shared<node>(res);
}

std::shared_ptr<parser::node> parser::D()  {
    node res("D");
    auto ch = std::make_shared<node>(",");
    std::shared_ptr<node> ch1;
    std::shared_ptr<node> ch3;
    switch(lexer_ptr->get_cur_token()) {
        case token::COMA:
            res.add_children(ch);
            lexer_ptr->next_token();

            assert(lexer_ptr->get_cur_token() == token::NAME);
            ch1 = std::make_shared<node>(lexer_ptr->get_cur_attribute());
            res.add_children(ch1);
            lexer_ptr->next_token();

            ch3 = D();
            res.add_children(ch3);
            break;
        case token::DOTDOT:
            break;
        default:
            throw parse_exception("smth went wrong");
    }
    return std::make_shared<node>(res);
}
