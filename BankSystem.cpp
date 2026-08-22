#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <limits>  
using namespace std;
const string ClientsFileName = "Clients.txt";
const string UsersFileName = "Users.txt";
void PressAnyKeyToContinue() {
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	system("pause > nul");
}
struct sClient
{
	string AccountNumber;
	string PinCode;
	string Name;
	string Phone;
	double AccountBalance;
	bool MarkForDelete = false;
	bool MarkForUpdate = false;
};
struct sUsers {
	string UserName;
	string Password;
	int Permisions;
	bool MarkForDelete = false;
	bool MarkForUpdate = false;
};
sClient UpdateClientInfo(sClient& newclientinfo) {
	cout << "Enter PINCode : ";
	cin >> newclientinfo.PinCode;
	cout << "Enter Your Name : ";
	cin.ignore();
	getline(cin, newclientinfo.Name);
	cout << "Enter Phone Number : ";
	cin >> newclientinfo.Phone;
	cout << "Enter Your Balance : ";
	cin >> newclientinfo.AccountBalance;
	to_string(newclientinfo.AccountBalance);
	return newclientinfo;


}
sClient AddClientInfo(sClient& newclientinfo) {
	cout << "Enter Account Number : ";
	cin >> newclientinfo.AccountNumber;
	cout << "Enter PINCode : ";
	cin >> newclientinfo.PinCode;
	cout << "Enter Your Name : ";
	cin.ignore();
	getline(cin, newclientinfo.Name);
	cout << "Enter Phone Number : ";
	cin >> newclientinfo.Phone;
	cout << "Enter Your Balance : ";
	cin >> newclientinfo.AccountBalance;
	to_string(newclientinfo.AccountBalance);
	return newclientinfo;
}
enum enPermissions
{
	pShowClients = 1,
	pAddClient = 2,
	pDeleteClient = 4,
	pUpdateClient = 8,
	pFindClient = 16,
	pTransactions = 32,
	pManageUsers = 64
};
bool HasPermission(int UserPermissions, enPermissions Permission)
{
	return (UserPermissions & Permission) == Permission;
}
int givepermissions() {
	int Permissions = 0;
	char ans;
	cout << "Do you want to give full access? (y/n)? ";
	cin >> ans;
	if (ans == 'y' || ans == 'Y') {
		return -1;
	}
	else {
		cout << "Do you want to give access to :\n";
		cout << "Show Client List ? y/n? ";
		cin >> ans;
		if (ans == 'y' || ans == 'Y') {
			Permissions |= pShowClients;
		}
		cout << "Add new Client ? y/n? ";
		cin >> ans;
		if (ans == 'y' || ans == 'Y') {
			Permissions |= pAddClient;
		}
		cout << "Delete Client ? y/n? ";
		cin >> ans;
		if (ans == 'y' || ans == 'Y') {
			Permissions |= pDeleteClient;
		}
		cout << "Update Client ? y/n? ";
		cin >> ans;
		if (ans == 'y' || ans == 'Y') {
			Permissions |= pUpdateClient;
		}
		cout << "Find Client ? y/n? ";
		cin >> ans;
		if (ans == 'y' || ans == 'Y') {
			Permissions |= pFindClient;
		}
		cout << "Transactions ? y/n? ";
		cin >> ans;
		if (ans == 'y' || ans == 'Y') {
			Permissions |= pTransactions;
		}
		cout << "Manage Users ? y/n? ";
		cin >> ans;
		if (ans == 'y' || ans == 'Y') {
			Permissions |= pManageUsers;
		}

	}

	return Permissions;

}
bool FindUserByUserName(string UserName, string Password, vector <sUsers>& vUser, sUsers& Userinfo)
{
	for (sUsers C : vUser)
	{
		if (C.UserName == UserName && C.Password == Password)
		{
			Userinfo = C;
			return true;
		}
	}
	return false;
}
bool FindUserByUserNameOnly(string UserName, vector <sUsers>& vUser, sUsers& Userinfo)
{
	for (sUsers C : vUser)
	{
		if (C.UserName == UserName)
		{
			Userinfo = C;
			return true;
		}
	}
	return false;
}
sUsers AddUserInfo(sUsers& Userinfo, vector <sUsers>& vUser) {
	char ans;
	cout << "Enter UserName : ";
	cin >> Userinfo.UserName;
	while (FindUserByUserName(Userinfo.UserName, Userinfo.Password, vUser, Userinfo)) {
		cout << "User with " << "[" << Userinfo.UserName << "]" << " already exists, ";
		cout << "Enter UserName : ";
		cin >> Userinfo.UserName;
	}
	cout << "Enter password : ";
	cin >> Userinfo.Password;
	Userinfo.Permisions = givepermissions();
	return Userinfo;
}
vector<string> SplitString(string S1, string Delim)
{
	vector<string> vString;
	short pos = 0;
	string sWord; // define a string variable
	// use find() function to get the position of the delimiters
	while ((pos = S1.find(Delim)) != std::string::npos)
	{
		sWord = S1.substr(0, pos); // store the word
		if (sWord != "")
		{
			vString.push_back(sWord);
		}
		S1.erase(0, pos + Delim.length());
	}
	if (S1 != "")
	{
		vString.push_back(S1); // it adds last word of the string.
	}
	return vString;
}

sClient ConvertLinetoRecord(string Line, string Seperator =
	"#//#")
{
	sClient Client;
	vector<string> vClientData;
	vClientData = SplitString(Line, Seperator);
	Client.AccountNumber = vClientData[0];
	Client.PinCode = vClientData[1];
	Client.Name = vClientData[2];
	Client.Phone = vClientData[3];
	Client.AccountBalance = stod(vClientData[4]);
	return Client;
}
sUsers ConvertLinetoRecord4User(string Line, string Seperator =
	"#//#")
{
	vector <string> vUser;
	sUsers Userinfo;
	vUser = SplitString(Line, Seperator);
	Userinfo.UserName = vUser[0];
	Userinfo.Password = vUser[1];
	Userinfo.Permisions = stoi(vUser[2]);
	return Userinfo;
}
string ConvertRecordToLine(sClient Client, string Seperator =
	"#//#")
{
	string stClientRecord = "";
	stClientRecord += Client.AccountNumber + Seperator;
	stClientRecord += Client.PinCode + Seperator;
	stClientRecord += Client.Name + Seperator;
	stClientRecord += Client.Phone + Seperator;
	stClientRecord += to_string(Client.AccountBalance);
	return stClientRecord;
}
string ConvertRecordToLine4User(sUsers Userinfo, string Seperator =
	"#//#")
{
	string stUserRecord = "";
	stUserRecord += Userinfo.UserName + Seperator;
	stUserRecord += Userinfo.Password + Seperator;
	stUserRecord += to_string(Userinfo.Permisions);
	return stUserRecord;
}
vector <sClient> LoadCleintsDataFromFile(string FileName)
{
	vector <sClient> vClients;
	fstream MyFile;
	MyFile.open(FileName, ios::in);//read Mode
	if (MyFile.is_open())
	{
		string Line;
		sClient Client;
		while (getline(MyFile, Line))
		{
			if (Line.empty())
				continue;
			Client = ConvertLinetoRecord(Line);
			vClients.push_back(Client);
		}
		MyFile.close();
	}
	return vClients;
}
vector <sUsers> LoadUsersDataFromFile(string FileName)
{
	vector <sUsers> vUser;
	fstream MyFile;
	MyFile.open(FileName, ios::in);//read Mode
	if (MyFile.is_open())
	{
		string Line;
		sUsers Userinfo;
		while (getline(MyFile, Line))
		{
			Userinfo = ConvertLinetoRecord4User(Line);
			vUser.push_back(Userinfo);
		}
		MyFile.close();
	}
	return vUser;
}
void PrintClientCard(sClient Client) {
	cout << "\nThe following are the client details:\n";
	cout << "\nAccout Number: " << Client.AccountNumber;
	cout << "\nPin Code : " << Client.PinCode;
	cout << "\nName : " << Client.Name;
	cout << "\nPhone : " << Client.Phone;
	cout << "\nAccount Balance: " << Client.AccountBalance;
}
void PrintUserCard(sUsers& Userinfo) {
	cout << "\nThe following are the User details:\n";
	cout << "\nUserName : " << Userinfo.UserName;
	cout << "\nPassword : " << Userinfo.Password;
	cout << "\nUser's Permissions : " << Userinfo.Permisions << endl;
}
bool FindClientByAccountNumber(string AccountNumber, vector
	<sClient> vClients, sClient& Client)
{
	for (sClient C : vClients)
	{
		if (C.AccountNumber == AccountNumber)
		{
			Client = C;
			return true;
		}
	}
	return false;
}
bool MarkClientForDeleteByAccountNumber(string AccountNumber,
	vector <sClient>& vClients)
{
	for (sClient& C : vClients)
	{
		if (C.AccountNumber == AccountNumber)
		{
			C.MarkForDelete = true;
			return true;
		}
	}
	return false;
}
bool MarkUserForDeleteByUserName(string UserName,
	vector <sUsers>& vUser)
{
	for (sUsers& C : vUser)
	{
		if (C.UserName == UserName)
		{
			C.MarkForDelete = true;
			return true;
		}
	}
	return false;
}
bool MarkClientForUpdateByAccountNumber(string AccountNumber,
	vector <sClient>& vClients)
{
	for (sClient& C : vClients)
	{
		if (C.AccountNumber == AccountNumber)
		{
			C.MarkForUpdate = true;
			return true;
		}
	}
	return false;
}
bool MarkUserForUpdateByUserName(string UserName,
	vector <sUsers>& vUser)
{
	for (sUsers& C : vUser)
	{
		if (C.UserName == UserName)
		{
			C.MarkForUpdate = true;
			return true;
		}
	}
	return false;
}
vector <sClient> SaveCleintsDataToFile(string FileName, vector
	<sClient> vClients)
{
	fstream MyFile;
	MyFile.open(FileName, ios::out);//overwrite
	string DataLine;
	if (MyFile.is_open())
	{
		for (sClient C : vClients)
		{
			if (!C.MarkForDelete)
			{
				//we only write records that are not marked for delete

				DataLine = ConvertRecordToLine(C);
				MyFile << DataLine << endl;
			}
		}
		MyFile.close();
	}
	return vClients;
}
vector <sUsers> SaveUserDataToFile(string FileName, vector
	<sUsers>& vUser)
{
	fstream MyFile;
	MyFile.open(FileName, ios::out);//overwrite
	string DataLine;
	if (MyFile.is_open())
	{
		for (sUsers C : vUser)
		{
			if (!C.MarkForDelete)
			{
				//we only write records that are not marked for delete

				DataLine = ConvertRecordToLine4User(C);
				MyFile << DataLine << endl;
			}
		}
		MyFile.close();
	}
	return vUser;
}
vector <sUsers> SaveUsersDataToFile(string FileName, vector
	<sUsers>& vUser)
{
	fstream MyFile;
	MyFile.open(FileName, ios::out);//overwrite
	string DataLine;
	if (MyFile.is_open())
	{
		for (sUsers C : vUser)
		{
			if (!C.MarkForDelete)
			{
				//we only write records that are not marked for delete

				DataLine = ConvertRecordToLine4User(C);
				MyFile << DataLine << endl;
			}
		}
		MyFile.close();
	}
	return vUser;
}
void addtofile(string S1, fstream& clientfile) {
	clientfile.open(ClientsFileName, ios::app);
	if (clientfile.is_open())
		clientfile << S1 << endl;
	clientfile.close();
}
void addtofile4User(string S1, fstream& UsersFile) {
	UsersFile.open(UsersFileName, ios::app);
	if (UsersFile.is_open())
		UsersFile << S1 << endl;
	UsersFile.close();
}
sClient UpdateClientData(string AccountNumber, vector <sClient>& vClients) {
	for (sClient& C : vClients)
	{
		if (C.AccountNumber == AccountNumber)
		{
			cout << "enter pincode : ";
			cin >> C.PinCode;
			cout << "enter name : ";
			cin.ignore();
			getline(cin, C.Name);
			cout << "enter phone : ";
			cin >> C.Phone;
			cout << "enter account balance : ";
			cin >> C.AccountBalance;
			return C;
		}
	}
	sClient NoClient;
	return NoClient;

}
sUsers UpdateUserData(string UserName, vector
	<sUsers>& vUser) {
	for (sUsers& C : vUser)
	{
		if (C.UserName == UserName)
		{
			cout << "Enter Password : ";
			cin >> C.Password;
			C.Permisions = givepermissions();
			return C;
		}
	}
	sUsers NoUser;
	return NoUser;

}
bool DeleteClientByAccountNumber(string AccountNumber, vector
	<sClient>& vClients)
{
	sClient Client;
	char Answer = 'n';
	if (FindClientByAccountNumber(AccountNumber, vClients,
		Client))
	{
		PrintClientCard(Client);
		cout << "\n\nAre you sure you want delete this client? y/n ? ";
		cin >> Answer;
		if (Answer == 'y' || Answer == 'Y')
		{
			MarkClientForDeleteByAccountNumber(AccountNumber,
				vClients);
			SaveCleintsDataToFile(ClientsFileName, vClients);
			//Refresh Clients
			vClients = LoadCleintsDataFromFile(ClientsFileName);
			cout << "\n\nClient Deleted Successfully.";
			return true;
		}
	}
	else
	{
		cout << "\nClient with Account Number (" << AccountNumber
			<< ") is Not Found!";
		return false;
	}
}
bool DeleteUsersByUserName(string UserName, vector
	<sUsers>& vUser)
{
	sUsers Userinfo;
	char Answer = 'n';
	if (FindUserByUserNameOnly(UserName, vUser,
		Userinfo))
	{
		PrintUserCard(Userinfo);
		cout << "\n\nAre you sure you want delete this User? y/n ? ";
		cin >> Answer;
		if (Answer == 'y' || Answer == 'Y')
		{
			MarkUserForDeleteByUserName(UserName, vUser);
			SaveUserDataToFile(UsersFileName, vUser);
			//Refresh Clients
			vUser = LoadUsersDataFromFile(UsersFileName);
			cout << "\nUser Deleted Successfully.";
			return true;
		}
	}
	else
	{
		cout << "\nUser with UserName (" << UserName
			<< ") is Not Found!\n";
		return false;
	}
}
bool UpdateClientByAccountNumber(string AccountNumber, vector
	<sClient>& vClients, sClient& newclientinfo)
{
	sClient Client;
	char Answer = 'n';
	if (FindClientByAccountNumber(AccountNumber, vClients,
		Client))
	{
		PrintClientCard(Client);
		cout << "\n\nAre you sure you want Update this client? y/n ? ";
		cin >> Answer;
		if (Answer == 'y' || Answer == 'Y')
		{
			MarkClientForUpdateByAccountNumber(AccountNumber,
				vClients);
			UpdateClientData(AccountNumber, vClients);
			SaveCleintsDataToFile(ClientsFileName, vClients);
			//Refresh Clients
			vClients = LoadCleintsDataFromFile(ClientsFileName);
			cout << "\n\nClient Updated Successfully.";
			return true;
		}
	}
	else
	{
		cout << "\nClient with Account Number (" << AccountNumber
			<< ") is Not Found!";
		return false;
	}
}
bool UpdateUserByUserName(string UserName, vector
	<sUsers>& vUser, sUsers& Userinfo)
{
	sUsers TargetUser;
	sUsers User;
	char Answer = 'n';
	if (FindUserByUserNameOnly(UserName, vUser,
		TargetUser))
	{
		PrintUserCard(TargetUser);
		cout << "\n\nAre you sure you want Update this user? y/n ? ";
		cin >> Answer;
		if (Answer == 'y' || Answer == 'Y')
		{
			MarkUserForUpdateByUserName(UserName,
				vUser);
			UpdateUserData(UserName, vUser);
			SaveUserDataToFile(UsersFileName, vUser);
			vUser = LoadUsersDataFromFile(UsersFileName);
			cout << "\n\User Updated Successfully.";
			return true;
		}
	}
	else
	{
		cout << "\User with UserName (" << UserName
			<< ") is Not Found!";
		return false;
	}
}
string ReadClientAccountNumber()
{
	string AccountNumber = "";
	cout << "\nPlease enter AccountNumber? ";
	cin >> AccountNumber;
	return AccountNumber;
}
void showclientfile(int clientnum, vector<sClient>& vClients) {
	cout << setw(32) << "Client List(" << clientnum << ") Client(s)." << endl;
	cout << "---------------------------------------------------------------------------------\n";
	cout << "| " << setw(15) << "Account Number " << "| " << setw(15) << "PIN Code " << "| " << setw(20) << "Client Name " << "| " << setw(15) << "Phone " << "| " << setw(15) << "balance" << endl;
	cout << "---------------------------------------------------------------------------------\n";
	for (sClient& client : vClients) {
		cout << "| " << setw(15) << client.AccountNumber << "| " << setw(15) << client.PinCode << "| " << setw(20) << client.Name << "| " << setw(15) << client.Phone << "| " << setw(15) << client.AccountBalance << endl;
	}

}
void showuserfile(int usernum, vector <sUsers>& vUser) {
	cout << setw(32) << "User List(" << usernum << ") User(s)." << endl;
	cout << "---------------------------------------------------------------------------------\n";
	cout << "| " << setw(15) << "UserName " << "| " << setw(15) << "Password " << "| " << setw(20) << "Permissions " << endl;
	cout << "---------------------------------------------------------------------------------\n";
	for (sUsers& user : vUser) {
		cout << "| " << setw(15) << user.UserName << "| " << setw(15) << user.Password << "| " << setw(20) << user.Permisions << endl;
	}
}
void showoperation() {
	cout << "[1] Show Client List.\n";
	cout << "[2] Add New Client.\n";
	cout << "[3] Delete Client.\n";
	cout << "[4] Update Client Info.\n";
	cout << "[5] Find Client.\n";
	cout << "[6] Transactions.\n";
	cout << "[7] Manage Users.\n";
	cout << "[8] Exit.\n";
}
void AddNewClient(sClient& clientinfo, vector<sClient>& vBank, fstream& clientfile, vector<sClient>& vClients) {
	string ans = "";
	do {
		AddClientInfo(clientinfo);
		string S1 = "";
		S1 = ConvertRecordToLine(clientinfo);
		addtofile(S1, clientfile);
		vClients = LoadCleintsDataFromFile(ClientsFileName);
		cout << "Client Added Successfully , do you want to add more clients? (yes/no)\n";
		cin >> ans;
	} while (ans == "yes");
}
void AddNewUser(sUsers& NewUserInfo, fstream& userfile, vector <sUsers>& vUser) {
	string ans = "";
	do {
		AddUserInfo(NewUserInfo, vUser);
		string S1 = "";
		S1 = ConvertRecordToLine4User(NewUserInfo);
		addtofile4User(S1, userfile);
		vUser = LoadUsersDataFromFile(UsersFileName);
		cout << "User Added Successfully , do you want to add more Users? (yes/no)\n";
		cin >> ans;
	} while (ans == "yes");
}
int showtranactions() {
	int select;
	cout << "====================================================\n";
	cout << setw(25) << "Tranactions Menue Screen\n";
	cout << "====================================================\n";
	cout << "[1] Deposit.\n";
	cout << "[2] Withdraw.\n";
	cout << "[3] Total Balances.\n";
	cout << "[4] Main Menu.\n";
	cout << "====================================================\n";
	cout << "Choose What do you want to do? ";
	cin >> select;
	return select;
}
int showusersui() {
	int select;
	cout << "====================================================\n";
	cout << setw(25) << "Manage Users Menue Screen\n";
	cout << "====================================================\n";
	cout << "[1] List Users.\n";
	cout << "[2] Add New User.\n";
	cout << "[3] Delete User.\n";
	cout << "[4] Update User.\n";
	cout << "[5] Find User.\n";
	cout << "[6] Main Menue.\n";
	cout << "====================================================\n";
	cout << "Choose What do you want to do? ";
	cin >> select;
	return select;
}
void Deposit(vector<sClient>& vClients, sClient& Client) {
	string AccountNumber;
	cout << "====================================================\n";
	cout << setw(25) << "Deposit Screen\n";
	cout << "====================================================\n\n";
	do {
		cout << "Please Enter Account Number : ";
		cin >> AccountNumber;
	} while (!(FindClientByAccountNumber(AccountNumber, vClients, Client)));
	PrintClientCard(Client);
	int Deposit;
	char Answer;
	cout << "\nEnter Deposit Ammount ? ";
	cin >> Deposit;
	cout << "\nAre you sure you want perform this transaction? y/n? ";
	cin >> Answer;
	if (Answer == 'y' || Answer == 'Y') {
		for (sClient& C : vClients) {
			if (C.AccountNumber == AccountNumber) {
				C.AccountBalance += Deposit;
				Client = C;
			}
		}
		SaveCleintsDataToFile(ClientsFileName, vClients);
		cout << "Done Successfully New Balance Is : " << Client.AccountBalance << endl;
	}
	else {
		system("cls");
		showtranactions();
	}
}
void Withdraw(vector<sClient>& vClients, sClient& Client) {
	string AccountNumber;
	cout << "====================================================\n";
	cout << setw(25) << "Withdraw Screen\n";
	cout << "====================================================\n\n";
	do {
		cout << "Please Enter Account Number : ";
		cin >> AccountNumber;
	} while (!(FindClientByAccountNumber(AccountNumber, vClients, Client)));
	PrintClientCard(Client);
	int Withdraw;
	char Answer;
	cout << "\nEnter Withdraw Ammount ? ";
	cin >> Withdraw;
	cout << "\nAre you sure you want perform this transaction? y/n? ";
	cin >> Answer;
	if ((Answer == 'y' || Answer == 'Y') && (Withdraw <= Client.AccountBalance)) {
		for (sClient& C : vClients) {
			if (C.AccountNumber == AccountNumber) {
				C.AccountBalance -= Withdraw;
				Client = C;
			}
		}
		SaveCleintsDataToFile(ClientsFileName, vClients);
		cout << "Done Successfully New Balance Is : " << Client.AccountBalance << endl;

	}
	else
		showtranactions();

}
void TotalBalances(int clientnum, vector<sClient>& vClients) {
	int totalbalances = 0;
	cout << setw(32) << "Balances List(" << clientnum << ") Client(s)." << endl;
	cout << "---------------------------------------------------------------------------------\n";
	cout << "| " << setw(25) << "Account Number " << "| " << setw(25) << "Client Name " << "| " << setw(25) << "Balance " << endl;
	cout << "---------------------------------------------------------------------------------\n";
	for (sClient& client : vClients) {
		cout << "| " << setw(25) << client.AccountNumber << "| " << setw(25) << client.Name << "| " << setw(25) << client.AccountBalance << endl;
		totalbalances += client.AccountBalance;
	}
	cout << "\n---------------------------------------------------------------------------------\n";
	cout << setw(25) << "Total Balances = " << totalbalances << endl;
}
void tranactionsoperations(int select, vector<sClient>& vClients, int clientsnum, sClient& Client) {
	switch (select) {
	case 1: {
		system("cls");
		Deposit(vClients, Client);
		cout << "Press any key to return to the previous page...";
		PressAnyKeyToContinue();
		break;
	}
	case 2: {
		system("cls");
		Withdraw(vClients, Client);
		cout << "Press any key to return to the previous page...";
		PressAnyKeyToContinue();
		break;
	}
	case 3: {
		system("cls");
		TotalBalances(clientsnum, vClients);
		cout << "Press any key to return to the previous page...";
		PressAnyKeyToContinue();
		break;
	}
	case 4: {
		break;
	}
	}
}
void SwitchUserOperations(int selection, int usernum, vector <sUsers>& vUser, sUsers& Userinfo, fstream& userfile) {
	switch (selection) {
	case 1: {
		system("cls");
		showuserfile(usernum, vUser);
		cout << "\nPress any key to return to main page...";
		PressAnyKeyToContinue();
		break;
	}
	case 2: {
		system("cls");
		sUsers NewUserInfo;
		AddNewUser(NewUserInfo, userfile, vUser);
		cout << "Press any key to return to main page...";
		PressAnyKeyToContinue();
		break;
	}case 3: {
		system("cls");
		string UserName;
		cout << "Enter UserName To Delete\n";
		cin >> UserName;
		DeleteUsersByUserName(UserName, vUser);
		cout << "Press any key to return to main page...";
		PressAnyKeyToContinue();
		break;
	}
	case 4: {
		system("cls");
		string Username;
		cout << "Enter User to Update : ";
		cin >> Username;
		UpdateUserByUserName(Username, vUser, Userinfo);
		cout << "\nPress any key to return to main page...";
		PressAnyKeyToContinue();
		break;
	}
	case 5: {
		system("cls");
		string Username, Password;
		cout << "Enter Username to Find : ";
		cin >> Username;
		cout << endl;
		cout << "Enter Password of (" << Username << ") : ";
		cin >> Password;
		sUsers FoundUser;
		if (FindUserByUserName(Username, Password, vUser, FoundUser))
			PrintUserCard(FoundUser);
		else
			cout << "User Not Found\n";
		cout << "Press any key to return to main page...";
		PressAnyKeyToContinue();
		break;
	}
	case 6: {
		system("cls");
		cout << "Press any key to return to main page...";
		PressAnyKeyToContinue();
		break;
	}
	}
}
sUsers Login(sUsers& Userinfo)
{
	cout << "Enter Username? ";
	cin >> Userinfo.UserName;
	cout << "\nEnter Password? ";
	cin >> Userinfo.Password;
	return Userinfo;
}
void switchoperation(int selection, vector<sClient>& vClients, int clientsnum, sClient& newclientinfo
	, vector<sClient>& vBank, fstream& clientfile, sClient& Client, int usernum,
	vector <sUsers>& vUser, sUsers& Userinfo, fstream& userfile) {
	switch (selection) {
	case 1: {
		system("cls");
		if (HasPermission(Userinfo.Permisions, pShowClients)) {
			showclientfile(clientsnum, vClients);
		}
		else {
			cout << "Access Denied !\n";
		}
		cout << "Press any key to return to the main page...";
		PressAnyKeyToContinue();

		break;
	}
	case 2: {
		system("cls");
		if (HasPermission(Userinfo.Permisions, pAddClient)) {
			AddNewClient(newclientinfo, vBank, clientfile, vClients);
		}
		else {
			cout << "Access Denied !\n";
		}
		cout << "Press any key to return to the main page...";
		PressAnyKeyToContinue();

		break;
	}
	case 3: {
		system("cls");
		if (HasPermission(Userinfo.Permisions, pDeleteClient)) {
			string AccountNumber;
			cout << "Enter Account Number To Delete\n";
			cin >> AccountNumber;
			DeleteClientByAccountNumber(AccountNumber, vClients);
		}
		else {
			cout << "Access Denied !\n";
		}
		cout << "Press any key to return to the main page...";
		PressAnyKeyToContinue();
		break;
	}
	case 4: {
		system("cls");
		if (HasPermission(Userinfo.Permisions, pUpdateClient))
		{
			string AccountNumber;
			cout << "Enter Account Number To Update\n";
			cin >> AccountNumber;
			UpdateClientByAccountNumber(AccountNumber, vClients, newclientinfo);
		}
		else {
			cout << "Access Denied !\n";
		}
		cout << "\nPress any key to return to the main page...";
		PressAnyKeyToContinue();
		break;
	}
	case 5: {
		system("cls");
		if (HasPermission(Userinfo.Permisions, pFindClient)) {
			string AccountNumber;
			cout << "Enter Account Number To Find\n";
			cin >> AccountNumber;
			if (FindClientByAccountNumber(AccountNumber, vClients, Client)) {
				PrintClientCard(Client);
			}
			else
				cout << "Client Not Found\n";
		}
		else {
			cout << "\nAccess Denied !\n";
		}
		cout << "\nPress any key to return to the main page...";
		PressAnyKeyToContinue();

		break;
	}
	case 6: {
		system("cls");
		if (HasPermission(Userinfo.Permisions, pTransactions)) {
			int select = showtranactions();
			tranactionsoperations(select, vClients, clientsnum, Client);
		}
		else {
			cout << "\nAccess Denied !\n";
			cout << "\nPress any key to return to the main page...";
			PressAnyKeyToContinue();
		}
		break;
	}
	case 7: {
		system("cls");
		if (HasPermission(Userinfo.Permisions, pManageUsers)) {
			int selection = showusersui();
			SwitchUserOperations(selection, usernum, vUser, Userinfo, userfile);
		}
		else {
			cout << "Access Denied !\n";
			cout << "Press any key to return to the main page...";
			PressAnyKeyToContinue();
		}
		break;
	}
	case 8:
		break;
	}
}
bool Loginscreen(sUsers& Userinfo, vector <sUsers>& vUser)
{
	cout << "====================================================\n";
	cout << setw(25) << "Login Screen\n";
	cout << "====================================================\n";
	Login(Userinfo);
	while (!FindUserByUserName(Userinfo.UserName, Userinfo.Password, vUser, Userinfo)) {
		cout << "Invalid UserName/Password\n";
		Login(Userinfo);
	}
	return true;
}
int main()
{
	sClient Client;
	fstream clientfile;
	fstream userfile;
	vector<sClient> vBank;
	sClient newclientinfo;
	vector<sClient> vClients;
	vector <sUsers> vUser;
	sUsers Userinfo;
	int selection = 0;
	vUser = LoadUsersDataFromFile(UsersFileName);
	if (Loginscreen(Userinfo, vUser)) {
		while (selection >= 0)
		{
			system("cls");
			vClients = LoadCleintsDataFromFile(ClientsFileName);
			int clientsnum = vClients.size();
			int usernum = vUser.size();
			cout << "====================================================\n";
			cout << setw(25) << "Main Menue Screen\n";
			cout << "====================================================\n";
			showoperation(); //show all operations to select
			cout << "====================================================\n";
			cout << "Choose What do you want to do? ";
			cin >> selection;
			if (selection == 8)
				break;

			switchoperation(selection, vClients, vClients.size(),
				newclientinfo, vBank, clientfile, Client, usernum, vUser, Userinfo, userfile);
		}
	}
	return 0;
}