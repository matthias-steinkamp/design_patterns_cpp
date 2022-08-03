# Template Method Pattern

[Zur�ck](../../../Resources/Readme_05_Catalog.md)

---

<img src="dp_template_methodpattern_intro.png" width="600" />

<sup>(Credits: [Blog von Vishal Chovatiya](http://www.vishalchovatiya.com/category/design-patterns/))</sup>

---

## Wesentliche Merkmale

##### Kategorie: *Behavioral Pattern*

#### Ziel / Absicht:

###### In einem Satz:

&ldquo;Um einen Entwurf eines Algorithmus auf einer h�heren Ebene bereitzustellen, der von seinen abgeleiteten Klassen zu vervollst�ndigen ist.&rdquo;

Definiert das prinzipielle Grundger�st eines Algorithmus in einer zentralen Methode.
Diese lagert einen oder vorzugsweise mehrere Teilschritte in Methoden abgeleiteter Klassen aus.
�nderungen an den Teilschritten haben keine Auswirkungen auf die Arbeitsweise (Realisierung)
der zentralen Methode.

Das *Template Method Pattern* ist ein Verhaltensentwurfsmuster,
das das Grundger�st eines Algorithmus in einer Oberklasse definiert,
Unterklassen jedoch bestimmte Schritte des Algorithmus �berschreiben l�sst,
ohne dabei seine prinzipielle Struktur zu �ndern.

#### Problem:

Es gibt eine Methode oder anders formuliert, eine Reihe von auszuf�hrenden Schritten (Teilmethoden),
die auf einer h�heren Abstraktionsebene
festgelegt sind (Reihenfolge der Ausf�hrung, Bereitstellung von Parametern, ...).

In einer niedrigeren Abstraktionsebene (Detailebene) k�nnen die Teilmethoden eine unterschiedliche Implementierung haben.


#### L�sung:

Das *Template Method Pattern* hat zum Inhalt, dass Sie einen Algorithmus in eine Reihe von Schritten aufteilen,
diese Schritte in Methoden umwandeln und diese Methoden in einer einzigen &ldquo;Vorlagenmethode&rdquo; aufrufen,
daher auch der Name dieses Entwurfsmusters.
Die Schritte k�nnen entweder abstrakt sein oder eine Standardimplementierung aufweisen.
Um den Algorithmus zu verwenden, muss der Client eine eigene Unterklasse bereitstellen, alle abstrakten Schritte implementieren und bei Bedarf einige der optionalen Schritte �berschreiben.
Die Vorlagenmethode sollte dabei nicht �berschrieben oder ver�ndert werden!

Das *Template Method Pattern* erm�glicht die Realisierung von variierenden Teilschritten, w�hrend ein konsistenter Grundprozess beibehalten wird.


#### Struktur (UML):

<img src="dp_template_method_pattern.svg" width="450">

*Abbildung* 1: Schematische Darstellung des *Template Method Patterns*.


#### Hinweis: Was ist der Unterschied zwischen dem *Template Method Pattern* und dem *Strategy Pattern*? 

*Template Method Pattern* und *Strategy Pattern* besitzen viele Gemeinsamkeiten:

  * Ein Unterschied zwischen den beiden Mustern ist,
  dass das *Template Method Pattern* auf Vererbung beruht, das *Strategy Pattern* hingehen auf Komposition.

  * Das *Template Method Pattern* funktioniert auf Klassenebene, ist also statisch.

  * Das *Strategy Pattern* funktioniert auf Objektebene, so dass Sie das Verhalten zur Laufzeit �ndern k�nnen.


## Anwendungsbeispiel:

In Spezialisierungen der Oberklasse k�nnen bzw. sollten ein oder mehrere Teilmethoden �berschrieben werden,
um die **Template Methode** in der Oberklasse zu vervollst�ndigen. 

Die Skelett-Methode ist davon ausgenommen - die prinzipielle Struktur des Algorithmus ist beizubehalten,
also nicht zu ver�ndern.

---

#### Conceptual Example:

[Quellcode](../ConceptualExample.cpp)

---

#### 'Real-World' Beispiel:

Im 'Real-World' Beispiel zu diesem Entwurfsmuster 
definiert die Template-Methode einen Algorithmus f�r die Arbeit mit einem sozialen Netzwerk.
Unterklassen, die einem bestimmten sozialen Netzwerk entsprechen,
implementieren diese Schritte gem�� der vom sozialen Netzwerk bereitgestellten API.

Die Klasse `SocialNetwork` repr�sentiert die Basisklasse des sozialen Netzwerks.
Zwei weitere Klassen `Twitter` und `Facebook` stehen f�r konkrete Beispiele sozialer Netzwerke.

Die &ldquo;Vorlagenmethode&rdquo; ist in der Klasse `SocialNetwork` vorgegeben, sie lautet `post`:

```cpp
bool post(const std::string& message);
```

Ihre Implementierung darf nicht ver�ndert werden, um dem Charakter des Entwurfsmusters gerecht zu werden.
Die Teilschritte, die zur Realisierung der `post`-Methode erforderlich sind, lauten in dem Beispiel
`logIn`, `logOut` und `sendData`. Diese drei Methoden sind geeignet von konkreten Social Media Klassen
zu �berschreiben, siehe dazu auch *Abbildung* 2:

<img src="dp_template_method_pattern_social_media.svg" width="800">

*Abbildung* 2: Das *Template Method Pattern* am Beispiel sozialer Netzwerke.

---

## FAQs

*Frage*: Was ist der Unterschied zwischen dem *Strategy*- und *Template Method*-Pattern?

  * Das *Template Method*-Pattern basiert auf Vererbung: Es werden Teile eines Algorithmus ver�ndert, indem diese Teile in abgeleiteten Klassen erweitert werden.

  * *Strategy*-Pattern basiert auf der Komposition: Es werden Teile des Verhaltens eines Objekts ver�ndert, indem es verschiedene Strategien erh�lt, die unterschiedlichem Verhalten entsprechen.

oder auch:

  * *Template Method*-Pattern: Funktioniert auf Klassenebene, es ist also statisch.

  * *Strategy*-Pattern: Funktioniert auf Objektebene, das Verhalten wird zur Laufzeit ge�ndert.

---

## Literaturhinweise

Die Anregungen zum konzeptionellen Beispiel finden Sie unter

[https://refactoring.guru/design-patterns](https://refactoring.guru/design-patterns/template-method/cpp/example#example-0)

und

[https://www.codeproject.com](https://www.codeproject.com/Articles/455228/Design-Patterns-3-of-3-Behavioral-Design-Patterns#Template)

vor.

---

[Zur�ck](../../../Resources/Readme_05_Catalog.md)

---
