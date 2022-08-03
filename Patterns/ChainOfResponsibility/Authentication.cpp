// ===========================================================================
// Authentication.cpp // Chain of Responsibility
// ===========================================================================

#include <iostream>
#include <string>
#include <memory>

namespace ChainofResponsibilityExample
{
    class Authentication
    {
    protected:
        std::unique_ptr<Authentication> m_next;

    public:
        // c'tor(s)
        Authentication() : m_next{ nullptr } {}

        virtual bool authenticate() = 0;   // handleRequest

        void nextAuthentication(std::unique_ptr<Authentication>& nextAuth) {  // setSuccessor
            m_next = std::move(nextAuth);
        }
    };

    class UserName : public Authentication
    {
    private:
        std::string m_name;

    public:
        // c'tor(s)
        UserName(std::string name) : m_name{ name } {}

        virtual bool authenticate() override {
            if (!is_valid_user_name()) {
                std::cout << "Invalid user name" << std::endl;
                return false;
            }
            else if (m_next) {


                // Sollte man in einem Architektur Seminar nicht machen....

                // Will m_next nach unten auf Password casten
                // um eine Methode wie zb setUserName aufrufen zu k�nnen.

                // std::shared_ptr<Password> pwPtr = 
                //    std::dynamic_pointer_cast<Password> (m_next);

               // m_next->setUserName ("Hans");

                return m_next->authenticate();
            }
            return true;
        }

    private:
        // helper methods
        bool is_valid_user_name() {
            std::cout << "Authentication of User Name succeeded!" << std::endl;
            return true;
        }
    };

    class Password : public Authentication
    {
    private:
        std::string m_password;

    public:
        // c'tor(s)
        Password(std::string password) : m_password{ password } {}

        virtual bool authenticate() override {
            if (!is_valid_password()) {
                std::cout << "Invalid password" << std::endl;
                return false;
            }
            else if (m_next) return m_next->authenticate();
            return true;
        }

    private:
        // helper methods
        bool is_valid_password() {
            std::cout << "Authentication of Password succeeded!" << std::endl;
            return true;
        }
    };
}

void test_authentication_example()
{
    using namespace ChainofResponsibilityExample;

    // Input:

    std::unique_ptr<Authentication> auth1{ new UserName("John") };

    std::unique_ptr<Authentication> auth2{ new Password("password") };

    auth1->nextAuthentication(auth2);

    bool result{ auth1->authenticate() };

    if (result) {
        std::cout << "Authentication succeeded!" << std::endl;
    }
}

// ===========================================================================
// End-of-File
// ===========================================================================
