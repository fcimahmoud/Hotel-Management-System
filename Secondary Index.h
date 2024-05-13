#pragma once
#include<fstream>
#include"available_list.h"
using namespace std;
availableLinkedlist listSecondary;

void AddInFileSecindaryIndex(char* name, int id) {
	fstream file;
	file.open("Secondary Index.txt", ios::in | ios::out | ios::binary);
	if (listSecondary.isEmpty()) {
		file.seekp(0, ios::end);
	}
	else {
		    int recordSize = strlen(name) + sizeof(id);
			int offset = listSecondary.searchAndDeleteNode(recordSize);
			if (offset != -1) {
				file.seekp(offset, ios::beg);
			}
			else {
				file.seekp(0, ios::end);
			}	 
		 
	}
	short len;
	len = strlen(name);
	file.write((char*)&len, sizeof(short));
	file.write(name, len);

	len = sizeof(id);
	file.write((char*)&len, sizeof(short));
	file.write((char*)&id, len);
	file.clear();
	file.close();
}

void DeleteInFileSecindaryIndex(int ID) {
	fstream SecondaryIndex;
	SecondaryIndex.open("Secondary Index.txt", ios::in | ios::out | ios::binary);
	SecondaryIndex.seekg(0, ios::beg);
	char name[20]{}; int id{};
	short len;
	int i = 0; static int size = 0;
	int offsetrecord = 0;
	do {
		if (i && id == ID) {
			name[0] = '*';
			int recordSize = strlen(name) + sizeof(id);
			listSecondary.addDeletedNodeToList(offsetrecord, recordSize);
			SecondaryIndex.seekp(offsetrecord, ios::beg);
			len = strlen(name);
			SecondaryIndex.write((char*)&len, sizeof(short));
			SecondaryIndex.write(name, len);
			break;
		}

		offsetrecord = SecondaryIndex.tellg();

		SecondaryIndex.read((char*)&len, sizeof(short));
		SecondaryIndex.read(name, len);

		SecondaryIndex.read((char*)&len, sizeof(short));
		SecondaryIndex.read((char*)&id, len);

		i++;
	} while (!SecondaryIndex.eof());
	SecondaryIndex.clear();
	SecondaryIndex.close();
}

void DisplayInFileSecindaryIndex() {
	fstream SecondaryIndex;
	SecondaryIndex.open("Secondary Index.txt", ios::in | ios::out | ios::binary);
	SecondaryIndex.seekg(0, ios::beg);

	char name[20]{}; int id;
	short len = 0;
	int i = 0;
	do {
		if (i && name[0] != '*') {
			cout << "name: " << name << " | " << "id: " << id << endl;
		}

		SecondaryIndex.read((char*)&len, sizeof(short));
		SecondaryIndex.read(name, len);
		name[len] = '\0';

		SecondaryIndex.read((char*)&len, sizeof(short));
		SecondaryIndex.read((char*)&id, len);

		/*SecondaryIndex.clear();*/

		i++;

	} while (!SecondaryIndex.eof());

	SecondaryIndex.clear();
	SecondaryIndex.close();
}

int searcheSimilarNames(char* Name) {
	fstream file;
	file.open("Secondary Index.txt", ios::in | ios::out | ios::binary);
	file.seekg(0, ios::beg);
	char name[11];
	int id, i = 0;
	short len;
	 
	do {
		if (i && (!strcmp(name, Name)) && name[0]!='*') {
			cout << "name: " << name << " | " << "Id: " << id << endl;
		}
		file.read((char*)&len, sizeof(short));
		file.read(name, len);
		name[len] = '\0';

		file.read((char*)&len, sizeof(short));
		file.read((char*)&id, len);

		i++;
	} while (!file.eof());
	file.clear();
	file.close();
	cout << "------ Enter id that you want ------\n";
	int x;  cin >> x;
	
	return x;

}
