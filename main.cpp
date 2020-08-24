#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>

using namespace std;

// Function prototypes
int initialRoom(bool);
int treasureRoom(int, int, bool, bool);
int dragonRoom(int, int, bool, bool);


int main()
{
   /*    Initial room (playerPosition 1): has an exit door which is locked and needs key
    *    Treasure room (playerPosition 2): contains 2 chests, one trapped, one with key (randomly)
    *    Dragon room (playerPosition 3): contains a dragon, can be asked for key, he asks user to answer a riddle.
    *    Exit (playerPosition 0): the player exited the dungeon - ends the game
    */

    int silverChest;
    int goldenChest;
    int scenario;
    int outcome;
    bool playerHasKey = false;
    bool playerSolvedRiddle = false;
    int playerPosition = 1;
    string playerAnswer;

    // Initializing Chests (key=1, poison=0)
    srand(time(0));
    silverChest = rand()%2;
    if(silverChest==0)
    {
        goldenChest=1;
    }
    else
    {
        goldenChest=0;
    }

    // Starting the game
    do
    {
        if(playerPosition==1) // Player is in the initial room
        {
            cout << "   *You are currently in the dark hallway of an ancient dungeon.*" << endl;
            cout << "   *Behind you, to the SOUTH there is an exit door that leads out of this dungeon*" << endl;
            cout << "   *Ahead of you, to the NORTH you can see the entrance to another room*" << endl << endl;
            playerPosition = initialRoom(playerHasKey);
        }
        else if(playerPosition==2) // Player is in the treasure room
        {
            cout << "   *This room contains two chests. One of them is silver and the other one is made of gold*." << endl;
            if(playerHasKey==true)
            {
                cout << "   *You have already found the key in one of those chests*" << endl;
            }
            else
            {
                cout << "   *Surely one of them contains the key you need to exit the dungeon. But they could also be trapped*" << endl;
            }
            cout << "   *Behind you, to the SOUTH is the hallway you came from. To the EAST you can see the entrance to a huge room*" << endl << endl;
            scenario = treasureRoom(silverChest, goldenChest, playerHasKey, playerSolvedRiddle);
            if(scenario==1) // Scenario 1 : The user goes back to initial room with no key
            {
                playerHasKey=false;
                playerPosition=1;
            }
            else if(scenario==2) // Scenario 2 : The user goes to the dragon room with no key
            {
                playerHasKey=false;
                playerPosition=3;
            }
            else if(scenario==3) // Scenario 3 : The user goes back to initial room with key
            {
                playerHasKey=true;
                playerPosition=1;
            }
            else if(scenario==4) // Scenario 4 : The user goes back to dragon room with key
            {
                playerHasKey=true;
                playerPosition=3;
            }
            else if(scenario==5) // Scenario 5 : The user dies from opening wrong chest
            {
                break;
            }
            else // This should never display
            {
                cout << "Houston we have a problem 2" << endl;
            }
        }
        else if(playerPosition==3) // Player is in the dragon room
        {
            cout << "   *You find yourself inside the enormous hall. In front of you, among a pile of skeletons lies a giant dragon*" << endl;
            cout << "   *Since you have no weapons at hand, it would be impossible to fight him, but perhaps you could bargain with him*" << endl;
            cout << "   *Behind you to the WEST is the treasure room you came from. In front of you lies the dragon you could TALK to*" << endl << endl;
            outcome = dragonRoom(silverChest, goldenChest, playerHasKey, playerSolvedRiddle);
            if(outcome==1) // Outcome 1 : The user solved the riddle before so dragon does not talk anymore
            {
                playerPosition=2;
            }
            else if(outcome==2) // Outcome 2 : The user solved the riddle and found out where they key is
            {
                playerSolvedRiddle=true;
                playerPosition=3;
            }
            else if(outcome==3) // Outcome 3 : The user got eaten
            {
                break;
            }
            else if(outcome==4) // Outcome 4 : The user goes back without solving riddle or finding where the key is
            {
                playerSolvedRiddle=false;
                playerPosition=2;
            }
            else // This should never display
            {
                cout << "Houston we have a problem 10" << endl;
            }
        }
        else // This should never display
        {
            cout << "Houston we have a problem 1" << endl;
        }
    }while(playerPosition!=0); // Repeat while user is not in the exit room
    if(playerPosition==0) // Player found key and went through the exit
    {
        cout << "Congratulations, you managed to exit the dungeon alive" << endl << endl;
    }
    else // Game loop ended before finding key and going through exit
    {
        cout << "Unfortunately you died. Better luck next time" << endl << endl;
    }
    cout << "Press the X button on the command console to close this game";
    cin >> playerAnswer;
    return 0;
}

int initialRoom(bool playerHasKey)
{
    int playerPosition;
    string playerAnswer;
    do
    {
        cout << "Which direction do you go ?" << endl;
        cin >> playerAnswer;
        if(playerAnswer=="South" || playerAnswer=="south" || playerAnswer=="SOUTH")
        {
            if(playerHasKey==true)
            {
                cout << "   *You used the rusty old key to unlock the exit door. You can finally leave this place*" << endl;
                playerPosition=0;
            }
            else
            {
                playerPosition=1;
                cout << "   *The door that leads out of this dungeon is locked, there has to be a key somewhere.*" << endl << endl;
            }
        }
        else if(playerAnswer=="North" || playerAnswer=="north" || playerAnswer=="NORTH")
        {
            playerPosition=2;
        }
        else
        {
            playerPosition=1;
            cout << "Answer not acceptable, please try another one" << endl << endl;
        }
    }while(playerPosition==1);
    return playerPosition;
}
// There are 5 possible scenarios as outcome of the treasure room
// Scenario 1 : The user goes back to initial room with no key
// Scenario 2 : The user goes to the dragon room with no key
// Scenario 3 : The user goes back to initial room with key
// Scenario 4 : The user goes back to dragon room with key
// Scenario 5 : The user dies from opening wrong chest
int treasureRoom(int silverChest, int goldenChest, bool playerHasKey, bool playerSolvedRiddle)
{
    int scenario=0;
    string playerAnswer;
    do
    {
        if(playerSolvedRiddle==false && playerHasKey==false)
        {
            cout << "   *You still have no clue which chest might be trapped and which has the key*" << endl;
            cout << "   *You could leave it up to fate to decide and open one randomly, or search around for clues*" << endl << endl;
        }
        else if(playerSolvedRiddle==true && playerHasKey==false)
        {
            cout << "   *According to the dragon the ";
            if(silverChest==0)
            {
                cout << "golden chest contains the key to this dungeon*" << endl << endl;
            }
            else if(silverChest==1)
            {
                cout << "silver chest contains the key to this dungeon*" << endl << endl;
            }
            else // This should never display
            {
                cout << "Houston we have a problem 3" << endl;
            }
        }
        cout << "   *Do you want to OPEN a chest or SEARCH this room further?*" << endl;
        cout << "   *You could also go SOUTH back to the hallway you came from or go EAST and see what lies deeper in the dungeon.*" << endl << endl;
        cin >> playerAnswer;
        if(playerAnswer=="open" || playerAnswer=="Open" || playerAnswer=="OPEN")
        {
            if(playerHasKey==true)
            {
                cout << "   *You have already found the key in those chests*" << endl;
            }
            else if(playerHasKey==false)
            {
                cout << "   *Do you want to open the SILVER chest or the GOLDEN chest*" << endl;
                cin >> playerAnswer;
                if(playerAnswer=="silver" || playerAnswer=="Silver" || playerAnswer=="SILVER")
                {
                    if(silverChest==0)
                    {
                    scenario=5;
                    cout << "   *As you try to open the chest, you hear a small click sound coming from it's lid*" << endl;
                    cout << "   *Unfortunately the chest was trapped with deadly poison*" << endl;
                    cout << "   *As you inhale the poison released by the chest, you feel your vision blur and you begin gasping for air*" << endl << endl;
                    }
                    else if(silverChest==1)
                    {
                        playerHasKey=true;
                        cout << "   *You open the chest with ease and you look inside*" << endl;
                        cout << "   *Inside the chest you find an old rusty key*" << endl;
                    }
                    else // This should never display
                    {
                        cout << "Houston we have a problem 4" << endl;
                    }
                }
                else if(playerAnswer=="golden" || playerAnswer=="Golden" || playerAnswer=="GOLDEN" || playerAnswer=="gold" || playerAnswer=="Gold" || playerAnswer=="GOLD" )
                {
                    if(goldenChest==0)
                    {
                    scenario=5;
                    cout << "   *As you try to open the chest, you hear a small click sound coming from it's lid*" << endl;
                    cout << "   *Unfortunately the chest was trapped with deadly poison*" << endl;
                    cout << "   *As you inhale the poison released by the chest, you feel your vision blur and you begin gasping for air*" << endl << endl;
                }
                    else if(goldenChest==1)
                    {
                        playerHasKey=true;
                        cout << "   *You open the chest with ease and you look inside*" << endl;
                        cout << "   *Inside the chest you find an old rusty key*" << endl;
                    }
                    else // This should never display
                    {
                        cout << "Houston we have a problem 4" << endl;
                    }
                }
                else
                {
                    scenario=0;
                    cout << "Answer not acceptable, please try another one" << endl << endl;
                }
            }
            else // This should never display
            {
                cout << "Houston we have a problem 7" << endl;
            }
        }
        else if(playerAnswer=="search" || playerAnswer=="Search" || playerAnswer=="SEARCH")
        {
            if(playerHasKey==true)
            {
                scenario=0;
                cout << "   *You have already found the key, so there is no reason anymore to search for clues*" << endl;
            }
            else
            {
                scenario=0;
                cout << "   *You search around this room, but can't find anything that might suggest which chest contains the key*" << endl;
                cout << "   *Maybe you could find the clue in another room of this dungeon*" << endl << endl;
            }
        }
        else if(playerAnswer=="south" || playerAnswer=="South" || playerAnswer=="SOUTH" || playerAnswer=="back" || playerAnswer=="Back" || playerAnswer=="BACK" || playerAnswer=="hallway" || playerAnswer=="Hallway" || playerAnswer=="HALLWAY")
        {
            if(playerHasKey==false)
            {
                scenario=1;
                cout << "   *You decide to go back to the hallway you started*" << endl << endl;
            }
            else if(playerHasKey==true)
            {
                scenario=3;
                cout << "   *Having found the key, you decide to go back to the hallway you started*" << endl << endl;
            }
            else // This should never display
            {
                cout << "Houston we have a problem 5" << endl;
            }
        }
        else if(playerAnswer=="east" || playerAnswer=="East" || playerAnswer=="EAST")
        {
            if(playerHasKey==false)
            {
                scenario=2;
                cout << "   *You decide to go east to the huge room and see what you can find there*" << endl << endl;
            }
            else if(playerHasKey==true)
            {
                scenario=4;
                cout << "   *Having found the key, you decide to go talk to the dragon again*" << endl << endl;
            }
            else // This should never display
            {
                cout << "Houston we have a problem 5" << endl;
            }
        }
        else
        {
            scenario=0;
            cout << "Answer not acceptable, please try another one" << endl << endl;
        }
    }while(scenario==0);
    return scenario;
}
// There are 4 possible outcomes of the dragon room
// Outcome 1 : The user solved the riddle before so dragon does not talk anymore
// Outcome 2 : The user solved the riddle and found out where they key is
// Outcome 3 : The user got eaten
// Outcome 4 : The user goes back without solving riddle or finding where the key is
int dragonRoom(int silverChest, int goldenChest, bool playerHasKey, bool playerSolvedRiddle)
{
    int outcome=0;
    string playerAnswer;
    do
    {
        cout << "   *Do you TALK to the dragon, or go WEST back to the treasure room?*" << endl;
        cin >> playerAnswer;
        if(playerAnswer=="talk" || playerAnswer=="Talk" || playerAnswer=="TALK" || playerAnswer=="dragon" || playerAnswer=="Dragon" || playerAnswer=="DRAGON")
        {
            if(playerSolvedRiddle==true)
            {
                cout << "   *You have already answered my riddle mortal, leave this place before i change my mind and decide to feast on you!*" << endl;
                cout << "   *You decide it would be better to not anger the dragon any more, so you retreat back to the treasure room!*" << endl;
                outcome = 1;
            }
            else if(playerSolvedRiddle==false)
            {
                cout << "   *Hmmm another mortal, trapped inside my dungeon, finds the courage to stand before me*" << endl;
                cout << "   *I will give you the same choice i gave the ones before you,*" << endl;
                cout << "   *I will ask you of a riddle. You have 3 chances to answer correctly, otherwise i will feed on you*" << endl;
                cout << "   *What walks on four legs in the morning, two legs in the afternoon and three legs in the evening?*" << endl;
                for(int i=3; i>0; i--)
                {
                    cout << "you have " << i << " tries left, answer carefully" << endl;
                    cin >> playerAnswer;
                    if(playerAnswer=="human" || playerAnswer=="Human" || playerAnswer=="HUMAN" || playerAnswer=="man" || playerAnswer=="Man" || playerAnswer=="MAN")
                    {
                        cout << "   *Hmmm, you are correct mortal. Your intelligence has earned you your life*" << endl;
                        cout << "   *To get out of my dungeon you will need a key from one on the chests in the room you came from*" << endl;
                        if(silverChest==1)
                        {
                            cout << "   *The key to the exit is inside the silver chest*" << endl;
                            cout << "   *Do not attempt to open the golden one mortal, it would be a waste of the life you just earned*" << endl << endl;
                        }
                        else if(goldenChest==1)
                        {
                            cout << "   *The key to the exit is inside the golden chest*" << endl;
                            cout << "   *Do not attempt to open the silver one mortal, it would be a waste of the life you just earned*" << endl << endl;
                        }
                        else // This should never display
                        {
                            cout << "Houston we have a problem 9" << endl;
                        }
                        playerSolvedRiddle=true;
                        outcome = 2;
                        break;
                    }
                    else if(i==1)
                    {
                        cout << "   *You lost all your chances mortal, i will enjoy feasting on your flesh!!*" << endl;
                        cout << "   *Before you can even react, the dragon's head moves at surprising speed, closing his teeth around you and swallowing you whole*" << endl;
                        outcome = 3;
                    }
                    else
                    {
                        cout << "This answer was incorrect, try again" << endl;
                    }
                }
            }
            else // This should never display
            {
                cout << "Houston we have a problem 8" << endl;
            }
        }
        else if(playerAnswer=="west" || playerAnswer=="West" || playerAnswer=="WEST" || playerAnswer=="back" || playerAnswer=="Back" || playerAnswer=="BACK")
        {
            if(playerSolvedRiddle==true)
            {
                cout << "   *Having already found the answer to the dragon's riddle you decide to return to the treasure room*" << endl << endl;
                outcome = 1;
            }
            else if(playerSolvedRiddle==false)
            {
                cout << "   *You decide to return to the treasure room without talking to the dragon.*" << endl;
                cout << "   *You wonder if you have better chances triggering a deadly trap or a deadly dragon*" << endl << endl;
                outcome = 4;
            }
            else // This should never display
            {
                cout << "Houston we have a problem 8" << endl;
            }
        }
        else
        {
            outcome=0;
            cout << "Answer not acceptable, please try another one" << endl << endl;
        }
    }while(outcome==0);
    return outcome;
}
