# Observer Pattern

[Zur�ck](../../../Resources/Readme_05_Catalog.md)

---

<img src="dp_observer-pattern_intro.png" width="600" />

<sup>(Credits: [Blog von Vishal Chovatiya](http://www.vishalchovatiya.com/category/design-patterns/))</sup>

---

## Wesentliche Merkmale

#### Kategorie: *Behavioral Pattern*

#### Ziel / Absicht:

###### In einem Satz:

&ldquo;Um Benachrichtigungen zu erhalten, wenn Ereignisse eintreten.&rdquo;

Das *Observer Pattern* ist ein Entwurfsmuster aus der Kategorie der *Behavioral Pattern*,
mit dem Sie einen Mechanismus f�r Benachrichtigungen definieren,
um Objekte �ber Ereignisse zu informieren, die in einem beobachteten Objekt auftreten.

#### Problem:

Betrachten wir als Szenario ein Beispiel mit zwei Arten von Objekten:
mehrere Kunden und ein Gesch�ft. Der Kunde ist an einem bestimmten Produkt interessiert,
das bald erh�ltlich sein soll.

Der Kunde kann das Gesch�ft jeden Tag aufsuchen oder die entsprechende WebSite konsultieren,
um die Verf�gbarkeit des Produkts zu �berpr�fen.
Solange das Produkt aber noch gefertigt wird oder sich auf dem Versand zum Gesch�ft befindet,
sind all diese Nachfragen sinnlos.

Auf der anderen Seite k�nnte der Laden genau dann, wenn das Produkt abholbereit ist,
dem oder den interessierten Kunden eine Nachricht zukommen lassen. Auf diese Weise
ist die Information �ber die Verf�gbarkeit am effizientesten gegeben.


#### L�sung:

Das Objekt, das den bereitzustellenden Status besitzt, wird h�ufig als &ldquo;*Subject*&rdquo; oder auch
&ldquo;*Publisher*&rdquo; bezeichnet. Diejenigen Objekte, die die �nderungen am Status des *Publishers* verfolgen,
werden als &ldquo;*Subscriber*&rdquo; oder auch &ldquo;*Observer*&rdquo; bezeichnet. Das Pendant eines &ldquo;*Observers*&rdquo;
kann man auch als &ldquo;*Observable*&rdquo; bezeichnen.

Das *Observer Pattern* sieht vor, dass das &ldquo;*Subject*&rdquo; einen Benachrichtigungsmechanismus der Gestalt aufweist, 
dass einzelne Objekte (*Subscriber*) sich f�r das Benachrichtigen von Ereignissen
an- und abmelden k�nnen.

Typischerweise l�sst sich diese Funktionalit�t mit einer Liste (`std::list` oder �hnliches)
zum Speichern von Verweisen auf *Subscriber*-Objekte realisieren.
Dazu geh�ren dann meist zwei Methoden (zum Beispiel `register` und `unregister`, `add` und `remove` oder `attach` und `detach`),
um *Subscriber* zu dieser Liste hinzuzuf�gen und aus dieser wieder zu entfernen.


#### Struktur (UML):

<img src="dp_observer_01.svg" width="400">

*Abbildung* 1: Schematische Darstellung des *Observer Pattern Musters*: An- und Abmelden.

<img src="dp_observer_02.svg" width="500">

*Abbildung* 2: Schematische Darstellung des *Observer Pattern Musters*: Benachrichtigungen.

<img src="dp_observer_03.svg" width="700">

*Abbildung* 3: Schematische Darstellung des *Observer Pattern Musters*: Abstraktion des Observers mittels Schnittstelle `IObserver`. 

---

#### Conceptual Example:

Das *Conceptual Example* liegt in drei Varianten vor:

  * Variante 1: klassisch - d.h. mit &ldquo;raw&rdquo;-Zeigern.
  * Variante 2: Mit `std::shared_ptr` Objekten.
  * Variante 3: Wie Variante 2, aber mit `std::enable_shared_from_this<>` Mechanismus.
  * Variante 4: Wie Variante 1, aber mit Template-Technik.

[Quellcode 1](../ConceptualExample01.cpp)

[Quellcode 2](../ConceptualExample02.cpp)

[Quellcode 3](../ConceptualExample03.cpp)

[Quellcode 4](../ConceptualExample04.cpp)

---

Die Anregung zum konzeptionellen Beispiel finden Sie unter

[https://refactoring.guru/design-patterns](https://refactoring.guru/design-patterns/observer/cpp/example#example-0)

vor.

**Hinweis**:

In Variante 2 wird prinzipiell ohne &ldquo;raw&rdquo;-Zeiger gearbeitet, also so,
wie man es der &ldquo;reinen Lehre&rdquo; nach machen sollte. Dabei stellt sich aber eine Frage:
Wie erhalte ich von einem Objekt einen `std::shared_ptr`, desses Objekterzeugung
au�erhalb meines Wirkungskreises liegt. Die Frage lautet also gewisserma�en:

```cpp
std::shared_ptr<IObserver> me = this;
```

Das geht so nicht, wie zu erwarten war. Es gibt aber den folgenden Weg:

```cpp
class Observer : public IObserver, public std::enable_shared_from_this<Observer> {
    ...
}
```

Die Klasse `Observer` leitet sich von einer Standard-Klasse `std::enable_shared_from_this<>` ab,
die genau zu diesem Zweck realisiert wurde.
Damit vererbt sie eine Methode `shared_from_this` an die Kindklasse.
Auf diese Weise kann man dann beispielsweise eine Methode `removeMeFromTheList`
wie folgt implementieren:

```cpp
void removeMeFromTheList() {
    std::shared_ptr<Observer> me = shared_from_this();
    m_subject->detach(me);
    std::cout << "Observer \"" << m_number << "\" removed from the list.";
}
```

**Achtung**: Der Aufruf `shared_from_this` ist aber nur dann zul�ssig,
wenn es von dem Objekt (hier: Klasse `Observer`) bereits einen Shared Pointer gibt!
Das muss nicht immer der Fall sein!
Deshalb ist in der vorliegenden Fallstudie zumindest eine Methode im Stile von `removeMeFromTheList` realisierbar,
aber nicht ein entsprechendes Gegenst�ck zum Anmelden. Weitere Details der Realisierung
entnehmen Sie bitte der dritten Variante des *Conceptual Example*.

---

[Zur�ck](../../../Resources/Readme_05_Catalog.md)

---
