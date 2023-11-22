#include <iostream>
#include <fstream>
#include <ctime>
#include <string>
#include "Board.h"

int main(const int argc, const char*argv[]) {
  //Get the input file first
  std::string file;
  if (argc == 1) {
    file = "default.txt";
  } else if (argc >= 2) {
    file = argv[1];
  }
  std::ifstream File{file};
  file = "";
  std::string s;
  while(getline(File,s)) {
    file += s;
  }

  if (argc >= 3) {
    srand(std::stoi(argv[2]));
  } else {
    srand(time(NULL));
  }

  //Create Board
  Board board(file);
  
  if (argc >= 4) {
    int whichF = std::stoi(argv[3]);
    board.changefloor(whichF-1);
  }

  board.updateView();
  std::cout << board;
  
  //Taking commands
  std::string com;
  std::cout << "Please enter your command: ";
  while(std::cin >> com) {
    // Moving
    if (com == "no") {
      if (board.playerMove(Direction::N)) {
	std::cout << "Congratulation! You Win! Your Score is: " << board.getScore() << std::endl;
	board.restart();
      } 
      board.updateView();
    } else if (com == "so") {
      if (board.playerMove(Direction::S)) {
	std::cout << "Congratulation! You Win! Your Score is: " << board.getScore() << std::endl; 
	board.restart();
      }
      board.updateView();
    } else if (com == "ea") {
      if (board.playerMove(Direction::E)) {
	std::cout << "Congratulation! You Win! Your Score is: " << board.getScore() << std::endl;
        board.restart();
      } 
      board.updateView();
    } else if (com == "we") {
      if (board.playerMove(Direction::W)) {
	std::cout << "Congratulation! You Win! Your Score is: " << board.getScore() << std::endl;
	board.restart();
      }
      board.updateView();
    } else if (com == "ne") {
      if (board.playerMove(Direction::NE)) {
	std::cout << "Congratulation! You Win! Your Score is: " << board.getScore() << std::endl;
	board.restart();
      }
      board.updateView();
    } else if (com == "nw") {
      if (board.playerMove(Direction::NW)) {
	std::cout << "Congratulation! You Win! Your Score is: " << board.getScore() << std::endl;
        board.restart();
      }
      board.updateView();
    } else if (com == "se") {
      if (board.playerMove(Direction::SE)) {
	std::cout << "Congratulation! You Win! Your Score is: " << board.getScore() << std::endl;
        board.restart();
      }
      board.updateView();
    } else if (com == "sw") {
      if (board.playerMove(Direction::SW)) {
	std::cout << "Congratulation! You Win! Your Score is: " << board.getScore() << std::endl;
        board.restart();
      }
      board.updateView();
    }
    // Using
    else if (com == "u<no>") {
      board.playerUse(Direction::N);
      board.updateView();
    } else if (com == "u<so>") {
      board.playerUse(Direction::S);
      board.updateView();
    } else if (com == "u<ea>") {
      board.playerUse(Direction::E);
      board.updateView();
    } else if (com == "u<we>") {
      board.playerUse(Direction::W);
      board.updateView();
    } else if (com == "u<ne>") {
      board.playerUse(Direction::NE);
      board.updateView();
    } else if (com == "u<nw>") {
      board.playerUse(Direction::NW);
      board.updateView();
    } else if (com == "u<se>") {
      board.playerUse(Direction::SE);
      board.updateView();
    } else if (com == "u<sw>") {
      board.playerUse(Direction::SW);
      board.updateView();
    }
    // Attacking
    else if (com == "a<no>") {
      board.playerAttack(Direction::N);
      board.updateView();
    } else if (com == "a<so>") {
      board.playerAttack(Direction::S);
      board.updateView();
    } else if (com == "a<ea>") {
      board.playerAttack(Direction::E);
      board.updateView();
    } else if (com == "a<we>") {
      board.playerAttack(Direction::W);
      board.updateView();
    } else if (com == "a<ne>") {
      board.playerAttack(Direction::NE);
      board.updateView();
    } else if (com == "a<nw>") {
      board.playerAttack(Direction::NW);
      board.updateView();
    } else if (com == "a<se>") {
      board.playerAttack(Direction::SE);
      board.updateView();
    } else if (com == "a<sw>") {
      board.playerAttack(Direction::SW);
      board.updateView();
    } else if (com == "r") {
      board.restart();
      board.updateView();
      std::cout << board;
      std::cout << "Please enter your command: ";
      continue;
    } else if (com == "q") {
      std::cout << "Game Over" << std::endl;
      break;
    } else {
      std::cout << "Invalid Command" << std::endl;
      std::cout << "Please enter your command: ";
      continue;
    }

    //enemy move
    if (board.RandomAct()) {
      std::cout << "You die! Your Score is: " << board.getScore() << std::endl;
      board.restart();
    }

    std::cout << board;
    std::cout << "Please enter your command: ";
  }
}
