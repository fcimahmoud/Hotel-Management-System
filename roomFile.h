#pragma once
#include<iostream>
#include<fstream>
using namespace std;
class Room;
void writeIN(Room&, int);
void read();
class Room
{
	char type;
	int roomNumber;
	char emptyOrNot;// 0 is Empty  , 1 booked
	int id;// id of client booked room if id==-1 empty
public:
    //set
    void set_Room_type(char type) {this->type = type;}
    void set_Room_roomNumber(int roomNumber) { this->roomNumber = roomNumber; }
    void set_Room_emptyOrNot(char emptyOrNot) {  this->emptyOrNot= emptyOrNot; }
    void set_Room_id(int id) { this->id = id; }
    //get
    char get_Room_type() {return type;}
    int get_Room_id() {return id;}
    char get_Room_emptyOrNot() { return emptyOrNot; }
    int get_Room_roomNumber() { return roomNumber; }
    void showDataForRoom() {

        cout << "\n|ID : " << id;
        cout << "\n|The type of custom : " << type;
        cout << "\n|The Room Number : " << roomNumber;
        cout << "\n|The Room is Empty or Not : " << emptyOrNot;

        cout << "\n";
    }
    int recordSize() {
        int recordsize =   sizeof(id) + sizeof(emptyOrNot) +
              sizeof(roomNumber) + sizeof(type);
        return recordsize;
    }
 
    friend void read();
    friend int ser(char  , int  );
    friend void EmptyRoom(int ID);
};

void get() {
    Room obj{};
    char emptyOrNot = '0', type;
    int id = -1,i=0; static int roomNumber=100;
    while (i < 15) {
        cout << "**********" << endl;
        static int ind = 1;
        if (ind <= 10)type = 'S';
        else type = 'D';

        obj.set_Room_id(id);
        obj.set_Room_roomNumber(roomNumber);
        obj.set_Room_type(type);
        obj.set_Room_emptyOrNot(emptyOrNot);
        obj.showDataForRoom();
        //writeIN(obj);
        i++; roomNumber++; ind++;
    }
}

void writeIN(Room &room,int offsett) {

    fstream RoomFlie;
    RoomFlie.open("RoomFlie.txt", ios::in | ios::out| ios::binary);
    RoomFlie.clear();
    RoomFlie.seekp(offsett, ios::beg);
   

    short len;
    char roomType = (room.get_Room_type());

    len = sizeof(room.get_Room_type());
    RoomFlie.write((char*)&len, sizeof(short));
    RoomFlie.write((char*)&roomType, sizeof(room.get_Room_type()));

    int roomNumber = room.get_Room_roomNumber();

    len = sizeof(room.get_Room_roomNumber());
    RoomFlie.write((char*)&len, sizeof(short));
    RoomFlie.write((char*)&roomNumber, sizeof(room.get_Room_roomNumber()));

    char emptyOrNot = room.get_Room_emptyOrNot();

    len = sizeof(room.get_Room_emptyOrNot());
    RoomFlie.write((char*)&len, sizeof(short));
    RoomFlie.write((char*)&emptyOrNot, sizeof(room.get_Room_emptyOrNot()));

    int id = room.get_Room_id();

    len = sizeof(room.get_Room_id());
    RoomFlie.write((char*)&len, sizeof(short));
    RoomFlie.write((char*)&id, sizeof(room.get_Room_id()));

    RoomFlie.clear();
    RoomFlie.close();

}

void read() {
    fstream RoomFlie;
    RoomFlie.open("RoomFlie.txt", ios::in | ios::out| ios::binary);
    RoomFlie.seekg(0, ios::beg);
    Room room{};
    int i = 0;
    short len = 0;
    do {
        if (i) {
            cout << "*************" << i << "*************\n";
            room.showDataForRoom();
        }
        RoomFlie.read((char*)&len, sizeof(short));
        RoomFlie.read((char*)&room.type, len);

        RoomFlie.read((char*)&len, sizeof(short));
        RoomFlie.read((char*)&room.roomNumber, len);

        RoomFlie.read((char*)&len, sizeof(short));
        RoomFlie.read((char*)&room.emptyOrNot, len);


        RoomFlie.read((char*)&len, sizeof(short));
        RoomFlie.read((char*)&room.id, len);
        i++;
    } while (!RoomFlie.eof());
    RoomFlie.clear();
    RoomFlie.close();


}

int ser(char TYPE, int ID) {
    fstream RoomFlie;
    RoomFlie.open("RoomFlie.txt", ios::in | ios::out | ios::binary);
    RoomFlie.seekg(0, ios::beg);
    Room room{};
    int i = 0 ,offset=0;
    short len = 0;
    do {
        if (i && (room.emptyOrNot == '0') && (room.type == TYPE)) {
            room.id = ID;
            room.emptyOrNot = '1';
            writeIN(room,offset);
            RoomFlie.clear();
            RoomFlie.close();

            return room.roomNumber;
        }
        offset = RoomFlie.tellg();
        RoomFlie.read((char*)&len, sizeof(short));
        RoomFlie.read((char*)&room.type, len);

        RoomFlie.read((char*)&len, sizeof(short));
        RoomFlie.read((char*)&room.roomNumber, len);

        RoomFlie.read((char*)&len, sizeof(short));
        RoomFlie.read((char*)&room.emptyOrNot, len);

        RoomFlie.read((char*)&len, sizeof(short));
        RoomFlie.read((char*)&room.id, len);
        i++;
    } while (!RoomFlie.eof());
    RoomFlie.clear();
    RoomFlie.close();
    return -1;
}

void EmptyRoom(int ID) {
    fstream RoomFlie;
    RoomFlie.open("RoomFlie.txt", ios::in | ios::out | ios::binary);
    RoomFlie.seekg(0, ios::beg);
    Room room{};
    int i = 0, offset = 0;
    short len = 0;
    do {
        if (i && (room.id == ID)) {
          
            room.emptyOrNot = '0';
            room.id = -1;
            writeIN(room, offset);
            RoomFlie.clear();
            RoomFlie.close();

        }
        offset = RoomFlie.tellg();
    
        RoomFlie.read((char*)&len, sizeof(short));
        RoomFlie.read((char*)&room.type, len);

        RoomFlie.read((char*)&len, sizeof(short));
        RoomFlie.read((char*)&room.roomNumber, len);

        RoomFlie.read((char*)&len, sizeof(short));
        RoomFlie.read((char*)&room.emptyOrNot, len);

        RoomFlie.read((char*)&len, sizeof(short));
        RoomFlie.read((char*)&room.id, len);
        i++;
    } while (!RoomFlie.eof());
    RoomFlie.clear();
    RoomFlie.close();
}