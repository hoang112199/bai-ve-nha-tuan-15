#include<iostream>
#include<string.h>
#include<string>

using namespace std;

//khai bao lop person
class person {

private:
	int id;
	string name;
	string gender;
	person* next;
public:
	person(int _id = 0, string _name = "unknow", string _gender = "unknow", person* _next = NULL) {
		id = _id;
		name = _name;
		gender = _gender;
		next = _next;
	}
	person(const person& per1) {
		id = per1.id;
		name = per1.name;
		gender = per1.gender;
		next = per1.next;
	}
	person& operator = (const person& per2) {
		id = per2.id;
		name = per2.name;
		gender = per2.gender;
		next = per2.next;
		return *this;
	}
	~person() {
		next = NULL;
	}
	void input_pers(int& id, string& name, string& gender)
	{
		cout << "nhap ma dinh danh: "; cin >> id;
		cout << "\n nhap ho ten: ";
		cin.ignore(1); getline(cin, name); cin.ignore(1);
		cout << "\n nhap gioi tinh: ";
		getline(cin, gender);
	}
	void swap(person& pers2) {
		person tmp = *this;
		*this = pers2;
		pers2 = tmp;
	}
	void display() {
		cout << "Person:\n";
		cout << "ID:\t" << id << endl;
		cout << "Name:\t" << name << endl;
		cout << "Gender:\t" << gender << endl;
	}
	friend class listofperson;
	friend class listofstudent;
};

//khai bao lop danh sach doi tuong person

class listofperson {
private:
	person* firstpers;
public:
	void lopers_Init(listofperson* lofpers) {
		lofpers->firstpers = 0;
	}
	void add_pers(listofperson* lofpers, person& per2); //ham them doi tuong person vao danh sach
	void add_pers_Final_input(listofperson* lofpers); //ham them doi tuong person vao cuoi danh sach
	int lofperson_Length(listofperson* lofpers); //ham them tinh chieu dai danh sach
	void lofpers_Display(listofperson* lofpers); //ham them hien thi cac doi tuong trong danh sach
	person* lofperson_Search(listofperson* lofpers, string name); //ham tim kiem doi tuong trong danh sach theo thuoc tinh ten
	void lofpers_RemoveAfter(person* node); //ham loai bo mot doi tuong sau mot doi tuong khac trong danh sach
	void sortListPerson(listofperson* lofpers); //sap xep theo thu tu có id tang dan
};

void listofperson::add_pers(listofperson* lofpers, person& per2)
{
	person* newpers = new person;
	newpers->id = per2.id;
	newpers->name = per2.name;
	newpers->gender = per2.gender;
	newpers->next = lofpers->firstpers;
	lofpers->firstpers = newpers;
}

void listofperson::add_pers_Final_input(listofperson* lofpers)
{
	int id;
	string name;
	string gender;
	person persIn;
	persIn.input_pers(id, name, gender);
	person* newpers = new person;
	newpers->id = id;
	newpers->name = name;
	newpers->gender = gender;
	person* node = lofpers->firstpers;
	while (node->next != 0)
	{
		node = node->next;
	}
	newpers->next = node->next;
	node->next = newpers;
}

int listofperson::lofperson_Length(listofperson* lofpers)
{
	person* node = lofpers->firstpers;
	int i = 0;
	while (node != 0)
	{
		i++;
		node = node->next;
	}
	return i;
}

void listofperson::lofpers_Display(listofperson* lofpers)
{
	person* node = lofpers->firstpers;
	int i = lofperson_Length(lofpers);
	cout << "\nDo dai cua list:\t" << i;
	if (lofpers->firstpers == 0)
		cout << "\nList rong " << endl;
	else
	{
		while (node != 0)
		{
			cout << "\nnguoi thu " << i << endl;
			cout << "\nid:\t\t" << node->id;
			cout << "\nname:\t\t" << node->name;
			cout << "\ngender:\t\t" << node->gender;
			node = node->next;
			i--;
		}
		cout << endl;
	}
}

person* listofperson::lofperson_Search(listofperson* lofpers, string name)
{
	person* node = lofpers->firstpers;
	while (node != 0) {
		if (node->name == name)
			return node;
		else
			return node = node->next;
	}
	return 0;
}

void listofperson::lofpers_RemoveAfter(person* node)
{
	person* obsoleteNode = node->next;
	node->next = obsoleteNode->next;
	delete obsoleteNode;
}

void listofperson::sortListPerson(listofperson* lofpers)
{
	for (person* node = lofpers->firstpers;node != NULL;node = node->next) {
		for (person* node1 = node->next;node1 != NULL;node1 = node1->next) {
			if (node->id > node1->id)
			{
				int temp = node->id;
				node->id = node1->id;
				node1->id = temp;
				string temp1 = node->name;
				node->name = node1->name;
				node1->name = temp1;
				temp1 = node->gender;
				node->gender = node1->gender;
				node1->gender = temp1;
			}
		}
	}
}

class student :public person {
	int stuID;
	string clas;
	student* next;
public:
	student() :person() {
		stuID = 0;
		clas = "None";
	}
	student(int _id, string _name, string _gender, person* _next, int _stuID, string _clas, student* __next = NULL) :person(_id, _name, _gender, _next) {
		stuID = _stuID;
		clas = _clas;
		next = __next;
	}
	student(const student& stu1) :person(stu1) {
		stuID = stu1.stuID;
		clas = stu1.clas;
	}
	student& operator = (const student& stu2) {
		person::operator=(stu2);
		stuID = stu2.stuID;
		clas = stu2.clas;
		return (*this);
	}
	~student() {
		next = NULL;
	}
	void display() {
		person::display();
		cout << "student ID:\t" << stuID << endl;
		cout << "Class:\t" << clas << endl;
	}
	friend class listofstudent;
};

class listofstudent {
private:
	student* firststudent;
public:
	void lopers_Init(listofstudent* lofstus) {
		lofstus->firststudent = 0;
	}
	void add_stus(listofstudent* lofstus, student& stu2); 
	int lofStudent_Length(listofstudent* lofstus); 
	void lofstus_Display(listofstudent* lofstus); 
	student* lofstudent_Search(listofstudent* lofstus, string name); 
	void lofstus_Fix(student* node);
	void lofstus_RemoveAfter(student* node); 
	void sortListStudent(listofstudent* lofstus); 
};

void listofstudent::add_stus(listofstudent* lofstus, student& stu2)
{
	student* newstus = new student;
	newstus->id = stu2.id;
	newstus->name = stu2.name;
	newstus->gender = stu2.gender;
	newstus->next = lofstus->firststudent;
	newstus->stuID = stu2.stuID;
	newstus->clas = stu2.clas;
	lofstus->firststudent = newstus;
}

int listofstudent::lofStudent_Length(listofstudent* lofstus)
{
	student* node = lofstus->firststudent;
	int i = 0;
	while (node != 0)
	{
		i++;
		node = node->next;
	}
	return i;
}

void listofstudent::lofstus_Display(listofstudent* lofstus)
{
	student* node = lofstus->firststudent;
	int i = lofStudent_Length(lofstus);
	cout << "\nDo dai cua list:\t" << i;
	if (lofstus->firststudent == 0)
		cout << "\nList rong " << endl;
	else
	{
		while (node != 0)
		{
			cout << "\nhoc sinh thu " << i << endl;
			cout << "\nid:\t\t" << node->id;
			cout << "\nname:\t\t" << node->name;
			cout << "\ngender:\t\t" << node->gender;
			cout << "\nstudent ID:\t" << node->stuID;
			cout << "\nclass:\t\t" << node->clas;
			node = node->next;
			i--;
		}
		cout << endl;
	}
}

student* listofstudent::lofstudent_Search(listofstudent* lofstus, string name)
{
	student* node = lofstus->firststudent;
	while (node != 0) {
		if (node->name == name)
			return node;
		else
			return node = node->next;
	}
	return 0;
}

void listofstudent::lofstus_Fix(student* node)
{
	int _ID,_stuID;
	string _name, _gender, _class;
	cout << "sua thong tin cua " << node->name << " :" << endl;
	cout << "nhap ID:";
	cin >> _ID;
	node->id = _ID;
	cout << "nhap ho ten :";
	cin.ignore(1);
	getline(cin, _name);
	node->name = _name;
	cout << "gioi tinh :";
	cin.ignore(1);
	getline(cin, _gender);
	node->gender = _gender;
	cout << "student ID:";
	cin >> _stuID;
	node->stuID = _stuID;
	cout << "lop :";
	cin.ignore(1);
	getline(cin, _class);
	node->clas = _class;
}

void listofstudent::lofstus_RemoveAfter(student* node)
{
	student* obsoleteNode = node->next;
	node->next = obsoleteNode->next;
	delete obsoleteNode;
}

void listofstudent::sortListStudent(listofstudent* lofstus)
{
	for (student* node = lofstus->firststudent;node != NULL;node = node->next) {
		for (student* node1 = node->next;node1 != NULL;node1 = node1->next) {
			if (node->stuID > node1->stuID)
			{
				int temp = node->id;
				node->id = node1->id;
				node1->id = temp;
				string temp1 = node->name;
				node->name = node1->name;
				node1->name = temp1;
				temp1 = node->gender;
				node->gender = node1->gender;
				node1->gender = temp1;
				temp = node->stuID;
				node->stuID = node1->stuID;
				node1->stuID = temp;
				temp1 = node->clas;
				node->clas = node1->clas;
				node1->clas = temp1;
			}
		}
	}
}

int main() {
	person per1(01, "nguyen van a", "male");
	person per2 = per1;
	cout << "thong tin nguoi 2: " << endl;
	per2.display();
	person per3(02, "nguyen van b", "male");
	per3.swap(per2);
	per2.display();
	listofperson lofpers;
	lofpers.lopers_Init(&lofpers);
	lofpers.add_pers(&lofpers, per1);
	lofpers.add_pers(&lofpers, per2);
	lofpers.add_pers(&lofpers, per3);
	lofpers.sortListPerson(&lofpers);
	cout << "\nnoi dung list 1 " << endl;
	lofpers.lofpers_Display(&lofpers);
	student std1(01, "le thi mai", "female", NULL, 22, "ET4");
	student std2(02, "le thi hoa", "female", NULL, 23, "ET4");
	std1.display();
	per2 = std1;
	per2.display();
	listofstudent lofstus;
	student std3(03, "le thi lan", "female", NULL, 24, "ET4");
	lofstus.lopers_Init(&lofstus);
	lofstus.add_stus(&lofstus, std1);
	lofstus.add_stus(&lofstus, std2);
	lofstus.add_stus(&lofstus, std3);
	lofstus.sortListStudent(&lofstus);
	lofstus.lofstus_Display(&lofstus);
	lofstus.lofstus_Fix(lofstus.lofstudent_Search(&lofstus, "le thi mai"));
	lofstus.lofstus_Display(&lofstus);
	lofstus.lofstus_RemoveAfter(lofstus.lofstudent_Search(&lofstus,"le thi hoa"));
	lofstus.lofstus_Display(&lofstus);
}