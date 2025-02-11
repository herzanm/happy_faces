/*
Smajlici...

- Prepsat matice do objektu tridy a prevest smiley face a barvy na int, kde:
    Zelená:
        oči -> 1
        ústa -> 2
    Červená:
        oči -> 3
        ústa -> 4
    Modrá:
        oči -> 5
        ústa -> 6
    Žlutá:
        oči -> 7
        ústa -> 8

- Hledat možné kombinace směrem -> a vytvořit kombinace řádků
- Najít všechny možné kombinace řádků
*/

#include "Square.hpp"
#include <iostream>
#include <vector>
#include <unordered_set>

//----------------------------------------------------------------
// Deklarace funkcí

bool matchEmoji(const Square& lastSquare, const Square& nextSquare);
bool noOverlap(const std::vector<Square>& firstRow, const std::vector<Square>& secondRow,const std::vector<Square>& thirdRow);
std::vector<Square> flipRow(const std::vector<Square>& chain);
void searchRows(const std::vector<Square>& squares, std::vector<Square> row, std::vector<std::vector<Square>>& rowSets);
bool rowContainsSquare(const std::vector<Square>& squares, const Square& newSquare);
bool matchingEmojiRows(const Square& top, const Square& bottom);
void printRow(const std::vector<Square>& row);
void getStartingSquare(const std::vector<Square>& squares, std::vector<std::vector<Square>>& rowSets);
void findThreeRowStack(const std::vector<std::vector<Square>>& rowSets);

//----------------------------------------------------------------
// Vyhledávání všech možných řádků

// Funkce na kotrolu zda dané čtverce mají správné smajlíky na straně
bool matchEmoji(const Square& lastSquare, const Square& nextSquare) {
    int left = nextSquare.getLeft();
    int right = lastSquare.getRight();

    if (left % 2 != 0) {  // pokud je getLeft liché, getRight musí být o 1 větší (2-1,4-3,6-5,8-7)
        return (right == left + 1);
    } else {           // opačný případ (1-2,3-4,5-6,7-8)
        return (right == left - 1);
    }
}

// Funkce na nastavení prvního čtverce a jeho všech rotací 
void getStartingSquare(const std::vector<Square>& squares, std::vector<std::vector<Square>>& rowSets)
{
    for (const auto& originalSquare : squares) {
        for (int r = 0; r < 4; r++) {
            // Vytvoření kopi abych neměnil rotaci čtverce ve squares
            Square firstSquare = originalSquare;
            firstSquare.rotate(r);
            
            std::vector<Square> row;
            row.push_back(firstSquare);
            searchRows(squares, row, rowSets);
        }
    }
}

// Funkce na vyhledání řádků ppo 3
void searchRows(const std::vector<Square>& squares, std::vector<Square> row, std::vector<std::vector<Square>>& rowSets)
{
    // Pokud už máme řadu o 3 čtvercích, uložíme ho a končíme
    if (row.size() == 3) {
        // uložit řádek do setu
        rowSets.push_back(row);
        return;
    }

    const Square& lastSquare = row.back();

    // Přídání dalšího čtverce, otočit 4x 
    for (const auto& newSquare : squares) {
        // Zkontroluj zda není tento čtverec už v řadě
        if (rowContainsSquare(row, newSquare)) {
            continue; // přeskoč pokud ano
        }

        // 
        for (int i = 0; i < 4; i++) {
            // Vytvoříme kopii čtverce a otočíme i-Times
            Square rotatedSquare = newSquare;
            rotatedSquare.rotate(i);

            // Kontrola smileyFace v posledním čtverci s novým čtvercem
            if (matchEmoji(lastSquare, rotatedSquare)) {
                // Pokud sedí, vytvoříme newRow a pokračujeme rekurzí
                auto newRow = row;
                newRow.push_back(rotatedSquare);

                searchRows(squares, newRow, rowSets);
            }
        }
    }
}

//Kontrola jestli není čtverec už v řadě
bool rowContainsSquare(const std::vector<Square>& squares, const Square& newSquare){
    std::unordered_set<int> startPositions;
    // Uložení všech startPosition do setu 
    for (const auto& square : squares){
        startPositions.insert(square.getStartingPosition());
    }
    // Kontrola oproti nové pozici
    for (const int& position : startPositions){
        if (newSquare.getStartingPosition() == position){
            return true;
        }
    }
    return false;
}

// Vytisknutí řady s hodnotou otočení čtverců
void printRow(const std::vector<Square>& row)
{
    for (auto &sq : row) {
        std::cout << "square_"<< sq.getStartingPosition() 
                  << "(rotated by=" << sq.getRotation() << ") ";
    }
    std::cout << "\n";
}


//---------------------------------------------------------
// Vyhledávání kombinacá řádků pod sebe
//---------------------------------------------------------

//Kontrola zda se neopakují řádky v matici
bool noOverlap(const std::vector<Square>& firstRow, const std::vector<Square>& secondRow, const std::vector<Square>& thirdRow)
{
    std::unordered_set<int> used;
    for (auto &sq : firstRow) used.insert(sq.getStartingPosition());
    for (auto &sq : secondRow) used.insert(sq.getStartingPosition());
    for (auto &sq : thirdRow) used.insert(sq.getStartingPosition());

    // Musí být 9 unikátních
    return (used.size() == 9);
}

// Kontrola SmileyFace (up-down) pro 3 čtverce v řadě - stejná logika jak matchingEmoji()
bool matchingEmojiRows(const std::vector<Square>& topSquare, const std::vector<Square>& bottomSquare)
{
    for (int i = 0; i < 3; i++) {
        int down = topSquare[i].getDown();
        int up   = bottomSquare[i].getUp();

        if (up % 2 != 0) {
            // pokud je up liché, chceme down == up + 1
            if (down != up + 1) {
                return false;  // jakmile narazíme na neshodu, vrátíme false
            }
        } else {
            // pokud je up sudé, chceme down == up - 1
            if (down != up - 1) {
                return false;
            }
        }
    }
    // Pokud jsou všechny 3 ok vracíme true
    return true;
}


// Funkce na otočení řady o 180°
std::vector<Square> flipRow(const std::vector<Square>& chain)
{
    std::vector<Square> solution;

    for (auto& sq : chain) {
        Square copy = sq;
        // otočení o 180°
        copy.rotate(2);
        
        solution.push_back(copy);
    }
    return solution;
}

void findThreeRowStack(const std::vector<std::vector<Square>>& rowSets)
{
    for (size_t i = 0; i < rowSets.size(); i++) {
        // i-řada a jeho 180° varianta
        auto firstRow = rowSets[i];
        auto firstRowFlipped = flipRow(rowSets[i]);

        for (size_t j = 0; j < rowSets.size(); j++) {
            auto secondRow = rowSets[j];
            auto secondRowFlipped = flipRow(rowSets[j]);

            for (size_t k = 0; k < rowSets.size(); k++) {
                auto thirdRow = rowSets[k];
                auto thirdRowFlipped
                 = flipRow(rowSets[k]);

                // 8 možných kombinací
                // firstRow, secondRow, thirdRow
                if (matchingEmojiRows(firstRow, secondRow) && matchingEmojiRows(secondRow, thirdRow) && noOverlap(firstRow, secondRow, thirdRow)) {
                    std::cout << "Found the solution:\n";
                    printRow(firstRow); printRow(secondRow); printRow(thirdRow);
                    return;
                }
                // firstRow, secondRow, thirdRowFlipped

                if (matchingEmojiRows(firstRow, secondRow) && matchingEmojiRows(secondRow, thirdRowFlipped
                ) && noOverlap(firstRow, secondRow, thirdRowFlipped
                )) {
                    std::cout << "Found the solution:\n";
                    printRow(firstRow); printRow(secondRow); printRow(thirdRowFlipped
                    );
                    return;
                }
                // firstRow, secondRowFlipped, thirdRow
                if (matchingEmojiRows(firstRow, secondRowFlipped) && matchingEmojiRows(secondRowFlipped, thirdRow) && noOverlap(firstRow, secondRowFlipped, thirdRow)) {
                    std::cout << "Found the solution:\n";
                    printRow(firstRow); printRow(secondRowFlipped); printRow(thirdRow);
                    return;
                }
                // firstRow, secondRowFlipped, thirdRowFlipped

                if (matchingEmojiRows(firstRow, secondRowFlipped) && matchingEmojiRows(secondRowFlipped, thirdRowFlipped
                ) && noOverlap(firstRow, secondRowFlipped, thirdRowFlipped
                )) {
                    std::cout << "Found the solution:\n";
                    printRow(firstRow); printRow(secondRowFlipped); printRow(thirdRowFlipped
                    );
                    return;
                }
                // firstRowFlipped, secondRow, thirdRow
                if (matchingEmojiRows(firstRowFlipped, secondRow) && matchingEmojiRows(secondRow, thirdRow) && noOverlap(firstRowFlipped, secondRow, thirdRow)) {
                    std::cout << "Found the solution:\n";
                    printRow(firstRowFlipped); printRow(secondRow); printRow(thirdRow);
                    return;
                }
                // firstRowFlipped, secondRow, thirdRowFlipped

                if (matchingEmojiRows(firstRowFlipped, secondRow) && matchingEmojiRows(secondRow, thirdRowFlipped
                ) && noOverlap(firstRowFlipped, secondRow, thirdRowFlipped
                )) {
                    std::cout << "Found the solution:\n";
                    printRow(firstRowFlipped); printRow(secondRow); printRow(thirdRowFlipped
                    );
                    return;
                }
                // firstRowFlipped, secondRowFlipped, thirdRow
                if (matchingEmojiRows(firstRowFlipped, secondRowFlipped) && matchingEmojiRows(secondRowFlipped, thirdRow) && noOverlap(firstRowFlipped, secondRowFlipped, thirdRow)) {
                    std::cout << "Found the solution:\n";
                    printRow(firstRowFlipped); printRow(secondRowFlipped); printRow(thirdRow);
                    return;
                }
                // firstRowFlipped, secondRowFlipped, thirdRowFlipped

                if (matchingEmojiRows(firstRowFlipped, secondRowFlipped) && matchingEmojiRows(secondRowFlipped, thirdRowFlipped
                ) && noOverlap(firstRowFlipped, secondRowFlipped, thirdRowFlipped
                )) {
                    std::cout << "Found the solution:\n";
                    printRow(firstRowFlipped); printRow(secondRowFlipped); printRow(thirdRowFlipped
                    );
                    return;
                }

            }
        }
    }

    std::cout << "No solution was found!\n";
}

//-----------------------------------------------------
int main()
{
    // Inicializace objektů
    // Smajlící jsou  přepsány pomocí int - Popsáno v komentáři na začátku souboru
    std::vector<Square> squares = {
        {1, 4, 8, 3, 1},
        {2, 5, 7, 6, 2},
        {3, 3, 7, 6, 8},
        {4, 4, 5, 2, 4},
        {5, 5, 1, 4, 8},
        {6, 6, 8, 3, 1},
        {7, 6, 2, 7, 5},
        {8, 5, 4, 6, 7},
        {9, 7, 4, 8, 7}
    };

    // Seznam všech možných řádků
    std::vector<std::vector<Square>> rowSets;
    getStartingSquare(squares, rowSets);

    std::cout << "Looking for all posible row combination: " << "\n";
    std::cout << "Found posible row combinations (" << rowSets.size() << " total):\n";
    for (const auto& ch : rowSets) {
        std::cout << "Row: ";
        printRow(ch);
    }
    std::cout << "__________________________________" << "\n";
    
    //Hledání kombinací řádků a jejich obrácené verzi o 180°
    findThreeRowStack(rowSets);
    
    std::cout << "\nStisknete Enter pro ukonceni programu..." << std::endl;
    std::cin.get();  // počká, dokud uživatel nestiskne Enter
    return 0;
}

