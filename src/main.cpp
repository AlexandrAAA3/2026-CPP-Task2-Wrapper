#include <iostream>
#include <string>
#include <tuple>
#include "engine.h"
#include "text_processor.h"
#include "wrapper.h"

int main() {
    TextProcessor tp;

    auto *w_replace = make_wrapper(&tp, &TextProcessor::replace_words,
                                   std::make_tuple("text", std::string{}),
                                   std::make_tuple("target", std::string{}),
                                   std::make_tuple("replacement", std::string{}));

    auto *w_find = make_wrapper(&tp, &TextProcessor::find_phrase,
                                std::make_tuple("text", std::string{}),
                                std::make_tuple("phrase", std::string{}));

    auto *w_cap_words = make_wrapper(&tp, &TextProcessor::capitalize_words,
                                     std::make_tuple("text", std::string{}));

    auto *w_cap_sentences = make_wrapper(&tp, &TextProcessor::capitalize_sentences,
                                         std::make_tuple("text", std::string{}));

    auto *w_number = make_wrapper(&tp, &TextProcessor::number_sentences,
                                  std::make_tuple("text", std::string{}));

    Engine engine;
    engine.register_command(w_replace, "replace");
    engine.register_command(w_find, "find");
    engine.register_command(w_cap_words, "cap_words");
    engine.register_command(w_cap_sentences, "cap_sentences");
    engine.register_command(w_number, "number");

    std::string in = "hello world. this is a test. is it working?";

    std::cout << engine.execute("replace", {{"text", in}, {"target", "world"}, {"replacement", "C++"}}) << "\n\n";
    std::cout << engine.execute("find", {{"text", in}, {"phrase", "hello"}}) << "\n\n";
    std::cout << engine.execute("find", {{"text", in}, {"phrase", "xyz"}}) << "\n\n";
    std::cout << engine.execute("cap_words", {{"text", in}}) << "\n\n";
    std::cout << engine.execute("cap_sentences", {{"text", in}}) << "\n\n";
    std::cout << engine.execute("number", {{"text", in}}) << "\n\n";
    std::cout << engine.execute("replace", {{"text", in}, {"target", "test"}}) << std::endl;

    delete w_replace;
    delete w_find;
    delete w_cap_words;
    delete w_cap_sentences;
    delete w_number;

    return 0;
}
