# File System Project - Hotel Management System

This project is a file system implementation within a Hotel Management System. It provides functionalities to manage client information, perform file operations, generate bills, and enable efficient searching and manipulation of records.

## Table of Contents
- [Introduction](#introduction)
- [Client Class](#client-class)
- [File System Functions](#file-system-functions)
- [Bill Calculation](#bill-calculation)
- [Record Manipulation](#record-manipulation)
- [Searching Records](#searching-records)
- [User Interface](#user-interface)
- [Installation](#installation)
- [Usage](#usage)
- [Contributing](#contributing)
- [License](#license)

## Introduction
The File System Project is a part of the Hotel Management System. It aims to provide an efficient way to store, retrieve, and manipulate client records within the system. The project utilizes a client class and various file system functions to achieve these goals.

## Client Class
The `Client` class represents a hotel client and contains the following methods:
- `set_Client_name`: Sets the name of the client.
- `set_Client_numberOfDays`: Sets the number of days the client will stay.
- `set_Client_id`: Sets the client's ID.
- `set_Client_mobileNumber`: Sets the client's mobile number.
- `set_Client_roomType`: Sets the type of room reserved by the client.
- `set_Client_roomNumber`: Sets the room number assigned to the client.
- `get_Client_id`: Retrieves the client's ID.
- `get_Client_numberOfDays`: Retrieves the number of days the client will stay.
- `get_Client_roomType`: Retrieves the type of room reserved by the client.
- `get_Client_roomNumber`: Retrieves the room number assigned to the client.
- `showDataForClient`: Displays the client's data.
- `recordSize`: Calculates the size of a record.
- `getData_info`: Retrieves information about the data.

## File System Functions
The project includes several file system functions to manage client records. These functions operate on a file and provide functionalities such as adding records, displaying all records, reading from the file, writing to the file, deleting records by ID, and searching for records by ID or name. The file system functions include:
- `addRecordInFile`: Adds a client record to the file.
- `ShowAllRecordInFile`: Displays all client records stored in the file.
- `readFromFlie`: Reads data from the file.
- `writeEndFile`: Writes data at the end of the file.
- `writeAtPlace`: Writes data at a specific place in the file.
- `DeleteById`: Deletes a client record from the file based on the ID.
- `searchById`: Searches for a client record in the file by ID.
- `searchByName`: Searches for a client record in the file by name.

## Bill Calculation
The project includes a `Bill` function that calculates and generates bills for clients. This functionality allows the system to calculate the total amount due based on the number of days stayed and the room type chosen by the client.

## Searching Records
To facilitate efficient searching, the project provides a `Search` function. This function allows users to search for client records by ID or name, enabling quick retrieval of specific information.

## User Interface
The project includes a `menu` function that serves as a user interface for the Hotel Management System. It provides a menu-driven approach for interacting with the system and accessing various functionalities.

## Installation
To use the File System Project, follow these steps:
1. Clone the repository to your local machine.
2. Ensure that you have the required dependencies installed.
3. Compile and build the project.

## Usage
Once the project is installed, you can run it and interact with the Hotel Management System. Use the provided menu options to perform operations such as adding client records, displaying records, calculating bills, searching for records, and more.

## Contributing
Contributions to the File System Project are welcome! If you want to contribute, please fork the repository, create a new branch, make your changes, and submit a pull request.