#pragma once
#include <functional>
#include <memory>
#include <type_traits>
#include <unordered_map>

namespace kat {

    using signal_connection_id = uint32_t;

    template <typename R, typename... Args>
    class signal_connection_list {
        using S = R(Args...);

      public:
        inline signal_connection_id connect(const std::function<S> &f) {
            signal_connection_id id = m_counter++;
            m_signals.insert({ id, f });
            return id;
        };

        inline void disconnect(signal_connection_id id) { m_signals.erase(id); };

      private:
        std::unordered_map<signal_connection_id, std::function<S>> m_signals;
        signal_connection_id                                       m_counter = 0;

      public:
        inline void emit(Args... args)
            requires std::same_as<R, void>
        {
            for (const auto &signal : m_signals) {
                signal.second(args...);
            }
        };

        inline std::vector<R> emit(Args... args)
            requires !std::same_as<R, void>
        {
            std::vector<R> values;
            values.reserve(m_signals.size());
            for (const auto &signal : m_signals) {
                values.push_back(signal.second(args...));
            }

            return values;
        };
    };

    template <typename S>
    class signal_connection;

    template <typename R, typename... Args>
    class signal_connection<R(Args...)> {
      public:
        signal_connection(const signal_connection_id &id, const std::shared_ptr<signal_connection_list<R, Args...>> &signal_list) :
            id(id), m_signal_list(signal_list) {}

        inline ~signal_connection() { m_signal_list->disconnect(id); }

        signal_connection_id id;

      private:
        std::shared_ptr<signal_connection_list<R, Args...>> m_signal_list;
    };

    template <typename S>
    class signal;

    template <typename R, typename... Args>
    class signal<R(Args...)> {
      public:
        inline signal() { m_signal_connection_list = std::make_shared<signal_connection_list<R, Args...>>(); };

        inline std::shared_ptr<signal_connection<R(Args...)>> connect(const std::function<R(Args...)> &f) {
            auto id = connect_unsafe(f);
            return std::make_shared<signal_connection<R(Args...)>>(id, m_signal_connection_list);
        };

        inline signal_connection_id connect_unsafe(const std::function<R(Args...)> &f) {
            return m_signal_connection_list->connect(f);
        };

        inline void disconnect(signal_connection_id id) { m_signal_connection_list->disconnect(id); };

        inline void emit(Args... args)
            requires std::same_as<R, void>
        {
            m_signal_connection_list->emit(args...);
        };

        inline std::vector<R> emit(Args... args)
            requires !std::same_as<R, void>
        {
            return m_signal_connection_list->emit(args...);
        };

      private:
        std::shared_ptr<signal_connection_list<R, Args...>> m_signal_connection_list;
    };
} // namespace kat
