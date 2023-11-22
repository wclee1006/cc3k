#ifndef __INFO__H
#define __INFO__H
#include <string>

enum class CellType {Nothing, VerWall, HorWall, Passageway, Door, Floor};
enum class Direction {NW, N, NE, W, E, SW, S, SE};

class Info {
 public:
  int x;
  int y;
  CellType celltype;
  std::string cellContent; // "" if there is nothing
                           // Potion is P, Player is @, Tresure is G, basically
                           // the character of the textdisplay
};
  
#endif
