//
// Created by kirant on 10.10.17.
//

#ifndef LAB2_LEXICAL_ANAYZER_H
#define LAB2_LEXICAL_ANAYZER_H

#include <fstream>

enum token {
    BEGIN, PROCEDURE, FUNCTION, NAME, DOTDOT, DOTCOMA, COMA, LBR, RBR, END
};

struct lexical_analyzer {
    explicit lexical_analyzer(std::string file_name) noexcept;

    void next_token();

    token get_cur_token() const noexcept;

    int get_cur_pos() const noexcept;

    std::string get_cur_attribute() const noexcept;

    ~lexical_analyzer() noexcept;

private:

    void next_char();

    std::ifstream is;
    int cur_char;
    int cur_pos;
    token cur_token;
    std::string cur_attribute;
    bool was_declaration = false;

};

#endif //LAB2_LEXICAL_ANAYZER_H
