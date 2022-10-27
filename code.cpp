// Варіант 6. Переписати з вхідного файлу у вихідний кожен третій блок.
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <Windows.h>  // поддержка кириллицы в консоли
#include <fstream>
#include "conio.h"
using namespace std;
#define MAX_LEN 80

struct train {
	char serialn[20]; // номер рейсу
	char from[20]; // звідки відправка
	char to[20]; // куди відправляється
	char cost[20]; // ціна за квиток
};
train addDir()	// добавление в словарь
{
	train newdetail;
	cout << "Введіть звідки відправка: ";
	cin >> newdetail.from;
	cout << "Введіть куди відправляється: ";
	cin >> newdetail.to;
	cout << "Введіть номер рейсу: ";
	cin >> newdetail.serialn;
	cout << "Введіть ціна за квиток: ";
	cin >> newdetail.cost;

	system("cls");
	return newdetail;
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	fstream start_file;
	ofstream result_file;
	char name[MAX_LEN + 40];
	char way_to_file[MAX_LEN + 40] = "F:\\data\\";
	train dir[8];
	int counter = 0;

	do
	{
		strcpy(way_to_file, "F:\\data\\");	// открытие файла для чтения
		cout << "Введіть назву файла за шляхом F:\\data\\";
		cin.getline(name, MAX_LEN);
		strcat(way_to_file, name);
		strcat(way_to_file, ".bin");
		start_file.open(way_to_file, ios::binary | ios::in);
		cout << way_to_file << endl;
	} while (!start_file.is_open() && cout << "Файл не знайдено!" << endl);

	strcpy(way_to_file, "F:\\data\\");	// открытие файла для записи
	cout << "Введіть назву файла за шляхом F:\\data\\";
	cin.getline(name, MAX_LEN);
	strcat(way_to_file, name);
	strcat(way_to_file, ".bin");
	result_file.open(way_to_file, ios::binary);
	cout << way_to_file << endl;
	system("cls");

	cout << "Додайте 8 елементів у словник: " << endl << endl;
	for (int i = 0; i < 8; i++)		// цикл записи массива структур в файл
	{
		cout << i + 1 << "-й елемент" << endl;
		dir[counter] = addDir();
		counter++;
	}
	start_file.write((char*)dir, sizeof(dir));
	cout << "Текст записано у перший файл." << endl << endl;
	// прочитать из первого файла 1, 4, 7 блоки и записать во второй файл
	train dir2;
	int size_of_block = sizeof(train);
	cout << "Размер блока = " << size_of_block << "байт" << endl;
	// первый блок
	start_file.read((char*)(&dir2), size_of_block);
	result_file.write((char*)(&dir2), size_of_block);	// запись первого блока во второй файл
	// четвертый блок
	start_file.seekg(4 * size_of_block, ios::cur);
	start_file.read((char*)(&dir2), size_of_block);
	result_file.seekp(0, ios::end);		// запись четвертого блока после первого
	// седьмой блок
	start_file.seekg(-size_of_block, ios::end);
	start_file.read((char*)(&dir2), size_of_block);
	result_file.seekp(0, ios::end);
	cout << "Кожен третій блок було записано у файл \"result\"." << endl;

	// закрытие файлов
	start_file.close();
	result_file.close();
}
