# mattybtraphouse
COP3503 Spring 2018 Semester Project
Game Design


https://github.com/user-attachments/assets/adfc6d31-b0c9-42e6-bc7a-1f958e170ca4


Items: 
Red Health Potion +Full Health (15% spawn chance)
Blue Speed Boost Potion +50% Speed +50% Attackspeed for 20 seconds (10% spawn chance)
Green Stamina Potion +Unlimited Stamina for 20 seconds (10% spawn chance)
Yellow Attack Potion +50% Damage for 20 seconds (8% spawn chance)
White Time Potion -50% enemy Walkspeed and Attackspeed for 20 seconds (7% spawn chance)

Weapons:
Rarities:
Default - D
Uncommon - U
Rare - R
Epic - E

*SPS -Swings per second*

Default Knife - D
-25 HP per hit
Attack Range: 2 Nodes
-1/2 SPS

Sword - R 
-60 HP per hit
Attack Range: 5 Nodes
1/5 SPS
5% spawn chance


Default Pistol (M1911) - D
Unlimited Ammo
10 Ammo per clip
-10 HP per shot 
Penetration: 1 enemy
1 second reload time

Heavy Pistol (Desert Eagle) - U
35 Ammo
7 Ammo per clip 
-50 HP per shot
Penetration: 2 enemies
2 second reload time
=======
15% Spawn Chance

Bolt Action Sniper Rifle (L96A1) - E
15 Ammo 
5 Ammo per clip 
-100 HP per shot 
+1 second bolt time 
Penetration: 5 enemies
=======
2% Spawn Chance

Semi Auto Rifle (M14) - R
60 Ammo
10 Ammo per clip
 -20 HP per shot 
Penetration: 2 enemies
2 second reload time
=======
5% spawn chance

Pump Action Shotgun (KSG) - R
30 Ammo
 6 Ammo per clip
-20 HP per shot
Shoots out 12 projectiles at a certain angle from each other in a 30 degree cone 
Penetration: Each pellet, 1 enemy
0.25 second reload time for each shell

Assault Rifle (AK47) - E
=======
4% spawn chance
90 Ammo
30 Ammo per clip
-30 HP per shot
Penetration: 2 enemies
2 second reload time

Machine Gun (Minigun) - E
=======
4% spawn chance
180 Ammo
60 Ammo per clip
 -20 HP per shot 
Penetration: 2 enemies
5 second reload time

=======
2% spawn chance
Semi Auto Sniper Rifle (Barrett .50 Cal) - E
30 Ammo
10 Ammo per clip
-80 HP per shot
Penetration: 4 enemies
4 second reload time
2% spawn chance

Submachine gun (MP40) - U
96 Ammo
32 ammo per clip
-20 HP per shot
Penetration: 1 enemy
2 seconds reload time
10% Spawn Chance


Monsters
Skeleton -
-5 HP per attack
35 speed
30 HP
60% spawn chance
Spider - 
webShot(); shoots web that -50% speed when player is in the range
Bite(); -3 HP per attack
50 speed
15 HP
30% spawn chance
Ogre - 
Hammer();
-25 HP per attack
10 speed
100 HP
10% spawn chance
Demon - 
-35 HP per fireball hit
-50 HP per smash
30 Speed
500 HP
1 spawns in boss room
//Progression (as the levels progress you see more of these, stats are better but sprites are different)
//Skeleton -> Zombie -> Voidwalker
//Black widow -> Huntsman  -> Tarantula (bigger)
//Giant-> Cyclops-> Ogre-> Scherik the Orc (Easter Egg)
//Demon starts showing up mid game.

****************MileStone*******************
Milestone #2
Group 37 -- Suman Adari, John Thurber, Edward Goodman, Chimeziri Mbionwu, Kayton Fletcher, Matthew Baumaister, Bricson Linares 

Definition (20%):
The system is a top down shooter video game called “Traphouse.” 
The game takes in input from the user and displays various on-screen elements that correlate with the user’s choices. This includes moving, shooting, and interacting with objects.
The system will be written so that, on certain key events from the user, it will respond on screen with the desired choices -- moving, shooting, or interaction.The system will also create its own “enemies” that, when shot, increase the player’s score. It will also create random levels for the player to progress through, keeping the game unique and interesting for the player.
The game is designed just for the entertainment of the player.
The game will be easy enough to be played by people of all ages, so we have a wide audience.

Analysis (30%) 
What should be the inputs? 
1. Inputs: what data will be input into the program by one or more “actors”?

Enemy position
Enemy health
Mouse position
Keyboard input
Left/Right mouse clicks
Score
User health
User ammo
User stamina
Camera position
Map seeds
Inventory
Player Buffs
Game time loop

– What commands will be available?
Left Click
Right Click
WASD 
Q, E,F,R,Left Shift, Space
Esc

– What will be the format for each type of data?

Player name (for high scores): string
Level: int
Score: int
Ammo: int
Health: int
Stamina: int
Movement speed: double
Positions: SFML coordinates (from external graphics library)
Inventory/Buffs: Array
Time: SFML time (from external graphics lib)


What should be the outputs?

2. Outputs: what data will our program generate that will be needed by one or more “actors”?

The time the program has been running.
The location of the player based on the map. 
The location of the enemies.
The location of weapon particles and other objects that cause damage.


– How will data be output?

The spawn room and minimap will be generated first onto the screen. Game data like mob health will not be shown. Other data, such as ammunition count, or player health, will be displayed graphically on the screen. The player would be shown as a sprite. Mouse position will be shown to assist with aiming, and movement will be shown as the player’s sprite moving through the room. Enemy spawning will also be output on the screen in addition to bullet/attack animations.

– Are there different ways it may potentially need to be output?
UI such as weapon ammunition and game score will be output to the screen constantly while other elements such as menu screen will be displayed dynamically.

Different window resolutions (you can make it as big or as little as you want, within reason)
Dungeon rendering
 

What are the flow/logic required for the proposed system?

The game will run in a while loop, only exiting when the “exit game” button in the escape menu is pressed.


3. Constraints: we’ve previously noted that sometimes objects should have limitations imposed on them “artificially,” in order to model what they represent in the real world more accurately.
-Might there be analogous system-level constraints which should be enforced?

Movement speed will be modeled after real human movement, but sped up a bit to keep the game from being boring. The same goes for stamina and health.

Monsters will have varying degrees of handicaps, since different monsters will go at different speeds, have different attack power, and have different health.

4. Assumptions: Are we operating under any sort of assumptions?

We are assuming the game will work on any compiler and that the user won’t try to break it or use outside applications to affect the pieces of the game itself (like cheat programs).

5. Modifications: Whenever an object within the program is modified, will any corresponding changes be expected elsewhere within the system?
Adding a new element into a data structure (typically) may not automatically add it into corresponding structures of the user interface.

In the case of mobs, no. All mobs are independent objects and won’t all die if one dies. However, once a mob is killed, the score is affected. 
In the case of the player dying, then the game will have to end the current level. This means every object in simulation is affected. 
The inventory will change if the user picks up a new item. The same goes for player stats if a potion is used.

6. Relationships/Effects: How are system-level modifications related to system constraints?

System level modifications such as window size and frame rate are directly related to your system’s resolution and processing power, which will be scalable in out program based off of system specs.


Design (30%) 

How many modules are required?
Graphics
Audio
System
Window

What are the classes and methods for each module/component?
Graphics
Player class
Getter/setters for player struct(speed, health, attack, position, name)
Update (for position)
Enemy Class
Getter/setters for enemy struct (speed, health, attack, position)
Update (for position)
Map Class
Map generator
Game Manager
Game data module (collection of user data and game data)
Graphics module (renders sprites and map)
Pickup Class
Items child class
Mutators for player variables
Weapons child class
Audio Module -- It will handle the sound portion of the game. For example, gunshots, mob sounds, footsteps, etc. will be handled by the audio module. 
Audio
Audio::playSound(string name)
Background music / ambient noises

What are the shared classes/methods across all modules?
Player class, enemy class, classes for each individual mob created, game manager class

Execution Plan (20%):

What is the best way to divide the coding tasks?

There will be one student working on the graphics. This involves creating sprites, weapons, the map, and animations for each. 
Another student will work alongside him, helping to implement the graphics into the program properly. 
One student will deal with audio implementation for the different game actions and help to debug existing code.
Two students will work on the core game code, including map generation, key events for the user, and “actor” classes for the enemies and player. 
The final two students will develop the AI for the enemies and  


What will the makefile look like?
The Makefile will include targets/dependencies/actions for each of the following cpp files (and their respective header files): Player, Enemy, Map, GameManager, Chest, Pickup, Health Potion, Speed Potion, Time Potion, Attack Potion, Stamina Potion, and Weapon.

Your own planned deadlines to carry out the implementation/testing on each module:

March 20: Final planning for project structure

March 22:: Get coding outline for project, including classes and methods.

March 29: Finish map generation for the program

April 5: Finish most classes and methods for game “actors” (getters, setters, other functionality)

April 9: Have sprites completed for game

April 12: Complete game menu 

April 15: Get sprites integrated into game code

April 17: Audio implemented into game

April 20: Get enemy AI completed. 

April 22: Finish final debugging and finishing touches on game.

April 23rd: Project Due


UML 
Player
---------------------
- int hp;
- int attack;
- double walkspeed;
- string name;
- Sprite player;
- Texture texture;
- Pickup inventory[];

-----------------------------
+ Player();
+ void setName(std::string);
+ void setHp(int);
+ void setAttack(int);
+ void setWalkspeed(double);
+ std::string getName();
+ int getLevel();
+ int getWalkspeed();
+ int getHp();
+ int getAttack();
+ Sprite getPlayer();
+ void Update(double);
+ ~Player();

Enemy
----------------------
- int hp;
- double walkspeed;
- double spawnChance();
- int attack;
- Sprite sprite;
-----------------------
+ void setWalkspeed(int);
+ int getWalkspeed();
+ int getHp();
+ int getAttack();
+ Sprite getEnemy();
+ void Update(double);
+ ~Enemy();

Map
------------------
-RectangleShape map[];
-Texture texture;
--------------------------------
+ Map();
+ void Generate();
+ ~Map();

GameManager
------------------------
+ GameManager();
+ void Start();
+ void Pause();
+ ~GameManager();





---------------------------

Chest 
-------------------------
- double spawnChance;
- Vector2f spawnLocation;
- Sprite sprite;
- Texture texture;
----------------------------
+ vector<Pickup> Open();

Pickup
-------------------------
- double spawnChance;

Health Potion:Pickup
----------------------------
- Sprite potion;A
- Texture texture;
--------------------------
+ void Heal();

Speed Potion
------------------------
- Sprite potion;
- Texture texture;
---------------------------
+ void boostSpeed();

Time Potion
-------------------------
- Sprite potion;
- Texture texture;
--------------------------
+ void slowTime();

Attack Potion
--------------------------
- Sprite potion;
- Texture texture;
---------------------------
+ void boostAttack();

Stamina Potion
---------------------------
- Sprite potion;
- Texture texture;
---------------------------
+ void increaseStamina();

Weapon
-----------------------
- string name;
- int damage;
- double attackSpeed;
- int ammo;
- Sprite sprite;
- Texture texture;
------------------------------
+ void setAmmo(int);
+ int getAmmo();
+ double getAttackSpeed();
+ void setAttackSpeed(int);

Pistol:Weapon
-----------------------
+ void Shoot();

Shotgun:Weapon
-----------------------
+ void Shoot();

Sniper:Weapon
-----------------------
+ void Shoot();

Subby:Weapon
-----------------------
+ void Shoot();


Skeleton:Enemy
----------------------
+void boneThrow();
+void boneWhack();

Spider:Enemy
----------------------
+void webShot();
+void Bite();

Giant:Enemy
---------------------------
+ void Hammer();

Demon:Enemy
-----------------------
+ void Fireball();
+ void groundSmash();


**********************Pseudocode**********************************
~enumeration for sprinting, walking , idle
~while true check each enumeration status and loop corresponding audio clip
~break loop when enumeration is idle
~if state changes (sprinting->walking), play current audio for extra half second, but start new state audio clip
~if state changes to idle cut sound immediately
