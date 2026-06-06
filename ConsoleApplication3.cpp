#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <cctype>
#include <fstream>

using namespace std;

const string ClientsFileName = "Clients.txt";
struct stClient
{
	string AccountNumber;
	string PinCode;
	string UserName;
	string PhoneNumber;
	int AccountBalance;
	bool MarkToDelete = false;
};

stClient CurrentUser;

void ShowAtmMainMenuScreen();
void Login();

enum enATM_Options
{
	enQuickWithdraw = 1, enNormalWithdraw = 2, enDeposit = 3, enCheckBalance = 4, enLogout = 5
};

vector<string> SplitString(string s1, string delim) {

	vector<string> vString;
	short pos = 0;
	string word;

	while ((pos = s1.find(delim)) != std::string::npos) {

		word = s1.substr(0, pos);

		if (word != "") {

			vString.push_back(word);

		}
		s1.erase(0, pos + delim.length());
	}

	if (s1 != "") {
		vString.push_back(s1);
	}
	return vString;
}

string ConvertRecordToLine(stClient ClientData, string Delim = "/##/") {

	string stClientRecord = "";

	stClientRecord += ClientData.AccountNumber + Delim;
	stClientRecord += ClientData.PinCode + Delim;
	stClientRecord += ClientData.UserName + Delim;
	stClientRecord += ClientData.PhoneNumber + Delim;
	stClientRecord += to_string(ClientData.AccountBalance);

	return stClientRecord;
}

stClient ConvertLinetoRecord(string Line, string Delim = "/##/") {

	stClient Client;
	vector <string> vClientData;

	vClientData = SplitString(Line, Delim);

	Client.AccountNumber = vClientData[0];
	Client.PinCode = vClientData[1];
	Client.UserName = vClientData[2];
	Client.PhoneNumber = vClientData[3];
	Client.AccountBalance = stoi(vClientData[4]);

	return Client;
}

vector <stClient> LoadClieanDataFromFile(string FileName) {

	vector <stClient> vClient;
	fstream MyFile;
	MyFile.open(FileName, ios::in);//Read Mode;

	if (MyFile.is_open())
	{

		string Line;
		stClient Client;

		while (getline(MyFile, Line)) {

			Client = ConvertLinetoRecord(Line);

			vClient.push_back(Client);
		}


		MyFile.close();
	}
	return vClient;
}

vector <stClient> SaveCleintsDataToFile(string FileName, vector <stClient>vClient) {

	fstream MyFile;
	MyFile.open(ClientsFileName, ios::out);

	string Line;

	if (MyFile.is_open())
	{
		for (stClient C : vClient) {

				
			Line = ConvertRecordToLine(C);
			MyFile << Line << endl;
			

		}

		MyFile.close();
	}
	return vClient;

}

bool LoginByAccountNumberAndPincode(string AccountNumber, string Pincode, vector <stClient> &vClient, stClient& Client) {


	for (stClient C : vClient) {

		if ((C.AccountNumber == AccountNumber) && (C.PinCode == Pincode))
		{
			Client = C;
			return true;
		}
	}

	return false;
}

void PrintLoginScreen() {
	cout << "\n---------------------------\n";
	cout << "\tLogin Screen\n";
	cout << "---------------------------\n";
}

string ReadAccountNumber() {

	string AccountNumber = "";
	cout << "Please Enter Account Number? ";
	cin >> AccountNumber;

	return AccountNumber;
}

string ReadPinCode() {

	string PinCode = "";
	cout << "Please Enter Pin Code ";
	cin >> PinCode;

	return PinCode;
}

void GoBackToMainMenue()
{
	cout << "\n\nPress any key to go back to Main Menue...";
	system("pause>0");
	ShowAtmMainMenuScreen();
}


bool DepositBalanceToClientByAccountNumber(string AccountNumber, int Amount, vector<stClient>& vClient) {

	char y_n = 'y';
	cout << "Are you sure you want perfrom this transcation ? y/n ? ";
	cin >> y_n;

	if (y_n == 'y' || y_n == 'Y')
	{
		for (stClient& C : vClient) {

			if (C.AccountNumber == AccountNumber)
			{
				C.AccountBalance += Amount;
				SaveCleintsDataToFile(ClientsFileName, vClient);
				CurrentUser.AccountBalance = C.AccountBalance;
				cout << "Done. Successfully new balance is : " << C.AccountBalance;
				return true;
			}
		}
	}
	return false;
}

short ReadQuickWithdrawAmount() {
	cout << "===============================\n";
	cout << "\tQucik Withdraw\n";
	cout << "===============================\n";
	cout << "[1] 20 \t [2] 50\n";
	cout << "[3] 100\t [4] 200\n";
	cout << "[5] 400\t [6] 600\n";
	cout << "[7] 800\t [8] 1000\n";
	cout << "[9]Exit\n";
	cout << "===============================\n";
	cout << "Your Balance is " << CurrentUser.AccountBalance << endl;
	short Number = 0;
	cout << "Choose what to withdraw from [1] to [8] ? ";
	cin >> Number;
	
	if (Number == 1)
	{
		return 20;
	}
	else if (Number == 2) {
		return 50;
	}
	else if (Number == 3) {
		return 100;
	}
	else if (Number == 4) {
		return 200;
	}
	else if (Number == 5) {
		return 400;
	}
	else if (Number == 6) {
		return 600;
	}
	else if (Number == 7) {
		return 800;
	}
	else if (Number == 8) {
		return 1000;
	}
	else
	{
		GoBackToMainMenue();
	}


}

int ReadWithdrawAmount() {

	int Amount = 0;

	do
	{
		cout << "Enter an amount multiple of 5's? ";
		cin >> Amount;

	} while (Amount % 5 != 0);

	return Amount;
}

int ReadDepositAmount() {

	int Amount = 0;
	cout << "Enter a  postive Deposit Amount? ";
	cin >> Amount;
	return Amount;
}


void QuickWithdrawScreen() {

	vector <stClient> vClient = LoadClieanDataFromFile(ClientsFileName);
	short WithdrawAmount = ReadQuickWithdrawAmount();

	while (WithdrawAmount > CurrentUser.AccountBalance) {
		cout << "\nAmount Exceeds the balance, you can withdraw up to : " << CurrentUser.AccountBalance << endl;
		cout << "Please enter another amount? ";
		WithdrawAmount = ReadQuickWithdrawAmount();
	}

	DepositBalanceToClientByAccountNumber(CurrentUser.AccountNumber,-1 * WithdrawAmount, vClient);
	
}

void NormalWithdrawScreen() {
	cout << "=============================\n";
	cout << "Normal Withdraw Screen\n";
	cout << "=============================\n\n";

	int Amount = ReadWithdrawAmount();
	vector <stClient> vClient = LoadClieanDataFromFile(ClientsFileName);

	while (Amount > CurrentUser.AccountBalance) {
		cout << "\nAmount Exceeds the balance, you can withdraw up to : " << CurrentUser.AccountBalance << endl;
		cout << "Please enter another amount? ";
		Amount = ReadWithdrawAmount();
	}

	
	DepositBalanceToClientByAccountNumber(CurrentUser.AccountNumber, -1 * Amount, vClient);
}

void DepositScreen() {
	cout << "=============================\n";
	cout << "Deposit Screen\n";
	cout << "=============================\n\n";

	int Amount = ReadDepositAmount();
	vector <stClient> vClient = LoadClieanDataFromFile(ClientsFileName);
	DepositBalanceToClientByAccountNumber(CurrentUser.AccountNumber,Amount, vClient);
}

void CheckBalanceScreen() {
	cout << "=============================\n";
	cout << "Check Balance Screen\n";
	cout << "=============================\n\n";
	cout << "Your Balance is " << CurrentUser.AccountBalance << endl << endl;
}

void PerfromATMOption(enATM_Options ATMoptions) {

	switch (ATMoptions)
	{
	case enATM_Options::enQuickWithdraw: {
		system("cls");
		QuickWithdrawScreen();
		GoBackToMainMenue();
		break;
	}
	case enATM_Options::enNormalWithdraw: {
		system("cls");
		NormalWithdrawScreen();
		GoBackToMainMenue();
		break;
	}
	case enATM_Options::enDeposit: {
		system("cls");
		DepositScreen();
		GoBackToMainMenue();
		break;
	}
	case enATM_Options::enCheckBalance: {
		system("cls");
		CheckBalanceScreen();
		GoBackToMainMenue();
		break;
	}
	case enATM_Options::enLogout: {
		system("cls");
		Login();
		break;
	}

	}

}


short ReadChoise() {
	short Number = 0;
	cout << "Choose what do you want to do? [1 to 5]? ";
	cin >> Number;
	return Number;
}

void ShowAtmMainMenuScreen() {

	system("cls");
	cout << "=======================================\n";
	cout << "\t ATM Main Menue Screen\n";
	cout << "=======================================\n";
	cout << "[1] Quick Withdraw.\n";
	cout << "[2] Normal Withdraw.\n";
	cout << "[3] Deposit.\n";
	cout << "[4] Check Balance.\n";
	cout << "[5] Logout\n";
	cout << "=======================================\n";

	PerfromATMOption((enATM_Options)ReadChoise());
}

void Login() {

	stClient Client;
	vector<stClient> stClient = LoadClieanDataFromFile(ClientsFileName);

	PrintLoginScreen();
	string AccountNumber = ReadAccountNumber();
	string PinCode = ReadPinCode();

	while (!LoginByAccountNumberAndPincode(AccountNumber, PinCode, stClient, Client)) {

		system("cls");
		PrintLoginScreen();
		cout << "Invalid Account Number/Pin code\n";
		AccountNumber = ReadAccountNumber();
		PinCode = ReadPinCode();
	}

	CurrentUser = Client;
	ShowAtmMainMenuScreen();
}

int main()
{
	Login();
}

