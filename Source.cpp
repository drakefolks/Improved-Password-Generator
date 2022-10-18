#include<iostream>
#include<fstream>
#include<random>
#include<string>

using namespace std;

using u32 = uint_least32_t;
using engine = mt19937;

class PasswordGenerator
{
private:
	string chars[80] = { "a","A","b","B","c","C","d","D","e","E","f","F","g","G","h","H","i","I","j","J","k","K","l","L","m","M","n","N",
							"o","O","p","P","q","Q","r","R","s","S","t","T","u","U","v","V","w","W","x","X","y","Y","z","Z",
							"0","1","2","3","4","5","6","7","8","9","@","%","+","!","#","?",".","$","-","@","%","+","!","#","?",".","$","-" };

public:
	int getRandomNum();
	void getRandomPass();
	string pass[20];
	int numChar = 0;

};

int PasswordGenerator::getRandomNum()
{
	random_device os_seed;
	const u32 seed = os_seed();

	engine generator(seed);
	uniform_int_distribution<u32> distribute(0, 80);

	int rNum = distribute(generator);

	int randomNum = rNum;
	return randomNum;
}

void PasswordGenerator::getRandomPass()
{
	string service;
	cout << "What service is this password for?\n";
	getline(cin, service);

	//opening and inputting basic data to password sheet
	ofstream outData;
	outData.open("passwordFile.csv", ios::app);
	outData << "\n\nYour password for " << service << " is: \n";

	//gathering total char number and keyphrase if wanted
	int numChars;
	cout << "\nHow many charecters would you like in your password? (8-14 suggested) \n--If you want a pass that will take centuries to crack, have at least 14 charecters\n--If you want a keyphrase, have more charecters\n";
	cin >> numChars;
	numChar = numChars;

	char ans;
	cout << "Would you like a keyphrase in your password?\n";
	cin >> ans;

	if (ans == 'y' || ans == 'Y')
	{
		string key;
		cout << "\nEnter your keyphrase, no whitespaces\n--Consider replacing some letters with numbers or symbols, it will make the password stronger\n";
		cin >> key;

		srand(time(NULL));

		int keyLength = key.length();		    //getting keyphrase length 
		int total_rChar = numChars - keyLength; //determing how many chars to iterate randomly
		int randomIndex = rand() % numChars;    //choosing random index to drop in keyphrase

		//making sure that random index is less than total_rChar, if it is not, generates another one
		if (total_rChar < randomIndex)
		{
			do
			{
				cout << "--rejected random index: " << randomIndex << endl;
				randomIndex = rand() % numChars;
			} while (total_rChar < randomIndex);
		}

		//assembeling password into string pass, writing pass to file
		for (int i = 0; i <= total_rChar; i++)
		{
			if (i == randomIndex)
			{
				pass[i] = key;
			}

			else
			{
				int rNum = getRandomNum();
				pass[i] = chars[rNum];
			}

			outData << pass[i];
		}
	}

	else
	{
		for (int i = 0; i < numChars; i++)
		{
			int rNum = getRandomNum();
			pass[i] = chars[rNum];
			outData << pass[i];
		}
	}

	outData.close();
}

int main()
{
	PasswordGenerator password;

	password.getRandomPass();

	cout << "\nYour password is\n";

	for (int i = 0; i <= password.numChar; i++)
	{
		cout << password.pass[i];
	}
	cout << "\n\n";
	cout << "*********************************\n";
	cout << "--Password stored to excel file--\n";
	cout << "*********************************\n";

	return 0;
}