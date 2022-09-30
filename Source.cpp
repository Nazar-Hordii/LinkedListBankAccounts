#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <windows.h>
#include <cstdlib>
#include <ctime>
#include <conio.h>
using namespace std;

struct Account {
	string Username;
	long Accno;
	string Pin;
	int Balance;
	Account *next;
};
int noOfAccounts = 0;
Account *temp = NULL;
struct list {
	Account *head = NULL;

	bool login(string u, string p)
	{
		if (u == "Faizan Zaheer" || u == "faizan zaheer" && p == "123456")
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	void newAccount()
	{
		system("cls");
		system("Color 1A");
		ofstream outFile("Accounts.txt", ios::app);
		Account *acc = new Account;
		cout << "Enter Username: ";
		cin.ignore();
		getline(cin, acc->Username);
		cout << "Enter Pin Code: ";
		getline(cin, acc->Pin);
		cout << "Enter Balance Rs. (must be atleast 10000):";
		cin >> acc->Balance;
		acc->Accno = 10000 + rand() % 99999;
		if (acc->Balance < 10000)
		{
			cout << "Insufficient Balance to Open Account!\n";
		}
		else
		{
			if (head == NULL)
			{
				head = acc;
				acc->next = NULL;
				noOfAccounts++;
			}
			else
			{
				temp = head;
				while (temp->next != NULL)
				{
					temp = temp->next;
				}
				temp->next = acc;
				acc->next = NULL;
				noOfAccounts++;
			}
			if (outFile.is_open())
			{
				outFile << "\n"<< acc->Username<< "    "<< acc->Pin<< "     "<< acc->Accno<< "        "<< acc->Balance<< endl;
				Sleep(1500);
				cout << "Account No.: "<< acc->Accno << endl;
				Sleep(500);
				cout << "Account has been created.\n";
			}
			else
			{
				cout << "Cannot open Balances File!\n";
			}
		}
		outFile.close();
	}
	Account* Search(string name, string p, long no)
	{
		bool isFound = false;
		temp = head;
		while(temp->next != NULL)
		{
			if (temp->Username == name)
			{
				if (temp->Pin == p)
				{
					if (temp->Accno == no)
					{
						isFound = true;
						break;
					}
				}
			}
			else
			{
				temp = temp->next;
			}
		}
		if (isFound == true)
		{
			return temp;
		}
		else
		{
			return NULL;
		}
	}
	void Display()
	{
		system("cls");
		system("Color 2F");
		string data;
		Account *acc = new Account;
		cout << "Enter Username: ";
		cin.ignore();
		getline(cin, acc->Username);
		cout << "Enter Pin Code: ";
		cin.ignore();
		getline(cin, acc->Pin);
		cout << "Enter Account No.: ";
		cin >> acc->Accno;
		stringstream stream;
		stream << acc->Accno;
		string c = stream.str();
		ifstream inFile("Accounts.txt", ios::in);
		if (inFile.is_open())
		{
			while (!inFile.eof())
			{
				getline(inFile, data);
				if (data.find(acc->Username, 0) != string::npos)
				{
					if (data.find(acc->Pin, 0) != string::npos)
					{
						if (data.find(c, 0) != string::npos)
						{
							cout << "Processing...";
							Sleep(2000);
							cout << "\nUsername\t  Pin\tAccount No.\tBalance\n";
							cout << data << "\n\n";
							break;
						}
						else
						{
							cout << "Account NOT FOUND!\n";
							break;
						}
					}
				}
			}
		}
		else
		{
			cout << "Cannot open Balance File!\n";
		}
		inFile.close();
	}
	void displayAll()
	{
		ifstream inFile("Accounts.txt", ios::in);
		system("cls");
		system("Color 4D");
		cout << "READGING FILE...\n";
		Sleep(2500);
		string data;
		cout << "Username\tPin\tAccount No.\tBalance\n";
		if (inFile.is_open())
		{
			while (!inFile.eof())
			{
				getline(inFile, data);
				cout << data << endl;
			}
		}
		else
		{
			cout << "Cannot open Balance File!\n";
		}
		cout << endl;
		inFile.close();
	}
	char* currentTime()
	{
		time_t now = time(0);
		time_t r = time(0);
		char* dt = ctime(&now);
		char* rt = ctime(&r);
		tm *gmtm = gmtime(&now);
		return dt;
	}
	void Withdraw()
	{
		system("cls");
		system("Color 5E");
		ifstream inFile("Accounts.txt", ios::in);
		ofstream tempFile("temp.txt", ios::out);
		string data;
		Account *acc = new Account;
		int c;
		cout << "Enter Username: ";
		cin.ignore();
		getline(cin, acc->Username);
		cout << "Enter Pin Code: ";
		getline(cin, acc->Pin);
		cout << "Enter Account No.: ";
		cin >> acc->Accno;
		stringstream stream;
		stream << acc->Accno;
		string d = stream.str();
		if (inFile.is_open())
		{
			while (!inFile.eof())
			{
				getline(inFile, data);
				if (data.find(acc->Username, 0) != string::npos)
				{
					if (data.find(acc->Pin, 0) != string::npos)
					{
						if (data.find(d, 0) != string::npos)
						{
							d = data.substr(acc->Username.size() + 26, data.size());
							Sleep(1500);
							cout << "Available Balance = Rs. " << d << endl;
							cout << "Enter Amount to Withdraw (Limit = Rs. 25000): ";
							cin >> c;
							acc->Balance = atoi(d.c_str());
							cout << "Processing...\n";
							Sleep(2000);
							if (c > acc->Balance)
							{
								cout << "Insufficient Balance!\n";
								break;
							}
							else if (acc->Balance > 25000)
							{
								cout << "Over The Limit!\n";
							}
							else
							{
								acc->Balance = acc->Balance - c;
								cout << "New Balance = Rs. " << acc->Balance << endl;
								cout << "Transaction Done at : " << currentTime() << endl;
								break;
							}
						}
					}
					else
					{
						cout << "Account NOT FOUND!\n";
						break;
					}
				}
			}
		}
		if (tempFile.is_open())
		{
			if (inFile.is_open())
			{
				while (!inFile.eof())
				{
					getline(inFile, data);
					if (data.find(acc->Username, 0) == string::npos)
					{
						tempFile << data << endl;
					}
					tempFile << acc->Username << "    " << acc->Pin << "     " << acc->Accno << "        " << acc->Balance << endl;
				}
			}
		}
		inFile.close();
		tempFile.close();
		remove("Accounts.txt");
		rename("temp.txt", "Accounts.txt");
	}
	void Deposit()
	{
		system("cls");
		system("Color 6F");
		ifstream inFile("Accounts.txt", ios::in);
		ofstream tempFile("temp.txt", ios::out);
		string data;
		Account *acc = new Account;
		int c;
		cout << "Enter Username: ";
		cin.ignore();
		getline(cin, acc->Username);
		cout << "Enter Pin Code: ";
		getline(cin, acc->Pin);
		cout << "Enter Account No.: ";
		cin >> acc->Accno;
		stringstream stream;
		stream << acc->Accno;
		string d = stream.str();
		if (inFile.is_open())
		{
			while (!inFile.eof())
			{
				getline(inFile, data);
				if (data.find(acc->Username, 0) != string::npos)
				{
					if (data.find(acc->Pin, 0) != string::npos)
					{
						if (data.find(d, 0) != string::npos)
						{
							d = data.substr(acc->Username.size() + 26, data.size());
							Sleep(1500);
							cout << "Available Balance = Rs. " << d << endl;
							cout << "Enter Amount to Deposit: ";
							cin >> c;
							acc->Balance = atoi(d.c_str());
							cout << "Processing...\n";
							Sleep(2000);
							acc->Balance = acc->Balance + c;
							cout << "New Balance = Rs. " << acc->Balance << endl;
							cout << "Transaction Done at : " << currentTime() << endl;
							break;
						}
					}
					else
					{
						cout << "Account NOT FOUND!\n";
						break;
					}
				}
			}
		}
		if (tempFile.is_open())
		{
			if (inFile.is_open())
			{
				while (!inFile.eof())
				{
					getline(inFile, data);
					if (data.find(acc->Username, 0) == string::npos)
					{
						tempFile << data << endl;
					}
					tempFile << acc->Username << "    " << acc->Pin << "     " << acc->Accno << "        " << acc->Balance << endl;
				}
			}
		}
		inFile.close();
		tempFile.close();
		remove("Accounts.txt");
		rename("temp.txt", "Accounts.txt");
	}
	void Remove()
	{
		system("cls");
		system("Color 1A");
		ifstream inFile("Accounts.txt", ios::in);
		ofstream tempFile("temp.txt", ios::out);
		string data;
		Account *acc = new Account;
		int c;
		cout << "Enter Details of Account to Delete:\n";
		cout << "Enter Username: ";
		cin.ignore();
		getline(cin, acc->Username);
		cout << "Enter Pin Code: ";
		getline(cin, acc->Pin);
		cout << "Enter Account No.: ";
		cin >> acc->Accno;
		stringstream stream;
		stream << acc->Accno;
		string d = stream.str();
		if (inFile.is_open())
		{
			while (!inFile.eof())
			{
				getline(inFile, data);
				if (tempFile.is_open())
				{
					if (data.find(acc->Username, 0) == string::npos)
					{
						tempFile << data << endl;
					}
				}
				else
				{
					cout << "Account NOT FOUND!\n";
					break;
				}
			}
		}
		else
		{
			cout << "Cannot open Accounts File!\n";
		}
		inFile.close();
		tempFile.close();
		remove("Accounts.txt");
		rename("temp.txt", "Accounts.txt");
	}
};
void menu()
{
	system("Color 1A");
	cout << "\n\t\t******************* Main Menu ABCD ATM *****************************\n";
	cout << "\t\t*\t\t1. CREATE NEW ACCOUNT                              *\n\n";
	cout << "\t\t*\t\t2. DISPLAY DETAILS OF AN ACCOUNT                   *\n\n";
	cout << "\t\t*\t\t3. DISPLAY ALL ACCOUNTS                            *\n\n";
	cout << "\t\t*\t\t4. WITHDRAW CASH FROM AN ACCOUNT                   *\n\n";
	cout << "\t\t*\t\t5. DEPOSIT CASH INTO AN ACCOUNT                    *\n\n";
	cout << "\t\t*\t\t6. REMOVE AN ACCOUNT                               *\n\n";
	cout << "\t\t*\t\t7. EXIT SYSTEM                                     *\n";
	cout << "\t\t********************************************************************\n";
}
int main()
{
	int ch = 0;
	list l;
	cout << "---------------- WELCOME TO ABCD BANK -----------------\n";
	cout << "\t\tAdmin LOGIN\n";
	string a, b;
	cout << "\t\tEnter Username: ";
	getline(cin, a);
	cout << "\t\tEnter Password: ";
	char c;
	for (int i = 0; i<100; i++)
	{
		c = _getch();
		if (c == '\r')
			break;
		cout << "*";
		b = b + c;
	}
	cout << endl;
	bool flag = l.login(a, b);
	if (flag == true)
	{
		cout << "\t\tLOGIN SUCCESSFUL!\n";
		cout << "-------------------------------------------------------\n";
		Sleep(2500);
		system("cls");
		menu();
		while (ch != 7)
		{
			cout << "\t\tEnter choice: ";
			cin >> ch;
			if (ch == 1)
			{
				cout << "\t\tProcessing...";
				Sleep(1500);
				l.newAccount();
				system("pause");
				Sleep(1500);
				system("cls");
				menu();
			}
			else if (ch == 2)
			{
				cout << "\t\tProcessing...";
				Sleep(1500);
				l.Display();
				system("pause");
				Sleep(1500);
				system("cls");
				menu();
			}
			else if (ch == 3)
			{
				cout << "\t\tProcessing...";
				Sleep(1500);
				l.displayAll();
				system("pause");
				Sleep(1500);
				system("cls");
				menu();
			}
			else if (ch == 4)
			{
				cout << "\t\tProcessing...";
				Sleep(1500);
				l.Withdraw();
				system("pause");
				Sleep(1500);
				system("cls");
				menu();
			}
			else if (ch == 5)
			{
				cout << "\t\tProcessing...";
				Sleep(1500);
				l.Deposit();
				system("pause");
				Sleep(1500);
				system("cls");
				menu();
			}
			else if (ch == 6)
			{
				cout << "\t\tProcessing...";
				Sleep(1500);
				l.Remove();
				system("pause");
				Sleep(1500);
				system("cls");
				menu();
			}
		}
		if (ch == 7)
		{
			cout << "\t\tExiting System.....\n\t\t";
			Sleep(1500);
		}
	}
	else
	{
		cout << "\t\tWrong Username or Password!\n";
		cout << "-------------------------------------------------------\n\t\t";
	}
	system("pause");
	return 0;
}
