#include <stdio.h>
#include <stdlib.h>

// RecordType
struct RecordType
{
	int	id;
	char name;
	int	order; 
	//making a next pointer for a linked list structure
	struct RecordType* next;
};

// Fill out this structure
struct HashType
{
 	//creating a pointer to a RecordType 
	struct RecordType* record;
};

// Compute the hash function
int hash(int x, int tableSize)
{
	//hash function created by taking the remainder of doing modulus table
	return x % tableSize; 
}

// parses input file to an integer array
int parseData(char* inputFileName, struct RecordType** ppData)
{
	FILE* inFile = fopen(inputFileName, "r");
	int dataSz = 0;
	int i, n;
	char c;
	struct RecordType *pRecord;
	*ppData = NULL;

	if (inFile)
	{
		fscanf(inFile, "%d\n", &dataSz);
		*ppData = (struct RecordType*) malloc(sizeof(struct RecordType) * dataSz);
		// Implement parse data block
		if (*ppData == NULL)
		{
			printf("Cannot allocate memory\n");
			exit(-1);
		}
		for (i = 0; i < dataSz; ++i)
		{
			pRecord = *ppData + i;
			fscanf(inFile, "%d ", &n);
			pRecord->id = n;
			fscanf(inFile, "%c ", &c);
			pRecord->name = c;
			fscanf(inFile, "%d ", &n);
			pRecord->order = n;
		}

		fclose(inFile);
	}

	return dataSz;
}

// prints the records
void printRecords(struct RecordType pData[], int dataSz)
{
	int i;
	printf("\nRecords:\n");
	for (i = 0; i < dataSz; ++i)
	{
		printf("\t%d %c %d\n", pData[i].id, pData[i].name, pData[i].order);
	}
	printf("\n\n");
}

void insertRecord(struct HashType *hashTable, struct RecordType *record, int tableSize)
{
        
	// call the hash function to get the index
	int idx = hash(record->id, tableSize);
    struct HashType* pEntry = &hashTable[idx];
    struct RecordType* pRecord = pEntry->record;

	// if the RecordType at that index is NULL
    if (pRecord == NULL) {

		// set 'record' equal to the HashType pointer in the table at index
        pEntry->record = record;
    } else {
        while (pRecord->next != NULL) {

			// else traverse to the end of the linkedlist and add 'record' to the end of it
            pRecord = pRecord->next;
        }
        pRecord->next = record;
    }
}

// display records in the hash structure
// skip the indices which are free
// the output will be in the format:
// index x -> id, name, order -> id, name, order ....
void displayRecordsInHash(struct HashType *pHashArray, int hashSz)
{
	int i;

	for (i=0;i<hashSz;++i)
	{
		printf("Index %d -> ", i);
        struct RecordType* record = pHashArray[i].record;
        if (record != NULL) {

			//printing out the contents in each index
            printf("%d, %c, %d", record->id, record->name, record->order);
            record = record->next;
            while (record != NULL) {
                printf(" -> %d, %c, %d", record->id, record->name, record->order);
                record = record->next;
            }
        }
        printf(" -> NULL\n");
	}
}

int main(void)
{
	struct RecordType *pRecords;
	int recordSz = 0;

	recordSz = parseData("input.txt", &pRecords);
	printRecords(pRecords, recordSz);
	// Your hash implementation

	//creating variable Hash Table Size and assigning it to 11
	int hashTableSize = 11;

	//initializing the Hash Table 
    struct HashType* hashTable = (struct HashType*)calloc(hashTableSize, sizeof(struct HashType));

    for (int i = 0; i < recordSz; i++) {
		//inserting each record into the Hash Table 
        insertRecord(hashTable, &pRecords[i], hashTableSize);
    }

	//calling this function to display the records 
    displayRecordsInHash(hashTable, hashTableSize);

    // Free all the allocated memory
    for (int i = 0; i < hashTableSize; i++) {
        struct RecordType* record = hashTable[i].record;
        while (record != NULL) {
            struct RecordType* next = record->next;
            free(record);
            record = next;
        }
    }

// Free the memory set for the hash table and the records
    free(hashTable);
    free(pRecords);
    return 0;
}
