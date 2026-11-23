#include "text_processor.h"
#include <cctype>
#include <cstddef>
#include <string>
#include <vector>
#include "string_utils.h"

std::string TextProcessor::replace_words(const std::string &text, const std::string &from, const std::string &to) {
    if (from.empty()) return text;
    std::string result = text;
    std::size_t pos = 0;
    while ((pos = result.find(from, pos)) != std::string::npos) {
        result.replace(pos, from.size(), to);
        pos += to.size();
    }
    return result;
}

std::string TextProcessor::find_phrase(const std::string &text, const std::string &phrase) {
    return text.find(phrase) != std::string::npos ? "found" : "not found";
}

std::string TextProcessor::capitalize_words(const std::string &text) {
    std::string result = text;
    bool at_word_start = true;
    for (char &c: result) {
        const auto uc = static_cast<unsigned char>(c);
        if (std::isspace(uc) != 0) at_word_start = true;
        else {
            if (at_word_start && (std::isalpha(uc) != 0)) c = static_cast<char>(std::toupper(uc));
            at_word_start = false;
        }
    }
    return result;
}

std::string TextProcessor::capitalize_sentences(const std::string &text) {
    std::string result = text;
    bool at_sentence_start = true;
    for (char &c: result) {
        const auto uc = static_cast<unsigned char>(c);
        if (at_sentence_start && (std::isalpha(uc) != 0)) {
            c = static_cast<char>(std::toupper(uc));
            at_sentence_start = false;
        } else if (c == '.' || c == '!' || c == '?') {
            at_sentence_start = true;
        } else if (std::isspace(uc) == 0) at_sentence_start = false;
    }
    return result;
}

std::string TextProcessor::number_sentences(const std::string &text) {
    const std::vector<std::string> sentences = utils::split_sentences(text);
    std::string result;
    for (std::size_t i = 0; i < sentences.size(); ++i) {
        std::size_t start = sentences[i].find_first_not_of(' ');
        std::string clean_sentence = (start == std::string::npos) ? "" : sentences[i].substr(start);

        result += std::to_string(i + 1) + ". " + clean_sentence;
        if (i + 1 < sentences.size()) result += '\n';
    }
    return result;
}