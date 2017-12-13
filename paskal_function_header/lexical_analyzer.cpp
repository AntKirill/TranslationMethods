//
// Created by kirant on 10.10.17.
//

#include <string>
#include <istream>
#include "lexical_analyzer.h"
#include "parse_exception.h"

lexical_analyzer::lexical_analyzer(std::string file_name) noexcept {
    is.open(file_name);
    cur_pos = 0;
    next_char();
    cur_token = token::BEGIN;
}

lexical_analyzer::~lexical_analyzer() noexcept {
    is.close();
}

int lexical_analyzer::get_cur_pos() const noexcept {
    return cur_pos;
}

token lexical_analyzer::get_cur_token() const  noexcept {
    return cur_token;
}

static bool is_blank(int c) noexcept {
    return c == ' ' || c == '\r' || c == '\n' || c == '\t';
}

void lexical_analyzer::next_char() {
    cur_pos++;
    try {
        cur_char = is.get();
    } catch (std::exception &e) {
        throw parse_exception(e.what(), cur_pos);
    }
}

static bool is_letter(int c) noexcept {
    return ('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z') || (c == '_') || ('0' <= c && c <= '9');
}

void lexical_analyzer::next_token() {
    while (is_blank(cur_char)) next_char();
    std::string word;
    while (is_letter(cur_char)) {
        word += static_cast<char>(cur_char);
        next_char();
    }
    if (!was_declaration && word == "function") {
        cur_token = token::FUNCTION;
        cur_attribute = word;
        was_declaration = true;
        return;
    }
    if (!was_declaration && word == "procedure") {
        cur_token = token::PROCEDURE;
        cur_attribute = word;
        was_declaration = true;
        return;
    }
    if (word.length() > 0) {
        cur_token = token::NAME;
        cur_attribute = word;
        return;
    }
    //now cur_char contains symbol!!!
    switch (cur_char) {
        case ';':
            cur_token = token::DOTCOMA;
            next_char();
            break;
        case ':':
            cur_token = token::DOTDOT;
            next_char();
            break;
        case ',':
            cur_token = token::COMA;
            next_char();
            break;
        case '(':
            cur_token = token::LBR;
            next_char();
            break;
        case ')':
            cur_token = token::RBR;
            next_char();
            break;
        case -1:
            cur_token = token::END;
            break;
        default:
            std::string s = "illegal character ";
            throw parse_exception(s + static_cast<char>(cur_char), cur_pos);
    }
}

std::string lexical_analyzer::get_cur_attribute() const  noexcept {
    return cur_attribute;
}
