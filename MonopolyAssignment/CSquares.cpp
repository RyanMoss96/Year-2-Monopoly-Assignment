#include "stdafx.h"
#include "CSquares.h"
#include <sstream>
#include <iostream>

//MonopolySquares Constructor
CSquares::CSquares(string line)
{
	istringstream monopolySquare(line);
	int i = 1;

	do
	{
		//Splits the string by its white space.
		string sub;
		monopolySquare >> sub;

		if (i == 1)
		{
			//Assign the propertycode of each property.
			mPropertyCode = atoi(sub.c_str());
		}
		if (mPropertyCode != 7)
		{
			//Assign the property name (for properties with 2 words)
			if (i == 2)
			{
				mPropertyName = sub;
			}
			else if (i == 3)
			{
				mPropertyName = mPropertyName + " " + sub;
			}
			//Assign the cost
			else if (i == 4)
			{
				mCost = atoi(sub.c_str());
			}
			//Assign rent
			else if (i == 5)
			{
				mRent = atoi(sub.c_str());
			}
			//Assign colour group
			else if (i == 5)
			{
				mColourGroup = atoi(sub.c_str());
			}
		}
		else
		{
			//Assign property name for those with 3 words in the name (Go To Jail)
			if (i == 2)
			{
				mPropertyName = sub;
			}
			else if (i == 3)
			{
				mPropertyName = mPropertyName + " " + sub;
			}
			else if (i == 4)
			{
				mPropertyName = mPropertyName + " " + sub;
			}

		}


		i++;


	} while (monopolySquare);
}

int CSquares::GetPropertyType()
{
	//Returns the property code which indicates whether it is airport etc
	return mPropertyCode;
}
string CSquares::GetPropertyName()
{
	///Returns property name
	return mPropertyName;
}
int CSquares::GetPropertyCost()
{
	//Returns property cost
	return mCost;
}
string CSquares::GetOwnedBy()
{
	//Returns who owns the property
	return mOwner;
}
void CSquares::SetOwner(string owner)
{
	//Sets the owner after purchasing the property
	mOwner = owner;
	mOwned = true;
}
bool CSquares::IsOwned()
{
	//returns whether te property is owned.
	return mOwned;
}
int CSquares::GetPropertyRent()
{
	//returns rent
	return mRent;
}
int CSquares::PassGo()
{
	//returns pass go value
	return mPassGo;
}

int CSquares::GoToJail()
{
	//returns jail fee
	return mJailFee;
}
int CSquares::Penalty()
{
	//selects a random penalty
	int i = 0;
	i = Random();
	cout << mPenaltyOptions[i-1] << ". Player loses \x9C" << mPenaltyCost[i] << endl;
	return mPenaltyCost[i-1];
}
int CSquares::Bonus()
{ 
	//returns random bonus
	int i = 0;
	i = Random();
	cout << mBonusOptions[i-1] << ". Player gains \x9C" << mBonusReward[i] << endl;
	return mBonusReward[i-1];
}
int CSquares::GetAirportCost()
{
	//returns airport cost
	return mAirportCost;
}
int CSquares::GetAirportFee()
{
	//returns airport fee
	return mAirportFee;
}
int CSquares::GetJailFee()
{
	//returns jail fee
	return mJailFee;
}
int CSquares::Random()
{
	return static_cast<int>(static_cast<double> (rand()) / (RAND_MAX + 1) * 6.0f + 1);
}

//Sets the arrays for use in the penalty and bonus array.
const string CSquares::mPenaltyOptions[6] = {
	"Pay food bill", "Pay Phone bill", "Pay Heating Bill", "Pay Vehicle Tax", "Pay fuel bill", "Pay Windfall tax" 
};

const int CSquares::mPenaltyCost[6] = {
		 20, 50, 100, 150, 200, 300 
};


const string CSquares::mBonusOptions[6] = {
	"Find Some Money", "Win Competition", "Tax Rebate", "Win Lottery", "Bequest", "Birthday" 
};

const int CSquares::mBonusReward[6] = {
	20, 50, 100, 150, 200, 300
};
