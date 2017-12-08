#pragma once

#ifndef __MODULE__
#define __MODULE__ "Ui"
#endif

#include "soundengine.h"
#include "model.h"
#include "image.h"
#include "engine.h"

#define SOL_CHECK_ARGUMENTS 1

#include "sol.hpp"

namespace sol {
    template <typename T>
    struct unique_usertype_traits<TRef<T>> {
        typedef T type;
        typedef TRef<T> actual_type;
        static const bool value = true;

        static bool is_null(const actual_type& value) {
            return value == nullptr;
        }

        static type* get(const actual_type& p) {
            T* result = p;
            return result;
        }
    };
}

class CallbackSink : public IEventSink {
private:
    std::function<bool()> m_funcCallback;

public:
    CallbackSink(std::function<bool()> funcCallback) :
        m_funcCallback(funcCallback)
    {}

    bool OnEvent(IEventSource* pevent) {
        return m_funcCallback();
    }
};

template <class ...Types>
class CallbackValueSink : public TEvent<Types...>::Sink {
private:
    std::function<bool(Types...)> m_funcCallback;

public:
    CallbackValueSink(std::function<bool(Types...)> funcCallback) :
        m_funcCallback(funcCallback)
    {}

    bool OnEvent(typename TEvent<Types...>::Source* pevent, Types ... values) override {
        return m_funcCallback(values...);
    }
};

#include "UiEngine.h"
#include "UiState.h"
