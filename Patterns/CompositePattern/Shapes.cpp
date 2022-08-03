// ===========================================================================
// Shapes.cpp
// ===========================================================================

#include <iostream>
#include <string>
#include <vector>
#include <memory>

struct Shape
{
    virtual void draw() const = 0;
};

class Circle : public Shape
{
private:
    std::string m_name;

public:
    Circle(const std::string& name) : m_name { name } {}

    virtual void draw() const override {
        std::cout << "Circle: " << m_name;
    }
};

class Group : public Shape
{
private:
    std::string m_name;
    std::vector<std::shared_ptr<Shape>> m_objects;

public:
    Group(const std::string& name) : m_name{ name } {}
        
    virtual void draw() const override {

        m_indentation += 2;

        std::cout << "Group " << m_name << " contains:" << std::endl;
        for (const std::shared_ptr<Shape> shape : m_objects) {

            std::string ident( m_indentation, ' ' );
            std::cout << ident;
            shape->draw();
            std::cout << std::endl;
        }

        m_indentation -= 2;
    }

    void push(std::shared_ptr<Shape> shape) {
        m_objects.push_back(shape);
    }

private:
    static size_t m_indentation;
};

size_t Group::m_indentation = 0;

void test_shapes()
{
    Group root("Root");

    std::shared_ptr<Shape> circle = std::make_shared<Circle>("Top Level Circle");
    root.push(circle);

    std::shared_ptr<Group> subgroup = std::make_shared<Group>("Subgroup");
    subgroup->push(std::make_shared<Circle>("First Second Level Circle"));
    subgroup->push(std::make_shared<Circle>("Another Second Level Circle"));
    root.push(subgroup);

    root.draw();
}

// ===========================================================================
// End-of-File
// ===========================================================================
