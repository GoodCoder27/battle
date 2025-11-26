#include "table.h"
#include <cstdlib>
#include <iostream>

void Table::init() {
  srand(time(0));
  int current = 0;
  int coordinate = 0;
  gameOver = false;

  while (current < 5) {
    if (placeComputerShips(current, coordinate) == true) {
      coordinate += ship_sizes[current];
      current++;
    }
  }
  /* print a 10x10 computer grid
  for (int i = 0; i < 10; i++) {
    std::cout << letters[i] << ' ';
    for (int j = 0; j < 10; j++) {
      std::cout << computerGrid[i][j] << ' ';
    }
    std::cout << '\n';
  }
  // print where the points are
  for (int i = 0; i < 17; ++i) {
    std::cout << "Point " << i << ": (" << computerCoordinates[i].x << ", "
              << computerCoordinates[i].y << "), "
              << computerCoordinates[i].shot << "\n";
  }
  */
}

bool Table::placeComputerShips(int current, int coordinate) noexcept {
  int random_x = (rand() % 10);
  int random_y = (rand() % 10);
  int direction = (rand() % 4) + 1;

  int dir = direction - 1;
  for (int j = 0; j < ship_sizes[current]; ++j) {
    int nx = random_x + dx[dir] * j;
    int ny = random_y + dy[dir] * j;

    if (nx < 0 || nx >= 10 || ny < 0 || ny >= 10 || computerGrid[nx][ny] == '=')
      return false;
  }
  for (int i = 0; i < ship_sizes[current]; i++) {
    switch (direction) {
    case 1:
      computerGrid[random_x][random_y + i] = '=';
      computerCoordinates[coordinate + i] = {random_x, random_y + i};
      break;
    case 2:
      computerGrid[random_x][random_y - i] = '=';
      computerCoordinates[coordinate + i] = {random_x, random_y - i};
      break;
    case 3:
      computerGrid[random_x + i][random_y] = '=';
      computerCoordinates[coordinate + i] = {random_x + i, random_y};
      break;
    case 4:
      computerGrid[random_x - i][random_y] = '=';
      computerCoordinates[coordinate + i] = {random_x - i, random_y};
      break;
    }
  }
  return true;
}

void Table::printGrid() {
  int a = 0;
  int b = 0;
  // Print a 10x10 grid
  std::cout << "  0 1 2 3 4 5 6 7 8 9" << spacing << "  0 1 2 3 4 5 6 7 8 9\n";
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      a++;
      if (a == 1)
        std::cout << letters[i];
      if (a < 10)
        std::cout << ' ' << selfGrid[i][j];
      if (a == 10) {
        a = 0;
        std::cout << ' ' << selfGrid[i][j] << spacing << letters[i];

        for (int p = 0; p < 10; p++) {
          std::cout << ' ' << attackGrid[b][p];
        }
        std::cout << "\n";
        b++;
      }
    }
  }
}

// TODO: create rules like if a ship collides with another one
void Table::placeShips() {
  std::cout << "Place Ships\n1.Write a Cordinate(e.g., A0)\n2.Write a "
               "direction(u, d, r, l)\n";
  char y;
  int x;
  char z;
  int current_ship = 0;
  int coordinate = 0;

  while (current_ship < 5) {
    std::cout << "Coordinates for " << ship_sizes[current_ship]
              << "-slot ship: ";
    std::cin >> y >> x >> z;

    if (checkAndPrint(y, x, z, current_ship, coordinate) == true) {
      coordinate += ship_sizes[current_ship];
      current_ship++;
    } else {
      std::cout << "Try again please: ";
    }
  }
  printGrid();
}

bool Table::checkAndPrint(char y, int x, char z, int current,
                          int coordinate) noexcept {
  int dir = getDir(z) - 1;
  int y_val = getNumber(y);

  for (int j = 0; j < ship_sizes[current]; ++j) {
    int nx = y_val + dx[dir] * j;
    int ny = x + dy[dir] * j;

    if (nx < 0 || nx >= 10 || ny < 0 || ny >= 10 || selfGrid[nx][ny] == '=')
      return false;
  }
  for (int i = 0; i < ship_sizes[current]; i++) {
    int nx = y_val + dx[dir] * i;
    int ny = x + dy[dir] * i;

    selfGrid[nx][ny] = '=';
    playerCoordinates[coordinate + i] = {nx, ny};
  }
  return true;
}

void Table::shoot() {
  char letter;
  int x, y;

  std::cout << "Coordinate to shoot: ";
  std::cin >> letter >> y;

  x = getNumber(letter);

  if (computerGrid[x][y] == ' ') {
    attackGrid[x][y] = 'X';
  } else if (computerGrid[x][y] == '=') {
    int index = findIndex(computerCoordinates, x, y);
    computerCoordinates[index].shot = true;
    Range range = findGroup(index);
    if (shipSunk(computerCoordinates, range)) {
      for (int i = range.x; i <= range.y; i++) {
        int x_val = computerCoordinates[i].x;
        int y_val = computerCoordinates[i].y;
        attackGrid[x_val][y_val] = '*';
      }
      printGrid();
      std::cout << "Ship sunk, ";
      shoot();
    } else {
      attackGrid[x][y] = '+';
      printGrid();
      std::cout << "Good shot, ";
      shoot();
    }
  } else if (attackGrid[x][y] == 'X' || attackGrid[x][y] == '+' ||
             attackGrid[x][y] == '*') {
    std::cout << "Try again(coordinate been shot already)\n";
    shoot();
  }
  if (allShot(computerCoordinates)) {
    std::cout << "\n\n########################################";
    std::cout << "\n#              Player won              #";
    std::cout << "\n########################################\n\n\n";
    gameOver = true;
  }
}

void Table::computerShoot() {
  int x = (rand() % 10);
  int y = (rand() % 10);

  if (selfGrid[x][y] == ' ') {
    selfGrid[x][y] = 'X';
  } else if (selfGrid[x][y] == '=') {
    int index = findIndex(playerCoordinates, x, y);
    playerCoordinates[index].shot = true;
    Range range = findGroup(index);
    if (shipSunk(playerCoordinates, range)) {
      for (int i = range.x; i <= range.y; i++) {
        int x_val = playerCoordinates[i].x;
        int y_val = playerCoordinates[i].y;
        selfGrid[x_val][y_val] = '*';
      }
      std::cout << "Computer shot: " << letters[x] << y << "\n";
      computerShoot();
    } else {
      selfGrid[x][y] = '+';
      std::cout << "Computer shot: " << letters[x] << y << "\n";
      computerShoot();
    }
  } else if (selfGrid[x][y] == 'X' || selfGrid[x][y] == '+' ||
             selfGrid[x][y] == '*') {
    computerShoot();
  }
  if (allShot(playerCoordinates)) {
    std::cout << "\n\n########################################";
    std::cout << "\n#              Computer won              #";
    std::cout << "\n########################################\n\n\n";
    gameOver = true;
  }
  printGrid();
}

bool Table::allShot(Coordinates points[]) noexcept {
  for (int i = 0; i < 17; ++i) {
    if (!points[i].shot)
      return false;
  }
  return true;
}

bool Table::shipSunk(Coordinates points[], Range range) noexcept {
  for (int i = range.x; i <= range.y; i++) {
    if (!points[i].shot) {
      return false;
    }
  }
  return true;
}
