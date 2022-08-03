// ===========================================================================
// Program.cpp // SOLID
// ===========================================================================

#include <iostream>
#include <string>
#include <fstream>
#include <vector>

namespace ConceptualExampleSRP
{
    namespace SavingManager
    {
        void save(const std::string& filename, std::ostream& os) {

        }
    };
}


// function prototypes
void test_anti_conceptual_example_srp();
void test_conceptual_example_srp();

void test_anti_conceptual_example_ocp();
void test_conceptual_example_ocp_01();
void test_conceptual_example_ocp_02();
void test_conceptual_example_ocp_03();
void test_conceptual_example_ocp_04();
void test_conceptual_example_ocp_05();

void test_anti_conceptual_example_lsp();
void test_conceptual_example_lsp();

void test_anti_conceptual_example_isp();
void test_conceptual_example_isp();

void test_anti_conceptual_example_dip();
void test_conceptual_example_dip();

int main()
{
    std::string name = "file.txt";

    ConceptualExampleSRP::SavingManager::save(name, std::cout);

    test_anti_conceptual_example_srp();
    test_conceptual_example_srp();

    test_anti_conceptual_example_ocp();
    test_conceptual_example_ocp_01();
    test_conceptual_example_ocp_02();
    test_conceptual_example_ocp_03();
    test_conceptual_example_ocp_04();
    test_conceptual_example_ocp_05();

    test_anti_conceptual_example_lsp();
    test_conceptual_example_lsp();

    test_anti_conceptual_example_isp();
    test_conceptual_example_isp();

    test_anti_conceptual_example_dip();
    test_conceptual_example_dip();

    return 0;
}

// ===========================================================================
// End-of-File
// ===========================================================================
