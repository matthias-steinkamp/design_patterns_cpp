// ===========================================================================
// ConceptualExample.cpp // Adapter Pattern
// ===========================================================================

#include <iostream>
#include <string>
#include <memory>

/**
 * The Target defines the domain-specific interface used by the client code.
 */

class ITarget
{
public:
    virtual std::string getRequest() const = 0;
};

class Target : public ITarget
{
public:
    Target() = default;
    virtual ~Target() = default;

    virtual std::string getRequest() const
    {
        return std::string{ "Target: The target's default behavior." };
    }
};

/**
 * The Adaptee contains some useful behavior, but its interface is incompatible
 * with the existing client code. The Adaptee needs some adaptation before the
 * client code can use it.
 */
class Adaptee
{
public:
    Adaptee() = default;

    std::string getSpecificRequest() const
    {
        return { ".eetpadA eht fo roivaheb laicepS" };
    }
};

/**
 * The Adapter makes the Adaptee's interface
   compatible with the Target's interface.
 */
class Adapter : public ITarget {
private:
    Adaptee* m_adapteeee;
    std::shared_ptr<Adaptee> m_adaptee;

public:
    Adapter(std::shared_ptr<Adaptee> adaptee) 
        : m_adaptee(adaptee) {}

    std::string getRequest() const override {

        // toReverse ist inkompatibel für ITarget
        // zb  XML
        std::string toReverse{ m_adaptee->getSpecificRequest() };

        // Wandlung des Formats
        // XML -> JSON
        std::reverse(toReverse.begin(), toReverse.end());

        return { "Adapter: (TRANSLATED) " + toReverse };
    }
};

/**
 * The client code supports all classes that follow the Target interface
 */
void clientCode1(ITarget* target) {
    std::string request = target->getRequest();
    std::cout << request << std::endl << std::endl;

}
void clientCode(std::shared_ptr<ITarget> target) {
    std::string request = target->getRequest();
    std::cout << request << std::endl << std::endl;
}

// Kann nichts
class MockingClass : public ITarget
{
public:
    std::string getRequest() const {
        return "leer";
    }
};

void test_conceptual_example()
{
   // ITarget* tp = new ITarget();



    std::cout << "Client: I can work just fine with the Target object" << std::endl;
    
    ITarget* target1 = new Target();

    //std::shared_ptr<ITarget> target
    //    = std::shared_ptr<Target>(new Target());

    std::shared_ptr<ITarget> target (new Target());
    clientCode(target);

    // -----------------------------------------------

    Adaptee* adaptee1 = new Adaptee();

    std::shared_ptr<Adaptee> adaptee (new Adaptee{ });

    //std::cout << "Client: The Adaptee class has an incompatible interface:" << std::endl;
    //std::string specificRequest = adaptee->getSpecificRequest();
    //std::cout << "Adaptee: " << specificRequest << std::endl << std::endl;

    std::cout << "Client: But I can work with the Adaptee via the Adapter:" << std::endl;
    
    Adapter* adapter1 = new Adapter{ adaptee };

    std::shared_ptr<Adapter> adapter 
        = std::shared_ptr<Adapter>(new Adapter{ adaptee });
    
    clientCode(adapter);

    std::shared_ptr<MockingClass> anderesObjekt
        (new MockingClass());

    clientCode(anderesObjekt);
}

// ===========================================================================
// End-of-File
// ===========================================================================
