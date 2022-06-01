/// Observer Interface taken from:
/// https://refactoring.guru/design-patterns/observer/cpp/example
/// Thank you for the extremely helpful resources.

#pragma once
#include <string>

// The observer, also known as the subscriber,
// is an object who has subscribed to event notifications from a publisher.
// The publisher may also dually be the subject itself, as implemented here.

class IObserver
{
public:
    virtual ~IObserver()= default;
    virtual void Update(const std::string &message_from_subject) = 0;
};

class ISubject
{
public:
    virtual ~ISubject()= default;
    virtual void Attach(IObserver *observer) = 0;
    virtual void Detach(IObserver *observer) = 0;
    virtual void Notify() = 0;
};