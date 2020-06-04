//Client
#pragma comment(lib, "ws2_32.lib")
#include <winsock2.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <conio.h>
#include <exception>
#include <string>
#include <iomanip>

#define BUFF 512
#pragma warning(disable: 4996)
SOCKET Connection;
using namespace std;

void term_func();

class Client {
protected:
	char name[BUFF];
	char surname[BUFF];
	char login[BUFF];
	char password[BUFF];
public:
	Client() {
		std::strncpy(this->name, "", sizeof(this->name));
		std::strncpy(this->surname, "", sizeof(this->surname));
		std::strncpy(this->login, "", sizeof(this->login));
		std::strncpy(this->password, "", sizeof(this->password));
	};
	void addBakery();
	void addClient(char name[BUFF], char surname[BUFF], char login[BUFF], char password[BUFF]) {
		std::strncpy(this->name, name, sizeof(this->name));
		std::strncpy(this->surname, surname, sizeof(this->surname));
		std::strncpy(this->login, login, sizeof(this->login));
		std::strncpy(this->password, password, sizeof(this->password));
	}
	void editBakery();
	void delBakery();
	void changePass(char pass[BUFF]) {
		strncpy(this->password, pass, sizeof(this->password));
	}
	string getName() {
		return string(name);
	};
	string getSurname() {
		return string(surname);
	};
	string getLogin() {
		return string(login);
	};
	string getPass() {
		return string(password);
	};
	string getInfo() {
		string result;
		result += string(login) + " " + string(password) + " " + string(name) + " " + string(surname);
		return result;
	}
};


class Admin : public Client {
public:
	Admin() {
		std::strncpy(this->login, "", sizeof(this->login));
		std::strncpy(this->password, "", sizeof(this->password));
	}
	void setAutorisation(const char login[BUFF], const char password[BUFF]) {
		std::strncpy(this->login, login, sizeof(this->login));
		std::strncpy(this->password, password, sizeof(this->password));
	}
	void setMarks();
	void calculate();
	void addClient();
	void generateReport();
};

class Service {
private:
	string name;
	double expenses;// ������� �� ������
	double perInterest;// ������� ������������������ ������������ ���� �����
	double profit; // �������
	int countEmployee; // ���������� �����������
public:
	Service(string name) {
		this->name = name;
	};
	void setExpenses(double expenses) {
		this->expenses = expenses;
	}
	void setPerInterest(double perInterest) {
		this->perInterest = perInterest;
	}
	void setProfit(double profit) {
		this->profit = profit;
	}
	void setCountEmployee(int count) {
		this->countEmployee = count;
	}
	string getName() {
		return name;
	}
	string getInfo() {
		string result;
		result += to_string(expenses) + " " + to_string(perInterest) + " "
			+ to_string(profit) + " " + to_string(countEmployee);
		return result;
	}
	void getInfoInTable(int id) {
		cout << setw(1) << "|" << setw(4) << id << setw(1) << "|" <<
			setw(45) << this->name << setw(1) << "|" <<
			setw(8) << this->expenses << setw(1) << "|" <<
			setw(25) << this->perInterest << setw(1) << "|" <<
			setw(8) << this->profit << setw(1) << "|" <<
			setw(20) << this->countEmployee << setw(1) << "|";
	}
	void getInfoInWholeTable(int id) {
		cout << setw(110) << setfill('=') << "=" << endl;
		cout << setfill(' ');
		cout << setw(1) << "|" << setw(4) << "id" << setw(1) << "|" <<
			setw(67) << "�������� ������" << setw(1) << "|" <<
			setw(2) << "�������" << setw(1) << "|" <<
			setw(25) << "������� ����������������" << setw(1) << "|" <<
			setw(8) << "�������" << setw(1) << "|" <<
			setw(9) << "���������� �������" << setw(1) << "|" << endl;
		cout << setw(110) << setfill('=') << "=" << endl;
		cout << setfill(' ');
		this->getInfoInTable(id);
		cout << endl;
		cout << setw(110) << setfill('=') << "=" << endl;
		cout << setfill(' ');
	}
	string getExpenses() {
		return to_string(this->expenses);
	}
	string getPerInterest() {
		return to_string(this->perInterest);
	}
	string getProfit() {
		return to_string(this->profit);
	}
	string getCountEmployee() {
		return to_string(this->countEmployee);
	}
};

class BakeryException : public std::exception {
private:
	std::string m_error;
public:
	BakeryException(std::string error) :m_error(error) {}
	const char* what() const noexcept {
		return m_error.c_str();
	}
};

string beautiful(string original) {
	for (int i = 0; i < original.length(); i++) {
		if (original[i] == ' ') {
			original[i] = '_';
		}
	}
	return original;
}

class Bakery {
private:
	char name[BUFF];
	char owner_name[BUFF];
	std::vector<Service> services;
	bool isChecked = false;
	double marks[5];
public:
	Bakery(const char owner_name[BUFF]) {
		strncpy(this->name, "", sizeof(this->name));
		strncpy(this->owner_name, owner_name, sizeof(this->owner_name));
		for (int i = 0; i < 5; i++) marks[i] = 0;
	};
	void setMarks(double marks[5]) {
		for (int i = 0; i < 5; i++) {
			this->marks[i] = marks[i];
		}
	}
	bool checkMarks(int expertMark, int marks[5]) {
		for (int i = 0; i < 5; i++) {
			if (marks[i] == expertMark) return true;
		}
		return false;
	}
	void setMarks() {
		system("cls");
		int expertsCount = 0;
		while (true) {
			try
			{
				cout << "������� ���������� ���������: ";
				cin >> expertsCount;
				if (!cin.good() || expertsCount < 2 || expertsCount > 10) {
					throw BakeryException("���������� ��������� ����� ���� �� 2 �� 10");
				}

				break;
			}
			catch (BakeryException& error)
			{
				cout << error.what() << endl;
				cin.clear();
				rewind(stdin);
				cout << "���������� ��� ���" << endl;
			}
		}
		char countOfExperts[BUFF];
		itoa(expertsCount, countOfExperts, sizeof(countOfExperts));
		send(Connection, countOfExperts, sizeof(countOfExperts), NULL);
		for (int i = 0; i < expertsCount; i++) {
			system("cls");
			int expertMarks[5][5];
			for (int i = 0; i < 5; i++)
				for (int j = 0; j < 5; j++)
					expertMarks[i][j] = -1;
			vector<Service>::iterator itService;
			itService = services.begin();
			cout << setw(122) << setfill('=') << "=" << endl;
			cout << setfill(' ');
			cout << setw(1) << "|" << setw(4) << "id" << setw(1) << "|" <<
				setw(35) << "�������� ������" << setw(5) << "|" <<
				setw(8) << "�������" << setw(5) << "|" <<
				setw(25) << "������� ����������������" << setw(2) << "|" <<
				setw(8) << "�������" << setw(5) << "|" <<
				setw(20) << "���������� �������" << setw(3) << "|" << endl;
			cout << setw(122) << setfill('=') << "=" << endl;
			cout << setfill(' ');
			for (int serviceNum = 0; serviceNum < 5; serviceNum++, itService++) {
				itService->getInfoInTable(serviceNum + 1);
				cout << endl;
			}
				
			//cout << endl;
			cout << setw(122) << setfill('=') << "=" << endl;
			cout << setfill(' ');
			for (int i1 = 0; i1 < 5; i1++) {
				for (int j = 0; j < 5; j++) {
					if (i1 == j) continue;
					while (true) {
						try {
							cout << "������� Z[" << i1 << "][" << j << "]: ";
							cin >> expertMarks[i1][j];
							if (!cin.good() || expertMarks[i1][j] < 0 || expertMarks[i1][j] > 20) {
								throw BakeryException("������ ������ ���� �� 0 �� 20");
							}
							break;
						}
						catch (BakeryException& error) {
							cout << error.what() << endl;
						}
					}
				}
				char sendMarksString[BUFF];
				strcpy(sendMarksString, "");
				char mark[BUFF];
				for (int j = 0; j < 4; j++) {
					
					itoa(expertMarks[i1][j], mark, 10);
					strcat(sendMarksString, mark);
					strcat(sendMarksString, " ");
				}
				itoa(expertMarks[i1][4], mark, 10);
				strcat(sendMarksString, mark);
				send(Connection, sendMarksString, sizeof(sendMarksString), NULL);
			}

		}

	}
	void addService(string service_name) {
		double expenses;// ������� �� ������
		double perInterest;// ������� ������������������ ������������ ���� �����
		double profit; // �������
		int countEmployee; // ���������� �����������
		Service temp(service_name);
		int choice;
		while (true)
		{
			try {

				cout << "\t������� ������� �� ������: "; cin >> expenses;
				if (expenses < 0) throw BakeryException("������� �� ����� ���� ������ 0");
				cout << "\t������� ������� ������������������ �� ������ (0-100%): "; cin >> perInterest;
				if (perInterest < 0 || perInterest > 100) throw BakeryException("������� ������� � ���������� �� 0 �� 100");
				cout << "\t������� ������� �� ������: "; cin >> profit;
				if (profit < 0) throw BakeryException("������� �� ����� ���� ������ 0");
				cout << "\t������� ���������� ����������� �� ������: "; cin >> countEmployee;
				if (countEmployee < 0) throw BakeryException("���������� ����������� �� ����� ���� ������ 0");
				temp.setExpenses(expenses);
				temp.setPerInterest(perInterest);
				temp.setProfit(profit);
				temp.setCountEmployee(countEmployee);
				services.push_back(temp);
				break;
			}
			catch (BakeryException& bakery_error)
			{
				cout << bakery_error.what();
				cout << "����������� ��� ���?\n1. ��\n0. ���" << endl;
				while (!scanf_s("%d", &choice) || (choice < 0 || choice > 1))
				{
					rewind(stdin);
					cout << "������. ������� ����� 1 ��� 0.\n";
				}
				if (choice == 0) {
					throw 1;
					cin.clear();
					rewind(stdin);
					return;
				}
			}
			catch (...) {
				term_func();
			}
			cin.clear();
			rewind(stdin);
		}


	};
	void createBakery() {
		cin.clear();
		rewind(stdin);
		int choice;
		while (true)
		{
			try
			{
				cout << "������� �������� �������: ";
				char Bakeryname[BUFF];
				cin.getline(Bakeryname, BUFF, '\n');
				rewind(stdin);
				strncpy(this->name, beautiful(Bakeryname).c_str(), sizeof(this->name));
				if (strlen(this->name) < 2) throw BakeryException("�������� ������� ������� ��������\n");
				cout << "���������� ���������� �� ������ <������� ��������� � �������>\n";
				addService("������� ��������� � �������");
				cout << "���������� ���������� �� ������ <�������� ��������� �� ���>\n";
				addService("�������� ��������� �� ���");
				cout << "���������� ���������� �� ������ <����������� ����������>\n";
				addService("����������� ����������");
				cout << "���������� ���������� �� ������ <���������� ���������� ������-�������>\n";
				addService("���������� ���������� ������-�������");
				cout << "���������� ���������� �� ������ <������������ �����>\n";
				addService("������������ �����");
				break;
			}
			catch (BakeryException& bakery_error)
			{
				cout << bakery_error.what();
				cout << "����������� ��� ���?\n1. ��\n0. ���" << endl;
				while (!scanf_s("%d", &choice) || (choice < 0 || choice > 1))
				{
					rewind(stdin);
					cout << "������. ������� ����� 1 ��� 0.\n";
				}
				if (choice == 0) {
					throw 1;
					cin.clear();
					rewind(stdin);
					return;
				}
			}
			catch (int) {
				throw 1;
				cin.clear();
				rewind(stdin);
				return;
			}
			catch (...) {
				term_func();
			}
			cin.clear();
			rewind(stdin);
		}
	}
	string getInfo() {
		string infoBakery;

		infoBakery += beautiful(string(name)) + " " + string(owner_name) + " " + (isChecked ? "1" : "0") + " ";
		for (Service temp : services) {
			infoBakery += temp.getInfo() + " ";
		}
		for (int i = 0; i < 4; i++) {
			infoBakery += to_string(marks[i]) + " ";
		}
		infoBakery += to_string(marks[4]);
		return infoBakery;
	}
	void addService(const char service_name[BUFF], double expenses, double perInterest, double profit, int countEmployee) {
		Service temp(service_name);
		temp.setExpenses(expenses);
		temp.setPerInterest(perInterest);
		temp.setProfit(profit);
		temp.setCountEmployee(countEmployee);
		services.push_back(temp);
	}
	void isCheckedSet(int isChecked) {
		this->isChecked = isChecked;
	}
	void setBakeryName(const char name[BUFF]) {
		strncpy(this->name, name, sizeof(this->name));
	}
	string getName() {
		return string(name);
	}
	string getIsChecked() {
		return this->isChecked ? "���������" : "�� ���������";
	}
	string getOwnerName() {
		return string(owner_name);
	}
	string getMarks() {
		string marks;
		for (int mark = 0; mark < 4; mark++) {
			marks += to_string(this->marks[mark]) + " ";
		}
		marks += to_string(this->marks[4]);
		return marks;
	}
	void changeInfo() {
		char choice;
		cout << "[1] ������������� �������� �������" << endl;
		cout << "[2] ������������� ������" << endl;
		while (true) {
			cin.clear();
			rewind(stdin);
			choice = _getch();
			if (choice == '1' || choice == '2') break;
		}
		switch (choice) {
		case('1'):
		{
			//�������� ��� �����
			while (true) {
				try
				{
					cout << "\t������� �������� �������: ";
					char Bakeryname[BUFF];
					cin.getline(Bakeryname, BUFF, '\n');
					rewind(stdin);
					strncpy(this->name, beautiful(Bakeryname).c_str(), sizeof(this->name));
					if (strlen(this->name) < 2) throw BakeryException("\t�������� ������� ������� ��������\n");
					break;
				}
				catch (BakeryException& error) {
					cout << error.what() << endl;
					cout << "\t���������� ��� ���\n������� Enter" << endl;
					cin.clear();
					rewind(stdin);
					cin.get();
				}
			}
		}
		break;
		case('2'):
		{
			//�������� �������
			cout << "��� ��������� ������ ����� ����������� ��������� �������� ���������\n";
			vector<Service>::iterator itService;
			itService = services.begin();
			for (int i = 0; i < 5; i++, itService++) {
				cout << "\t" << i + 1 << ". " << itService->getName() << endl;
			}
			itService = services.begin();
			char choice;
			while (true) {
				cin.clear();
				rewind(stdin);
				choice = _getch();
				if (choice >= 49 && choice <= 53) break;
			}
			advance(itService, (int(choice) - 49));


			double expenses;// ������� �� ������
			double perInterest;// ������� ������������������ ������������ ���� �����
			double profit; // �������
			int countEmployee; // ���������� �����������
			while (true)
			{
				try {
					system("cls");
					itService->getInfoInWholeTable(int(choice - 48));
					cout << "\t������� ������� �� ������: "; cin >> expenses;
					if (expenses < 0) throw BakeryException("������� �� ����� ���� ������ 0");
					cout << "\t������� ������� ������������������ �� ������ (0-100%): "; cin >> perInterest;
					if (perInterest < 0 || perInterest > 100) throw BakeryException("������� ������� � ���������� �� 0 �� 100");
					cout << "\t������� ������� �� ������: "; cin >> profit;
					if (profit < 0) throw BakeryException("������� �� ����� ���� ������ 0");
					cout << "\t������� ���������� ����������� �� ������: "; cin >> countEmployee;
					if (countEmployee < 0) throw BakeryException("���������� ����������� �� ����� ���� ������ 0");
					itService->setExpenses(expenses);
					itService->setPerInterest(perInterest);
					itService->setProfit(profit);
					itService->setCountEmployee(countEmployee);
					break;
				}
				catch (BakeryException& bakery_error)
				{
					cout << bakery_error.what();
					cout << "���������� ��� ���\n������� Enter" << endl;
					cin.clear();
					rewind(stdin);
					cin.get();
				}
				catch (...) {
					term_func();
				}
				cin.clear();
				rewind(stdin);
			}
			this->isChecked = false;
			double defMarks[] = { 0,0,0,0,0 };
			this->setMarks(defMarks);
			system("cls");
			itService->getInfoInWholeTable(int(choice - 48));
			cout << "������� Enter" << endl;
			cin.clear();
			rewind(stdin);
			cin.get();

		}
		break;
		}
	}
	void report(int id) {
		if (this->marks[0] == 0) {
			cout << "������ ������������ ����� ��� ������������� �������\n";
			cout << "������� Enter" << endl;
			cin.clear();
			rewind(stdin);
			cin.get();
			return;
		}
		char file_name[BUFF];
		cin.clear();
		rewind(stdin);
		while (true) {
			try {
				cout << "������� ��� �����: ";
				cin.getline(file_name, BUFF, '\n');
				rewind(stdin);
				strncpy(file_name, beautiful(file_name).c_str(), sizeof(file_name));
				if (strlen(file_name) < 2) throw BakeryException("��� ����� ������� ��������\n");
				break;
			}
			catch (BakeryException& error) {
				cout << error.what() << endl;
				cout << "���������� ��� ���\n������� Enter\n";
				cin.clear();
				rewind(stdin);
				cin.get();
			}
		}
		strcat(file_name, ".txt");
		fstream outfile;
		outfile.open(file_name, ios::out);
		outfile << "\t\t����� �� ������� " + string(this->name) << endl << endl;

		outfile << "\tid: " << id << endl;
		outfile << "\t��������: " << this->getName() << endl;
		outfile << "\t��������: " << this->getOwnerName() << endl;
		outfile << "\t������� ��������: " << this->getIsChecked() << endl;
		outfile << "\t������: " << this->getMarks() << endl << endl << endl;

		outfile << "\t\t������ �������" << endl << endl;

		vector<Service>::iterator itService;
		itService = services.begin();
		int i;
		for (itService = services.begin(), i = 1; itService != services.end(); itService++, i++) {
			outfile << i << ". " + itService->getName() << endl;
			outfile << "\t" << "�������: " << itService->getExpenses() << endl;
			outfile << "\t" << "������� ������������������: " << itService->getPerInterest() << endl;
			outfile << "\t" << "�������: " << itService->getProfit() << endl;
			outfile << "\t" << "���������� �������: " << itService->getCountEmployee() << endl;
		}
		//outfile << endl << "\t\t�������� �� ���������� �������" << endl;
		//outfile << "\t��� ���������� ������� ������� ���������� ��������� ������: " << endl;
		//for (int max = 5; max > 0; max--)
			//for (int j = 0; j < 5; j++) {
				//if (marks[j] == max) {
					//outfile << "\t" << 5 - max + 1 << ". " << services[j].getName() << endl;
				//}
			//}
	}
};

class Company {
private:
	char companyName[BUFF];
	Admin admin;
	std::vector<Client> clients;
	std::vector<Bakery> bakeries;
	std::vector<Client>::iterator itClient;
	std::vector<Bakery>::iterator itBakery;
public:
	Company(const char companyName[BUFF]) {
		std::strncpy(this->companyName, companyName, sizeof(this->companyName));
		admin.setAutorisation("admin", "admin");

	};
	~Company() {
		clients.clear();
		bakeries.clear();
	}
	void sendBakeries() {
		std::vector<Bakery>::iterator it;
		int countBakeries = bakeries.size();
		char count[BUFF];
		itoa(countBakeries, count, 10);
		send(Connection, count, sizeof(count), NULL);
		for (it = bakeries.begin(); it != bakeries.end(); it++) {
			char bakeryInfo[BUFF];
			strncpy(bakeryInfo, it->getInfo().c_str(), sizeof(bakeryInfo));
			send(Connection, bakeryInfo, sizeof(bakeryInfo), NULL);
		}
	}
	void sendClient() {
		char countClient[BUFF];
		itoa(clients.size(), countClient, 10);
		send(Connection, countClient, sizeof(countClient), NULL);
		for (itClient = clients.begin(); itClient != clients.end(); itClient++) {
			char clientInfo[BUFF];
			strncpy(clientInfo, itClient->getInfo().c_str(), sizeof(clientInfo));
			send(Connection, clientInfo, sizeof(clientInfo), NULL);
		}
	}
	void addBakery(const char Bakeryname[BUFF]) {
		Bakery temp(Bakeryname);
		try
		{
			temp.createBakery();
		}
		catch (int)
		{
			send(Connection, "-1", sizeof("-1"), NULL);
			return;
		}
		bakeries.push_back(temp);
		sendBakeries();
	}
	void recvClient() {
		char clientCount[BUFF];
		recv(Connection, clientCount, sizeof(clientCount), NULL);
		for (int i = 0; i < atoi(clientCount); i++) {
			char clientInfo[BUFF];
			Client temp;
			recv(Connection, clientInfo, sizeof(clientInfo), NULL);
			if (strlen(clientInfo) < 4) return;
			char login[BUFF], pass[BUFF], name[BUFF], surname[BUFF];
			strncpy(login, strtok(clientInfo, " "), sizeof(login));
			strncpy(pass, strtok(NULL, " "), sizeof(pass));
			strncpy(name, strtok(NULL, " "), sizeof(name));
			strncpy(surname, strtok(NULL, " "), sizeof(surname));
			temp.addClient(name, surname, login, pass);
			clients.push_back(temp);
		}

	}
	void recvbakeries() {
		char bakeryCount[BUFF];
		recv(Connection, bakeryCount, sizeof(bakeryCount), NULL);
		for (int i = 0; i < atoi(bakeryCount); i++) {
			char bakeryInfo[BUFF];
			recv(Connection, bakeryInfo, sizeof(bakeryInfo), NULL);
			if (strlen(bakeryInfo) < 4) return;
			char Bakeryname[BUFF], owner_name[BUFF], isChecked[BUFF];
			strncpy(Bakeryname, strtok(bakeryInfo, " "), sizeof(Bakeryname));
			strncpy(owner_name, strtok(NULL, " "), sizeof(owner_name));
			strncpy(isChecked, strtok(NULL, " "), sizeof(isChecked));
			Bakery temp(owner_name);
			temp.setBakeryName(Bakeryname);
			for (int service = 0; service < 5; service++) {
				double expenses = atoi(strtok(NULL, " "));
				double perInterest = atoi(strtok(NULL, " "));
				double profit = atoi(strtok(NULL, " "));
				int countEmployee = atoi(strtok(NULL, " "));
				switch (service) {
				case(0):
					temp.addService("������� ��������� � �������", expenses, perInterest, profit, countEmployee);
					break;
				case(1):
					temp.addService("�������� ��������� �� ���", expenses, perInterest, profit, countEmployee);
					break;
				case(2):
					temp.addService("����������� ����������", expenses, perInterest, profit, countEmployee);
					break;
				case(3):
					temp.addService("���������� ���������� ������-�������", expenses, perInterest, profit, countEmployee);
					break;
				case(4):
					temp.addService("������������ �����", expenses, perInterest, profit, countEmployee);
					break;
				}
			}
			temp.isCheckedSet(atoi(isChecked));
			double marks[5];
			for (int i = 0; i < 5; i++) {
				marks[i] = atof(strtok(NULL, " "));
			}
			temp.setMarks(marks);
			bakeries.push_back(temp);
		}
	}
	void printClientInfo() {
		int id = 0;
		cout << setw(89) << setfill('=') << "=" << endl;
		cout << setfill(' ');
		cout << setw(1) << "|" << setw(4) << "id" << setw(4) << "|" <<
			setw(12) << "���" << setw(8) << "|" <<
			setw(12) << "�������" << setw(8) << "|" <<
			setw(12) << "�����" << setw(8) << "|" <<
			setw(12) << "������" << setw(8) << "|" << endl;
		cout << setw(89) << setfill('=') << "=" << endl;
		cout << setfill(' ');
		for (itClient = clients.begin(); itClient != clients.end(); itClient++, id++) {
			cout << setw(1) << "|" << setw(4) << id << setw(4) << "|" <<
				setw(12) << itClient->getName() << setw(8) << "|" <<
				setw(12) << itClient->getSurname() << setw(8) << "|" <<
				setw(12) << itClient->getLogin() << setw(8) << "|" <<
				setw(12) << itClient->getPass() << setw(8) << "|" << endl;
		}
		cout << setw(89) << setfill('=') << "=" << endl;
	};
	int getClientsSize() {
		return clients.size();
	}
	int getbakeriesSize() {
		return bakeries.size();
	}
	void delClient() {
		int id;
		
		while (true) {
			try
			{
				cout << "����� id ������ �������?"; cin >> id;
				if (!cin.good() || id < 0 || (id > (clients.size() - 1))) throw BakeryException("�������� id");
				break;
			}
			catch (BakeryException& error)
			{
				cin.clear();
				rewind(stdin);
				cout << error.what() << endl << "���������� ��� ���" << endl;

			}
		}
		itClient = clients.begin();
		advance(itClient, id);
		clients.erase(itClient);
	}
	void addClient() {
		Client temp;
		char login[BUFF], pass[BUFF], name[BUFF], surname[BUFF];
		while (true) {
			try {
				system("cls");
				cout << "������� ���: "; cin >> name;
				if (strlen(name) < 2) throw BakeryException("������� �������� ���");
				for (int i = 0; i < clients.size(); i++) {
					if (strcmp(clients[i].getName().c_str(), name) == 0) {
						throw BakeryException("������������ � ����� ������ ��� ���������������");
					}
				}
				cout << "������� �������: "; cin >> surname;
				if (strlen(surname) < 2) throw BakeryException("������� �������� �������");
				cout << "������� �����: "; cin >> login;
				if (strlen(login) < 6) throw BakeryException("������� �������� �����");
				cout << "������� ������: "; cin >> pass;
				if (strlen(pass) < 6) throw BakeryException("������� �������� ������");

				break;
			}
			catch (BakeryException& error) {
				rewind(stdin);
				cout << error.what() << endl << "���������� ��� ���\n������� Enter\n";
				cin.clear();
				cin.get();
			}
		}
		temp.addClient(name, surname, login, pass);
		clients.push_back(temp);
	}
	void printbakeryInfo() {
		int id = 0;
		cout << setw(115) << setfill('=') << "=" << endl;
		cout << setfill(' ');
		cout << setw(1) << "|" << setw(4) << "id" << setw(4) << "|" <<
			setw(15) << "��������" << setw(5) << "|" <<
			setw(15) << "��������" << setw(5) << "|" <<
			setw(12) << "���������" << setw(8) << "|" <<
			setw(25) << "������" << setw(21) << "|" << endl;
		cout << setw(115) << setfill('=') << "=" << endl;
		cout << setfill(' ');
		for (itBakery = bakeries.begin(); itBakery != bakeries.end(); itBakery++, id++) {
			cout << setw(1) << "|" << setw(4) << id << setw(4) << "|" <<
				setw(15) << itBakery->getName() << setw(5) << "|" <<
				setw(15) << itBakery->getOwnerName() << setw(5) << "|" <<
				setw(12) << itBakery->getIsChecked() << setw(8) << "|" <<
				setw(25) << itBakery->getMarks() << setw(2) << "|" << endl;
		}
		cout << setw(115) << setfill('=') << "=" << endl;
	}
	void printbakeryInfo(string owner_name) {
		int CountBakery = 0;
		for (itBakery = bakeries.begin(); itBakery != bakeries.end(); itBakery++) {
			if (itBakery->getOwnerName() == owner_name) CountBakery++;
		}
		if (CountBakery > 0) {
			int id = 0;
			cout << setw(115) << setfill('=') << "=" << endl;
			cout << setfill(' ');
			cout << setw(1) << "|" << setw(4) << "id" << setw(4) << "|" <<
				setw(15) << "��������" << setw(5) << "|" <<
				setw(15) << "��������" << setw(5) << "|" <<
				setw(12) << "���������" << setw(8) << "|" <<
				setw(25) << "������" << setw(21) << "|" << endl;
			cout << setw(115) << setfill('=') << "=" << endl;
			cout << setfill(' ');
			for (itBakery = bakeries.begin(); itBakery != bakeries.end(); itBakery++, id++) {
				if (itBakery->getOwnerName() == owner_name) {
					cout << setw(1) << "|" << setw(4) << id << setw(4) << "|" <<
						setw(15) << itBakery->getName() << setw(5) << "|" <<
						setw(15) << itBakery->getOwnerName() << setw(5) << "|" <<
						setw(12) << itBakery->getIsChecked() << setw(8) << "|" <<
						setw(25) << itBakery->getMarks() << setw(2) << "|" << endl;
				}
			}
			cout << setw(115) << setfill('=') << "=" << endl;
		}
		else {
			cout << "����������� �������" << endl;
		}
	}
	void setMarks() {
		int numBakery;
		double marks[5];
		while (true) {
			try
			{
				cout << "������� id �������: "; cin >> numBakery;
				if (!cin.good() || (numBakery < 0 || numBakery >= this->bakeries.size()))
					throw(BakeryException("id ������ ���� �� 0 �� " + to_string((this->bakeries.size() - 1))));
				break;
			}
			catch (BakeryException& error)
			{
				cout << error.what() << endl;
			}
		}
		itBakery = bakeries.begin();
		advance(itBakery, numBakery);
		itBakery->setMarks();
		char result[BUFF];
		
		recv(Connection, result, sizeof(result), NULL);
		//������� ������ � ������������� ��� ������� ������
		char mark[BUFF];
		strncpy(mark, strtok(result, " "), sizeof(mark));
		marks[0] = atof(mark);
		for (int i = 1; i < 5; i++) {
			strncpy(mark, strtok(NULL, " "), sizeof(mark));
			marks[i] = atof(mark);
		}
		itBakery->setMarks(marks);
		itBakery->isCheckedSet(1);
	}
	void delBakery() {
		int bakeryNum;
		while (true)
		{
			try {
				cout << "������� ����� �������: ";
				cin >> bakeryNum;
				if (!cin.good() || bakeryNum < 0 || bakeryNum >= bakeries.size())
					throw BakeryException("����� ������� ������ ���� � �������� �� 0 �� " + to_string(bakeries.size() - 1));
				break;
			}
			catch (BakeryException& error) {
				cout << error.what() << endl;
				cout << "���������� ��� ���" << endl;
				cin.clear();
				rewind(stdin);
			}
		}
		itBakery = bakeries.begin();
		advance(itBakery, bakeryNum);
		bakeries.erase(itBakery);
	}
	void edit() {
		int bakeryNum;
		while (true)
		{
			try {
				cout << "������� ����� �������: ";
				cin >> bakeryNum;
				if (!cin.good() || bakeryNum < 0 || bakeryNum >= bakeries.size())
					throw BakeryException("����� ������� ������ ���� � �������� �� 0 �� " + to_string(bakeries.size() - 1));
				break;
			}
			catch (BakeryException& error) {
				cout << error.what() << endl;
				cout << "���������� ��� ���" << endl;
				cin.clear();
				rewind(stdin);
			}
		}
		itBakery = bakeries.begin();
		advance(itBakery, bakeryNum);
		itBakery->changeInfo();
	}
	void createReport() {
		int bakeryNum;
		while (true)
		{
			try {
				cout << "������� ����� �������: ";
				cin >> bakeryNum;
				if (!cin.good() || bakeryNum < 0 || bakeryNum >= bakeries.size())
					throw BakeryException("����� ������� ������ ���� � �������� �� 0 �� " + to_string(bakeries.size() - 1));
				break;
			}
			catch (BakeryException& error) {
				cout << error.what() << endl;
				cout << "���������� ��� ���" << endl;
				cin.clear();
				rewind(stdin);
			}
		}
		itBakery = bakeries.begin();
		advance(itBakery, bakeryNum);
		itBakery->report(bakeryNum);
	}
	void createReport(string owner_name) {
		int bakeryNum;
		while (true)
		{
			try {
				cout << "������� ����� �������: ";
				cin >> bakeryNum;
				if (bakeryNum >= bakeries.size()) throw BakeryException("����� ����� ������� �� ������");
				if (cin.good()) {
					itBakery = bakeries.begin();

					advance(itBakery, bakeryNum);
					if (itBakery->getOwnerName() == owner_name) {
						break;
					}
					else throw BakeryException("����� ����� ������� �� ������");
				}
				if (!cin.good())
					throw BakeryException("����������� ����");
				break;
			}
			catch (BakeryException& error) {
				cout << error.what() << endl;
				cout << "���������� ��� ���" << endl;
				cin.clear();
				rewind(stdin);
			}
		}
		itBakery = bakeries.begin();
		advance(itBakery, bakeryNum);
		itBakery->report(bakeryNum);
	}
	void changeClientPass(string owner_name) {
		char pass[BUFF];
		for (itClient = clients.begin(); itClient != clients.end(); itClient++) {
			if (itClient->getName() == owner_name) {
				break;
			}
		}
		cout << "������� ����� ������ : ";
		cin.getline(pass, BUFF, '\n');
		itClient->changePass(pass);
	}
};


void menu(int type, char owner_name[BUFF]) {
	Company bakery("�������");
	bakery.recvClient();
	bakery.recvbakeries();

	rewind(stdin);

	system("cls");
	rewind(stdin);
	std::cin.clear();
	if (type == 1) {
		rewind(stdin);
		bool flag1 = FALSE;
		while (flag1 == FALSE) {
			system("cls");
			std::cout << "\t\t\t[�������������]" << std::endl;
			std::cout << "[1] ���������� ����� �������" << std::endl;
			std::cout << "[2] ���������� ��������������" << std::endl;
			std::cout << "[3] ������ ���������" << std::endl;
			std::cout << "[4] �������� ������" << std::endl;
			std::cout << "[5] �������������� ������" << std::endl;
			std::cout << "[6] �������� ������" << std::endl;
			std::cout << "[7] ������������ �������" << std::endl;
			std::cout << "[8] ����� � �����������" << std::endl;
			rewind(stdin);
			char menu_2;
			menu_2 = _getch();
			switch (menu_2) {
			case('1'):
				//���������� �������
			{
				send(Connection, "1", sizeof("1"), NULL);
				bakery.addBakery(owner_name);
			}
			break;
			case('2'):
				//������ � ��������������
			{
				send(Connection, "2", sizeof("2"), NULL);
				rewind(stdin);
				bool flag21 = FALSE;
				while (flag21 == FALSE) {
					system("cls");
					cout << "\t\t\t[���������� ��������������]" << endl;
					cout << "[1] �������� �������������" << endl;
					cout << "[2] ���������� �������������" << endl;
					cout << "[3] �������� �������������" << endl;
					cout << "[4] �����" << endl;
					char client_choice;
					client_choice = _getch();
					switch (client_choice) {
					case('1'):
					{

						system("cls");
						if (bakery.getClientsSize() == 0) {
							cout << "������������ �����������" << endl << "������� Enter ����� ����������" << endl;
							rewind(stdin);
							cin.clear();
							rewind(stdin);
							cin.get();
							continue;
						}
						send(Connection, "1", sizeof("1"), NULL);
						bakery.printClientInfo();
						bakery.delClient();
						system("cls");
						bakery.printClientInfo();
						rewind(stdin);
						cin.get();
						bakery.sendClient();
					}
					break;
					case('2'):
					{
						send(Connection, "2", sizeof("2"), NULL);
						bakery.addClient();
						bakery.sendClient();
					}
					break;
					case('3'):
					{

						system("cls");
						if (bakery.getClientsSize() == 0) {
							cout << "������������ �����������" << endl << "������� Enter ����� ����������" << endl;
							rewind(stdin);
							cin.clear();
							rewind(stdin);
							cin.get();
							continue;
						}
						send(Connection, "3", sizeof("3"), NULL);
						bakery.printClientInfo();
						rewind(stdin);
						cin.get();
					}
					break;
					case('4'):
					{
						send(Connection, "4", sizeof("4"), NULL);
						rewind(stdin);
						flag21 = TRUE;
					}
					break;
					}
				}


			}
			break;
			case('3'):
				//����������� ������
			{
				system("cls");
				if (bakery.getbakeriesSize() == 0) {
					cout << "������ �����������" << endl << "������� Enter ����� ����������" << endl;
					rewind(stdin);
					cin.clear();
					rewind(stdin);
					cin.get();
					continue;
				}
				send(Connection, "3", sizeof("3"), NULL);
				bakery.printbakeryInfo();
				bakery.setMarks();
				bakery.sendBakeries();
				cout << endl;
				cout << "������� Enter ����� ����������" << endl;
				rewind(stdin);
				cin.clear();
				rewind(stdin);
				cin.get();
			}
			break;
			case('4'):
				//������ ������
			{
				system("cls");
				if (bakery.getbakeriesSize() == 0) {
					cout << "������ �����������" << endl << "������� Enter ����� ����������" << endl;
					rewind(stdin);
					cin.clear();
					rewind(stdin);
					cin.get();
					continue;
				}
				bakery.printbakeryInfo();
				cout << endl;
				cout << "������� Enter ����� ����������" << endl;
				rewind(stdin);
				cin.clear();
				rewind(stdin);
				cin.get();
			}
			break;
			case('5'):
				//�������������� �������
			{
				send(Connection, "5", sizeof("5"), NULL);
				system("cls");
				bakery.printbakeryInfo();
				bakery.edit();
				system("cls");
				bakery.printbakeryInfo();
				bakery.sendBakeries();
				cout << endl;
				cout << "������� Enter ����� ����������" << endl;
				rewind(stdin);
				cin.clear();
				rewind(stdin);
				cin.get();
			}
			break;
			case('6'):
				//�������� �������
			{
				system("cls");
				if (bakery.getbakeriesSize() == 0) {
					cout << "������ �����������" << endl << "������� Enter ����� ����������" << endl;
					rewind(stdin);
					cin.clear();
					rewind(stdin);
					cin.get();
					continue;
				}
				send(Connection, "6", sizeof("6"), NULL);
				bakery.printbakeryInfo();
				cout << endl;
				bakery.delBakery();
				system("cls");
				bakery.printbakeryInfo();
				cin.clear();
				rewind(stdin);
				cout << "������� Enter ����� ���������� " << endl; cin.get();
				if (bakery.getbakeriesSize() == 0) {
					send(Connection, "-1", sizeof("-1"), NULL);
					break;
				}
				bakery.sendBakeries();
			}
			break;
			case('7'):
				//������������ �������
			{
				system("cls");
				if (bakery.getbakeriesSize() == 0) {
					cout << "������ �����������" << endl << "������� Enter ����� ����������" << endl;
					rewind(stdin);
					cin.clear();
					rewind(stdin);
					cin.get();
					continue;
				}
				bakery.printbakeryInfo();
				bakery.createReport();

			}
			break;
			case('8'):
				//����� � �����������
			{
				send(Connection, "8", sizeof("8"), NULL);
				rewind(stdin);
				flag1 = TRUE;
			}
			break;
			}
		}
	}

	if (type == 2) {
		rewind(stdin);
		bool flag1 = FALSE;
		while (flag1 == FALSE) {
			system("cls");
			std::cout << "\t\t\t������������ ���, " << owner_name << std::endl;
			std::cout << "[1] ���������� ����� �������" << std::endl;
			std::cout << "[2] �������� ������" << std::endl;//change
			std::cout << "[3] �������������� ������" << std::endl;
			std::cout << "[4] �������� ������" << std::endl;
			std::cout << "[5] ����� ������" << std::endl;
			std::cout << "[6] ������������ �������" << std::endl;//change
			std::cout << "[7] ����� � �����������" << std::endl;
			rewind(stdin);
			char menu_2;
			menu_2 = _getch();
			switch (menu_2) {
			case('1'):
				//���������� 
			{
				send(Connection, "1", sizeof("1"), NULL);
				bakery.addBakery(owner_name);
			}
			break;
			case('2'):
				//������ ������
			{
				system("cls");
				if (bakery.getbakeriesSize() == 0) {
					cout << "������ �����������" << endl << "������� Enter ����� ����������" << endl;
					rewind(stdin);
					cin.clear();
					rewind(stdin);
					cin.get();
					continue;
				}
				bakery.printbakeryInfo(owner_name);
				cout << endl;
				cout << "������� Enter ����� ����������" << endl;
				rewind(stdin);
				cin.clear();
				rewind(stdin);
				cin.get();
				/*send(Connection, "2", sizeof("2"), NULL);
				rewind(stdin);
				bool flag21 = FALSE;
				while (flag21 == FALSE) {
					system("cls");
					cout << "\t\t\t������ � ��������������" << endl;
					cout << "1. �������� �������������" << endl;
					cout << "2. ���������� �������������" << endl;
					cout << "3. �������� �������������" << endl;
					cout << "4. �����" << endl;
					char client_choice;
					client_choice = _getch();
					switch (client_choice) {
					case('1'):
					{

						system("cls");
						if (bakery.getClientsSize() == 0) {
							cout << "���� �������������" << endl << "������� Enter ����� ����������" << endl;
							rewind(stdin);
							cin.clear();
							rewind(stdin);
							cin.get();
							continue;
						}
						send(Connection, "1", sizeof("1"), NULL);
						bakery.printClientInfo();
						bakery.delClient();
						system("cls");
						bakery.printClientInfo();
						rewind(stdin);
						cin.get();
						bakery.sendClient();
					}
					break;
					case('2'):
					{
						send(Connection, "2", sizeof("2"), NULL);
						bakery.addClient();
						bakery.sendClient();
					}
					break;
					case('3'):
					{

						system("cls");
						if (bakery.getClientsSize() == 0) {
							cout << "���� �������������" << endl << "������� Enter ����� ����������" << endl;
							rewind(stdin);
							cin.clear();
							rewind(stdin);
							cin.get();
							continue;
						}
						send(Connection, "3", sizeof("3"), NULL);
						bakery.printClientInfo();
						rewind(stdin);
						cin.get();
					}
					break;
					case('4'):
					{
						send(Connection, "4", sizeof("4"), NULL);
						rewind(stdin);
						flag21 = TRUE;
					}
					break;
					}
				}*/
			}
			break;
			case('3'):
				//��������������
			{
				send(Connection, "3", sizeof("3"), NULL);
				system("cls");
				bakery.printbakeryInfo();
				bakery.edit();
				system("cls");
				bakery.printbakeryInfo();
				bakery.sendBakeries();
				cout << endl;
				cout << "������� Enter ����� ����������" << endl;
				rewind(stdin);
				cin.clear();
				rewind(stdin);
				cin.get();
				/*system("cls");
				if (bakery.getbakeriesSize() == 0) {
					cout << "���� �������" << endl << "������� Enter ����� ����������" << endl;
					rewind(stdin);
					cin.clear();
					rewind(stdin);
					cin.get();
					continue;
				}
				send(Connection, "3", sizeof("3"), NULL);
				bakery.printbakeryInfo();
				bakery.setMarks();
				bakery.sendBakeries();
				cout << endl;
				cout << "������� Enter ����� ����������" << endl;
				rewind(stdin);
				cin.clear();
				rewind(stdin);
				cin.get();*/
			}
			break;
			case('4'):
				//��������
			{
				system("cls");
				if (bakery.getbakeriesSize() == 0) {
					cout << "������ �����������" << endl << "������� Enter ����� ����������" << endl;
					rewind(stdin);
					cin.clear();
					rewind(stdin);
					cin.get();
					continue;
				}
				send(Connection, "4", sizeof("4"), NULL);
				bakery.printbakeryInfo();
				cout << endl;
				bakery.delBakery();
				system("cls");
				bakery.printbakeryInfo();
				cin.clear();
				rewind(stdin);
				cout << "������� Enter ����� ���������� " << endl; cin.get();
				if (bakery.getbakeriesSize() == 0) {
					send(Connection, "-1", sizeof("-1"), NULL);
					break;
				}
				bakery.sendBakeries();
			}
			break;
			case('5'):
				//����� ������
			{
				send(Connection, "5", sizeof("5"), NULL);
				system("cls");
				bakery.changeClientPass(owner_name);
				cin.clear();
				rewind(stdin);
				cout << "������� Enter ����� ���������� " << endl; cin.get();
				bakery.sendClient();
				/*bakery.printbakeryInfo();
				bakery.edit();
				system("cls");
				bakery.printbakeryInfo();
				bakery.sendBakeries();
				cout << endl;
				cout << "������� Enter ����� ����������" << endl;
				rewind(stdin);
				cin.clear();
				rewind(stdin);
				cin.get();*/
			}
			break;
			case('6'):
				//������������ �������
			{
				system("cls");
				if (bakery.getbakeriesSize() == 0) {
					cout << "������ �����������" << endl << "������� Enter ����� ����������" << endl;
					rewind(stdin);
					cin.clear();
					rewind(stdin);
					cin.get();
					continue;
				}
				bakery.printbakeryInfo(owner_name);
				bakery.createReport(owner_name);
			}
			break;
			case('7'):
				//����� � �����������
			{
				send(Connection, "7", sizeof("7"), NULL);
				rewind(stdin);
				flag1 = TRUE;
			}
			break;
			}
		}
	}
}

void autorisation(const char companyName[BUFF]) {
	while (true) {
		system("cls");
		std::cout << "������������ ��� � " << companyName << std::endl;
		std::cout << "[1] ����� ��� �������������" << std::endl;
		std::cout << "[2] ����� ��� ������������" << std::endl;
		std::cout << "[3] �����" << std::endl;
		while (true) {
			rewind(stdin);
			std::cin.clear();
			char choice;
			choice = _getch();
			switch (choice) {
			case('1'):
			{
				send(Connection, "1", sizeof("1"), NULL);
				char login[BUFF], pass[BUFF];
				system("cls");
				while (true)
				{
					rewind(stdin);
					std::cin.clear();
					std::cout << "\t\t\t[�������������]" << std::endl;
					std::cout << "������� �����: "; std::cin >> login;
					std::cout << "������� ������: "; std::cin >> pass;
					if (strlen(login) < 3) {
						system("cls");
						std::cout << "������! ������� �������� �����. \n���������� ��� ���" << std::endl;
						continue;
					}
					if (strlen(pass) < 1) {
						system("cls");
						std::cout << "������! ������� �������� ������. \n���������� ��� ���" << std::endl;
						continue;
					}
					break;
				}

				//std::cout << "login - " << login << " pass - " << pass << std::endl;
				char answer_code[BUFF];//200 or 404
				send(Connection, login, sizeof(login), NULL);
				send(Connection, pass, sizeof(pass), NULL);
				recv(Connection, answer_code, sizeof(answer_code), NULL);
				rewind(stdin);
				//std::cout << answer_code << std:: endl;
				//std::cin.get();
				if (atoi(answer_code) == 200) {
					char owner[BUFF];
					strncpy(owner, "Admin", sizeof(owner));
					menu(1, owner);
				}
			}
			break;
			case('2'):
			{

				send(Connection, "2", sizeof("2"), NULL);
				char login[BUFF], pass[BUFF];
				system("cls");
				while (true)
				{
					rewind(stdin);
					std::cin.clear();
					std::cout << "\t\t\t[������������]" << std::endl;
					std::cout << "������� �����: "; std::cin >> login;
					std::cout << "������� ������: "; std::cin >> pass;
					if (strlen(login) < 6) {
						system("cls");
						std::cout << "������! ������� �������� �����. \n������� 6 ��������\n���������� ��� ���" << std::endl;
						continue;
					}
					if (strlen(pass) < 6) {
						system("cls");
						std::cout << "������! ������� �������� ������. \n������� 6 ��������\n���������� ��� ���" << std::endl;
						continue;
					}
					break;
				}
				//std::cout << "login - " << login << " pass - " << pass << std::endl;
				char answer_code[BUFF];//200 or 404
				send(Connection, login, sizeof(login), NULL);
				send(Connection, pass, sizeof(pass), NULL);
				recv(Connection, answer_code, sizeof(answer_code), NULL);

				rewind(stdin);
				//std::cout << answer_code << std::endl;
				//std::cin.get();
				if (atoi(answer_code) == 200) {
					char client_name[BUFF];
					recv(Connection, client_name, sizeof(client_name), NULL);
					menu(2, client_name);
				}
			}
			break;
			case('3'):
			{
				send(Connection, "3", sizeof("3"), NULL);
				exit(0);
			}
			break;
			}
			break;
		}
	}
}

void term_func() {
	cout << "��������� ����������� ������" << endl;
	system("pause");
	exit(-1);
}

int main(int argc, char* argv[]) {
	system("chcp 1251 >> null");
	set_terminate(term_func);
	//WSAStartup
	WSAData wsaData;
	WORD DLLVersion = MAKEWORD(2, 1);
	if (WSAStartup(DLLVersion, &wsaData) != 0) {
		std::cout << "Error" << std::endl;
		exit(1);
	}

	SOCKADDR_IN addr;
	int sizeofaddr = sizeof(addr);
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	addr.sin_port = htons(1111);
	addr.sin_family = AF_INET;

	Connection = socket(AF_INET, SOCK_STREAM, NULL);
	if (connect(Connection, (SOCKADDR*)& addr, sizeof(addr)) != 0) {
		std::cout << "Error: failed connect to server.\n";
		return 1;
	}
	std::cout << "Connected!\n";



	autorisation("�������");



	system("pause");
	return 0;
}