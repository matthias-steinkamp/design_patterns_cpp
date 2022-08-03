# Factory Method Pattern

[Zur�ck](../../../Resources/Readme_05_Catalog.md)

---

<img src="dp_factory_pattern_intro.png" width="600" />

<sup>(Credits: [Blog von Vishal Chovatiya](http://www.vishalchovatiya.com/category/design-patterns/))</sup>

---

## Wesentliche Merkmale

##### Kategorie: Erzeugungsmuster / *Creational Pattern*

#### Ziel / Absicht:

Das *Factory Method Pattern* ist ein Entwurfsmuster, mit dem Objekte erstellt werden k�nnen,
ohne den Objekttyp anzugeben, der hierzu verwendet werden soll.
Das Entwurfsmuster definiert zuallererst eine Methode, die ein Objekt erzeugt.
Welche Klasse hierbei herangezogen wird, entscheidet die konkrete Klasse, die diese Methode implementiert.

#### L�sung:

Das *Factory*-Entwurfsmuster definiert eine Schnittstelle zum Erstellen eines Objekts
und �berl�sst die Auswahl des konkreten Klassentyps den Unterklassen.
Das Entwurfsmuster macht ein Software-Design leichter anpassbar und weniger abh�ngig 
von anderen Klassen.

In dem Muster kommen zwei Vererbungshierarchien vor: eine mit den *Factory*-Klassen und
eine zweite mit den zu erzeugenden Objekten. Diese werden in dem Muster h�ufig als *Produkte* bezeichnet.

#### Struktur (UML):

Das folgende UML-Diagramm beschreibt eine Implementierung des *Factory Method Patterns*.
Es besteht im Wesentlichen aus vier Teilen:

  * **FactoryBase**: Abstrakte Klasse (oder Schnittstelle) f�r konkrete *Factory*-Klassen,
    die die gesuchten Objekte zur�ckgeben.
    Diese Klasse enth�lt die Signatur der Methode `FactoryMethod`,
    die ein `ProductBase`-Objekt zur�ckliefert.
  * **ConcreteFactory**: Repr�sentiert eine konkrete Umsetzung der `FactoryBase`-Klasse.
    Normalerweise �berschreibt diese Klasse die generierende Methode
    `FactoryMethod` und gibt ein `ConcreteProduct`-Objekt zur�ck.
  * **ProductBase**: Basisklasse (oder Schnittstelle) f�r alle Produkte,
    die von konkreten *Factory*-Klassen hergestellt werden.
  * **ConcreteProduct**: Konkrete Implementierung der Klasse `ProductBase`.
    Konkrete `ProductBase`-Klassen sollten produktspezifische
    Funktionalit�ten enthalten. Objekte des Typs `ConcreteProduct` werden von Methoden
    der *Factory*-Klassen erstellt.

<img src="dp_factory_method_pattern.svg" width="500">

*Abbildung* 1: Schematische Darstellung des *Factory Method Patterns*.

---

#### Conceptual Example:

[Quellcode 1](../ConceptualExample01.cpp) &ndash; Sehr einfaches Beispiel

[Quellcode 2](../ConceptualExample02.cpp) &ndash; Beispiel, das "konzeptionell" den Einsatz von *Factory Methods* aufzeigt.

---

#### 'Real-World' Beispiel:

[Quellcode 3](../RealWorldFactoryMethod.cpp) - *Real-World*-Beispiel (`ITelevision`), das exemplarisch mehrere *Factory Methods* betrachtet.<br/>

In *Quellcode 3* findet sich ein Programm mit den Klassen `ITelevision`, `LEDTelevision`, `OledTelevision`,
`AbstractTVFactory`, `LEDTVFactory` und `OledTVFactory` vor.
Studieren Sie die Methoden `manufactureTelevision`, `assembleTelevision`, `shippingCharge` 
und `productionCharge` der Klasse `AbstractTVFactory`.
Beschreiben Sie, wie diese Methoden zur Namensgebung des *Factory Method Patterns* beitragen.

<img src="dp_factory_method_pattern_television.svg" width="900">

*Abbildung* 2: Das *Factory Method Pattern* am Beispiel der Produktion von Fernsehger�ten.

---

#### Ein weiterer Anwendungsfall des Factory Method Patterns:

Das *Factory Method* Pattern kommt auch dann zum Zuge, wenn es

  * viele unterschiedliche M�glichkeiten gibt, ein Objekt zu konstruieren und
  * dies aber die Ursache von Fehlerquellen sein kann.

*Beispiel*:

```cpp
01:     struct Point {
02:         Point(double x, double y) { /*...*/ }        // Cartesian coordinates
03:         // ... Implementation
04: 
05:         // Not OK: Cannot overload with same type of arguments
06:         // 
07:         // Point(double a, double b){ /*...*/ }      // Polar coordinates
08:         // ... Implementation
09:     };
```

Zwei Konstruktoren in einer Klasse `Point` mit identischer Signatur,
aber unterschiedlicher Bedeutung:
Dies ist nicht m�glich, eine Abhilfe k�nnte so aussehen:

```cpp
01: enum class PointType { cartesian, polar };
02: 
03: class Point
04: {
05: public:
06:     Point(double a, double b, PointType type = PointType::cartesian)
07:     {
08:         if (type == PointType::cartesian) {
09:             m_x = a;
10:             m_y = b;
11:         }
12:         else {
13:             m_x = a * cos(b);
14:             m_y = a * sin(b);
15:         }
16:     }
17: 
18: private:
19:     double m_x;
20:     double m_y;
21: };
```

Dies ist jedoch keine sehr einfallsreiche Vorgehensweise, das Problem auf diese Weise zu l�sen.
Wir sollten vielmehr die jeweilige Instanziierung an separate Methoden delegieren:

```cpp
01: class Point
02: {
03: private:
04:     double     m_x;
05:     double     m_y;
06:     PointType  m_type;
07: 
08:     // private constructor, so that object can't be created directly
09:     Point(const double x, const double y, PointType t) 
10:         : m_x{ x }, m_y{ y }, m_type{ t } {}
11: 
12: public:
13:     friend std::ostream& operator<<(std::ostream& os, const Point& obj) {
14:         return os << "x: " << obj.m_x << " y: " << obj.m_y;
15:     }
16: 
17:     static Point NewCartesian(double x, double y) {
18:         return { x, y, PointType::cartesian };
19:     }
20: 
21:     static Point NewPolar(double a, double b) {
22:         return { a * cos(b), a * sin(b), PointType::polar };
23:     }
24: };
```

Wie man an der Implementierung beobachten kann, wird der explizite Gebrauch des Konstruktors
untersagt. Der Benutzer wird stattdessen gezwungen, statische Methoden (Klassenmethoden) zu verwenden:

```cpp
auto p = Point::NewPolar(5.0, M_PI / 4);
```

Jetzt haben wir die Funktionalit�ten zweier *Concerns* in eine Klasse gepackt:
Die von der Klasse `Point` als auch die ihrer Fabrik. Wir sollten den Codeanteil der Fabrik
in eine dedizierte Klasse verlagern. So f�hlen wir uns auch besser, 
was unsere Bedenken bzgl. des *Single Responsibility Principles* der SOLID-Designprinzipien anbelangt:

```cpp
01: class Point
02: {
03:     friend class PointFactory;
04: 
05: private:
06:     double    m_x;
07:     double    m_y;
08: 
09:     ...
10: };
11: 
12: class PointFactory
13: {
14: public:
15:     static Point NewCartesian(double x, double y) {
16:         return { x, y, PointType::cartesian };
17:     }
18: 
19:     static Point NewPolar(double a, double b) {
20:         return { a * cos(b), a * sin(b), PointType::polar };
21:     }
22: };
```

Auch hier gibt es noch die M�glichkeit einer Verfeinerung bzw. einer Stolperfalle:
Der Gebrauch des `friend`-Schl�sselworts ist h�ufig ein Indikator,
dass gegen das *Open-Closed-Prinzip* versto�en wird.


###### *Inner Factory*:

Wir machen eine kritische Beobachtung, die wir in unserer Factory-Klasse �bersehen haben:
Es gibt keine wirkliche Verbindung zwischen den beiden Klassen `PointFactory` und `Point`!

Warum m�ssen wir eine Fabrik �berhaupt au�erhalb der betroffenen Klasse entwerfen?
Wir k�nnten diese in die `Point`-Klasse integrieren (in einer so genannten *nested class*)
und den Benutzer auf diese Weise ermutigen, die Fabrik (sog. *Inner Factory*) zu verwenden.

```cpp
01: class Point
02: {
03: private:
04:     double m_x;
05:     double m_y;
06: 
07:     Point(double x, double y) : m_x(x), m_y(y) {}
08: 
09: public:
10:     struct Factory
11:     {
12:         static Point NewCartesian(double x, double y) { 
13:             return { x,y };
14:         }
15: 
16:         static Point NewPolar(double r, double theta) { 
17:             return{ r * cos(theta), r * sin(theta) };
18:         }
19:     };
20: };
```

Anwendung:

```cpp
auto p = Point::Factory::NewCartesian(2, 3);
```


###### Die Essenz des *Factory Method* Patterns:

  * Umstellung auf private Konstruktoren und Bereitstellung von Klassenmethoden.


---

#### *Virtual Constructor Idiom*:

Das *Factory Method* Muster wird auch als *Virtual Constructor* Pattern bezeichnet.
Dieses Idiom bringt zum Ausdruck, dass der Client mit einem Konstruktor ein Objekt erzeugt, dessen Typ er nicht kennt.
Der gesamte Zweck dieser Redewendung besteht darin, das Klonen eines Objekts �ber einen Basisklassenzeiger zu erm�glichen.
Hier ist ein Beispiel:

```cpp
class Base
{
public:
    Base() {}
    virtual ~Base() {}

    // the "Virtual Constructor"
    static Base* Create(int id);

    // the "Virtual Copy Constructor"
    virtual Base* Clone() = 0;

    virtual void printMe() = 0;
};

class Derived1 : public Base
{
public:
    Derived1()
    {
        std::cout << "default c'tor Derived1" << std::endl;
    }

    Derived1(const Derived1& rhs)
    {
        std::cout << "copy c'tor Derived1" << std::endl;
    }

    ~Derived1()
    {
        std::cout << "c'tor Derived1" << std::endl;
    }

    virtual Base* Clone() override
    {
        return new Derived1(*this);
    }

    virtual void printMe() override
    {
        std::cout << "I'm a Derived1" << std::endl;
    }
};

// dto. Derived2

// static method
Base* Base::Create(int id)
{
    if (id == 1)
    {
        return new Derived1();
    }
    else
    {
        return new Derived2();
    }
}

// global function
Base* CreateCopy(Base* pBase)
{
    return pBase->Clone();
}

void test_virtual_constructor_idiom()
{
    using namespace VirtualConstructorIdiom;

    std::cout << "Enter Id (1 or 2): ";
    int input;
    std::cin >> input;
    Base* pBase = Base::Create(input);
    Base* pCopy = CreateCopy(pBase);

    // dont know what object is created but still access functions through base pointer
    pBase->printMe();
    pCopy->printMe();

    delete pBase;
    delete pCopy;
}
```

*Beachte*: Der Client kennt den von `Base` geerbten Klassentyp nicht, ruft aber Methoden an diesem Objekt auf!

---

#### Hinweis:

Die beiden Entwurfsmuster *Simple Factory* und *Factory Method* sind nicht 
miteinander zu verwechseln.

**Simple Factory**<br/>
  * Mit dem *Simple Factory* Pattern versuchen wir, die Details in der Erstellung eines Objekts vor dem Anrufer (Client) zu abstrahieren.
    Das einzige, was der Client wei�, indem er eine Methode aufruft und den gew�nschten Parameter �bergibt, ist,
    dass er ein Objekt eines bestimmten Typs erh�lt. Aber wie dieses Objekt erstellt wird, wei� der Client-Code nicht.

**Factory Method**<br/>
  * Das *Factory Method* Pattern bietet sich an, wenn die Anforderungen an die Erstellung eines Objekts mehr als nur der Aufruf des `new`-Operators sind.
    Sind zur Erzeugung des Objekts mehrere Schritte notwendig, m�chte man diese Schritte ggf. anpassen k�nnen
    oder sind diese Schritte bei verschiedenen Objekten unterschiedlich, verwendet man das *Factory Method* Pattern.
  * Oder anders ausgedr�ckt: 
    Gibt es einen Algorithmus / eine Strategie, um die Erzeugung einer Produktfamilie zu steuern,
    dann kommt das *Factory Method* Pattern in Betracht. Dieses l�sst sich gut mit dem *Template Pattern*, oder auch *Strategy Pattern* kombinieren,
    da man mit einer Schablone (Template) die Schritte zum Erstellen des untergeordneten Elements abstrahieren kann.

---

## Literaturhinweise

Die Anregungen zum konzeptionellen Beispiel finden Sie unter

[https://refactoring.guru/design-patterns](https://refactoring.guru/design-patterns/factory-method/cpp/example#example-0)

und 

[https://www.codeproject.com](https://www.codeproject.com/Articles/430590/Design-Patterns-1-of-3-Creational-Design-Patterns#FactoryMethod)

vor.

Das Beispiel zum *Virtual Constructor Idiom* stammt aus

[Stackoverflow: Virtual constructor idiom and factory design](https://stackoverflow.com/questions/11574075/virtual-constructor-idiom-and-factory-design)

---

[Zur�ck](../../../Resources/Readme_05_Catalog.md)

---
