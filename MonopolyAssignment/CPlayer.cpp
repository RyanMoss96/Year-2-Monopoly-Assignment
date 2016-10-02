#include "stdafx.h"
#include "CPlayer.h"

CPlayer::CPlayer(string name, string counter)
//Constructor for setting the players starting name counter, money and position
{
	mPlayerMoney = mStartingMoney;
	mPlayerName = name;
	mPlayerPosition = 0;
	mPlayerCounter = counter;
}
string CPlayer::GetPlayerName()
{
	//Used to return the players name
	return mPlayerName;
}
string CPlayer::GetPlayerCounter()
{
	//Returns the players counter piece
	return mPlayerCounter;
}
int CPlayer::GetPlayerMoney()
{
	//Returns the players current money
	return mPlayerMoney;
}
void CPlayer::DecreasePlayerMoney(int value)
{
	//Decreases the players money by the value
	mPlayerMoney -= value;
}
void CPlayer::IncreasePlayerMoney(int value)
{
	//Increases the players money by the value
	mPlayerMoney += value;
}
void CPlayer::SetPlayerPosition(int pos)
{
	//Sets the players position
	mPlayerPosition = pos;
}
int CPlayer::GetPlayerPosition()
{
	//Gets the players current position
	return mPlayerPosition;
}