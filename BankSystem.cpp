#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
using namespace std;
const string ClientsFileName = "Clients.txt";
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
			Client = ConvertLinetoRecord(Line);
			vClients.push_back(Client);
		}
		MyFile.close();
	}
	return vClients;
}
void PrintClientCard(sClient Client) {
	cout << "\nThe following are the client details:\n";
	cout << "\nAccout Number: " << Client.AccountNumber;
	cout << "\nPin Code : " << Client.PinCode;
	cout << "\nName : " << Client.Name;
	cout << "\nPhone : " << Client.Phone;
	cout << "\nAccount Balance: " << Client.AccountBalance<<endl;
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
void addtofile(string S1, fstream& clientfile) {
	clientfile.open(ClientsFileName, ios::app);
	if (clientfile.is_open())
		clientfile << S1 << endl;
	clientfile.close();
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
			cout << "\n\nClient Deleted Successfully."<<endl;
			return true;
		}
	}
	else
	{
		cout << "\nClient with Account Number (" << AccountNumber
			<< ") is Not Found!"<<endl;
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
string ReadClientAccountNumber()
{
	string AccountNumber = "";
	cout << "\nPlease enter AccountNumber? ";
	cin >> AccountNumber;
	return AccountNumber;
}
void showfile(int clientnum, vector<sClient>& vClients) {
	cout << setw(32) << "Client List(" << clientnum << ") Client(s)." << endl;
	cout << "---------------------------------------------------------------------------------\n";
	cout << "| " << setw(15) << "Account Number " << "| " << setw(15) << "PIN Code " << "| " << setw(20) << "Client Name " << "| " << setw(15) << "Phone " << "| " << setw(15) << "balance" << endl;
	cout << "---------------------------------------------------------------------------------\n";
	for (sClient& client : vClients) {
		cout << "| " << setw(15) << client.AccountNumber << "| " << setw(15) << client.PinCode << "| " << setw(20) << client.Name << "| " << setw(15) << client.Phone << "| " << setw(15) << client.AccountBalance << endl;
	}

}
void showoperation() {
	cout << "[1] Show Client List.\n";
	cout << "[2] Add New Client.\n";
	cout << "[3] Delete Client.\n";
	cout << "[4] Update Client Info.\n";
	cout << "[5] Find Client.\n";
	cout << "[6] Transactions.\n";
	cout << "[7] Exit.\n";
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
int showtranactions() {
	int select;
	cout << "====================================================\n";
	cout << setw(25) << "Tranactions Menu Screen\n";
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
	else
	{
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
	else {
		system("cls");
		showtranactions();
	}

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
		cout << "Press any key to return to the Main Menu page...";
		system("pause > nul");
		break;
	}
	case 2: {
		system("cls");
		Withdraw(vClients, Client);
		cout << "Press any key to return to the Main Menu page...";
		system("pause > nul");
		break;
	}
	case 3: {
		system("cls");
		TotalBalances(clientsnum, vClients);
		cout << "Press any key to return to the Main Menu page...";
		system("pause > nul");
		break;
	}
	case 4: {
		break;
	}
	}
}
void switchoperation(int selection, vector<sClient>& vClients, int clientsnum, sClient& newclientinfo, vector<sClient>& vBank, fstream& clientfile, sClient& Client) {
	switch (selection) {
	case 1: {
		system("cls");
		showfile(clientsnum, vClients);
		cout << "Press any key to return to the Main Menu page...";
		system("pause > nul");
		break;
	}
	case 2: {
		system("cls");
		AddNewClient(newclientinfo, vBank, clientfile, vClients);
		cout << "Press any key to return to the Main Menu page...";
		system("pause > nul");
		break;
	}
	case 3: {
		system("cls");
		string AccountNumber;
		cout << "Enter Account Number To Delete\n";
		cin >> AccountNumber;
		DeleteClientByAccountNumber(AccountNumber, vClients);
		cout << "Press any key to return to the Main Menu page...";
		system("pause > nul");
		break;
	}
	case 4: {
		system("cls");
		string AccountNumber;
		cout << "Enter Account Number To Update\n";
		cin >> AccountNumber;
		UpdateClientByAccountNumber(AccountNumber, vClients, newclientinfo);
		cout << "Press any key to return to the Main Menu page...";
		system("pause > nul");
		break;
	}
	case 5: {
		system("cls");
		string AccountNumber;
		cout << "Enter Account Number To Find\n";
		cin >> AccountNumber;
		if (FindClientByAccountNumber(AccountNumber, vClients, Client)) {
			PrintClientCard(Client);

		}
		else
			cout << "Client Not Found\n";
		cout << "Press any key to return to the Main Menu page...";
		system("pause > nul");
		break;
	}
	case 6: {
		system("cls");
		int select = showtranactions();
		tranactionsoperations(select, vClients, clientsnum, Client);
	}
	case 7:
		break;
	}
}
int main()
{
	sClient Client;
	fstream clientfile;
	vector<sClient> vBank;
	sClient newclientinfo;
	vector<sClient> vClients;
	int selection=0;

	while (selection>=0)
	{
		system("cls");
		vClients = LoadCleintsDataFromFile(ClientsFileName);
		int clientsnum = vClients.size();
		cout << "====================================================\n";
		cout << setw(25) << "Main Menu Screen\n";
		cout << "====================================================\n";
		showoperation(); //show all operations to select
		cout << "====================================================\n";
		cout << "Choose What do you want to do? ";
		cin >> selection;
		if (selection == 7)
			break;

		switchoperation(selection, vClients, vClients.size(),
			newclientinfo, vBank, clientfile, Client);
	}
	return 0;
}