#ifndef SQUARE_HPP
#define SQUARE_HPP

class Square
{
public:
    Square(int startPos, int upVal, int rightVal, int downVal, int leftVal);

    int getUp() const;
    int getLeft() const;
    int getDown() const;
    int getRight() const;
    int getStartingPosition() const;
    int getRotation() const;
    void rotate(int nTimes);

private:
    int startingPosition;
    // int currentPosition;
    
    // Jednotlive poloviny smajliku pomoci int
    int up, down, left, right;
    int rotated;
};

#endif
