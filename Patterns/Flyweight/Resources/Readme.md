# Flyweight Pattern

[Zur�ck](../../../Resources/Readme_05_Catalog.md)

---

<img src="dp_flyweight_pattern_intro.png" width="600" />

<sup>(Credits: [Blog von Vishal Chovatiya](http://www.vishalchovatiya.com/category/design-patterns/))</sup>

---

## Wesentliche Merkmale

#### Kategorie: *Structural Pattern*

#### Ziel / Absicht:

###### In einem Satz:

&ldquo;Um Redundanzen beim Speichern von Daten zu vermeiden.&rdquo;

Das *Flyweight Pattern* ist ein Entwurfsmuster aus der Kategorie der *Structural Pattern*,
das verwendet wird, um den Ressourcenverbrauch eines Programms mit einer sehr gro�en Anzahl von Objekten zu minimieren.
Beim Erzeugen von vielen tausend identischen Objekten k�nnen zustandslose &ldquo;Flyweight&rdquo;-Objekte
den in Anspruch genommen Speicher auf ein vertretbares Ma� reduzieren.

#### Problem:

Manchmal arbeiten Programme mit einer gro�en Anzahl von Objekten, die dieselbe Struktur haben,
und einige Zust�nde dieser Objekte haben stets denselben Wert.
Wenn wir den klassischen Ansatz verwenden (Instanzen erstellen, Instanzvariablen schreiben),
k�nnen sich die Speicher- bzw. Speicherbereichsanforderungen inakzeptabel erh�hen.
Das *Flyweight Pattern* stellt eine Alternative in diesem Zusammenhang dar.

#### Beispiel:

Zum Verst�ndnis des  *Flyweight* Entwurfsmusters spielen zwei Begriffe eine Rolle: *Intrinsischer* und *extrinsischer* Zustand.
Dazu ein Beispiel: Betrachten wir als Beispiel einen Texteditor. Pro Eingabe eines Zeichens wird ein Objekt einer Klasse `Character` erstellt.
Zu den Attributen der `Character`-Klasse z�hlen zum Beispiel `name` (welches Zeichen), `font` (welche Schriftart) und
`size` (welche Zeichengr��e). Diese Informationen m�ssen wir nicht jedes Mal kopieren, wenn der Benutzer ein  Zeichen eingibt,
da sich der Buchstabe 'B' nicht von einem anderen 'B' unterscheidet. 
Wenn der Client erneut ein 'B' eingibt, geben wir einfach das Objekt zur�ck, das wir bereits zuvor erstellt haben.
All dies bezeichnen wir als *intrinsische* Zust�nde (Name, Schriftart, Gr��e), da sie von den verschiedenen Objekten gemeinsam genutzt werden k�nnen!

Jetzt f�gen wir der Klasse `Character` weitere Attribute hinzu, zum Beispiel `row` (Zeile) und `col` (Spalte).
Sie geben die Position eines Zeichens im Dokument an. Diese Attribute k�nnen niemals dieselben sein, auch nicht f�r dieselben Zeichen,
da keine zwei Zeichen dieselbe Position in einem Dokument haben k�nnen.
Diese Zust�nde werden als *extrinsische* Zust�nde bezeichnet und k�nnen von den betrachteten Objekten nicht gemeinsam genutzt werden.

An Stelle der beiden Fachw�rter *intrinsischer* und *extrinsischer* Zustand spricht
man auch von *repeatingState* und *uniqueState*.

#### L�sung:

Ein so genanntes *Flyweight* ist ein Objekt, das den Speicherbedarf minimiert,
indem so viele Daten wie m�glich mit anderen �hnlichen Objekten geteilt werden.
Es gestattet, Objekte in gro�er Anzahl zu verwenden,
wenn eine einfache wiederholte Erzeugung entsprechender Objekte 
einen nicht akzeptablen Speicherbereich beanspruchen w�rde.
F�r jedes Objekt, das gemeinsam genutzte Daten verwendet,
wird nur ein Verweis (Referenz, Pointer) auf ein gemeinsam genutztes Objekt gespeichert.

Das *Flyweight Pattern* verwendet h�ufig eine Variation des *Factory Method* Entwurfsmusters
f�r die Erzeugung der gemeinsam genutzten Objekte.
Die Fabrik erh�lt eine Anfrage f�r eine *Flyweight* Instanz.
Wenn bereits ein �bereinstimmendes Objekt verwendet wird,
wird eine Referenz dieses Objekt zur�ckgegeben. Andernfalls ist ein neues *Flyweight* Objekt zu generieren.

#### Struktur (UML):

Das folgende UML-Diagramm beschreibt eine Implementierung des *Flyweight Patterns*.
Es besteht im Wesentlichen aus vier Teilen:

  * **Flyweight**: Beschreibt eine Klasse *Flyweight*, die den Teil des Status des zu betrachtenden Objekts enth�lt, der von mehreren Objekten gemeinsam genutzt werden kann.
    Dieses Objekt kann mehrfach verwendet werden. Der im *Flyweight* Objekt gespeicherte Zustand wird als &ldquo;intrinsisch&rdquo; oder &ldquo;repeating&rdquo; bezeichnet.
    Der Zustand, der an die Methoden des *Flyweight* Objekt �bergeben wird, wird als &ldquo;extrinsisch&rdquo; bezeichnet.
    Ein Flyweight-Objekt muss &ldquo;gemeinsam nutzbar&rdquo; (*sharable*) sein.
    Jeder Zustand, den dieses Objekt speichert, muss intrinsisch sein.
  * **FlyweightBase**: Abstraktion der Klasse *Flyweight* zu einem Schnittstellentyp.
  * **UnsharedFlyweight**: Nicht alle *Flyweight* Objekte k�nnen gemeinsam genutzt werden.
    Die `UnsharedFlyweight`-Klasse enth�lt den extrinsischen Status, der f�r alle `UnsharedFlyweight`-Objekte eindeutig (*unique*) ist.
    Wenn ein `UnsharedFlyweight`-Objekt mit einem `Flyweight`-Objekt gepaart wird,
    repr�sentiert es den vollst�ndigen Status des zu betrachtenden Objekts.
  * **FlyweightFactory**: Die *FlyweightFactory* (Fabrik) erstellt und verwaltet *Flyweight* Objekte.
    Dar�ber hinaus verwaltet die Fabrik einen Pool unterschiedlicher *Flyweight* Objekte.
    Die Fabrik gibt bei einer entsprechenden Anforderung ein Objekt aus dem Pool zur�ck,
    falls es bereits erstellt wurde,
    oder f�gt dem Pool ein Neues hinzu und gibt dieses zur�ck, falls dies der Anforderung entspricht.


<img src="dp_flyweight_pattern.svg" width="800">

*Abbildung* 1: Schematische Darstellung des *Flyweight Patterns*.

---

#### Conceptual Example:

[Quellcode](../ConceptualExample.cpp)

---

#### 'Real-World' Beispiel:


Wir betrachten als Beispiel eine *Paint-Brush*-Anwendung.

Der Anwender kann Pinsel-Objekte in drei St�rken benutzen: THICK, THIN and MEDIUM.
Alle dicken (d�nnen oder mittleren) Pinsel zeichnen den Inhalt auf genau �hnliche Weise &ndash; nur
die Inhaltsfarbe ist anders.

Worauf kommt es an:
Die Pinselfarbe ein extrinsisches Attribut, das vom Aufrufer bereitgestellt wird,
ansonsten bleibt f�r den Pinsel alles gleich.
Im Wesentlichen erstellen wir also nur dann einen Stift mit einer bestimmten Gr��e, wenn die Farbe anders ist.
Sobald ein anderer Client diese Stiftgr��e und -farbe ben�tigt, werden wir sie wiederverwenden.

Wir testen die Flyweight-Pen-Objekte in einem Beispielprogramm.
Der Client erstellt hier zwei THICK-Stifte und einen THIN-Stift,
aber zur Laufzeit sind es nur zwei Stiftobjekte,
das in Aktion treten:

*Ausgabe*:

```
Drawing THICK content in color : YELLOW
Drawing THICK content in color : YELLOW
Drawing THICK content in color : BLUE

00000238DF950180      //same object
00000238DF950180      //same object
00000238DF950BA0
```

[Quellcode](../PaintBrush.cpp)


---

## FAQs

*Frage*: Unterschied zwischen Singleton- und Flyweight Pattern?

Das Singleton-Pattern hilft uns, nur ein Objekt im System zu verwalten.
Mit anderen Worten, sobald das erforderliche Objekt erstellt ist, k�nnen wir keine weiteren erstellen.
Wir m�ssen das vorhandene Objekt in allen Teilen der Anwendung wiederverwenden.

Das Flyweight-Pattern wird verwendet, wenn wir eine gro�e Anzahl �hnlicher Objekte erstellen m�ssen,
die sich basierend auf dem vom Client bereitgestellten extrinsischen Attribut unterscheiden.

---

## Literaturhinweise

Die Anregungen zum konzeptionellen Beispiel finden Sie unter

[https://refactoring.guru/design-patterns](https://refactoring.guru/design-patterns/flyweight)

und

[https://www.codeproject.com](https://www.codeproject.com/Articles/438922/Design-Patterns-2-of-3-Structural-Design-Patterns#Flyweight)

vor.

Das *PaintBrush*-Beispiel ist an [Flyweight Design Pattern](https://howtodoinjava.com/design-patterns/structural/flyweight-design-pattern/) angelehnt (Abruf: 15.07.2022).

---

[Zur�ck](../../../Resources/Readme_05_Catalog.md)

---
