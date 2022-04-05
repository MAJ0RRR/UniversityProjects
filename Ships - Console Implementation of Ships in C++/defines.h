#pragma once
// Libraries
#include"stdio.h"
#include"string.h"
#include"stdlib.h"
// Defines

/* Board */
#define DEFAULT_ROWS_AMOUNT 21
#define DEFAULT_COLS_AMOUNT 10
/* Players */
#define DEFAULT_FLEET_SIZE 10
/* Ships */
#define SHIP_TYPES 4
#define DEFAULT_CAR_AMOUNT 1
#define DEFAULT_BAT_AMOUNT 2
#define DEFAULT_CRU_AMOUNT 3
#define DEFAULT_DES_AMOUNT 4
#define CAR_SIZE 5
#define BAT_SIZE 4
#define CRU_SIZE 3
#define DES_SIZE 2
/* Input */
#define MAX_TAG_SIZE 10
#define MAX_LINE_LENGTH 128
#define MAX_WORD_LENGTH 32
/* ERROR CODES */
#define NOT_IN_STARTING_POSITION -1
#define SHIP_ALREDY_PRESENT -2
#define ALL_SHIPS_OF_THE_CLASS_ALREDY_SET -3
#define FIELD_DOES_NOT_EXIST -4
#define NOT_ALL_SHIPS_PLACED -5
#define THE_OTHER_PLAYER_EXPECTED -6

// Enums

enum class Direction {
	NORTH,
	EAST,
	SOUTH,
	WEST,
	NONE
};

// Data structures

struct Ship {
	Direction dir = Direction::NONE;
	int head_x = -1;
	int head_y = -1;
	int size = 0;
	int hit_points = 0;
	bool placed = false;
	char type[4];
};

struct Field {
	char glyph = ' ';
	bool empty = true;
    bool destroyed = false;
    Ship* occupied_by = nullptr;
};

typedef struct NODE {
    Ship* value;
    NODE* next;
}node_t;

class List {
private:
    int length;
    NODE* head;
public:
    List() {
        head = new NODE();
        this->length = 0;
    };
    void push_back(Ship* ship) {
        if (length == 0) {
            NODE* node = new NODE();
            node->value = ship;
            this->head = node;
            this->head->next = nullptr;
        }
        else {
            NODE* node = new NODE();
            NODE* tmp;
            tmp = head;
            while (tmp->next != nullptr) {
                tmp = tmp->next;
            }
            node->value = ship;
            tmp->next = node;
        }
        this->length++;
    }

    int sum() {
        if (length == 0) {
            return 0;
        }
        else {
            int sum = 0;
            NODE* tmp;
            tmp = this->head;
            while (tmp != nullptr) {
                sum += tmp->value->hit_points;
                tmp = tmp->next;
            }
            return sum;
        }
    }

    bool is_on_board(Ship* ship) {
        if (length == 0) {
            return false;
        }
        else {
            NODE* tmp;
            tmp = this->head;
            while (tmp != nullptr) {
                if (tmp->value == ship) {
                    return true;
                }
                tmp = tmp->next;
            }
        }
        return false;
    }

    int getLength() const { return this->length; }
    ~List() {};
};

