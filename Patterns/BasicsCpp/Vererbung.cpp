#include <iostream>

// interface
class IDrawable
{
public:
    virtual void draw() = 0;
    virtual void drawBorder() = 0;
};

// Implementierung von Teilen der Funktionalität
// Abstrakte Basisklasse
// Unvollständige Klasse
class Drawable : public IDrawable
{
public:
    void drawBorder() {}

    void eraseBackground() {
        std::cout << "eraseBackground" << std::endl;
        drawBorder();
    }
};

class Rectangle : public Drawable
{
public:
    virtual void draw() override {
        eraseBackground();
        std::cout << "Male ein Rectangle" << std::endl;
    }
};


class ColoredRectangle : public Rectangle
{
public:
    // dieses draw ERWEITERT die Methode in der Vaterklasse
    void draw() {
        Rectangle::draw();
        std::cout << "Male ein ColoredRectangle" << std::endl;
    }
};

class Circle : public Drawable
{
public:
    //void paint() {
    //    std::cout << "Male ein Circle" << std::endl;
    //}

    void draw() {
        eraseBackground();
        std::cout << "Male ein Circle" << std::endl;
    }
};


int main0()
{
    // Drawable d;   unvollständig // abstrakt

    Rectangle* rect;

    ColoredRectangle cr;

    rect = &cr;

    rect->draw();   // KEIN virtual:
                    // rect ist vom Typ Rectange
                    // draw wird von der Basisklasse Rectange aufgerufen

                    // virtual:
                    // Virtuelle Methodenaufrufmechanismus:
                   // Der Inhalt von rect ist ein
                   // Zeiger, der auf ColoredRectangle zeigt

    return 0;
}

int main2()
{
    Rectangle r;
    Circle c;
    ColoredRectangle cr;

    r.draw();
    c.draw();
    cr.eraseBackground();

    return 0;
}

int main_vererbung()
{
    Rectangle r;
    Circle c;
    ColoredRectangle cr;

    IDrawable* figuren[3];  // geht weil Zeiger

    figuren[0] = &r;
    figuren[1] = &c;
    figuren[2] = &cr;

    for (IDrawable* d : figuren) {
        d->draw();  // Z. 28, Z. 52, ..
    }

    return 0;
}