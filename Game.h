#ifndef GAME_H_
#define GAME_H_


#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <map>

using std::string;
using namespace std;

class Player; // forward declaration so that Object can refer to Player

// ------------------ Object and its subclasses -------------------

class Object {
public:



    // Default constructor, just to make this release version compilable.
   
    // Constructor, specifying the name and the value of an object.
    Object(string name, int value);

    // Destructor
    virtual ~Object();

    // Return the name of the object.
    string getName() const;

    // Return the value of the object.
    int getValue() const;

    // Return a string giving details of the object, as specified in
    // the assignment webpage.
    virtual string print() const;

    string objectName;
    int objectValue;
private:
    // Use this object.
    
    virtual void use() = 0;
    friend class Player;
protected:
    // You probably want to have something like this.
    // For technical reason it may be easier to just use a raw pointer
    Player* owner_;


    // TODO: add any other protected/private member variables

// Overloaded output stream redirection operator, printing the object to the
// given output stream
    friend std::ostream& operator<<(std::ostream& os, const Object& o);

// You can "friend" other classes

};

class Food final : public Object {
public:
    // Constructor
    Food(string name, int value);

    // Destructor
    ~Food();

    // Add any member functions if needed
    string print() const override;
private:
    // Add any member variables if needed

    void use();
};

class Weapon final : public Object {
public:
    // Constructor
    Weapon(string name, int value);

    // Destructor
    ~Weapon();

    // Add any member functions if needed
    string print() const override;
private:
    // Add any member variables if needed
    void use();
};

class Armour final : public Object {
public:
    // Constructor
    Armour(string name, int value);

    // Destructor
    ~Armour();

    // Add any member functions if needed
    string print() const override;
private:
    // Add any member variables if needed
    void use();
};

// ----------------- Player and its subclasses --------------------

class Player {
public:
    // Default constructor, just to make this release version compilable.

    // Constructor, specifying the name of the player
    // Set the health and stamina both to 100
    Player(string name);



    // Destructor
    ~Player();

    // Return the name of the player
    string getName() const;

    // Setter and Getter for health
    int getHealth() const;
    void setHealth(int newHealth);

    //Setting for weapon and armour
    void setWeapon(string newWepName);
    void insertArmour(string armourName);

    // Setter and Getter for stamina
    int getStamina() const;
    void setStamina(int newStamina);

    // Add the object pointed to by the unique pointer to the
    // inventory of objects this player carries.
    // As this is a unique pointer, it has to be "moved" into this
    // function using std::move().
    void pickup(std::unique_ptr<Object> obj);

    // Return a string listing all objects this player owns, in
    // the format specified in the assignment page
    string getInventory() const;

    // Return a string that contains all details of a player, as
    // specified in the assignment page
    virtual string print() const;

    // Use the object with the given name. If the player does not
    // own any object of this name, return false and do nothing,
    // otherwise return true.
    bool use(string name);
    map<string, int> plrArmour;
    vector<std::unique_ptr<Object>> plrInvVec;
    string plrWeapon;
    string plrType;
    int plrStamina;
private:


protected:
    // TODO: add any protected or private member variables


    int getAttackStrength();
    int getDefendStrength();

    string plrName;

    int plrHealth;
// Overloaded stream redirection operator, that prints the contents of
// the player to the given output stream
    friend std::ostream& operator<<(std::ostream& os, const Player& p);





};

class Fighter : public Player {
public:
    // Constructor
    Fighter(string name);

    // Destructor
    ~Fighter();

    // Attack the specified player, following the rules in the
    // assignment page
    bool attack(Player& other);

   
    string print() const override;
private:
  

};

class Healer : public Player {
public:
    // Constructor
    Healer(string name);

    // Destructor
    ~Healer();

    // Heal the specified player, following the rules in the
    // assignment page
    bool heal(Player& other);

    string print() const override;
private:


};

#endif /* GAME_H_ */