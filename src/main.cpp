#include "table.h"

int main() {
  Table playerTable;
  playerTable.init();
  playerTable.printGrid();
  playerTable.placeShips();
  while (playerTable.gameOver == false) {
    playerTable.shoot();
    playerTable.computerShoot();
  }

  return 0;
}
