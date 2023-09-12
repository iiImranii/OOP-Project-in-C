#include "Game.h"
#include <vector>
#include <map>
#include <algorithm>

// -------------------- Object class ----------------------



Object::Object(string name, int value) {
    objectName = name;
    owner_= nullptr;
    if (value < 0) {
        throw std::invalid_argument("Negative number not allowed");
    } else {
        objectValue = value;
    }


}

Object::~Object() {}

string Object::getName() const {
    return objectName; // dummy
}

int Object::getValue() const {
    return objectValue; // dummy
}

string Object::print() const {
    return "XXX, name: YYY, value: ZZZ"; // dummy
}

void Object::use() {

}

std::ostream& operator<<(std::ostream& os, const Object& o) {
    os << o.print();
    return os;
}



// ------------------- Food class ----------------------

Food::Food(string name, int value) : Object(name, value) {

}

Food::~Food() {}

void Food::use() {
    // IMPLEMENT ME
    //Setting stamina and looping through inventory to find this object and erase from vector
   owner_->setStamina(std::min(this->getValue()+this->owner_->getStamina(),100));
    for (auto it = owner_->plrInvVec.begin(); it != owner_->plrInvVec.end(); ++it) {
        if ((*it)!= nullptr && (*it)->getName()==this->objectName) {
            if ((*it)->getName()==this->objectName) {
                owner_->plrInvVec.erase(it);
                break;
            }
        }
    }

}

string Food::print() const {
    string str =  "Food, ";
    str += "name: " + this->getName() +  ", value: " + std::to_string(this->getValue());
    return str;
}
// ------------------- Weapon class ----------------------

Weapon::Weapon(string name, int value) : Object(name, value) {


}

Weapon::~Weapon() {}

void Weapon::use() {
    this->owner_->setWeapon(this->getName());
}

string Weapon::print() const {
    string str =  "Weapon, ";
    str += "name: " + this->getName() +  ", value: " + std::to_string(this->getValue());
    return str;
}

// ------------------- Armour class ----------------------

Armour::Armour(string name, int value) : Object(name, value) {

}

Armour::~Armour() {}

void Armour::use() {
    //Adds armour object to the players current armour
    this->owner_->insertArmour(this->getName());

}

string Armour::print() const {
    string str =  "Armour, ";
    str += "name: " + this->getName() +  ", value: " + std::to_string(this->getValue());
    return str;
}

// ------------------- Player class ----------------------


Player::Player(string name) {
    plrName = name;
    plrStamina = 100;
    plrHealth = 100;
    plrWeapon = "none";
}

Player::~Player() {}

string Player::getName() const {
    //Getter for player name
    return plrName; // dummy
}

int Player::getHealth() const {
    //Getter for players health
    return plrHealth; // dummy
}

void Player::setHealth(int newHealth) {
    //Setter for players health
    this->plrHealth = newHealth;

}

void Player::setWeapon(string newWepName) {
    //Setters for player weapon
    this->plrWeapon = newWepName;
}

void Player::insertArmour(string armourName) {
    //Inserts armour into object player taking the armour name as key.
    this->plrArmour.insert(make_pair(armourName, this->plrArmour.size()));
}

int Player::getStamina() const {
    //Getter for player stamina
    return plrStamina; // dummy
}

void Player::setStamina(int newStamina) {
    //Setter for player stamina
    this->plrStamina = newStamina;
}


void Player::pickup(std::unique_ptr<Object> o) {
    if (this->plrHealth <= 0) {
        throw std::logic_error("Player is already dead");
    } else {
        //Player is not dead
        o->owner_ = this;
        this->plrInvVec.push_back(std::move(o));
    }
}

string Player::getInventory() const {
    string str = "";
    //Checking if size of inventory is greater than 0
    if (this->plrInvVec.size()<= 0) {
        str = "List of items: none";
    } else {
        str = "List of items:\n";
            for (auto & obj : this->plrInvVec) {
                if (this->plrInvVec.back() == obj) {
                    str += " "+obj->print();
                } else {
                    str += +" "+obj->print()+"\n";
                }
            }
    }
    return str;
}

string Player::print() const {
    return ""; // dummy
}

bool Player::use(string name) {
    bool exitStatus = false;
    bool found = false;

    //Checking player is not dead and loop through inventory use their use method
   if (this->plrHealth > 0  ) {
       for (auto it = plrInvVec.begin(); it != plrInvVec.end(); ++it) {
            if ((*it)!= nullptr && (*it)->getName()==name) {
                exitStatus=true;
                (*it)->use();
                break;
            }
       }
    } else if(this->plrHealth <=0) {
        throw std::logic_error("Player is already dead");
    }
    return exitStatus; // dummy
}

std::ostream& operator<<(std::ostream& os, const Player& p) {
    os << p.print();
    return os;
}

// ------------------- Fighter class ----------------------

Fighter::Fighter(string name) : Player(name) {
    //Player type is initialized here
    plrType = "Fighter";
}

Fighter::~Fighter() {}

string Fighter::print() const {
    string str = "Name: "+this->getName()+"\n"+"Type: "+this->plrType+"\n"+
                 "Health: "+std::to_string(this->getHealth())+"\n" +"Stamina: " +
                 std::to_string(this->getStamina())+"\n" + getInventory()+"\n";

    str += "Weapon in use: "+plrWeapon+"\n";
    str+="Armour in use: ";
    if (this->plrArmour.empty()) {
        str+="none";
    } else {
        for (auto it = this->plrArmour.rbegin(); it!= this->plrArmour.rend(); ++it) {
            if (it==prev(this->plrArmour.rend())) {
                str += (*it).first;
                break;
            } else {
                str += (*it).first+", ";
            }
        }

    }
    return str;
}



bool Fighter::attack(Player& other) {
    bool exitStatus = false;
    if (this->getHealth() <=0 || other.getHealth() <=0 ) {
        if (other.getHealth() <= 0) {
            throw std::logic_error("Stop! "+other.getName()+" is already dead.");
        }
        if (this->getHealth()<=0) {
            throw std::logic_error("Stop! Attacker is already dead");
        }
    } else if (this->getStamina() < 10) {
        exitStatus = false;
    } else {
        this->plrStamina=std::max(this->getStamina()-10,0);
        int playerAAttackStrength = 10;
        int playerBDefenseStrength = 0;


        for (auto & obj : this->plrInvVec) {
            if (this->plrWeapon == obj->getName()) {
                playerAAttackStrength += obj->getValue();
            }
        }


        for (auto & obj : other.plrInvVec) {
            auto it = other.plrArmour.find(obj->getName());
            if (it!= other.plrArmour.end()) {
                playerBDefenseStrength += obj->getValue();
            }

        }

        //Checking strength greater than player 2 defense, if its the same then exitStatus will not change and health is not reduced
        if (playerAAttackStrength >playerBDefenseStrength) {
            other.setHealth(std::max(other.getHealth()-(playerAAttackStrength-playerBDefenseStrength),0));
            exitStatus = true;
        }
    }
    return exitStatus; // dummy

}



// ------------------- Healer class ----------------------
string Healer::print() const {
    string str = "Name: "+this->getName()+"\n"+"Type: "+this->plrType+"\n"+
                 "Health: "+std::to_string(this->getHealth())+"\n" +"Stamina: " +
                 std::to_string(this->getStamina())+"\n" + getInventory()+"\n";

    str+="Armour in use: ";
    if (this->plrArmour.empty()) {
        str+="none";
    } else {
        for (auto it = this->plrArmour.rbegin(); it!= this->plrArmour.rend(); ++it) {
            if (it==prev(this->plrArmour.rend())) {
                str += (*it).first;
                break;
            } else {
                str += (*it).first+", ";
            }
        }

    }
    return str;
}

Healer::Healer(string name) : Player(name) {
    plrType = "Healer";
}

Healer::~Healer() {}



bool Healer::heal(Player& other) {
    bool exitStatus = false;
    if (this->getHealth()>0 && other.getHealth()>0) {
        if (this->getStamina() >= 10 && other.getHealth()<100) {
            this->plrStamina=std::max(this->getStamina()-10,0);
            other.setHealth(std::min(other.getHealth()+20,100));
            exitStatus = true;
        } else if (this->getStamina()>=10 && other.getHealth()>=100) {
            this->plrStamina=std::max(this->getStamina()-10,0);
        }

    } else {
        throw std::logic_error("A or B is already dead.");
    }

    return exitStatus;
}


