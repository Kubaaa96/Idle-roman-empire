#ifndef IRE_EVENTS_H
#define IRE_EVENTS_H

#include <SFML/Window/Event.hpp>

#include <functional>
#include <type_traits>
#include <typeindex>
#include <utility>
#include <map>
#include <memory>
#include <cassert>

namespace ire::core::gui {

    struct Event
    {
        bool handled = false;
    };

    struct EventEmitter
    {
        struct AnyEventListener;

        using ListenerMapType = std::multimap<std::type_index, std::unique_ptr<AnyEventListener>>;
        using EventType = std::type_index;

        struct AnyEventListener
        {
            AnyEventListener() = default;

            AnyEventListener(const AnyEventListener&) = delete;
            AnyEventListener(AnyEventListener&&) = delete;

            AnyEventListener& operator=(const AnyEventListener&) = delete;
            AnyEventListener& operator=(AnyEventListener&&) = delete;

            virtual ~AnyEventListener() = default;

            virtual void onEvent(void* typeErasedEvent) = 0;
        };

        template <typename EventT, typename FuncT>
        struct EventListener : AnyEventListener, private FuncT
        {
            static_assert(std::is_base_of_v<Event, EventT>, "EventT must derive from Event");
            static_assert(
                std::is_same_v<
                    decltype(std::declval<FuncT>()(std::declval<EventT&>())), 
                    void
                >, "Invalid event listener signature. Must be void(EventT&)");

            using EventType = EventT;

            template <typename T>
            EventListener(T&& func) :
                FuncT(std::forward<T>(func))
            {
            }

            void onEvent(void* typeErasedEvent) override
            {
                EventT& ev = *(reinterpret_cast<EventT*>(typeErasedEvent));
                FuncT::operator()(ev);
            }
        };

        EventEmitter() = default;

        EventEmitter(const EventEmitter&) = delete;
        EventEmitter(EventEmitter&&) = delete;

        EventEmitter& operator=(const EventEmitter&) = delete;
        EventEmitter& operator=(EventEmitter&&) = delete;

        // The listener currently must outlive the emitter.
        // In the future it's possible to add unsubscription.
        template <typename EventT, typename FuncT>
        void addEventListener(FuncT&& func)
        {
            using DecayedFuncT = std::remove_reference_t<FuncT>;
            using EventListenerType = EventListener<EventT, DecayedFuncT>;
            auto listener = std::make_unique<EventListenerType>(std::forward<FuncT>(func));
            auto type = eventType<EventT>();
            m_listeners.emplace(type, std::move(listener));
        }

    protected:

        template <typename EventT>
        void emitEvent(EventT& ev)
        {
            auto type = eventType<EventT>();
            auto [begin, end] = m_listeners.equal_range(type);
            while (begin != end && !ev.handled)
            {
                begin->second->onEvent(reinterpret_cast<void*>(&ev));
                ++begin;
            }
        }

    private:
        ListenerMapType m_listeners;

        template <typename EventT>
        [[nodiscard]] static EventType eventType()
        {
            return std::type_index(typeid(EventT));
        }
    };

    struct MouseDownEvent : Event
    {
        sf::Mouse::Button button;
        sf::Vector2f coords;
    };

    struct MouseUpEvent : Event
    {
        sf::Mouse::Button button;
        sf::Vector2f coords;
    };

}

#endif // !IRE_EVENTS_H