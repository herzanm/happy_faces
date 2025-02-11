#include "Square.hpp"

// Konstruktor
Square::Square(int startPos, int upVal, int rightVal, int downVal, int leftVal)
    : startingPosition(startPos),
      up(upVal), left(leftVal), down(downVal), right(rightVal),
      rotated(0)
{
}

int Square::getUp() const {
    return up;
}

int Square::getLeft() const {
    return left;
}

int Square::getDown() const {
    return down;
}

int Square::getRight() const {
    return right;
}

int Square::getStartingPosition() const {
    return startingPosition;
}

int Square::getRotation() const {
    return rotated;
}

// Otočení n-times o 90°
void Square::rotate(int nTimes) {
    
    int temp = 0;
    for (int i = 0; i < nTimes; i++){
        temp = up;
        up = left;
        left = down;
        down = right;
        right = temp;
        
        rotated = (rotated + 90) % 360;
    }
}
