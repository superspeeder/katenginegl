#pragma once
#include <functional>
#include <memory>
#include <type_traits>
#include <unordered_map>

namespace kat {

    using signal_connection_id = uint32_t;

    template <typename R, typename... Args>
    class signal_list {
        using S = R(Args...);

      public:
        inline signal_connection_id insert_signal(const std::function<S> &f) {
            signal_connection_id id = m_counter++;
            m_signals.insert({ id, f });
            return id;
        };

        inline void remove(signal_connection_id id) { m_signals.erase(id); };

      private:
        std::unordered_map<signal_connection_id, std::function<S>> m_signals;
        signal_connection_id                                       m_counter = 0;

      public:
        inline void call(Args &&...args)
            requires std::same_as<R, void>
        {
            for (const auto &signal : m_signals) {
                signal.second(args...);
            }
        };

        inline std::vector<R> call(Args &&...args)
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

    template<typename S>
    class signal_connection;

    template <typename R, typename... Args>
    class signal_connection<R(Args...)> {
      public:
        signal_connection(const signal_connection_id &id, const std::shared_ptr<signal_list<R, Args...>> &signal_list) :
            id(id), m_signal_list(signal_list) {}

        inline ~signal_connection() { m_signal_list->remove(id); }

        signal_connection_id id;

      private:
        std::shared_ptr<signal_list<R, Args...>> m_signal_list;
    };

    template <typename S>
    class slot;

    template <typename R, typename... Args>
    class slot<R(Args...)> {
      public:
        inline slot() { m_signal_list = std::make_shared<signal_list<R, Args...>>(); };

        inline std::shared_ptr<signal_connection<R(Args...)>> connect_signal(const std::function<R(Args...)> &f) {
            auto id = connect_signal_unsafe(f);
            return std::make_shared<signal_connection<R(Args...)>>(id, m_signal_list);
        };

        inline signal_connection_id connect_signal_unsafe(const std::function<R(Args...)> &f) {
            return m_signal_list->insert_signal(f);
        };

        inline void disconnect_signal(signal_connection_id id) { m_signal_list->remove(id); };

        inline void call(Args &&...args)
            requires std::same_as<R, void>
        {
            m_signal_list->call(args...);
        };

        inline std::vector<R> call(Args &&...args)
            requires !std::same_as<R, void>
        {
            return m_signal_list->call(args...);
        };

      private:
        std::shared_ptr<signal_list<R, Args...>> m_signal_list;
    };
} // namespace kat
