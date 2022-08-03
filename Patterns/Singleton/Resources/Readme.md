# Singleton Pattern

[Zur�ck](../../../Resources/Readme_05_Catalog.md)

---

<img src="dp_singleton_pattern_intro.png" width="600" />

<sup>(Credits: [Blog von Vishal Chovatiya](http://www.vishalchovatiya.com/category/design-patterns/))</sup>

---

## Wesentliche Merkmale

##### Kategorie: Erzeugungsmuster / *Creational Pattern*

#### Ziel / Absicht:

Das *Singleton Pattern* ist ein Entwurfsmuster, mit dem sichergestellt wird,
dass es zu einer Klasse nur eine einzige Instanz gibt.
Immer wenn neue Objekte einer Singleton-Klasse ben�tigt werden,
wird die zuvor erstellte Einzelinstanz bereitgestellt.

#### Problem:

In einigen F�llen ist es wichtig, zu einer konkreten Klasse maximal nur eine Instanz zu haben.
Zum Beispiel dann, wenn man nur einen einzigen globalen Zugriffspunkt
auf eine begrenzte Ressource ben�tigt. 

W�rde man eine derartige globale Variable erstellen, die kopiert wird,
w�rde dies zu mehreren Zugriffspunkten f�hren und damit zu m�glichen Dateninkonsistenzen.

*Beispiele*:
  * Stream Objekte von C++: `std::cout`, `std::cin` und `std::cerr`.
  * `HttpContext`-Klasse (Java, C# und andere).
 
Ein weiteres Beispiel f�r Singletons sind Klassen wie zum Beispiel `Color`.
W�rde man &ndash; beispielsweise bei jeder Notwendigkeit im Gebrauch einer Farbe wie *rot* &ndash;
ein entsprechendes `Color`-Objekt erzeugen, w�rde man die Speicherplatzanforderungen
dieser Anwendung nicht mehr in den Griff bekommen. 

Aus diesem Grund gibt es in den entsprechenden Frameworks (J2SE, .NET) f�r diesen
Anwendungsfall zugeschnittene (leicht
modifizierte `getSingleton`) Methoden, die f�r jeweils eine Farbe immer dasselbe Objekt
zur�ckliefern:

```c#
// C# / .NET Framework
public static Color FromArgb (byte a, byte r, byte g, byte b);
```

Nat�rlich setzt dies voraus, dass die Klasse Color in derartigen Anwendungsf�llen
*immutable*, also unver�nderbar ist. Andernfalls k�nnte zur Laufzeit aus einer
roten eine blaue Farbe werden, was so sicherlich nicht erw�nscht ist.

#### Struktur (UML):

Das folgende UML-Diagramm beschreibt eine Implementierung des *Singleton Patterns*.
Es besteht nur aus einer einzigen Klasse:

  * **Singleton**: Dieser Klasse besitzt eine statische Methode `getSingleton`,
    die pro Aufruf eine einzelne Instanz zur�ckgibt (Referenz, Zeiger),
    die in einer privaten Variablen residiert.

<img src="dp_singleton_pattern.svg" width="300">

*Abbildung* 1: Schematische Darstellung des *Singleton Patterns*.

#### Double-Checked Locking / Doppelt �berpr�fte Sperrung:

Eine *doppelt �berpr�fte Sperrung* (englisch *double-checked locking*) ist ein Muster in der Softwareentwicklung,
welches dazu dient, den Zugriff auf ein gemeinsames Objekt durch mehrere gleichzeitig laufende Threads zu regeln.

Die klassische Realisierung der `getInstance`-Methode weist einen kleinen Sch�nheitsfehler auf:

```cpp
Singleton* Singleton::getInstance()
{
    {
        std::scoped_lock<std::mutex> lock{ m_mutex };
        if (m_instance == nullptr) {
            m_instance = new Singleton();
        }
    }

    return m_instance;
}
```

Das Erzeugen des (einzigen) Objekts erfolgt thread-sicher, so weit, so gut. Der Sch�nheitsfehler dabei ist,
dass der Zugriff auf das Objekt (pr�ziser: der lesende Zugriff zum Erlangen einer Zeigervariablen, die auf das Objekt zeigt)
�ber dieselbe Methode (!) sehr oft geschehen kann und damit auch
die lesenden Zugriffe auf das Singleton-Objekt thread-sicher ausgef�hrt werden, was �berfl�ssig ist und
unn�tige Rechenzeit beansprucht.

Die `getInstance`-Methode sollte deshalb mit einer so genannten *doppelt �berpr�ften Sperrung*
realisiert werden. Hier wird nur das Erzeugen des Singleton-Objekts thread-sicher ausgef�hrt,
der (lesende) Zugriff auf die Zeigervariable des Objekts wird ohne Sperre durchgef�hrt:

```cpp
Singleton* Singleton::getInstance()
{
    if (m_instance == nullptr)
    {
        std::scoped_lock<std::mutex> lock{ m_mutex };
        if (m_instance == nullptr)  // <= NOTE: double-check of m_instance being nullptr
        {
            m_instance = new Singleton(value);
        }
    }

    return m_instance;
}
```

---

#### Conceptual Example:

[Quellcode 1](../ConceptualExample01.cpp) &ndash; Sehr einfache Version

[Quellcode 2](../ConceptualExample02.cpp) &ndash; Mit *Double-Checked Locking*

---

## Weiterarbeit:

Ein seht guter Aufsatz, wie `std::shared_ptr`-, `std::weak_ptr`- und Singleton-Objekte zusammenarbeiten,
kann unter

[Shared Singleton's](http://btorpey.github.io/blog/2014/02/12/shared-singletons/)

nachgelesen werden.

---

## Literaturhinweise

Die Anregungen zum konzeptionellen Beispiel finden Sie unter

[https://refactoring.guru/design-patterns](https://refactoring.guru/design-patterns/singleton/cpp/example#example-0)

und 

[https://www.codeproject.com](https://www.codeproject.com/Articles/430590/Design-Patterns-1-of-3-Creational-Design-Patterns#Singleton)

vor.

---

[Zur�ck](../../../Resources/Readme_05_Catalog.md)

---
