#pragma once

#include <functional>
#include <string>
#include <tuple>
#include <type_traits>
#include <unordered_map>
#include <utility>
#include "string_utils.h"

template <typename Class, typename ReturnType, typename... Args>
class Wrapper {
public:
    // Разрешаем методам быть const (обратите внимание на const в конце)
    using MethodPtr = ReturnType (Class::*)(Args...) const;
    using Overrides = std::unordered_map<std::string, std::string>;
    using Executor  = std::function<std::string(const Overrides&)>;

    Wrapper(Class* obj, MethodPtr method, std::tuple<std::string, Args>... defaults)
        : obj_(obj), method_(method), defaults_(std::move(defaults)...) {}

    [[nodiscard]] Executor make_executor() {
        return [this](const Overrides& ov) -> std::string {
            return do_invoke(ov, std::index_sequence_for<Args...>{});
        };
    }

private:
    Class*    obj_;
    MethodPtr method_;
    std::tuple<std::tuple<std::string, Args>...> defaults_;

    template <std::size_t I>
    auto resolve_argument(const Overrides& ov) {
        using ArgType = std::tuple_element_t<I, std::tuple<Args...>>;
        using CleanType = std::decay_t<ArgType>;

        const auto& [name, def] = std::get<I>(defaults_);
        auto it = ov.find(name);
        if (it == ov.end()) {
            return utils::from_string<CleanType>(utils::to_display(def));
        }
        return utils::from_string<CleanType>(it->second);
    }

    template <std::size_t... I>
    std::string do_invoke(const Overrides& ov, std::index_sequence<I...>) {
        if constexpr (std::is_void_v<ReturnType>) {
            // std::invoke умеет работать с указателями на методы
            std::invoke(method_, obj_, resolve_argument<I>(ov)...);
            return {};
        } else {
            auto result = std::invoke(method_, obj_, resolve_argument<I>(ov)...);
            return utils::to_display(result);
        }
    }
};