//
// Created by Igli milaqi on 13/03/2020.
//

#ifndef CROW_EVENTQUEUE_H
#define CROW_EVENTQUEUE_H


#include "MemberFunctionHandler.h"
#include <list>
#include <map>
#include <typeindex>

typedef std::list<MemberFunctionBase*> HandlerList;

class EventQueue {

public:
    template <typename EventType>
    void Publish(EventType* event)
    {
        HandlerList * handlers = m_subscribers[typeid(EventType)];

        if (handlers == nullptr)
        {
            return;
        }

        for (auto & handler : *handlers)
        {
            if (handler != nullptr) {
                handler->Execute(event);
                delete event;
            }
        }
    }


    template<class T, class EventType>
    void Subscribe(T * instance, void (T::*memberFunction)(EventType *))
    {
        HandlerList * handlers = m_subscribers[typeid(EventType)];

        if (handlers == nullptr)
        {
            handlers = new HandlerList();
            m_subscribers[typeid(EventType)] = handlers;
        }

        handlers->push_back(new MemberFunctionHandler<T, EventType>(instance, memberFunction));
    }

private:

    std::map<std::type_index,HandlerList*> m_subscribers;
};


#endif //CROW_EVENTQUEUE_H
