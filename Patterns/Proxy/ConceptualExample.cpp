// ===========================================================================
// ConceptualExample.cpp // Proxy Pattern
// ===========================================================================

#include <iostream>
#include <memory>

/**
 * The Subject interface declares common operations
   for both 'RealSubject' and the
 * 'Proxy'. As long as the client works with 'RealSubject'
    using this interface,
 * you'll be able to pass it a proxy instead of a real subject.
 */
class Subject {
public:
    virtual void request() const = 0;
};

/**
 * The RealSubject contains some core business logic. Usually, RealSubjects are
 * capable of doing some useful work which may also be very slow or sensitive -
 * e.g. correcting input data. A Proxy can solve these issues without any
 * changes to the RealSubject's code.
 */
class RealSubject : public Subject {
public:

    RealSubject(int wert) {}

    virtual void request() const override {
        std::cout << "RealSubject: Handling request." << std::endl;
    }
};

/**
 * The Proxy has an interface identical to the RealSubject.
 */
class Proxy : public Subject {
private:
    std::shared_ptr<RealSubject> m_realSubject;

    bool checkAccess() const {
        // some real checks should go here.
        std::cout << "Proxy: Checking access prior to executing a real request." << std::endl;
        return true;
    }

    void logAccess() const {
        std::cout << "Proxy: Logging the time of request." << std::endl;
    }

    /**
     * The Proxy maintains a reference to an object of the RealSubject class. It
     * can be either lazy-loaded or passed to the Proxy by the client.
     */
public:
    Proxy(std::shared_ptr<RealSubject> realSubject) 
        : m_realSubject(realSubject) {}

    /**
     * The most common applications of the Proxy pattern are lazy loading,
     * caching, controlling the access, logging, etc. A Proxy can perform one of
     * these things and then, depending on the result, pass the execution to the
     * same method in a linked RealSubject object.
     */
    virtual void request() const override {
        if (checkAccess()) {
            m_realSubject->request();
            logAccess();
        }
    }
};

/**
 * The client code is supposed to work with all objects (both subjects and
 * proxies) via the Subject interface in order to support both real subjects and
 * proxies. In real life, however, clients mostly work with their real subjects
 * directly. In this case, to implement the pattern more easily, you can extend
 * your proxy from the real subject's class.
 */
void clientCode(std::shared_ptr<Subject> subject) {

    subject->request();
}

void test_conceptual_example() {
    std::cout << "Client: Executing the client code with a real subject:" << std::endl;

    std::shared_ptr<RealSubject> realSubjectPtr 
        = std::make_shared<RealSubject>(123);

    std::shared_ptr<RealSubject> realSubjectPtr2(new RealSubject(123));

    // new Zeiger  // "Referenz�hler": new Control Block

    clientCode(realSubjectPtr);
    std::cout << std::endl;

    std::cout << "Client: Executing the same client code with a proxy:" << std::endl;
    std::shared_ptr<Proxy> proxy{ std::make_shared<Proxy>(realSubjectPtr) };
    clientCode(proxy);
}

// ===========================================================================
// End-of-File
// ===========================================================================
