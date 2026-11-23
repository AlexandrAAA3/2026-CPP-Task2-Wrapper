#pragma once

#include <string>

class TextProcessor {
public:
    std::string replace_words(std::string text, std::string target, std::string replacement) const;

    std::string find_phrase(std::string text, std::string phrase) const;

    std::string capitalize_words(std::string text) const;

    std::string capitalize_sentences(std::string text) const;

    std::string number_sentences(std::string text) const;
};
