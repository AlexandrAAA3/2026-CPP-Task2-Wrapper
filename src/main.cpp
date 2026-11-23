#include <iostream>
#include <string>
#include <tuple>
#include "engine.h"
#include "text_processor.h"
#include "wrapper.h"

int main() {
    TextProcessor tp;

    using CSS = const std::string &;

    Wrapper<TextProcessor, std::string, CSS, CSS, CSS>
            w_replace(&tp, &TextProcessor::replace_words,
                      std::make_tuple("text", std::string{}),
                      std::make_tuple("from", std::string{}),
                      std::make_tuple("to", std::string{}));

    Wrapper<TextProcessor, std::string, CSS, CSS>
            w_find(&tp, &TextProcessor::find_phrase,
                   std::make_tuple("text", std::string{}),
                   std::make_tuple("phrase", std::string{}));

    Wrapper<TextProcessor, std::string, CSS>
            w_cap_words(&tp, &TextProcessor::capitalize_words,
                        std::make_tuple("text", std::string{}));

    Wrapper<TextProcessor, std::string, CSS>
            w_cap_sentences(&tp, &TextProcessor::capitalize_sentences,
                            std::make_tuple("text", std::string{}));

    Wrapper<TextProcessor, std::string, CSS>
            w_number(&tp, &TextProcessor::number_sentences,
                     std::make_tuple("text", std::string{}));

    Engine engine;
    engine.register_command(&w_replace, "replace");
    engine.register_command(&w_find, "find");
    engine.register_command(&w_cap_words, "cap_words");
    engine.register_command(&w_cap_sentences, "cap_sentences");
    engine.register_command(&w_number, "number");

    std::string in = "hello world. this is a test. is it working? and how tis is work?";

    std::cout << engine.execute("replace", {{"text", in}, {"from", "world"}, {"to", "C++"}}) << "\n\n";
    std::cout << engine.execute("find", {{"text", in}, {"phrase", "hello"}}) << "\n\n";
    std::cout << engine.execute("find", {{"text", in}, {"phrase", "xyz"}}) << "\n\n";
    std::cout << engine.execute("cap_words", {{"text", in}}) << "\n\n";
    std::cout << engine.execute("cap_sentences", {{"text", in}}) << "\n\n";
    std::cout << engine.execute("number", {{"text", in}}) << "\n\n";
    std::cout << engine.execute("replace", {{"text", in}, {"from", "test"}}) << std::endl;

    return 0;
}
