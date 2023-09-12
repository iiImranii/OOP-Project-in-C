
## Practice on OOP with C++

A simple RPG game with different classes for objects, players, and character types.
Each class have their own abilities depending on the game class they are playing with.

## Playing around with game ( Attacking an enemy )

1. Create your class: Fighter player1("Arkov");
2. Add your enemy players in the game using player constructor: e.g. Player player2("Enemy Player");
3. With your fighter player you can now access his attack moving using: bool attackSuccess = player1.attack(anotherPlayer);
4. If the attack was successful the enemy player's health should have reduced, you can check using: 
int enemyHealth = enemyPlayer.getHealth();
std::cout << "Enemy player's health: " << enemyHealth << std::endl;

