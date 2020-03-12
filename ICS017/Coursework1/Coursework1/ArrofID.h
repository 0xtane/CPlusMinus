

while (1) {
	HEADER_E * lastHeader;
	if (pointer->cBegin == fname[0]) {
		int alphabeN = lname[0] - 65;
		ITEM9 * item = (ITEM9*)((pointer->ppItems)[alphabeN]);

		if (item->pNext) {
			ITEM9 * lastItem = item;
			while (item->pNext) {

				item = item->pNext;
			}
		}

		////if (strcmp(item->pID, fullName) == 0)

		break;
	}

	if (pointer->pNext) {
		pointer = pointer->pNext;
	}
	else { break; }

}

	}
	else {
	printf("\nError 55: Item with same ID doesn't exist in data structure\n");
	return 0;
	}

	-------------------
		if (thisItem->pNext) {
			ITEM9 * tmp2 = thisItem->pNext;
			delete thisItem;
			copied++;
			thisItem = tmp2;
		}
		else {
			delete thisItem;
			copied++;
			itemsChain[i] = 0;
			break;
		}
