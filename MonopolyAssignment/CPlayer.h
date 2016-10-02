#include <string>
using namespace std;
class CPlayer
{
private:

	string mPlayerCounter;
	string mPlayerName;
	int mPlayerMoney;
	const int mStartingMoney = 1500;
	int mPlayerPosition;

public:
	CPlayer(string name, string counter);
	string GetPlayerName();
	string GetPlayerCounter();
	int GetPlayerMoney();
	void DecreasePlayerMoney(int value);
	void IncreasePlayerMoney(int value);
	void SetPlayerPosition(int pos);
	int GetPlayerPosition();
	
	


};