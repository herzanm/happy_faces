# Happy Faces

## Popis projektu

**Happy Faces** je projekt napsaný v C++, jehož cílem je správně složit a orientovat čtverečky tak, aby každý smajlík měl obě své poloviny a zároveň byly zachovány správné barvy. Program pracuje se vstupním vzorem z obrázku a používá algoritmus pro jeho správné složení.

Původní obrázek byl převeden do číselné reprezentace pomocí integerů, kde jednotlivé prvky mají specifické hodnoty. Například:

- Zelené oči: `1`
- Zelený úsměv: `2`
- Modré oči: `3`
- Modrý úsměv: `4`
- Červené oči: `5`
- Červený úsměv: `6`
- Žluté oči: `7`
- Žlutý úsměv: `8`

Tyto hodnoty jsou využívány pro správné sestavení obrázku pomocí algoritmu, který hledá odpovídající části a skládá je dohromady.

Program se skládá ze tří hlavních souborů:

- `Smajlici.hpp` – deklarace tříd a funkcí pro manipulaci se smajlíky.
- `Smajlici.cpp` – implementace logiky skládání a otáčení čtverečků.
- `main.cpp` – hlavní soubor programu, který načítá vstupní obrázek, provádí analýzu a skládá správný výstup.

## Zadání
![smajlici](https://github.com/user-attachments/assets/a074ffba-cecb-49d7-b24c-72c9220a1f94)


## Použití

1. Naklonujte si tento repozitář:
   ```sh
   git clone https://github.com/herzanm/happy_faces.git
   ```
2. Přesuňte se do složky projektu:
   ```sh
   cd happy_faces
   ```
3. Zkompilujte zdrojový kód:
   ```sh
   g++ -o happy_faces main.cpp Smajlici.cpp
   ```
4. Spusťte program:
   ```sh
   ./happy_faces
   ```

## Požadavky

- C++ kompilátor (například GCC nebo Clang)

## Autor

[herzanm](https://github.com/herzanm)

