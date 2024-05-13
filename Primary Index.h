#pragma once
#include<fstream>
#include"available_list.h"
using namespace std;
availableLinkedlist listPrimary;
 
void AddInFilePrimaryIndex(int id, int offset) {
	fstream PrimaryKey;
	PrimaryKey.open("Primary File.txt", ios::in | ios::out | ios::binary);
	static int size = 0;
	if (listPrimary.isEmpty()) {
		PrimaryKey.seekp(0, ios::end);
	}
	else {
		int recordSize = sizeof(offset) + sizeof(id);
		int OFFSET = listPrimary.searchAndDeleteNode(recordSize);
		if (offset != -1) {
			PrimaryKey.seekp(OFFSET, ios::beg);
		}
		else {
			PrimaryKey.seekp(0, ios::end);
		}
 

	}
	short len;
	len = sizeof(id);
	PrimaryKey.write((char*)&len, sizeof(short));
	PrimaryKey.write((char*)&id, len);

	len = sizeof(offset);
	PrimaryKey.write((char*)&len, sizeof(short));
	PrimaryKey.write((char*)&offset, len);

	PrimaryKey.clear();
	PrimaryKey.close();
}

void DeleteInFilePrimaryIndex(int ID) {
	fstream PrimaryKey;
	PrimaryKey.open("Primary File.txt", ios::in | ios::out | ios::binary);
	PrimaryKey.seekg(0, ios::beg);
	int id, offset;
	short len;
	int i = 0; 
	int offsetrecord = 0;
	do {
		if (i && id == ID) {
			id = -1;
			int recordSize = sizeof(offset) + sizeof(id);
			listPrimary.addDeletedNodeToList(offsetrecord, recordSize);
			PrimaryKey.seekp(offsetrecord, ios::beg);
			len = sizeof(id);
			PrimaryKey.write((char*)&len, sizeof(short));
			PrimaryKey.write((char*)&id, len);
			break;
		}

		offsetrecord = PrimaryKey.tellg();

		PrimaryKey.read((char*)&len, sizeof(short));
		PrimaryKey.read((char*)&id, len);

		PrimaryKey.read((char*)&len, sizeof(short));
		PrimaryKey.read((char*)&offset, len);

		i++;
	} while (!PrimaryKey.eof());
	PrimaryKey.clear();
	PrimaryKey.close();
}

void DisplayInFilePrimaryIndex(fstream& file) {
	//file.open("Primary File.txt", ios::in | ios::out | ios::binary);

	file.seekg(0, ios::beg);

	int id, offset;
	short len;
	int i = 0;
	do {
		if (i && id != -1) {
			cout << "Id: " << id << " | " << "offset: " << offset << endl;
		}
		file.read((char*)&len, sizeof(short));
		file.read((char*)&id, len);

		file.read((char*)&len, sizeof(short));
		file.read((char*)&offset, len);

		i++;
	} while (!file.eof());

	file.clear();

}












