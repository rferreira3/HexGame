//Logic of the Hex game 

#include "HexGameLogic.h"
#include "disjointset.h"
#include <array>
#include <ctime>
#include <cstdlib> 
#include <vector>

bool edgeEnd(Player currentPlayer, int iteration, int position);
void setEndEdge(Player currentPlayer, std::vector<int>& edge1, std::vector<int>& edge2);
// Used to determine when a player has created a winning path
// on the Hex game board
static DisjointSet<NUM_CELLS> disjoint_set;

// The Hex board consists of a collection of NUM_CELLS Hex cells
// This array allows the game engine to access the cell objects
// in the program's presentation.
static std::array<HexCellInterface *, NUM_CELLS> cells;

// The constructor sets the blue player to start and ensures the
// the game status is "playing."  Note: You should not call the reset
// method in this constructor; the reset method attempts to clear the
// the players associated with each Hex cell, but Hex cells may be 
// added to the game board only after it has been created (see the
// Hex cell constructor in the GUI code).
HexGameLogic::HexGameLogic() {
	// Implement as needed (but add a constructor initialization
	// list to do it right!)
	srand((unsigned)time(NULL));
	player = Player::Blue;
	playing = true;

}

// If the current board configuration contains a winning path for
// a player, this function returns that player; otherwise, the 
// function returns Player::None if neither player has yet won.
Player HexGameLogic::check_for_win() { //change playing varble 
	//check for find on top or bottom for red 
	//check for find through left and right edge for blue 
	std::vector<int> edge1; //if blue left side or red bottom side
	std::vector<int> edge2; //if blue right side or red top side
	setEndEdge(player, edge1, edge2);
	for (int i = 0; i < edge1.size(); i++)
	{
		for (int j = 0; j < edge2.size(); j++)
		{
			if (disjoint_set.Find(edge1[i]) == disjoint_set.Find(edge2[j]))
			{

				playing = false;
				return player;

			}

		}
	}
	return Player::None;
}
void setEndEdge(Player currentPlayer, std::vector<int>& edge1, std::vector<int>& edge2)
{
	std::vector<int>* temp = &edge1;
	int startPosition = 0;
	int incriment;
	if (currentPlayer == Player::Blue)
		incriment = 11;
	else
		incriment = 1;
	for (int i = 0; i < 2; i++)
	{
		for (int j = startPosition; edgeEnd(currentPlayer, i, j); j += incriment)
		{
			temp->push_back(j);
		}
		temp = &edge2;
		if (currentPlayer == Player::Blue)
			startPosition = 10;
		else
			startPosition = 110;
	}
}

bool edgeEnd(Player currentPlayer, int iteration, int position)
{
	if (currentPlayer == Player::Blue)
	{
		if (iteration == 0)
		{
			return position >= 0 && position <= 110;
		}
		else
		{
			return position >= 10 && position <= 120;
		}
	}
	else
	{
		if (iteration == 0)
		{
			return position >= 0 && position <= 10;
		}
		else
		{
			return position >= 110 && position <= 120;
		}
	}
}
// Claims the Hex cell at the given index for the current player
// if the cell currently is unoccupied.  If the move is possible,
// and the move is not a winning move, the opposing player then 
// takes control of the next move.
void HexGameLogic::move(int index) {

	//check cell first
	if (cells[index]->get_player() == Player::None)
	{

		disjoint_set.Make_Set(index); //creating set 

		if (cells[index])
		{
			int x = index;
			int up_left = index + 11;
			int up_right = index + 12;
			int left = index - 1;
			int right = index + 1;
			int down_right = index - 11;
			int down_left = index - 12;

			cells[index]->set_player(player);
			//8 cases 4 on sides and 4 on corners 
			if (x == 110)
			{
				if (player == cells[right]->get_player())
				{
					disjoint_set.Union(x, right);
				}
				if (player == cells[down_right]->get_player())
				{
					disjoint_set.Union(x, down_right);
				}
			}

			else if (x == 120)
			{
				if (player == cells[left]->get_player())
				{
					disjoint_set.Union(x, left);
				}

				if (player == cells[down_right]->get_player())
				{
					disjoint_set.Union(x, down_right);
				}

				if (player == cells[down_left]->get_player())
				{
					disjoint_set.Union(x, down_left);
				}

			}

			else if (x == 0)
			{
				if (player == cells[right]->get_player())
				{
					disjoint_set.Union(x, right);
				}
				if (player == cells[up_left]->get_player())
				{
					disjoint_set.Union(x, up_left);
				}

				if (player == cells[up_right]->get_player())
				{
					disjoint_set.Union(x, up_right);
				}
			}
			else if (x == 10)
			{
				if (player == cells[left]->get_player())
				{
					disjoint_set.Union(x, left);
				}
				if (player == cells[up_left]->get_player())
				{
					disjoint_set.Union(x, up_left);
				}
			}
			else if (x > 109 && x != 110 && x != 120) //top 
			{
				if (player == cells[left]->get_player())
				{
					disjoint_set.Union(x, left);
				}

				if (player == cells[right]->get_player())
				{
					disjoint_set.Union(x, right);
				}
				if (player == cells[down_right]->get_player())
				{
					disjoint_set.Union(x, down_right);
				}
				if (player == cells[down_left]->get_player())
				{
					disjoint_set.Union(x, down_left);
				}
			}

			else if (x < 11 && x != 0 && x != 10) //bottom 
			{
				if (player == cells[up_left]->get_player())
				{
					disjoint_set.Union(x, up_left);
				}

				if (player == cells[up_right]->get_player())
				{
					disjoint_set.Union(x, up_right);
				}

				if (player == cells[left]->get_player())
				{
					disjoint_set.Union(x, left);
				}

				if (player == cells[right]->get_player())
				{
					disjoint_set.Union(x, right);
				}
			}

			else if (x % 11 == 0)//left
			{
				if (player == cells[up_left]->get_player())
				{
					disjoint_set.Union(x, up_left);
				}

				if (player == cells[up_right]->get_player())
				{
					disjoint_set.Union(x, up_right);
				}

				if (player == cells[right]->get_player())
				{
					disjoint_set.Union(x, right);
				}

			}

			else if ((x + 1) % 11 == 0)//right
			{
				if (player == cells[up_left]->get_player())
				{
					disjoint_set.Union(x, up_left);
				}

				if (player == cells[left]->get_player())
				{
					disjoint_set.Union(x, left);
				}

				if (player == cells[down_right]->get_player())
				{
					disjoint_set.Union(x, down_right);
				}
				if (player == cells[down_left]->get_player())
				{
					disjoint_set.Union(x, down_left);
				}
			}

			else
			{

				if (player == cells[up_left]->get_player())
				{
					disjoint_set.Union(x, up_left);
				}

				if (player == cells[up_right]->get_player())
				{
					disjoint_set.Union(x, up_right);
				}

				if (player == cells[left]->get_player())
				{
					disjoint_set.Union(x, left);
				}

				if (player == cells[right]->get_player())
				{
					disjoint_set.Union(x, right);
				}
				if (player == cells[down_right]->get_player())
				{
					disjoint_set.Union(x, down_right);
				}
				if (player == cells[down_left]->get_player())
				{
					disjoint_set.Union(x, down_left);
				}

			}
			check_for_win();
			if (playing)
			{
				if (player == Player::Blue)
				{
					player = Player::Red;
				}
				else
				{
					player = Player::Blue;
				}
			}

			//switch player 

		}
	}

	// Add your code
	//connect to disjoint union/find would determine winner 
	//can change player global variable and check for win 
}

// Positions the current player at an open cell pseudorandomly
// chosen on the Hex game board
void HexGameLogic::random_move() {

	
	//int random_index = rand() % NUM_CELLS;
	//move(random_index);
	//cells[random_index]->move();
	random_move(1);
	

}

// Makes upto n pseudorandom moves during a Hex game. 
// Makes fewer than n moves if a move results in a game
// winnner.
void HexGameLogic::random_move(int n) {
	srand(time(NULL));
	int numOfValidMoves = 0;
	bool move = true;
	while (move)
	{
		int random_index = rand() % NUM_CELLS;
		
		if (cells[random_index]->get_player() == Player::None)
		{
			cells[random_index]->move();
			numOfValidMoves++;
		}
		move = (numOfValidMoves < n) && playing;

	}
	
}

// Adds a Hex cell with index idx to the Hex board.
// Also adds it to the disjoint set used to detect a 
// game winner.
void HexGameLogic::add_cell(int idx, HexCellInterface *cell) {
	cells[idx] = cell; //Dr. Halterman 
	//disjoint_set.Make_Set(idx);
	//add more for disjoint 
}

// Returns the player (Player::Blue or Player::Red) whose 
// turn it is
Player HexGameLogic::current_player() const {

	return player;

}

// Returns true if a player has won the game; otherwise, the
// game is still in progress, and the method returns false
bool HexGameLogic::game_over() const {
	if (playing == false)
	{
		return true;
	}
	else
	{
		return false;
	}

}

// Resets the Hex board to begin a new game:
//  - The opening move should be the blue player's
//  - All the associated Hex cells (in the GUI) should
//    be empty (have no associated player)
//  - All the sets in the disjoint set should have cardinality one
//  - The game's status should be "playing"
void HexGameLogic::reset() {
	srand((unsigned)time(NULL));
	player = Player::Blue;
	playing = true;
	for (int i = 0; i < NUM_CELLS; i++)
	{
		cells[i]->set_player(Player::None);
	}
	disjoint_set.split();

}




