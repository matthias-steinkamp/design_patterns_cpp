// ===========================================================================
// ConceptualExample01.cpp
// ===========================================================================

#include <iostream>
#include <thread>
#include <mutex>

namespace ConceptualExample01 {

  //  Singleton* Singleton::m_instance{ nullptr };

    class Singleton final
    {
    private:
        Singleton() {};

        static Singleton* m_instance;
       // static Singleton* m_instance2 = nullptr;
        static std::mutex m_mutex;

    public:
        static Singleton* getInstance()
        {
            if (m_instance == nullptr) {
                m_instance = new Singleton();
            }

            return m_instance;
        }

        static Singleton* getInstanceThreadSafe()
        {
            {
                std::lock_guard<std::mutex> mylock{ m_mutex };
                //m_mutex.lock();

                if (m_instance == nullptr) {
                    m_instance = new Singleton();
                }
                //m_mutex.unlock();   Destructor mylock 
            }

            return m_instance;
        }
    };

    Singleton* Singleton::m_instance{ nullptr };

    std::mutex Singleton::m_mutex{};
}

void test_singleton_01()
{
    using namespace ConceptualExample01;

    auto singleton1 { Singleton::getInstance() };
    auto singleton2 { Singleton::getInstance() };

    std::cout << std::boolalpha << (singleton1 == singleton2) << std::endl;

    auto singleton3 { Singleton::getInstanceThreadSafe() };
    auto singleton4 { Singleton::getInstanceThreadSafe() };

    std::cout << std::boolalpha << (singleton3 == singleton4) << std::endl;
}

// ===========================================================================
// End-of-File
// ===========================================================================
