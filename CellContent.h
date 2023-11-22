#ifndef _CELL_CONTENT_H
#define _CELL_CONTENT_H

#include <vector>
#include <string>

enum class ActionType {PlayerMove, PlayerATK, PlayerUse, EnemyAct, Protect};

class Cell;
class Player;
class Enemy;
class DragonH;

class CellContent {
public:
	// tells the CellContent to act based on type. from will be the Cell
	// the CellContent is in.
	// In case of Player's action, to will be the cell this action is
	// directed towards. For example, if the player is attacking the
	// East Cell, to will be the East Cell and type will be PlayerATK
	// In case of other action, to will be the neighbors of from
	virtual void act(ActionType type);

	// DragonH will call this to find a dragon as a protector
	virtual void findDragon(DragonH *dragonH);

	// do any neccessary changes when the CellContent goes to the next turn
	virtual void newTurn();

	// provides the character representation of this CellContent
        virtual std::string getDisplay() const = 0;

	virtual ~CellContent() = 0;

	// called by the attacker when this CellContent is being attacked
	virtual void attacked(CellContent &attacker);

	// called by the attacked CellContent. This way you know what type
	// you are attacking.
	virtual void attacksOn(Player &player);
	virtual void attacksOn(Enemy &enemy);

	// called when this CellContent is being used by the Player
	virtual void usedBy(Player &player);

	// called when Player wants to know if they can move into the
	// Cell containing this CellContentt.
	// The CellContent will update things inside player appropriately
	virtual bool canMoveOn(Player &player);

	//link the curr to the cell
	virtual	void LinkCurr(Cell *);

	//update the info of the cellcontent to cell
	virtual void updateinfo();
 
 protected:
	Cell *curr;
};

#endif
