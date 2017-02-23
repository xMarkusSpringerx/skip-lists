# Skip Lists

Zur Realisierung der abstrakten Datenstrukturen sortierte Menge (set) und sortiertes assoziatives Feld (dictionary, map) werden meistens binäre Suchbäume verwendet. Damit die Operationen auf diese Datenstrukturen (Finden, Einfügen und Löschen) in allen Fällen eine logarithmische Laufzeitkom- plexität aufweisen, muss der Suchbaum bei jeder schreibenden Operation ausbalanziert werden. Die Implementierung von balanzierten Bäumen (Rot-Schwarz-Baum) ist allerdings sehr aufwändig.

In einer schon relativ alten Arbeit aus dem Jahr 1990 stellt William Pugh so genannte Skip Lists vor (das vollständige Paper finden Sie unter ftp://ftp.cs.umd.edu/pub/skipLists/skiplists.pdf), welche sich ebenfalls zur Implementierung der oben angesprochenen abstrakten Datenstrukturen eigenen. Skip Lists haben zwar im Durchschnittsfall dasselbe asymptotische Laufzeitverhalten wie balanzierte Suchbäume, sind aber bei Weitem einfacher zu implementieren.

a) Studieren Sie das Paper von Pugh und erstellen Sie auf Basis der daraus gewonnenen Erkennt- nisse eine C++-Schablone skip_set, welche die abstrakte Datenstruktur Menge implementiert, allerdings intern Skip Lists zur Repräsentation der Knoten verwendet. Die Schnittstelle von skip_set soll zunächst folgenermaßen aussehen:

template<typename T, const int MAXLEVEL=32> class skip_set {
  public:
    skip_set();
    virtual ~skip_set();
    int size() const;
    bool find(T value) const; // checks if value is in set void insert(T value); // inserts element into set bool erase(T value); // removes element and returns
 // if value was found in set

b) Schaffen Sie eine Möglichkeit, skip_set mit einem Funktionsobjekt zum Vergleich von Elementen zu instanzieren. Sie müssen dazu einen zusätzlichen Schablonenparameter einführen:
template<typename T, typename C = std::less<T>, const int MAXLEVEL=32> class skip_set {
... }
Führen Sie Tests mit zumindest einem benutzerdefinierten Vergleichsobjekt durch.
}; // skip_set


c) Erweitern Sie skip_set um einen Vorwärts-Iterator. Ein Vorwärts-Iterator muss die Operatoren ==, !=, ++ (Prä- u. Postinkrement), * und -> unterstützen. Die Schnittstelle von skip_set muss dafür natürlich auch erweitert und teilweise angepasst werden:
template<typename T, typename C = std::less<T>, const int MAXLEVEL=32> class skip_set {
public:
typedef skip_set_iterator iterator; ...
iterator find(T value);
...
iterator begin();
iterator end();
       }; // skip_set
       
d) Erweitern Sie den in b) entwickelten Iterator zu einem bidirektionalen Iterator. Sie müssen dafür leichte Modifikationen an der internen Datenstruktur vornehmen.

e) Führen Sie für die Implementierung von Mengen in der STL und Ihre Implementierung ausführ- liche Laufzeitanalysen durch. Übersetzen Sie dazu Ihre Quelltexte mit aktivierter Optimie- rungsoption. Überprüfen Sie zunächst, ob das erwartete asymptotische Laufzeitverhalten tatsäch- lich eintritt und belegen Sie Ihre Beobachtungen mit einer Grafik. Präzisieren Sie die Unterschiede im Laufzeitverhalten, indem Sie aus Ihrem Datenmaterial eine Regressionsfunktion für beide Implementierungen ermitteln.
