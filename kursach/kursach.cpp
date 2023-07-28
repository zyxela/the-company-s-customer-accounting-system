#include <iostream>
#include<fstream>
#include<string>
#include <stdio.h>
#include<regex>

using namespace std;

class ClientInfo
{
	string name;
	string surname;
	string patronymic;
	string contactInf;

public:
	void setName(string name) {
		this->name = name;
	}
	void setSurname(string surname) {
		this->surname = surname;
	}
	void setPatronymic(string patronymic) {
		this->patronymic = patronymic;
	}
	void setContactInf(string contactInf) {
		this->contactInf = contactInf;
	}


	string getName()
	{
		return name;
	}
	string getSurname()
	{
		return surname;
	}
	string getPatronymic()
	{
		return patronymic;
	}
	string getContactInf()
	{
		return contactInf;
	}


	virtual void createExcelFile(string path)
	{

		ofstream file;
		file.open(path + ".csv", std::ofstream::app);
		file << this->getName() << ";" << this->getSurname() << ";" << this->getPatronymic() << ';' << this->getContactInf() << endl;
		file.close();
	}
};


class Product
{
protected:
	int productId;
	string name;
	double price;

public:
	void setProductId(int productId) {
		this->productId = productId;
	}
	void setName(string name) {
		this->name = name;
	}
	void setPrice(double price) {
		this->price = price;
	}


	int getProductId() {
		return this->productId;
	}
	string getName() {
		return this->name;
	}
	double getPrice() {
		return this->price;
	}


	void createExcelFile(string path)
	{
		ofstream file;
		file.open(path + ".csv", std::ofstream::app);
		file << this->getProductId() << ";" << this->getName() << ";" << this->getPrice() << endl;
		file.close();
	}



};

class ProductForOrder
{
	int orderId;
	int productId;
	double count;


public:
	void setOrderId(int orderId) {
		this->orderId = orderId;
	}

	void setProductId(int productId) {
		this->productId = productId;
	}
	void setCount(double count) {
		this->count = count;
	}



	int getOrderId() {
		return orderId;
	}
	int getProductId() {
		return productId;
	}
	double getCount() {
		return count;
	}


	void createExcelFile(string path)
	{
		ofstream file;
		file.open(path + ".csv", std::ofstream::app);
		file << this->getOrderId() << this->getProductId() << ";" << this->getCount() << endl;
		file.close();
	}
	double getPrice(int productID)
	{
		ifstream fin;
		string str;
		double res;
		fin.open("products.csv");
		for (int i = 1; !fin.eof(); )
		{
			str = "";
			fin >> str;
			if (str != "")
			{
				cmatch res;
				regex regular("(\\w)\\d+");
				regex_search(str.c_str(), res, regular);

				return stod(res[0]);

			}

		}
		fin.close();
	}
	double getTotal(int prodId)
	{
		return getPrice(prodId) * getCount();
	}
	void getInfoFromFile(string path, int oId)
	{
		ifstream file;
		string str;
		file.open(path);
		for (int i = 1; !file.eof(); )
		{
			str = "";
			getline(file, str);
			if (str != "")
			{
				cout << i << ") " << str << ";" << this->getPrice(oId) << ";" << this->getTotal(oId) << endl;
				i++;
			}

		}
		file.close();

	}
};

class Order
{
	int orderId;
	int clientId;
	double sum;
	string status;
public:
	void setOrderId(int id) {
		this->orderId = id;
	}
	void setSum(double sum) {
		this->sum = sum;
	}
	void setStatus(string status) {
		this->status = status;
	}
	void setClientId(int id)
	{
		this->clientId = id;
	}

	int getOrderId() {
		return orderId;
	}
	double getSum() {
		return sum;
	}
	string getStatus() {
		return status;
	}
	int getClientId()
	{
		return clientId;
	}


	void createExcelFile(string path)
	{
		ofstream file;
		file.open(path + ".csv", std::ofstream::app);
		file << this->getOrderId() << ";" << this->getClientId() << ';' << this->getStatus() << endl;
		file.close();
	}
};

class ClientComerticalInfo :public ClientInfo
{
	int orderId;
	double debt;
	string status;

public:
	void setOrderId(int orderId)
	{
		this->orderId = orderId;
	}

	void setDebt(double debt)
	{
		this->debt = debt;
	}

	void setStatus(string status)
	{
		this->status = status;
	}

	int getOrderId()
	{
		return orderId;
	}

	double getDebt()
	{
		return debt;
	}

	string getStatus()
	{
		return status;
	}

	virtual void createExcelFile(string path) override
	{
		ofstream file;
		file.open(path + ".csv", std::ofstream::app);
		file << this->getName() << ";" << this->getSurname() << ";" << this->getPatronymic() << ';'
			<< this->getContactInf() << ";" << this->getOrderId() << ";" << this->getDebt() << ";" << this->getStatus() << endl;
		file.close();
	}

};

void getInfoFromFile(string path);
void clients_menu();
void main_menu();
void orders_menu();
void productsFO_menu();
void products_menu();



int main()
{
	setlocale(LC_ALL, "rus");

	main_menu();

}

void main_menu()
{
	while (true)
	{

		cout << "Выберете действие:\n";
		cout << "1) Клиенты\n";
		cout << "2) Заказы\n";
		cout << "3) Продукты \n";
		cout << "4) Выход\n";
		int key = 0;
		cin >> key;
		switch (key)
		{
		case 1:
			system("cls");
			clients_menu();
			break;
		case 2:
			system("cls");
			orders_menu();
			break;
		case 3:
			system("cls");
			products_menu();
			break;

		default:
			exit(0);
		}
	}
}

void addClient(string path, string name, string surname, string patronymic, string contactInf, int orderId = 0, double debt = 0, string status = "")
{
	ClientComerticalInfo cl;
	cl.setName(name);
	cl.setSurname(surname);
	cl.setPatronymic(patronymic);
	cl.setContactInf(contactInf);
	cl.setOrderId(orderId);
	cl.setDebt(debt);
	cl.setStatus(status);
	cl.createExcelFile(path);

}

void editInf(string path, int index, string editedInf)
{
	if (!isdigit(index))
		throw "недопустимый символ";
	string* arr = new string[100];
	int len = 0;
	string str;
	ifstream fin;
	fin.open(path);
	for (int i = 0; !fin.eof(); i++)
	{
		str = "";
		getline(fin, str);
		arr[i] = str;
		len++;
	}
	arr[index - 1] = editedInf;
	fin.close();

	ofstream fout;
	fout.open(path);
	for (int i = 0; i < len; i++)
	{
		fout << arr[i] << endl;
	}
	fout.close();
	delete[] arr;
}
void clients_menu()
{

	while (true)
	{
		system("cls");
		cout << "Выберете действие:\n";
		cout << "1) Добавить\n";
		cout << "2) Показать список клиентов\n";
		cout << "3) Редактировать \n";
		cout << "4) Удалить \n";
		cout << "5) Назад\n";
		int key = 0;
		cin >> key;
		string name, sn, p, ci, newInf;
		int oi, numberid;
		switch (key)
		{
		case 1:
			system("cls");
			cout << "Имя: " << endl;
			cin >> name;
			cout << "Фамилия: " << endl;
			cin >> sn;
			cout << "Отчество: " << endl;
			cin >> p;
			cout << "Контактная информация: " << endl;
			cin >> ci;
			cout << "Уникальный id для заказов: " << endl;
			cin >> oi;
			addClient("clients", name, sn, p, ci, oi);
			system("pause");
			break;
		case 2:
			system("cls");
			getInfoFromFile("clients.csv");
			system("pause");
			break;
		case 3:
			system("cls");
			cout << "Введите номер клиента:" << endl;
			cin >> numberid;
			cout << "Введите Новую информацию(имя, фамилия, отчество, контактная информация, айди для заказоа ),\n писать через \";\" без пробелов, а то программа сломается))):" << endl;
			cin >> newInf;
			try
			{
				editInf("clients.csv", numberid, newInf);

			}
			catch (const char* msg)
			{
				cout << msg;
				system("pause");
			}
			break;
		case 4:
			system("cls");
			cout << "Введите номер клиента:" << endl;
			cin >> numberid;
			editInf("clients.csv", numberid, "");
			break;
		default:
			system("cls");
			main_menu();
		}
	}
}

void addOrder(string path, int orderId, int clientId, string status)
{
	Order ordr;
	ordr.setOrderId(orderId);
	ordr.setClientId(clientId);
	ordr.setStatus(status);
	ordr.createExcelFile(path);
}

void showOrder(int orderId)
{
	ifstream fin;
	string str;
	fin.open("productsFO.csv");
	for (int i = 1; !fin.eof(); )
	{
		str = "";
		fin >> str;
		if (str != "")
		{
			if (orderId == atoi(str.c_str()))
			{
				cout << i << ") " << str << endl;
				i++;
			}

		}

	}
	fin.close();
}

void orders_menu()
{
	while (true)
	{

		cout << "Выберете действие:\n";
		cout << "1) Добавить\n";
		cout << "2) Показать список заказов\n";
		cout << "3) Редактировать \n";
		cout << "4) Удалить \n";
		cout << "5) Просмотреть заказ\n";
		cout << "6) Назад\n";

		int ordId, clientId;
		double sum;
		string status;

		int indx;
		string editInform;
		int key = 0;
		char kc;
		cin >> key;
		switch (key)
		{
		case 1:
			system("cls");

			cout << "Введите Id закакза: \n";
			cin >> ordId;

			cout << "Введите Id клиента: \n";
			cin >> clientId;


			cout << "Впишите статус: \n";
			cin >> status;

			addOrder("orders", ordId, clientId, status);
			break;

		case 2:
			system("cls");
			getInfoFromFile("orders.csv");
			cout << "Доп. инф. о заказе (y/n)";
			cin >> kc;
			if (kc == 'y')
				productsFO_menu();
			break;

		case 3:
			system("cls");
			cout << "Введите НОМЕР(не ID) заказа:\n";
			cin >> indx;
			cin >> editInform;
			editInf("orders.csv", indx, editInform);
			break;

		case 4:
			system("cls");
			cout << "Введите номер позиции, которую хотите закрыть: \n";
			cin >> indx;
			editInf("orders.csv", indx, "");
			system("cls");
			break;

		case 5:
			system("cls");
			cout << "Введите ID заказа";
			cin >> ordId;
			showOrder(ordId);
			break;
		default:
			system("cls");
			main_menu();
		}
	}
}

void addProductFO(string path, int orderId, int productId, double count)
{
	ProductForOrder pfo;
	pfo.setOrderId(orderId);
	pfo.setProductId(productId);
	pfo.setCount(count);
	pfo.createExcelFile(path);
}
void productsFO_menu()
{
	while (true)
	{
		system("cls");
		cout << "Выберете действие:\n";
		cout << "1) Добавить\n";
		cout << "2) Показать список продуктов\n";
		cout << "3) Редактировать \n";
		cout << "4) Удалить \n";
		cout << "5) Назад\n";

		int oId;
		int productId;
		double count;

		ProductForOrder pfo;


		int indx;
		string newInf;

		int key = 0;
		cin >> key;
		switch (key)
		{
		case 1:
			system("cls");

			cout << "Введите Id заказа для которого вы хотите добавить продукт:\n";
			cin >> oId;

			cout << "Введите Id продукта: \n";
			cin >> productId;

			cout << "Введите количество товара:\n";
			cin >> count;

			addProductFO("productsFO", oId, productId, count);
			system("pause");
			break;

		case 2:
			system("cls");
			pfo.getInfoFromFile("productsFO.csv", 1);

			system("pause");
			break;
		case 3:
			system("cls");
			cout << "Введите позицию продукта: \n";
			cin >> indx;
			cout << "Введите редактированную информацию: \n";
			cin >> newInf;
			editInf("productsFO.csv", indx, newInf);
			system("pause");
			break;

		case 4:
			system("cls");
			cout << "Введите позицию продукта: \n";
			cin >> indx;
			editInf("productsFO.csv", indx, "");
			system("pause");
			break;

		default:
			system("cls");
			main_menu();
		}
	}
}

void addProducts(string path, string name, int id, double price)
{
	Product pr;
	pr.setName(name);
	pr.setProductId(id);
	pr.setPrice(price);
	pr.createExcelFile(path);
}

void products_menu()
{
	cout << "Выберете действие:\n";
	cout << "1) Добавить\n";
	cout << "2) Показать список продуктов\n";
	cout << "3) Редактировать \n";
	cout << "4) Удалить \n";
	cout << "5) Назад\n";

	int price;
	int productId;
	double count;

	int indx;
	string newInf, name;

	int key = 0;
	cin >> key;
	switch (key)
	{
	case 1:
		system("cls");

		cout << "Введите название товара:\n";
		cin >> name;

		cout << "Введите Id продукта: \n";
		cin >> productId;

		cout << "Введите цену товара:\n";
		cin >> price;


		addProducts("products", name, productId, price);
		system("pause");

		break;
	case 2:
		system("cls");
		getInfoFromFile("products.csv");
		system("pause");
		break;
	case 3:
		system("cls");
		cout << "Введите позицию продукта: \n";
		cin >> indx;
		cout << "Введите редактированную информацию: \n";
		cin >> newInf;
		editInf("products.csv", indx, newInf);
		system("pause");

		break;
	case 4:
		system("cls");
		cout << "Введите позицию продукта: \n";
		cin >> indx;
		editInf("products.csv", indx, "");
		system("pause");

		break;
	default:
		system("cls");
		main_menu();
	}
}


void getInfoFromFile(string path)
{
	ifstream file;
	string str;
	file.open(path);
	for (int i = 1; !file.eof(); )
	{
		str = "";
		getline(file, str);
		if (str != "")
		{
			cout << i << ") " << str << endl;
			i++;
		}

	}
	file.close();

}
