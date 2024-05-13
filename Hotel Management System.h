#pragma once
#include<iostream>
#include<fstream>
#include <string>
#include<map>
#include"roomFile.h"
#include"available_list.h"
#include"Primary Index.h"
#include"Secondary Index.h"
using namespace std; 
 
//class Client form Hotel_management_system
availableLinkedlist list;
class Client  {
    //Fieldes
    char name[20];
    int id;
    int numberOfDays;
    char mobileNumber[12];
    int roomNumber;
    char roomType;
    
public:
  
    //set
    void set_Client_name(char* name) { strcpy_s(this->name, name); }
    void set_Client_numberOfDays(int numberOfDays) {  this->numberOfDays = numberOfDays; }
    void set_Client_id(int id) { this->id = id; }
    void set_Client_mobileNumber(char* mobileNumber) { strcpy_s(this->mobileNumber, mobileNumber); }
    void set_Client_roomType(char roomType) {  this->roomType = roomType; }
    void set_Client_roomNumber(int roomNumber) { this->roomNumber=roomNumber; }
    //get
    char* get_Client_name() { return name; }
    int get_Client_id() { return id; }
    int get_Client_numberOfDays() { return numberOfDays; }
    char* get_Client_mobileNumber() { return mobileNumber; }
    char get_Client_roomType() { return roomType; }
    int get_Client_roomNumber() { return roomNumber; }


    void showDataForClient() {

        cout << "\n|Name : "<< name;
        cout << "\n|Mobile Number : "<< mobileNumber;
        cout << "\n|ID : "<< id;
        cout << "\n|The type of custom : " << roomType;
        cout << "\n|The Room Number : " << roomNumber;
        cout << "\n|Number of days of reservation : " << numberOfDays;

        cout << "\n";
    }


    int recordSize() {
        int recordsize = strlen(name) + sizeof(id) + sizeof(numberOfDays) +
            strlen(mobileNumber) + sizeof(roomNumber) + sizeof(roomType); 
        return recordsize;
    }
    friend void  readFromFlie();
    friend void DeleteById(int Id) ;
    friend Client readAtPlace(int offset);
};
Client getData_info();
void addRecordInFile();
void ShowAllRecordInFile(Client&);
void readFromFlie(fstream&);
void writeEndFile(Client&, fstream&);
void writeAtPlace(Client&, fstream&, int);
void DeleteById(int);
void searchById(int);
void searchByName();
void Bill(int numberOfDays, char Type);
void Search();
int menu();
void HotelManagementSystem();
Client getData_info() {
    Client obj{};
    char name[20], mobileNumber[12]; char roomType;  
    int id, roomNumber, numberOfDays;
    cin.ignore();
    cout << "Enter  Name : ";
    cin.getline(name, 20); cin.clear();
    
    cout << "\nEnter  Mobile Number : ";
    cin.getline(mobileNumber, 12); cin.clear();

    cout << "\nThe type of custom for a Singl (Enter S) the price 50$ a night or Double (Enter D) ,the price 100$ a night? : ";
    cin >> roomType; cin.clear();
    
    cout << "\nEnter  ID : ";
    cin >> id; cin.clear();

    cout << "\nEnter Number of days of reservation : ";
    cin >> numberOfDays; cin.clear();

    /*cout << "\nEnter The Room Number : ";*/
   /* cin>>roomNumber; cin.clear();*/
    roomNumber = ser(roomType, id);
    
    cout << "\n";
    cin.ignore();

    obj.set_Client_name(name);
    obj.set_Client_id(id);
    obj.set_Client_mobileNumber(mobileNumber);
    obj.set_Client_roomNumber(roomNumber);
    obj.set_Client_roomType(roomType);
    obj.set_Client_numberOfDays(numberOfDays);
    return obj;
}
/*
1.Open Primary and Secondary Index Files
2. Read and load Primary Index into array.
(PrmIndxArray)
3. Read and load Secondary Index into array.
(ScndIndxArray)
4. Take input record from the user
5. Open data file
6. Write the record to data file.
7. Close data file
8. Inorder insert of Record ID & offset into
PrmIndxArray.
9. Inorder insert Record ID & Name into
ScndIndxArray
10. Write the Primary and Secondary indices
to files
11. Close Primary and Secondary Index files


*/
void writeEndFile(Client& client, fstream& projectFile) {
    projectFile.seekp(0, ios::end);
   
    fstream PrimaryKey;
	PrimaryKey.open("Primary File.txt", ios::in | ios::out | ios::binary);
    AddInFilePrimaryIndex(client.get_Client_id(), projectFile.tellg());

    fstream SecondaryIndex;
    SecondaryIndex.open("Secondary Index.txt", ios::in | ios::out | ios::binary);
    AddInFileSecindaryIndex(client.get_Client_name(), client.get_Client_id());

	short len = strlen(client.get_Client_name());
    projectFile.write((char*)&len, sizeof(short));
    projectFile.write(client.get_Client_name(), strlen(client.get_Client_name()));


    int id = client.get_Client_id();

	len = sizeof(client.get_Client_id());
    projectFile.write((char*)&len, sizeof(short));
    projectFile.write((char*)&id, sizeof(client.get_Client_id()));

	len = strlen(client.get_Client_mobileNumber());
    projectFile.write((char*)&len, sizeof(short));
    projectFile.write(client.get_Client_mobileNumber(), strlen(client.get_Client_mobileNumber()));

    int roomNumber = client.get_Client_roomNumber();

	len = sizeof(client.get_Client_roomNumber());
    projectFile.write((char*)&len, sizeof(short));
    projectFile.write((char*)&roomNumber, sizeof(client.get_Client_roomNumber()));

    len = sizeof(client.get_Client_roomType()); char roomType = (client.get_Client_roomType());
    projectFile.write((char*)&len, sizeof(short));
    projectFile.write((char*)&roomType, sizeof(client.get_Client_roomType()));

    int numberOfDays = client.get_Client_id();

    len = sizeof(client.get_Client_numberOfDays());
    projectFile.write((char*)&len, sizeof(short));
    projectFile.write((char*)&numberOfDays, sizeof(client.get_Client_numberOfDays()));

    projectFile.clear();

    PrimaryKey.clear();
    PrimaryKey.close();

    SecondaryIndex.clear();
    SecondaryIndex.close();

}

void writeAtPlace(Client& client, fstream& fileName,int offset) {
    fileName.seekp(offset, ios::beg);

    fstream PrimaryKey;
    PrimaryKey.open("Primary File.txt", ios::in | ios::out | ios::binary);
    AddInFilePrimaryIndex(client.get_Client_id(),offset);

    fstream SecondaryIndex;
    SecondaryIndex.open("Secondary Index.txt", ios::in | ios::out | ios::binary);
    AddInFileSecindaryIndex(client.get_Client_name(), client.get_Client_id());

    short len = strlen(client.get_Client_name());
    fileName.write((char*)&len, sizeof(short));
    fileName.write(client.get_Client_name(), strlen(client.get_Client_name()));

    int id = client.get_Client_id();
    len = sizeof(client.get_Client_id());
    fileName.write((char*)&len, sizeof(short));
    fileName.write((char*)&id, sizeof(client.get_Client_id()));

    len = strlen(client.get_Client_mobileNumber());
    fileName.write((char*)&len, sizeof(short));
    fileName.write(client.get_Client_mobileNumber(), strlen(client.get_Client_mobileNumber()));

    int roomNumber = client.get_Client_roomNumber();
    len = sizeof(client.get_Client_roomNumber());
    fileName.write((char*)&len, sizeof(short));
    fileName.write((char*)&roomNumber, sizeof(client.get_Client_roomNumber()));

    len = sizeof(client.get_Client_roomType()); char roomType = (client.get_Client_roomType());
    fileName.write((char*)&len, sizeof(short));
    fileName.write((char*)&roomType, sizeof(client.get_Client_roomType()));

    int numberOfDays = client.get_Client_id();

    len = sizeof(client.get_Client_numberOfDays());
    fileName.write((char*)&len, sizeof(short));
    fileName.write((char*)&numberOfDays, sizeof(client.get_Client_numberOfDays()));

    fileName.clear();

    PrimaryKey.clear();
    PrimaryKey.close();

    SecondaryIndex.clear();
    SecondaryIndex.close();
}

void ShowAllRecordInFile(Client& client) {
    cout << " | Name : " << client.get_Client_name() << endl;
    cout << " | Id : " << client.get_Client_id() << endl;
    cout << " | Mobile Number : " << client.get_Client_mobileNumber() << endl;
    cout << " | Room Type : " << client.get_Client_roomType() << endl;
    cout << " | Room Number :" << client.get_Client_roomNumber() << endl;
    cout << " | Number of days of reservation :" << client.get_Client_numberOfDays() << endl;

}

void readFromFlie() {
    fstream fileName;
    fileName.open("projectFile.txt", ios::in | ios::out | ios::binary);
/*    fileName.clear();*/  
    fileName.seekg(0, ios::beg);
    Client client{};
    int i = 0;
    short len = 0;
    do {
        

        if (i && client.name[0] != '*') {
            cout << "*************" << i << "*************\n";
            client.showDataForClient();
        }
         

        fileName.read((char*)&len, sizeof(short));
        fileName.read(client.name, len);
        client.name[len] = '\0';

        fileName.read((char*)&len, sizeof(short));
        fileName.read((char*)&client.id, len);
        

        fileName.read((char*)&len, sizeof(short));
        fileName.read(client.mobileNumber, len);
        client.mobileNumber[len] = '\0';

        fileName.read((char*)&len, sizeof(short));
        fileName.read((char*)&client.roomNumber, len);
       

        fileName.read((char*)&len, sizeof(short));
        fileName.read((char*)&client.roomType, len);
         
        fileName.read((char*)&len, sizeof(short));
        fileName.read((char*)&client.numberOfDays, len);

        i++;
    } while (!fileName.eof());
    fileName.clear();
    system("PAUSE");
    
     
}  

Client readAtPlace(int offset) {
        fstream fileName;
        fileName.open("projectFile.txt", ios::in | ios::out | ios::binary);
        fileName.clear();
        fileName.seekg(offset,ios::beg);
        Client client;
        short len = 0;  
        
            fileName.read((char*)&len, sizeof(short));
            fileName.read(client.name, len);
            client.name[len] = '\0';

            fileName.read((char*)&len, sizeof(short));
            fileName.read((char*)&client.id, len);


            fileName.read((char*)&len, sizeof(short));
            fileName.read(client.mobileNumber, len);
            client.mobileNumber[len] = '\0';

            fileName.read((char*)&len, sizeof(short));
            fileName.read((char*)&client.roomNumber, len);

            fileName.read((char*)&len, sizeof(short));
            fileName.read((char*)&client.roomType, len);

            fileName.read((char*)&len, sizeof(short));
            fileName.read((char*)&client.numberOfDays, len);
           
        fileName.clear();
     return client;


}

void addRecordInFile() {
    Client client{};
    client=getData_info();
    fstream projectFile;
    projectFile.open("projectFile.txt", ios::in | ios::out | ios::binary);
    if (client.get_Client_roomNumber() == -1) {
        cout << "*********Not Room Empty*********"<<endl;
        projectFile.clear();
        return;
    }
    cout << "-------Reservation successful--------" << endl;
    if (list.isEmpty()) {
        writeEndFile(client, projectFile);
    }
    else{
        int recordsize = client.recordSize();
            
        int offset = list.searchAndDeleteNode(recordsize);
        if (offset == -1)
        {
            writeEndFile(client, projectFile);
        }
        else
        {
            writeAtPlace(client, projectFile, offset);
        }
    }
    cout << "The Room Number : " << client.get_Client_roomNumber() << endl;
    Bill(client.get_Client_numberOfDays(), client.get_Client_roomType());
    projectFile.clear();
}

void Bill(int numberOfDays,char Type) {
    if (Type == 'S') {
        cout << "Bill :" << numberOfDays * 50 << endl;
    }
    else {
        cout << "Bill :" << numberOfDays * 100 << endl;

    }
}

void DeleteById(int Id) {

 


    fstream PrimaryKey;
    PrimaryKey.open("Primary File.txt", ios::in | ios::out| ios::binary);
    Client client;
  
    short len;
    map<int, int>PrmIndxArray;
    int index, i = 0,id,offset;
    bool flag = 0;
    do {
        if (i && id != -1) {
            cout << "id= " << id << " " << "off=" << offset << endl;
            PrmIndxArray[id] = offset;
            if (id == Id) flag = 1;
        }

        PrimaryKey.read((char*)&len, sizeof(short));
        PrimaryKey.read((char*)&id, len);

        PrimaryKey.read((char*)&len, sizeof(short));
        PrimaryKey.read((char*)&offset, len);

        i++;
    } while (!PrimaryKey.eof());

     offset = PrmIndxArray[Id];

    fstream projectFile;
    projectFile.open("projectFile.txt", ios::in | ios::out | ios::binary);
    projectFile.seekg(0, ios::beg);
    projectFile.seekp(0, ios::beg);

    if (!flag) {
        cout << "Client is not found!\n";

    }
    else {
        client= readAtPlace(offset);
        cout << "--------Client Delete---------" << endl;
        int RecordSize = client.recordSize();
        list.addDeletedNodeToList(offset, RecordSize);
        projectFile.seekp(offset, ios::beg);
        client.name[0] = '*'; 
        short len = strlen(client.name);
        projectFile.write((char*)&len, sizeof(short));
        projectFile.write(client.name, strlen(client.name));
        EmptyRoom(Id);
 
        DeleteInFilePrimaryIndex(Id);
        DeleteInFileSecindaryIndex(Id);

        
    }

    projectFile.clear();
    projectFile.close();

    PrimaryKey.clear();
    PrimaryKey.close();
}

/*
1.Open Primary Index File
2. Read and load Primary Index into array.
(PrmIndxArray)
3. Take the required ID from user
4. Search PrmIndxArray using the retrieved
ID to get the record offset

5. Open data file
6. Read the student record from the file
using the retrieved offset. (Seek to
“offset” then read)
7. Close data file.
8. Close Primary file
*/
void searchById(int ID){
 
	fstream primaryFile;
    primaryFile.open("primary File.txt", ios::in | ios::out | ios::binary);
	map<int, int>PrmIndxArray;
	int id=0, offsetFromFile;
	short len;
    bool flag = 0;
	int i = 0;
	do {
		if (i && id != -1) {
            //cout << "id= " << id << " " << "offset =" << offsetFromFile << endl;
            PrmIndxArray[id] = offsetFromFile;
            if (id == ID)flag = 1;
		}

        primaryFile.read((char*)&len, sizeof(short));
        primaryFile.read((char*)&id, len);

        primaryFile.read((char*)&len, sizeof(short));
        primaryFile.read((char*)&offsetFromFile, len);

		i++;
	} while (!primaryFile.eof());

	int offset = PrmIndxArray[ID];
    if (!flag) {
        cout << "Client is not found!\n";
    }
    else {
        Client client = readAtPlace(offset);
        client.showDataForClient();
    }
    primaryFile.clear();
    primaryFile.close();
}

/*
2. Read and load Secondary Index into array.
(ScndIndxArray)
3. Take the required Name from user
4. Search ScndIndxArray using the given Name to get the
ID
5. If name found:
• Read and load Primary Index into array.
(PrmIndxArray)
• Search PrmIndxArray using the retrieved ID to get
the record offset
◦ If retrieved ID not found in PrmIndxArray (deleted
record), Go to step 9
◦ Else, go to step 6

6. Open data file
7. Read the student record from the file
using the retrieved offset. (Seek to
“offset” then read)
8. Close data file.
9. Close Primary index file
*/
void searchByName(){
    char Name[20];cout << "Enter Name :";
    cin.getline(Name,20); cin.clear();
    cout << "\n";
       int id= searcheSimilarNames(Name);
       searchById(id);
       /* fstream SecondaryIndex;
        SecondaryIndex.open("Secondary Index.txt", ios::in | ios::out | ios::binary);
        map<string, int>ScndIndxArray;
        SecondaryIndex.seekg(0, ios::beg);
        int id = 0, i = 0;
        short len; char name[20]{};
        bool flag = 0;

        do {
            if (i && name[0] != '*') {
                ScndIndxArray[name] = id;
                if (strcmp(name, Name) == 0)flag = 1;
            }

            SecondaryIndex.read((char*)&len, sizeof(short));
            SecondaryIndex.read(name, len);

            SecondaryIndex.read((char*)&len, sizeof(short));
            SecondaryIndex.read((char*)&id, len);

            i++;
        } while (!SecondaryIndex.eof());

        int ID = ScndIndxArray[Name];

        if (!flag) {
            cout << "The name not found!\n";
        }
        else {
            fstream primaryFile;
            primaryFile.open("primary File.txt", ios::in | ios::out | ios::binary);
            map<int, int>PrmIndxArray;
            int offsetFromFile;
            i = id = 0;
            do {
                if (i && id != -1) {
                    PrmIndxArray[id] = offsetFromFile;
                }

                primaryFile.read((char*)&len, sizeof(short));
                primaryFile.read((char*)&id, len);

                primaryFile.read((char*)&len, sizeof(short));
                primaryFile.read((char*)&offsetFromFile, len);

                i++;
            } while (!primaryFile.eof());
            int offset = PrmIndxArray[ID];


            Client client = readAtPlace(offset);
            cout << "------- Clinent Data --------" << endl;
            client.setDataForClient();

            primaryFile.clear();
            primaryFile.close();

            SecondaryIndex.clear();
            SecondaryIndex.close();
        }*/
    
}

void Search() {
    cout << "----- To research by id enter 0 for  research by name enter 1 ----- \n";
    int  expression,id;
    cin >> expression;
    cin.ignore();

    switch (expression) {
    case 0:
        cout << "Enter ID:";
        cin >> id; cin.clear();
        searchById(id);
        break;
    case 1:
        searchByName();
        break;
    default:
        cout << "***** NOT VALID *****\n";
    }

};

int menu()
{
 
    
        int choice = -1;
        while (choice == -1) {
            cout << "\n----------- Enter your choics ----------- \n";
            cout << "1) Reserve a room for a client \n";
            cout << "2) print all client \n";
            cout << "3) Search\n";
            cout << "4) Delete by ID\n";
            cout << "5) Update\n";
            cout << "6) Exit\n";

            cin >> choice;

            if (!(1 <= choice && choice <= 6))
            {
                cout << "Invalid choice. Try again\n";
                choice = -1;   //loop keep werking .....
            }

        }

        return choice;
 
}

void HotelManagementSystem()
{
    cout << "------------------- Welcome to the hotel------------------- "<< endl;
    fstream projectFile;
    projectFile.open("projectFile.txt", ios::in | ios::out  | ios::binary);
    fstream PrimaryKey;
    PrimaryKey.open("Primary File.txt", ios::in | ios::out  | ios::binary);
    fstream SecondaryKey;
    SecondaryKey.open("Secondary Index.txt", ios::in | ios::out  | ios::binary);
 
    while (1)
    {
         /*system("cls");*/

        int choice = menu();

        if (choice == 1) addRecordInFile();
        else if (choice == 2) readFromFlie();
        else if (choice == 3) Search();
        else if (choice == 4) {
            int id; cout << "Enter Id:";
            cin >> id; cout << "\n";
            DeleteById(id);
        }
        else if (choice == 5) {}
        else
        {
            projectFile.clear();
            projectFile.close();
            PrimaryKey.clear();
            PrimaryKey.close();
            SecondaryKey.clear();
            SecondaryKey.close();
            break;
        }
    }


}
