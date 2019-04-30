# CONSTRUCTOR  

Made by Mo-Talha and [https://github.com/alibagher]alibagher for CS246 Final Project.

Number of players: 4  
Players: 0 for Blue, 1 for Red, 2 for Orange, 3 for Yellow  
Turn order: Blue, Red, Orange, Yellow  
Motive: Be the first player that gets 10 building points  

## Game Components  

### Board  
Number of tiles: 19  
Each tile represents a hexagon, adjacent to up to 6 other tiles  
Each tile represents a type of resource  
Types of resources: Brick, Energy, Glass, Heat, Wifi, Park  
A tile with gesse does not give any resources  

#### Addresses  
Each tile is surrounded by addresses  
Addresses are located: Top, middle and bottom left and right corner  

Buildings can be placed on addresses  
Types of buildings:  
Basement (B):  
Costs 1 Brick, 1 Energy, 1 Glass, 1 Wifi  
Gives 1 resource when value of adjacent tile is rolled  
Gives 1 building point  

House (H):  
Upgraded from Basement  
Costs 2 Glass, 3 Heat  
Gives 2 resources when value of adjacent tile is rolled  
Gives 2 building points  

Tower (T):  
Upgraded from House  
Costs 3 Brick, 2 Energy, 2 Glass, 1 Wifi, 2 Heat  
Gives 3 resources when value of adjacent tile is rolled  
Gives 3 building points  

Syntax for something built at address:  
Ex. |YB| for Yellow basement. Similarily, |YH|, |YT|  

#### Paths  
Each tile is also surrounded by paths  
Paths are located: between addresses  

Roads can be built on paths  
Roads can only be built if adjacent road or residence has been built  

### Question: How can roads be adjacent to each other? 

Costs 1 Heat, 1 Wifi  

Syntax for road built at path:  
Ex. |YR| for Yellow Road.  

#### Dice  
Two types of dice: fair and loaded dice  
Each player has its own dice  

Fair dice:  
Two dice produce a random value between 2-12  
Any builder with residence on a tile with same value gets resource allocated  
Note: Can use observer pattern to do this. When a tile value is rolled, that tile should  
notify its addresses (observers)  

Load dice:  
Allows builder to enter value of roll  
Print:  
Input a roll between 2 and 12:  

If error:  
Invalid roll.  

Priority: Fair dice  

### Game rules  

Residences cannot be places adjacent to each other  
Residences must be connected by roads
### Question: does it matter who's road it is?

Roads can be built if they are adjacent to an address or another road  

### Command Line Inputs
"-seed xxx" sets the random number generator’s seed to xxx
"-load xxx" loads the game saved in file xxx
### loading a file should be a priority while implementation!!
"-board xxx" loads the game with the board specified in the file xxx instead of using random generation
"-random-board" starts a game with a randomly generated board -- this is ignored if the game is being loaded.

Note: - We can assume that the files given are all the same format as described.
      - Given in any order

#### Note  
Always print resources in the order of:  
Brick, Energy, Glass, Heat, Wifi  

#### Status  
Print:  
\<colour> has \<numPoints> building points, \<numBrick> brick, \<numEnergy> energy,
\<numGlass> glass, \<numHeat> heat, and \<numWiFi> WiFi.

#### Buildings
Print:  
\<colour> has built:  
\<address> \<buildingType>  
..  
\<address> \<buildingType>  

Note: \<buildType>:= {B, H, T}  

#### Using resources  
If not enough resources:  
Print:  
You do not have enough resources.  

#### Gaining resources  
Rules of distribution of resources through dice roll is the same as Catan.

Print:  
Builder \<colour> gained:  
\<numResource> \<resourceType>  
..  
\<numResource> \<resourceType>  

If a roll occurs and no builders gain any resources:  
Print:  
No builders gained resources.  

#### Trading
\<colour1> offers \<colour2> one \<resource1> for one \<resource2>.  
Does \<colour2> accept this offer?  

if yes, reduce and increase the given resources for each player(colour).

#### Tile generation  
By default, a file called layout.txt provides board layout  
CL Option to load from different file: -board xxx  

Syntax:  
0 for Brick, 1 for Energy, 2 for Glass, 3 for Heat, 4 for Wifi, 5 for Park  
Digit (0-5) followed by the resource value  
Always printed & read in the order of board layout (see sample board, top left->right)  

Ex. 0 3 1 10 3 5 1 4 5 7 3 10 2 11 1 3 3 8 0 2 0 6 1 8 4 12 1 5 4 11 3 4 4 6 3 9 3 9  
Brick with value 3, Energy with value 10, Heat with value 5,..  
Note: Park has no value in board but is followed by 7 just because  

CL Option to generate random board: -random-board  
Note: If also provided with -load xxx, ignore generating random board  

On random generation, board consists of following resources:  
3 Wifi, 3 Heat, 4 Brick, 4 Energy, 4 Glass, 1 Park  

Random distribution:  
One tile with value 2  
Two tiles with value 3-6  
Two tiles with value 8-11  
One tile with value 12  

### Question: What about the other tiles? Randomly distribute between 3-11?

#### Gesse  
If builder rolls a 7, they get to move geese anywhere 
Also, any builders with 10 or more resources lose half of their resources (round down)  
This includes the builder who rolled the 7  

### Question: Confirm this rule (losing resources to gesse) applies to the builder who rolled the 7 as well  
answer: yes; quoted: "Any builder with 10 or more resources will lose half of their resources (rounded down) to the geese."
                      ^^^

Print:  
Builder \<colour> loses \<numResourcesLost> resources to the geese. They lose:  
\<numResource> \<resourceName>  
..  
\<numResource> \<resourceName>  

Active builder who rolled 7:  
Print:  
Choose where to place the GEESE.  

Builder must respond with any tile value other than where gesse is already placed  

Once the gesse moves to a different tile, if there are any other residences in that
area belonging to other builders and those builders have a non-zero number of resources,
active builder gets to steal one of their resources

Print:  
Builder \<colour1> can choose to steal from [builders].  

Note: [builders]:=Red, Blue,..  

Choose a builder to steal from.  

Builder responds with color of builder they want to steal from.  
One resource is stolen based on following probability:  
The probability of stealing each type of resource is the number of the resource the builder 
being stolen from has, divided by the total number of resources the builder being stolen from has

Note: This means that resources that someone has a lot of or resources that someone doesn't have a lot of
have a higher probability of receiving those resources

After stolen:  
Print:  
Builder \<colour1> steals \<resource> from builder \<colour2>.  

If no builders to steal from:  
Print:  
Builder \<colour1> has no builders to steal from.  

Once geese is moved to a new tile, the bottom middle part of tile says the words
"GEESE"

#### Saving the game  
Note: This is a top-priority feature  

When game is saved, the following is printed to a file  

\<curTurn>  
\<builder0Data>  
\<builder1Data>  
\<builder2Data>  
\<builder3Data>  
\<board>  

Syntax for builder data:  
\<numBricks> \<numEnergies> \<numGlass> \<numHeat> \<numWifi> r \<roads> h \<housing>  

Ex. 1 2 1 2 3 r 16 36 19 h 10 B 15 T 27 H  

Note: 'r' is follwed by a list of paths that have roads on them.  
'h' is followed by pairs of addresses that have residences on them plus the builder who owns it  
### I believe that after 'h', its pairs of addresses that the the current builder owns, followed by the type of residence, Eg. basement is B

Syntax for board data:  
As listed above  in "tile generation"

## Gameplay  

### Beginning of game  
Each builder chooses where to place two basements  
Turn order: Blue, Red, Orange, Yellow, Yellow, Orange, Red, Blue  

Print:  
Builder \<colour>, where do you want to build a basement?  

Note: Usually, during the game, builder is not allowed to place residences without
roads connecting them. This rule does not apply during the beginning of the game  

### Beginning of turn  
Print:  
Builder \<colour>’s turn.  

CL Commands:  
load: sets to use loaded dice  
fair: sets to use fair dice  
roll: rolls the current builder’s dice  

### During the turn  
A builder can input any of the following:  

CL Commads:  
board: prints the board  
status: prints status of all builders in order from builder 0 to 3  
residences: prints the residences of the current builder  
build-road \<road#>  
build-res \<housing#>  
improve \<housing#>: improves the residence at \<housing#>  
trade \<colour> \<give> \<take>: Attempt to tade with builder \<color> offering \<give> 
and demanding \<take>  
save \<file>  

help: Prints the following:  
Print:  
Valid commands:  
board  
status  
residences  
build-road \<path#>  
build-res \<housing#>  
improve \<housing#>  
trade \<colour> \<give> \<take>  
next  
save \<file>  
help  

### End of game  
Print:  
Would you like to play again?  
If 'yes', starts from beginning. Otherwise quit  
### Question: Do we not output who won?

### Important notes about invalid user input  
Whenever program is waiting for input:  
Print:  
'> '  

Ex. Enter a number  
>  

If user attempts to build something at an invalid location:  
Print:  
You cannot build here.  

If user attempts to build something they do not have enough resources of:  
Print:  
You do not have enough resources.  

If user enters invalid command:  
Print:  
Invalid command.  

If program receives EOF signal, end with no winner and saves the current game to file:  
backup.sv   
