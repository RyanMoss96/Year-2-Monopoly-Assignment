// MonopolyAssignment.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "CSquares.h"
#include "CPlayer.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
using namespace std;

//Function for reading in the monopoly.txt file.
void ReadMonopolyFile(CSquares* monopolySquares[]);
//Random function that produces a random number between 1-6 to simulate dice rolling.
int Random();
//Function for checking if the players position goes over the board limit of 26 squares, thus passing Go.
void CheckPassedGo(int &newPosition, int numberOfSquares, CPlayer* player);
//Function for checking if the player has landed on a property that has been owned.
void CheckPropertyOwned(CSquares* square, CPlayer* player[], int i);
//Function for reading in the seed file.
int ReadSeedFile();
//Function for checking if the player has landed on a penalty or a bonus square or not.
void CheckPenaltyBonus(CSquares* square, CPlayer* player[], int seed, int i);
//Function for checking if the player has landed on Go To Jail and moves them to the Jail square.
void CheckGoToJail(CSquares* square[], CPlayer* player, int &position);
void CheckIfJail(CSquares* square[], CPlayer* player, int newPosition);
int _tmain(int argc, _TCHAR* argv[])
{
	cout << "Welcome to Monopoly!" << endl << endl;

	
	bool gameRunning = true;
	const int numberOfSquares = 26;
	CSquares* monopolySquares[numberOfSquares];
	CPlayer* players[2];
	int currentPlayer = 0;
	const int numOfPlayers = 2;
	const int numOfRounds = 20;

	//Setting up the 2 player objects passign in the player piece into the constructor.
	players[0] = new CPlayer("Player 1", "dog");
	players[1] = new CPlayer("Player 2", "car");

	//Function for reading in the monopoly.txt file.
	ReadMonopolyFile(monopolySquares);
	//Function for reading in the seed file.
	int seed =  ReadSeedFile();

	//Sets the seed for the random function.
	srand(seed);
	//for loop for the 20 rounds that are played by the game,
	for (int i = 0; i < numOfRounds; i++)
	{
		cout << "Round: " << i + 1 << endl;
		//for loop for the number of players playing the game
		for (int j = 0; j < numOfPlayers; j++)
		{
			//Random function that produces a random number between 1-6 to simulate dice rolling.
			int diceRoll = Random();

			cout << players[j]->GetPlayerCounter() << " rolls a " << diceRoll << endl;

			//Gets the current square number that the player is currently on.
			int currentPosition = players[j]->GetPlayerPosition();
			//Adds the diceroll to the current player position to get the new position of the square the player is on.
			int newPosition = currentPosition + diceRoll;
			
			//Function for checking if the players position goes over the board limit of 26 squares, thus passing Go.
			CheckPassedGo(newPosition, numberOfSquares, players[j]);
			
			//Set the players position to the new square position.
			players[j]->SetPlayerPosition(newPosition);
			
			//Output the square that the player has landed on.
			cout << players[j]->GetPlayerCounter() << " has landed on " << monopolySquares[players[j]->GetPlayerPosition()]->GetPropertyName() << endl;
			CheckIfJail(monopolySquares, players[j], newPosition);
			//Function for checking if the player has landed on Go To Jail and moves them to the Jail square.
			CheckGoToJail(monopolySquares, players[j], newPosition);
			//Set the players position to the new square position.
			players[j]->SetPlayerPosition(newPosition);
			
			//Function for checking if the player has landed on a property that has been owned.
			CheckPropertyOwned(monopolySquares[newPosition], players, j);
			//Function for checking if the player has landed on a penalty or a bonus square or not.
			CheckPenaltyBonus(monopolySquares[newPosition], players, seed, j);

			//Outputs the players current money total.
			cout << players[j]->GetPlayerCounter() << " has \x9C" << players[j]->GetPlayerMoney() << endl;
		}

		cout << endl;  

	}
	system("pause");
}
void ReadMonopolyFile(CSquares* monopolySquares[])
{
	ifstream monopolyFile;
	string line;
	int i = 0;
	//Opens the monopoly.txt file
	monopolyFile.open("Monopoly.txt");
	//Check that the file was successfully opened.
	if (monopolyFile.is_open())
	{
		//While there is a line to get from the file.
		while (getline(monopolyFile, line))
		{

			//Initialise a square of the board passing in the line from the file into the constructor.
			monopolySquares[i] = new CSquares(line);
			
			i++;
		}
		//Close the file.
		monopolyFile.close();
	}

}
void CheckPassedGo(int &newPosition, int numberOfSquares, CPlayer* player)
{
	//Check if the player has gone outside the monopoly board limit
	if (newPosition > numberOfSquares - 1)
	{
		//Claculate how far the player is off the board
		newPosition = newPosition - numberOfSquares;
		//Increase the players money by 200 ror passing GO
		player->IncreasePlayerMoney(200);

		//Output the player passed go
		cout << player->GetPlayerCounter() << " passes GO and collects \x9C 200" << endl;


	}
}
void CheckPropertyOwned(CSquares* square, CPlayer* player[], int i)
{
	//Check oif the current square is a general property
	if (square->GetPropertyType() == 1)
	{
		//If the square isnt owned
		if (!square->IsOwned())
		{
			//Set the current player as the owner
			square->SetOwner(player[i]->GetPlayerCounter());
			//Take the cost of the property from the player
			player[i]->DecreasePlayerMoney(square->GetPropertyCost());
			//Output the player has bought the property
			cout << player[i]->GetPlayerCounter() << " has bought " << square->GetPropertyName() << " for \x9C" << square->GetPropertyCost() << endl;
		}
		else
		{
			//If the current player doesnt own the p[roperty then rent needs to be paid
			if (square->GetOwnedBy() != player[i]->GetPlayerCounter())
			{
				//Decrease players money by the cost of the rent
				player[i]->DecreasePlayerMoney(square->GetPropertyRent());
				cout << player[i]->GetPlayerCounter() << " pays \x9C" << square->GetPropertyRent() << endl;
				//Loop for findign the array address of the person who owns the property
				bool playerFound = false;
				int j = 0;
				while (!playerFound)
				{
					if (square->GetOwnedBy() == player[j]->GetPlayerCounter())
					{
						//Increase the owners money by the cost of the rent
						player[j]->IncreasePlayerMoney(square->GetPropertyRent());
						 
						playerFound = true;
					}
					j++; 
				}
			}
		}
	}  
	//If the property is an airport
	else if(square->GetPropertyType() == 3)
	{
		//If the property isnt owned then buy the property
		if (!square->IsOwned())
		{
			//Set owner and decrease cost of property
			square->SetOwner(player[i]->GetPlayerCounter());
			player[i]->DecreasePlayerMoney(square->GetAirportCost());
			cout << player[i]->GetPlayerCounter() << " has bought " << square->GetPropertyName() << " for \x9C" << square->GetAirportCost() << endl;
		}
		else
		{
			//If not owned by the current player
			if (square->GetOwnedBy() != player[i]->GetPlayerCounter())
			{
				//Decrease money by the airport fee
				player[i]->DecreasePlayerMoney(square->GetAirportFee());
				cout << player[i]->GetPlayerCounter() << " pays \x9C" << square->GetAirportFee() << endl;
				//Loop for finding the airport owner
				bool playerFound = false;
				int j = 0;
				while (!playerFound)
				{
					if (square->GetOwnedBy() == player[j]->GetPlayerCounter())
					{
						//Increase owners money by airport fee
						player[j]->IncreasePlayerMoney(square->GetAirportFee());

						playerFound = true;
					}
					j++;
				}
			}
		}
	}
	//If player lands on jail
	else if (square->GetPropertyType() == 8)
	{
		
		cout << "Player is resting." << endl;
	}
	
}
void CheckGoToJail(CSquares* square[], CPlayer* player, int &position)
{
	bool jailFound = false;
	int i = 0;
	//if player lands on jail square
	if (square[position]->GetPropertyType() == 7)
	{
		while (!jailFound)
		{
			if (square[i]->GetPropertyType() == 6)
			{
				position = i;

				cout << "Player goes to jail." << endl;
				cout << "Player pays \x9C" << square[i]->GetJailFee() << endl;
				//Pay jail fee
				player->DecreasePlayerMoney(square[i]->GetJailFee());
				jailFound = true;
			}
			i++;
		}
		
	}
	
	
}

void CheckIfJail(CSquares* square[], CPlayer* player, int newPosition)
{
	//If the player lands jail
	if (square[newPosition]->GetPropertyType() == 6)
	{
		cout << "Player is just visiting." << endl;
	}
}
void CheckPenaltyBonus(CSquares* square, CPlayer* player[], int seed, int i)
{
	//If the square is a penalty square
	if (square->GetPropertyType() == 5)
	{
		//Decrease the players money by the random penalty cost
		player[i]->DecreasePlayerMoney(square->Penalty());
	}
	//If bonus
	else if (square->GetPropertyType() == 4)
	{
		//Increase player smoney by random bonus reward
		player[i]->IncreasePlayerMoney(square->Bonus());
	}
}
//Used to generate a random dice roll
int Random()
{
	return static_cast<int>(static_cast<double> (rand()) / (RAND_MAX + 1) * 6.0f + 1);
	
}
int ReadSeedFile()
{
	ifstream seedFile; 
	int line;
	int i = 0;
	//Open seed.txt file
	seedFile.open("seed.txt");
	if (seedFile.is_open())
	{
		//Read the seed line in
		seedFile >> line;
		seedFile.close();
	}

	return line;
}

