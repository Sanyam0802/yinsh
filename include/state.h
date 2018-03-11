/**
 * @file state.h
 * Function declarations for Yinsh's game state
 */
#ifndef STATE_STATE_H
#define STATE_STATE_H

#include <vector>
#include <utility>

namespace state {

struct Point {
	int x;
	int y;
};

enum Element {
	I, E, B_RING, W_RING, B_MARKER, W_MARKER
};

typedef std::pair<int,int> Dir;
const Dir N_Dir  = std::make_pair(-2, 0),
          NE_Dir = std::make_pair(-1, 1),
          SE_Dir = std::make_pair(1, 1),
          S_Dir  = std::make_pair(2, 0),
          SW_Dir = std::make_pair(1, -1),
          NW_Dir = std::make_pair(-1, -1);

/**
 * Game board for the simulation
 */
class Board {
public:
	std::vector<std::vector<Element> > current_board = 
	{
		{I, I, I, I, E, I, E, I, I, I, I},
		{I, I, I, E, I, E, I, E, I, I, I},
		{I, I, E, I, E, I, E, I, E, I, I},
		{I, E, I, E, I, E, I, E, I, E, I},
		{I, I, E, I, E, I, E, I, E, I, I},
		{I, E, I, E, I, E, I, E, I, E, I},
		{E, I, E, I, E, I, E, I, E, I, E},
		{I, E, I, E, I, E, I, E, I, E, I},
		{E, I, E, I, E, I, E, I, E, I, E},
		{I, E, I, E, I, E, I, E, I, E, I},
		{E, I, E, I, E, I, E, I, E, I, E},
		{I, E, I, E, I, E, I, E, I, E, I},
		{E, I, E, I, E, I, E, I, E, I, E},
		{I, E, I, E, I, E, I, E, I, E, I},
		{I, I, E, I, E, I, E, I, E, I, I},
		{I, E, I, E, I, E, I, E, I, E, I},
		{I, I, E, I, E, I, E, I, E, I, I},
		{I, I, I, E, I, E, I, E, I, I, I},
		{I, I, I, I, E, I, E, I, I, I, I}
	};
	
	/**
	 * @brief      Determines if valid board position
	 *
	 * @param[in]  x     x coordinate
	 * @param[in]  y     y coordinate
	 *
	 * @return     True if valid position, False otherwise.
	 */
	bool IsValid(int x, int y);
	
	/**
	 * @brief      Gets the element at given position
	 *
	 * @param[in]  x     x coordinate
	 * @param[in]  y     y coordinate
	 *
	 * @return     Type of element at given position
	 */
	Element GetElementAt(int x, int y);
	
	/**
	 * @brief      Adds an element at given position
	 *
	 * @param[in]  p     position to add at
	 * @param[in]  e     type of element to be added
	 *
	 * @return     True if successful, False if invalid board position
	 */
	bool AddElementAt(Point p, Element e);
	
	/**
	 * @brief      Removes an element at given position
	 *
	 * @param[in]  p    position to remove at 
	 *
	 * @return     True if successful, False if invalid board position
	 */
	bool RemoveElementAt(Point p);
	
	/**
	 * @brief      Move element from a position to another
	 *
	 * @param[in]  from  source position
	 * @param[in]  to    destination position
	 *
	 * @return     True if successful, False if invalid board position
	 */
	bool MoveElement(Point from, Point to);
	
	/**
	 * @brief      Flips marker type
	 *
	 * @param[in]  p     flipping start position
	 * @param[in]  q     flipping end position
	 *
	 * @return     True if successful, False if any point is an invalid board position
	 */
	bool FlipMarkers(Point p, Point q, Dir dir);
};

class GameState {
	int playerAScore, playerBScore;
	int currentPlayer;
/*	TurnMode turnMode;*/
	Board board;
public:

	/**
	 * @brief      Adds ring at given position (if move valid).
	 *
	 * @param[in]  ring_pos  Position to place ring
	 *
	 * @return     returns false if move invalid (no rings left, illegal
	 *             position or out of board)
	 */
	bool AddRing(Point ring_pos);

	/**
	 * @brief      Moves ring from point A to point B (if move valid).
	 *
	 * @param[in]  ring_pos		Ring's position
	 * @param[in]  ring_dest 	Ring's destination
	 *
	 * @return     returns false if move invalid (illegal
	 *             position or out of board)
	 */
	bool MoveRing(Point ring_pos, Point ring_dest);

	/**
	 * @brief      Removes a row of markers from Point A to Point B (if move
	 *             valid)
	 *
	 * @param[in]  row_start  Start of row
	 * @param[in]  row_end    End of row
	 * @param[in]  dir        The dir
	 * @param[in]  ring_pos   Position of ring to remove
	 *
	 * @return     returns false if row greater than 5, points doesn't form row,
	 *             if valid row not formed or invalid ring position
	 */
	bool RemoveRowAndRing(Point row_start, Point row_end, Dir dir, Point ring_pos);

	/**
	 * @brief      Returns valid moves in each direction
	 *
	 * @param[in]  ring_pos  Starting position of ring
	 *
	 * @return     Returns vector of pairs (int, point) for each direction
	 * 			   0: Blocked by a set of markers followed by ring or just a ring, Point: Opposing ring position
	 * 			   1: Not immediately blocked by a marker, Point: Last valid position
	 * 			   2: Blocked by only a set of markers, Point: First position after markers
	 */
	std::vector<std::pair<int, Point> > ValidMoves(Point ring_pos);

	/**
	 * @brief      Returns all valid points in given direction 
	 *
	 * @param[in]  ring_pos  The ring position
	 * @param[in]  dir       The direction
	 *
	 * @return     Returns a vector of all points in given direction
	 */
	std::vector<Point> ValidPoints(Point ring_pos, Dir dir);

	/**
	 * @brief      Returns all rows formed for player
	 *
	 * @param[in]  player_id  Player ID
	 *
	 * @return     Returns vector of pairs(start, end) for all rows
	 */
	std::vector<std::pair<Point, Point> > RowsFormed(int player_id);

	/**
	 * @brief      Undo's the given action from the board
	 *
	 * @param[in]  board   The board
	 * @param[in]  action  The action can be either of 3 things: 
	 * 					   1. Place ring
	 * 					   2. Place marker and move ring
	 * 					   3. Remove row and ring
	 *
	 * @return     returns board's configuration after undo is performed
	 */
	/*Board UndoAction(Board board, Action action);*/
};

}

#endif //STATE_STATE_H