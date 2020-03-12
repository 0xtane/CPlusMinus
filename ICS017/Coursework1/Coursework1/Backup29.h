#pragma once
// Coursework1.cpp : This file contains the 'main' function. Program execution begins and ends there.


#include "pch.h"
#include <iostream>
#include <stdlib.h>
#include "DateTime.h"
#include "Items.h"
#include "Headers.h"
#include "ICS0017DataSource.h"


void PrintDataStructure(HEADER_E *pointer, int Iamount) {
	//std::cout<< "CBegin: "  << pointer->cBegin <<" "<<sizeof(ITEM9)<< "\n";
	printf("\nBchar: %c  . SizeOfI9: %d . ppItems: %p . Had: %p \npNext: %p . pPrior: %p \n\n", pointer->cBegin, sizeof(ITEM9), pointer->ppItems, pointer, pointer->pNext, pointer->pPrior);

	//std::cout <<"Pnext: "<< *(pointer->pNext) <<"\n";
	//ITEM9* pp = pointer->ppItems; 

	for (int i = 0; i < Iamount; i++) {


		/*if ((pointer->ppItems)[i] != NULL) {

			ITEM9* myitem = (ITEM9*)pointer->ppItems;

			printf("%02d - Add: %p - Val: %d - Code: " , i , &((pointer->ppItems)[i]) , (pointer->ppItems)[i]);
			std::cout << (myitem[i]).pDate <<" t: "<< typeid((pointer->ppItems)[i]).name();
			std::cout << " \n";

		}*/

		ITEM9* myitem = (ITEM9*)(pointer->ppItems);

		//if ((myitem)[i].) {



		printf("%02d - Add: %p - Val: %d - Code: ", i, &myitem[i]), myitem[i];
		std::cout << (myitem[i]).Code << " t: " << typeid((myitem[i])).name();
		if ((myitem[i])) {
			std::cout << myitem[i].pID;
		}
		std::cout << " \n";

		//}
	}

	if (pointer->pNext) {
		PrintDataStructure(pointer->pNext, Iamount);
	}


}

//pointer_to_data_structure = InsertItem(pointer_to_data_structure, char *pNewItemID = 0);

int main()
{
	std::cout << "Hello World!\n";
	int Itype = 9;
	int Iamount = 100;


	HEADER_E *p = GetStruct5(Itype, Iamount);
	//ITEM9 *pNewItem = (ITEM9 *)GetItem(Itype);
	/*typedef struct item9
	{
		char *pID;
		unsigned long int Code;
		DATE3 *pDate;
		struct item9 *pNext;
	} ITEM9;*/
	PrintDataStructure(p, Iamount);
	//std::cout << pNewItem->pID;
	return 0;
}
