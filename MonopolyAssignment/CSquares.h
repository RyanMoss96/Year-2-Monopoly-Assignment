
#include <string>
using namespace std;

class CSquares{

private:
	string mPropertyName;
	int mCost;
	int mRent;
	int mColourGroup;
	int mPropertyCode;
	string mPropertyType;
	string mOwner;
	bool mOwned = false;
	int mSeed;

	const int mPassGo = 200;
	const int mAirportCost = 200;
	const int mAirportFee = 10;
	const int mJailFee = 50;

	static const string mBonusOptions[6];
	static const int mBonusReward[6];

	static const string mPenaltyOptions[6];
	static const int mPenaltyCost[6];
public:
	CSquares(string line);
	int GetPropertyType();
	string GetPropertyName();
	int GetPropertyCost();
	string GetOwnedBy();
	void SetOwner(string owner);
	bool IsOwned();
	int GetPropertyRent();
	int PassGo();
	int GoToJail();
	int Penalty();
	int Bonus();
	int Random();
	int GetAirportCost();
	int GetAirportFee();
	int GetJailFee();
	

};