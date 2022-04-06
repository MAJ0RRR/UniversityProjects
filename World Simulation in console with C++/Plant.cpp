#pragma warning (disable: 26812 )
#include"Plant.h"

Point Plant::Action() {
	this->Effect();
	return coordinates;
}
action Plant::Collision(Organism* attacker,Organism* defender) {
	/* Plants don't move so their only collision is defend */
	return Defend(attacker);
}
action Plant::Defend(Organism* attacker) {
	/* Default defend for Plant*/
	return NO_DEFENCE;
}

action Plant::Effect(){
/* Perform special action for plant, default none */
	return NONE;
}

void Plant::Reproduce(Organism* partner) {

}