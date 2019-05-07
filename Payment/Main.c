#include <stdio.h>
#include <string.h>
#include <stdlib.h>



typedef struct sPerson
{
	char* ID;
	char * Name;
}Person;


Person* LoadPerson(FILE *personFile, int * Count);
char *readLine(FILE *input);
char* trimString(char* Input);
void PrintPerson(Person * Value);
int closeFile(FILE *personFile, FILE *currencyFile, FILE *paymentFile)
{
	int closedFile;
	closedFile = fclose(personFile);
	if (closedFile != 0)
	{
		fprintf(stderr, "Error happened: PersonFile fclose failed\r\n");
		exit(-1);
	}
	closedFile = fclose(currencyFile);
	if (closedFile != 0)
	{
		fprintf(stderr, "Error happened: CurrencyFile fclose failed\r\n");
		exit(-1);
	}
	closedFile = fclose(paymentFile);
	if (closedFile != 0)
	{
		fprintf(stderr, "Error happened: PaymentFile fclose failed\r\n");
		exit(-1);
	}
	return 0;
}

int main(int argc, char **argv)
{
	if (argc != 4)
	{
		fprintf(stderr, "Error happened: 0");
		return -1;
	}
	FILE *personFile = NULL;
	FILE *currencyFile = NULL;
	FILE *paymentFile = NULL;

	personFile = fopen(argv[1], "r");
	if (personFile == NULL)
	{
		fprintf(stderr, "Error happened: PersonFile fopen failed\r\n");
		exit(-1);
	}
	currencyFile = fopen(argv[2], "r");
	if (currencyFile == NULL)
	{
		fprintf(stderr, "Error happened: CurrencyFile fopen failed\r\n");
		exit(-2);
	}
	paymentFile = fopen(argv[3], "r");
	if (paymentFile == NULL)
	{
		fprintf(stderr, "Error happened: PaymentFile fopen failed\r\n");
		exit(-3);
	}

	//All file st ream are open
	int PersonCount = 0;
	Person * Persons = LoadPerson(personFile, &PersonCount);
	for (int i = 0; i < PersonCount; i++)
	{
		//PrintPerson((Persons + i));

		printf("Line");
	}



	//close files
	closeFile(personFile, currencyFile, paymentFile);

	printf("Press any key to exit...\r\n");
	getchar();
	return 0;
}

Person* LoadPerson(FILE *personFile, int * Count)
{
	typedef struct sPersonList
	{
		Person* Current;
		struct sPersonList * NextPerson;
	}PersonList;

	PersonList* Head = malloc(sizeof(PersonList));
	PersonList* Actual = Head;
	char *line = NULL;

	int LineCounter = 0;
	for (; !feof(personFile);) 
	{
		line = readLine(personFile);
		if (emptyString(line))
			continue;
		//printf("|%s|\r\n", line);

		line = trimString(line);

		int charCounter = 0;
		while (1)
		{
			if (*(line + charCounter) == ' ' || *(line + charCounter) == '\t')
				break;
			else
				charCounter++;
		}
		*(line + charCounter) = '\0';
		
		char* ID = (line);
		char* Name = trimString((line + charCounter + 1));
		
		Person * newItem = malloc(sizeof(Person*));
		newItem->ID = malloc(sizeof(char) * strlen(ID));
		strcpy(newItem->ID, ID);
		newItem->Name = malloc(sizeof(char) * strlen(Name));
		strcpy(newItem->Name, Name);
		
		//PrintPerson(newItem);

		PersonList* tmp = malloc(sizeof(PersonList));
		tmp->Current = newItem;
		tmp->NextPerson = NULL;

		Actual->NextPerson = tmp;
		Actual = Actual->NextPerson;

		LineCounter++;
	}


	Person * AllPersons = malloc(sizeof(Person *) * LineCounter);

	Actual = Head->NextPerson;

	for (int i = 0; i < LineCounter; i++)
	{
		*(AllPersons + i) = *Actual->Current;
		Actual = Actual->NextPerson;
	}


	*Count = LineCounter;
	//return AllPersons;
	return NULL;
}

char *readLine(FILE *input) {
	size_t capacity = 16;
	size_t size = 0;
	char *buffer = (char *)malloc(capacity);
	int c;

	while ((c = fgetc(input)) != EOF && c != '\n') {
		if (size == capacity) {
			capacity *= 2;
			char *tmp = (char *)realloc(buffer, capacity);
			if (!tmp) {
				free(buffer);
				//errorHappened(ALLOCATION_FAILED);
			}
			buffer = tmp;
		}
		buffer[size++] = (char)c;
	}
	buffer[size] = '\0';
	return buffer;
}

int emptyString(char * string)
{
	for (int i = 0; i < strlen(string); i++)
	{
		char act = *(string + i);

		if (!(act == ' ' || act == '\t'))
			return 0;
	}
	return 1;
}

char* trimString(char* Input)
{
	int begin = 0;
	int end = (int)strlen(Input);
	for (int i = 0; i < (int)strlen(Input); i++)
	{
		char act = *(Input + i);
		if (!(act == ' ' || act == '\t'))
		{
			begin = i;
			break;
		}
	}
	//On i-item in Input is non whitespace character
	for (int i = (int)strlen(Input) - 1; i >= 0 ; i--)
	{
		char act = *(Input + i);
		if (!(act == ' ' || act == '\t'))
		{
			end = i + 1;
			break;
		}
	}

	//*(Input + begin) = '\0';
	char * newString = malloc(sizeof(char) * (end - begin));
	memcpy(newString, (Input + begin), end - begin);
	*(newString + end - begin) = '\0';

	return newString;


}

void PrintPerson(Person * Value)
{
	printf("Person:\r\n");
	printf("\tID: %s\r\n", Value->ID);
	printf("\tName: %s\r\n", Value->Name);
}

