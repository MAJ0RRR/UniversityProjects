#include"board.h"

Board::Board(): rows(DEFAULT_ROWS_AMOUNT),cols(DEFAULT_COLS_AMOUNT) {
	initBoard();
}

Board::Board(int rows_amount, int cols_amount) : rows(rows_amount), cols(cols_amount) {
	initBoard();
}

// Allocate memory for (rows x cols) board and fill it with empty fields
void Board::initBoard() {
    fields = new Field * [rows];
    for (int i = 0; i < rows; i++) fields[i] = new Field[cols];
}

// Check if ship of desired size will fit into the board
bool Board::validatePlacement(int min, int max, int x, int y, int dx, int dy, int size) {
    for (int i = 0; i < size; i++) {
        if (!(inBound(min, max, y + dy * i) && inBound(0, cols - 1, x + dx * i))) return false;
    }
    return true;
}

// Check if given value is between min and max
bool Board::inBound(int min, int max, int val) {
    return val <= max && val >= min;
}

// Translate type to index in player's fleet
int Board::typeToIdx(char* type) {
    if (!strcmp(type, "CAR")) return 0;
    else if (!strcmp(type, "BAT")) return 1;
    else if (!strcmp(type, "CRU")) return 2;
    else if (!strcmp(type, "DES")) return 3;
    else return -1; // Type was incorrect
}

// Translate char to direction
Direction Board::charToDir(char* c) {
    if (!strcmp(c, "N")) return Direction::NORTH;
    else if (!strcmp(c, "E")) return Direction::EAST;
    else if (!strcmp(c, "S")) return Direction::SOUTH;
    else if (!strcmp(c, "W")) return Direction::WEST;
    else return Direction::NONE;
}

// Translate Direction to delta in x and y directions
void Board::encodeDirection(int* dx, int* dy, Direction dir) {
    switch (dir) {
    case Direction::NORTH:
        *dx = 0;
        *dy = 1;
        break;
    case Direction::EAST:
        *dx = -1;
        *dy = 0;
        break;
    case Direction::SOUTH:
        *dx = 0;
        *dy = -1;
        break;
    case Direction::WEST:
        *dx = 1;
        *dy = 0;
        break;
    }
}

// Calculate minimal and maxmial row that given player can place their ships
void Board::calculateBounds(int* min, int* max, const char name) const {
    if (!strcmp(&name, "A")) {   // Player 1
        *min = 0;
        *max = rows / 2 - 1;
    }
    else {                      // Player 2
        *min = rows / 2 + 1;
        *max = rows - 1;
    }
}

// Assemble Ship of given type 
Ship Board::assembleShip(const char* type, int x, int y, Direction dir) {
    Ship ship;
    if (!strcmp(type, "CAR")) ship.size = CAR_SIZE;
    else if (!strcmp(type, "BAT")) ship.size = BAT_SIZE;
    else if (!strcmp(type, "CRU")) ship.size = CRU_SIZE;
    else if (!strcmp(type,"DES")) ship.size = DES_SIZE;

    ship.placed = false;
    ship.head_x = x;
    ship.head_y = y;
    ship.hit_points = ship.size;
    ship.dir = dir;
    strcpy_s(ship.type, type);
    return ship;
}

// Place ship from fleet at given (y,x) 
bool Board::placeShip(Ship* ship, int y, int x, Direction dir, char* ship_class, const char name,int* err_code) {
    int row_min, row_max;
    calculateBounds(&row_min, &row_max, name);
    if (inBound(row_min, row_max, y) && inBound(0, cols - 1, x)) { // Make sure that head of ship is in bounds
        int dx, dy;
        encodeDirection(&dx, &dy, dir);
        // Overwrite default info about ship
        *ship = assembleShip(ship_class, x, y, dir);
        if (validatePlacement(row_min, row_max, x, y, dx, dy, ship->size)) {
            for (int j = 0; j < ship->size; j++) {
                fields[y + dy * j][x + dx * j].empty = false;
                fields[y + dy * j][x + dx * j].glyph = '+';
            }
            return true; // Ship placemnet was succssful
        }
        else *err_code = NOT_IN_STARTING_POSITION; 
    }
    else *err_code = NOT_IN_STARTING_POSITION;
    return false; // Desired ship placement was incorrect
}

// Bound given ship to fields on board so they point to him
void Board::boundToField(Ship* ship,int x,int y) {
    int dx, dy;
    encodeDirection(&dx, &dy, ship->dir);
    for (int j = 0; j < ship->size; j++) {
        fields[y + dy * j][x + dx * j].occupied_by = ship;
    }
}

// Shoot at (y,x) by player 'name'
bool Board::shoot(int y, int x, int* err_code) {
    if (inBound(0, rows - 1, y) && inBound(0, cols - 1, x) && rows != 10) {
        if (fields[y][x].empty) {}   // Miss
        else if(!fields[y][x].empty && !fields[y][x].destroyed) { // Hit
            fields[y][x].glyph = 'x';
            fields[y][x].occupied_by->hit_points--;
            fields[y][x].destroyed = true;
        }
        return true;
    }
    *err_code = FIELD_DOES_NOT_EXIST;
    return false;
}

// Prints current state of the board
void Board::printBoard() {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%c", fields[i][j].glyph);
        }
        printf("\n");
    }
}

Board::~Board() {
    for (int i = 0; i < rows; i++) {
        delete[] fields[i];
    }
    delete[] fields;
}
