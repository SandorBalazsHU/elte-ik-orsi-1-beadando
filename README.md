# elte-ik-orsi-1-beadando
Első beadandó az ELTE IK Osztott Rendszerek Implementációja és Sepcifikációja (ORSI) tárgyához.

## Keretsztori:

A Thot könyvéről szóló mítoszok nyomait kutatva Lara Egyiptomba érkezett. A legendák szerint az, aki el tudja olvasni a bölcsesség istenének eredeti írásait, maga is végtelen tudásra tesz szert. Az ifjú Croft sejtette, hogy - mint minden történetnek, így ennek is - van valóságalapja, ám úgy gondolta, kódex inkább egyfajta ókori enciklopédiaként funkcionált.

A helyiektől megszerzett információk alapján egy barlang-rendszer felé vette az irányt, nem messze a Nílus nyugati partjától. A legendát követve csak az találhatja meg a könyvet, aki méltó annak tudására.

A bejáratnál leereszkedve a belső térbe egyfajta csarnokba érkezett - ám trón és asztalok helyett több száz kis táblát talált különböző méretekben a falba rejtve, rajtuk hieroglifákkal. A terem túlsó felén egy hatalmas, zárt ajtó állta útját. Ezen sem kulcslyuk, sem kilincs nem volt - ekkor döbbent rá (korábbi tapasztalatai alapján), hogy az egyetlen kiút innen, ha megoldja a táblák rejtélyét és így kinyitja az ajtót.

Közelebbről megvizsgálva azokat arra lett figyelmes, hogy mindegyik egyfajta kapcsolóként funkcionál, lehetőség volt oldalra tolni őket, melyet egy apró kattanásra emlékeztető hang kísért. A táblákon lévő írást elemezve arra jutott, hogy a különböző jelek minden esetben egyfajta rácsot alkotnak. Minden esetben a táblákon legfeljebb annyi különböző hieroglifával találkozott, ahány sort / oszlopot megszámolt ezeknél. Bár nyelvtudása átlagon felüli volt, akárhogy próbálkozott, értelmezhetetlen szöveget tudott csak kiolvasni a táblákon lévő szimbólumokból, így tudta, hogy ennek megoldása nem a lingvisztikai tudásán fog múlni.

Figyelembe véve az egyre fogyó víz- és élelemkészletét arra jutott, kivételesen nem próbál meg egyedül hősködni - a Te segítségedet kéri. A hatalmas zár brute-force megoldásához 100 tábla esetén 2^100 különböző kombinációt kéne végigpróbálgatnia - ez pedig lehetetlen küldetés.

A táblák fotóit megkapva úgy gondoltad, mivel nem a hieroglifák közvetlen jelentése a megoldás kulcsa, azokat egyszerű számokkal fogod helyettesíteni. Így az adatok feldolgozása is könnyebb, és neked sem kellett bagoly és piramis szimbólumok reprezentációjával bajlódni.

A rejtvényeket nézegetve arra jöttél rá, hogy bizonyos képek esetén lehetőség van minden sor és oszlop kitöltésére olyan módon, hogy csak egyszer szerepeljen benne minden szimbólum, máshol ez nem lehetséges. Rövid egyeztetés után arra jutottatok, az ajtó nyitja abban rejlik, hogy mely rejtvények oldhatóak meg és melyikek nem. Az ezekhez tartozó táblákat külön oldalra mozdítva sikerülni fog az akadály elhárítása.

Annak érdekében, hogy Larának ne ez legyen az utolsó kalandja úgy döntöttél, felgyorsítod a megoldási folyamatodat, és a megoldó algoritmusodat párhuzamosítod, hogy minél hamarabb eredményt kapj, és elmondhasd:

"Én mentettem meg Lara Croft életét."

## A megoldandó feladat tehát a következő:

A bemeneti fájlban (input.txt) M darab mátrix olvasható. Ezen mátrixok mindegyike egy NxN-es rejtvényt határoz meg (az N mátrixonként eltérő, de adott). A feladatunk, meghatározni a kapott mátrixból kiindulva azt az NxN-es mátrixot, melynek minden sorában és minden oszlopában csupán egyszer szerepel az összes i € [1..N] szám. A mátrix néhány eleme adott, ezek a megfelelő pozitív számok. Ahol a mátrix "nincs kitöltve", ott a bemenetben 0 olvasható. (A feladat tehát egy egyszerűsített sudoku-hoz hasonlít, de nincsenek kisebb blokkok a nagy rejtvényen belül.)

Az így kiszámított eredményeket (a bemenet sorrendjében) írjuk ki az output.txt fájlba! Amennyiben nem létezik megoldás, úgy az eredeti, beolvasott mátrix kerüljön a kimeneti fájlba.

### Az inputfájl felépítése az alábbi:

Az első sorban egy M, nemnegatív egész szám olvasható, ezt követően összesen M darab mátrix található a fájlban. Az ezt követő M bemenetet a következő infók alapján lehet beolvasni:

Először a mátrix mérete (N) olvasható. Minden mátrix N x N-es, tehát négyzetes alakú. Az ezt következő N sor az aktuális mátrix egy-egy sorát tartalmazza, nemnegatív egész számokat a [0..N] intervallumból szóközzel tagolva.

Egy 4x4-es mátrixot tehát 5 sorból tudunk beolvasni, először a méretet (4), majd a következő 4 sorban a mátrix adatait.
Feltehetjük, hogy az input fájl a fent leírtaknak megfelelően van kitöltve, és nem található benne pl. negatív, valós vagy N-nél nagyobb szám, erre külön ellenőrzést nem kell végezni.

A program olvassa be az adatokat, majd M folymatot indítva számítsa ki az egyes mátrixokhoz tartozó megoldást, majd az így kapott eredményeket írja ki az "output.txt" fájlba. A fő szál a rejtvények megoldásához kapcsolódó számítást ne végezzen!

### Egy példa bemenet (input.txt)

```
3
2
1 1
0 0
3
1 0 0
0 1 0
2 0 0
4
1 2 4 0
3 0 0 0
0 0 1 2
2 4 0 1
```

### Az ehhez tartozó kimenet (output.txt)

```
1 1
0 0
1 2 3
3 1 2
2 3 1
1 2 4 3
3 1 2 4
4 3 1 2
2 4 3 1
```

### Segítség a megoldáshoz:

#### Segítség a feladat algoritmusához (persze más módszerrel is megoldható):

    Próbáljunk meg a problémára rekurzív megoldást adni.
    Az algoritmus egy adott mátrix kitölthetőségéről adjon vissza információt (bool) az (i,j) koordináta alapján.
    Ha végigértünk a mátrixon (tehát az (i,j) pár már nem egy valós index), akkor megoldható a feladat.
    Ha az adott (i,j) érték nem 0, akkor rekurzívan oldjuk meg a feladatot a következő cellára (sor/oszlop végét figyelembe véve).
    Ellenkező esetben (ha tehát az (i,j) biztosan 0):
    Az [1..n] intervallum egy (k) elemét írjuk be az (i,j) helyre.
    Vizsgáljuk meg, hogy igaz -e az, hogy az adott sorban/oszlopban a k csupán egyszer szerepel, illetve az így kapott mátrix kitölthető -e a szabályok alapján (rekurzió).
    Ha igen, adjunk vissza igazat, ellenkező esetben próbálkozzunk egy másik k értékkel (lásd: 2 ponttal ezelőtt).
    Ha így sem kapunk igazat, az adott feladat nem oldható meg, az (i,j) érték maradjon 0.

Egy mátrix megoldhatóságának vizsgálatát érdemes a (0,0) párból indítani.

## Általános elvárások:

Fokozottan kérünk mindenkit, hogy a beadandó határidejét (november 4, 19:59) vegye figyelembe! Kérjük osszátok be az időtöket, hogy ne csússzatok le a határidőről semmi esetben sem! Ez után nem áll módunkban elfogadni megoldásokat, kifogástól és indoklástól függetlenül! (Szült a halam, nem tudtam beadni, de elküldöm emailben; pont feltöltöttem volna, de lezárt a BEAD, jó lesz facebookon?; Késett a vonat de majd behozom pendriveon úgy jó? Nem, nem lesz jó egyik esetben sem.)

Kérünk mindenkit, hogy olvassa el a BEAD-on a hozzászólásokat, amiket írunk neki, mielőtt újra és újra feltölti a megoldást, így elkerülhető, hogy feleslegesen terheljétek a szervert, és egy körben lehet a legtöbb hibát javítani.

A megoldásaitokat egyetlen ZIP fájlba tömörítve töltsétek fel! Kérünk benneteket, hogy csak a szükséges forrásfájl(oka)t rakjátok bele az állomány gyökerébe, teljes projektet, solutiont (.cbp, .sln, illetve az ezekhez tartozó többi fájl), object fájlokat, vagy közvetlenül futtatható állományt (a.exe, a.out, etc..) semmiképp sem!

Az első két beadandóhoz nem kötelező a dokumentáció, de aki szeretné gyakorolni a 3-ikhoz, az mintadokumentációt talál itt, kérjük ez alapján dolgozzon! http://people.inf.elte.hu/mykeesg/orsi17_18_1/mintadoksi.zip

A beadandót binárisan értékeljük, de ettől függetlenül fogtok kapni (valószínűleg) megjegyzéseket a megoldásotokra vonatkozóan.

Javítani bármennyiszer lehet, de a határidő szoros közeledtével egyre kisebb az esély rá, hogy lesz időnk megnézni azt.
Szeretnénk mindenkit megkérni, hogy az alábbiak vegye figyelembe a feltöltés során:

    C++11: Lehetőleg egy fájl (*.cpp) legyen, melyben található a belépési pont (main() függvény).
    A fájl(oka)t a ZIP gyökerébe helyezzétek el, tehát ne mappát tömörítsetek, csupán a fájl(oka)t!

Értékelési megjegyzés: Az automata tesztelő elutasítja a megoldást, ha az nem fordult le (ennek okát is jelezni fogja). Amennyiben fordítható, lefuttatja több különböző inputra, és összeveti a megoldásodat az elvárt kimenetekkel. Ha mindegyik egyezik (a whitespacek között nem tesz különbséget, így mindegy, hogy a sorok végén van -e plusz szóköz vagy nincs, illetve sorvégi enter az utolsó bejegyzés után), akkor a BEADon átment a megoldásod. Ez után még valamelyik oktató is ellenőrzi a megoldást - a kódot átnézve, megjegyzéseket fűzve hozzá. Ha ez is rendben van, akkor elfogadottnak minősítjük a beadandót. Ha valami problémába ütközünk (vagy a BEADon nem megy át), akkor elutasításra kerül a megoldásod. Ennek okát részletezni fogjuk.

Egyéb segítség: http://people.inf.elte.hu/mykeesg/orsi18_19_1

A leggyakrabban ismételt kérdésekre http://people.inf.elte.hu/mykeesg/orsi18_19_1/orsi_faq.pdf itt találhattok választ.

Az értékelési szempontrendszer http://people.inf.elte.hu/mykeesg/orsi18_19_1/kovetelmeny.pdf ez alapján történik, kérjük figyelmesen olvassátok el.

Ha egyéb kérdésetek van, akkor az orsi4ever@gmail.com címen tudtok kérdezni.
