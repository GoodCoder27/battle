#ifndef TABLE
#define TABLE

#include <string>
class Table {
private:
  char selfGrid[10][10] = {
      {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
      {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
      {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
      {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
      {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
      {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
      {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
      {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
      {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
      {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
  };
  char attackGrid[10][10] = {
      {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
      {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
      {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
      {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
      {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
      {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
      {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
      {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
      {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
      {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},

  };
  char computerGrid[10][10] = {
      {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
      {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
      {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
      {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
      {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
      {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
      {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
      {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
      {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
      {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},

  };
  const int dx[4] = {0, 0, 1, -1}; // right, left, down, up
  const int dy[4] = {1, -1, 0, 0};
  const int ship_sizes[5] = {5, 4, 3, 3, 2};
  const char letters[10] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J'};
  const std::string spacing = "          ";

  int getNumber(char letter) {
    switch (letter) {
    case 'A':
      return 0;
    case 'B':
      return 1;
    case 'C':
      return 2;
    case 'D':
      return 3;
    case 'E':
      return 4;
    case 'F':
      return 5;
    case 'G':
      return 6;
    case 'H':
      return 7;
    case 'I':
      return 8;
    case 'J':
      return 9;
    default:
      return -1;
    }
  }
  int getDir(char dir) {
    switch (dir) {
    case 'r':
      return 1;
    case 'l':
      return 2;
    case 'd':
      return 3;
    case 'u':
      return 4;
    default:
      return -1;
    }
  }
  bool checkAndPrint(char y, int x, char z, int current,
                     int coordinate) noexcept;
  bool placeComputerShips(int current, int coordinate) noexcept;
  // A simple array that with ship coordinates
  // there is a total of 5+4+3+3+2=17 coordinates
  // two grids, one for player's coordinates
  // one for computer coordinates
  struct Coordinates {
    int x;
    int y;
    bool shot;
  };
  struct Range {
    int x, y;
  };
  Coordinates playerCoordinates[17];
  Coordinates computerCoordinates[17];
  bool allShot(Coordinates points[]) noexcept;
  bool shipSunk(Coordinates points[], Range range) noexcept;
  int findIndex(Coordinates points[], int targetX, int targetY) {
    int size = 17;
    for (int i = 0; i < size; ++i) {
      if (points[i].x == targetX && points[i].y == targetY) {
        return i;
      }
    }
    return -1; // not found
  }
  Range findGroup(int index) {
    if (index <= 4 && index >= 0)
      return {0, 4};
    if (index <= 8 && index >= 5)
      return {5, 8};
    if (index <= 11 && index >= 9)
      return {9, 11};
    if (index <= 14 && index >= 12)
      return {12, 14};
    if (index <= 16 && index >= 15)
      return {15, 16};
    return {-1, -1};
  }

public:
  void printGrid();
  void init();
  void placeShips();
  void shoot();
  void computerShoot();
  bool gameOver = false;
};

#endif // !TABLE
