#include <iostream>
#include <string>
#include <tuple>

#include "engine.h"
#include "text_processor.h"
#include "wrapper.h"

int main() {
    TextProcessor processor;

    auto *w_replace = make_wrapper(&processor, &TextProcessor::replace_words,
                                   std::make_tuple("text", std::string{}),
                                   std::make_tuple("target", std::string{}),
                                   std::make_tuple("replacement", std::string{}));

    auto *w_find = make_wrapper(&processor, &TextProcessor::find_phrase,
                                std::make_tuple("text", std::string{}),
                                std::make_tuple("phrase", std::string{}));

    auto *w_cap_words = make_wrapper(&processor, &TextProcessor::capitalize_words,
                                     std::make_tuple("text", std::string{}));

    auto *w_cap_sentences = make_wrapper(&processor, &TextProcessor::capitalize_sentences,
                                         std::make_tuple("text", std::string{}));

    auto *w_number = make_wrapper(&processor, &TextProcessor::number_sentences,
                                  std::make_tuple("text", std::string{}));

    Engine engine;
    engine.register_command(w_replace, "replace");
    engine.register_command(w_find, "find");
    engine.register_command(w_cap_words, "cap_words");
    engine.register_command(w_cap_sentences, "cap_sentences");
    engine.register_command(w_number, "number");

    std::string input = "hello world. this is a test. is it working?";

    std::cout << engine.execute("replace", {{"text", input}, {"target", "world"}, {"replacement", "C++"}}) << "\n\n";
    std::cout << engine.execute("find", {{"text", input}, {"phrase", "hello"}}) << "\n\n";
    std::cout << engine.execute("find", {{"text", input}, {"phrase", "xyz"}}) << "\n\n";
    std::cout << engine.execute("cap_words", {{"text", input}}) << "\n\n";
    std::cout << engine.execute("cap_sentences", {{"text", input}}) << "\n\n";
    std::cout << engine.execute("number", {{"text", input}}) << "\n\n";
    std::cout << engine.execute("replace", {{"text", input}, {"target", "test"}}) << "\n";

    delete w_replace;
    delete w_find;
    delete w_cap_words;
    delete w_cap_sentences;
    delete w_number;

    return 0;
}
