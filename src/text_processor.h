#pragma once

#include <string>

class TextProcessor {
public:
    std::string replace_words(const std::string &text, const std::string &from, const std::string &to);

    std::string find_phrase(const std::string &text, const std::string &phrase);

    std::string capitalize_words(const std::string &text);

    std::string capitalize_sentences(const std::string &text);

    std::string number_sentences(const std::string &text);
};
