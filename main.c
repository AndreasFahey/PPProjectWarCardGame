#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

//Program By Andreas Fahey - Student 
//Student Number - G00346830
//Procedural Programming Assignment Card Game - "WAR".

//===Function Def===
void NewGame();
void displayGameStatus(int scores[], int rnd, int pls);
void loadGame();
void shuffleDeck();
void gameSelectionOptions();

//===Global Var To Load "FILE"===
FILE* filep;

char gameName[40];
char loadSavedGame[40];
char gameNameAll[40];

int pl[10][13] = { 0 };
//^^^===The Players cards Given and the Number===^^^
int cards[4][13] = { { 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, },{ 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, },{ 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, },{ 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, } };
int plScore[10];
int ifNewGame = 0;

int numOfPls;
int currentRndNum;
int i, j, k;
int num_char;
int loadSelect;
int exitSelect;

void main()
{
	//===Variables===
	int intitialGameSelect;
	int cardSelection;
	int largestPlNum;
	int winningPl;
	int nxtRndChecker;

	int cardsChosen[10];
	int rndCounter = 0;
	int largestCard = 0;
	int largestOverallScore = 0;
	int currentRndScore = 0;
	int nxtRndScore = 0;
	int oldV = 0;

	//===User Menu Selection===
	printf("Welcome To The Card Game -WAR- By Andreas Fahey - Student\n");
	printf("1- To Start a New Game\n2- To Load an Existing Game\n0- To Exit The Program\n");
	scanf("%d", &intitialGameSelect);

	while (intitialGameSelect != 0)
	{
		if (intitialGameSelect == 1)
		{
			NewGame();
		}
		else if (intitialGameSelect == 2)
		{
			loadGame();
		}
		else
		{
			printf("THIS IS AN INVALID INPUT PLEASE ENTER A KEY THAT IS VALID FROM THE INFO PROVIDED.\n"); //===Invalid Input Response===
		}
		//===Game Play / Play Game===
		if (intitialGameSelect == 1 || intitialGameSelect == 2)
		{
			for (i = currentRndNum; i < 13; ++i)
			{
				rndCounter++;
				printf("\nRound %d\n", i + 1);

				for (j = 0; j < 10; j++)
				{
					cardsChosen[j] = 0;
				}

				for (j = 0; j < numOfPls; j++)
				{
					printf("\nPlayer %d: Your Hand -> ", j + 1);//===This is to Display the Current Players Hand===

					for (k = 0; k < 13; k++)
					{
						printf("%d  ", pl[j][k]);
					}
					printf("\n\n\n");
					do
					{
						//===This Lets the Current Player to Pick a Card===
						printf("Pick the Card from your Hand That You Would like to use for Round %d\n", i + 1);
						printf("Numbers from 0 - 13. E.G card 3 = 2 -However- Your Pick Must Only Be Used Once\n");
						scanf("%d", &cardSelection);


					} while (cardSelection < 0 || cardSelection >= 13 || pl[j][cardSelection] == 0); //===Check===

					printf("You Picked %d\n", pl[j][cardSelection]);

					cardsChosen[j] = pl[j][cardSelection]; //===Saves Pick===

					pl[j][cardSelection] = 0; //===Card Used Back to 0===
				} //===for===

				printf("\n\n");
				printf("Round %d Picks and Scores \n", i + 1);

				//===Round Statistics===
				for (j = 0; j < numOfPls; j++) //===Checks, Counts and Prints===
				{
					printf("Player %d: ", j + 1);
					printf("%d \n", cardsChosen[j]);

					currentRndScore += cardsChosen[j]; //===Results===
				}

				for (j = 0; j < numOfPls; j++) //===Duplicate Check===
				{
					oldV = cardsChosen[j];

					for (k = 0; k < numOfPls; k++)
					{
						if (k == j)
						{
							continue;
						}

						if (oldV == cardsChosen[k]) //===Used to Remove Duplicates===
						{
							cardsChosen[j] = 0;
							cardsChosen[k] = 0;
						}
					}
				} //===outer for===
				nxtRndChecker = 0;
				for (j = 0; j < numOfPls; j++)
				{
					if (cardsChosen[j] >= largestCard)
					{
						largestCard = cardsChosen[j];
						largestPlNum = j + 1;
					}
					//===This Checks if Card Picked is greater than 0===
					if (cardsChosen[j] > 0)
					{
						nxtRndChecker = 1;
					}
				}
				//===If for a Draw===
				if (nxtRndChecker == 0)
				{
					nxtRndScore = currentRndScore;
					printf("\nThis Round has Resulted in a Draw, %d Points from this Round Will Carry Over to the Next.\n", nxtRndScore);
				}
				else
				{
					//===Score Carried===
					if (nxtRndScore > 0)
					{
						currentRndScore += nxtRndScore;
					}
					//===Adds Players Score===
					plScore[largestPlNum - 1] += currentRndScore;
					printf("\nRound %d Winner is Player %d\n", i + 1, largestPlNum);
					printf("Player %d's Overall Score is %d\n", largestPlNum, plScore[largestPlNum - 1]);
				}
				//===User Option Selection===
				if (i < 12)
				{
					gameSelectionOptions();
				}
				currentRndScore = 0; //===Reset Back To 0===
			} //===for===

			  //===End Game===

			for (i = 0; i < numOfPls; i++) //===Winner Check===
			{
				if (plScore[i] > largestOverallScore)
				{
					largestOverallScore = plScore[i];
					winningPl = i + 1;
				}
			}
			printf("\nThe Overall Winner is Player %d Scoring %d\n", winningPl, largestOverallScore);
			printf("\n\nPlayer %d Has Won The War ! Congrats !", winningPl);
		}
		printf("1- To Start a New Game\n2- To Load an Existing Game\n0- To Exit The Program\n");
		scanf("%d", &intitialGameSelect);
	} //===while===
}

//===Functions===
//===New Game===
void NewGame()
{
	int suit = 0;
	int randomCardPos;
	//===File Save===
	printf("Please Enter a Name For this Game so it Can be Saved and Loaded at Anytime ! \n");
	scanf("%s", gameName);
	strcat(gameName, ".txt");
	//==^^^This Adds File Extension to Game Name^^^===
	do
	{
		printf("Please Enter The Number of Players, To Play You must Select 2-10 Players\n");
		scanf("%d", &numOfPls);
	} while (numOfPls < 2 || numOfPls > 10);

	for (i = 0; i < numOfPls; i++)
	{
		plScore[i] = 0;
	}
	currentRndNum = 0;
	ifNewGame = 1;
	//===Dealing The Cards===
	srand(time(NULL));

	for (i = 0; i < numOfPls; i++)
	{
		shuffleDeck(); //===Shuffle Call===

		for (j = 0; j < 13; j++)
		{
			randomCardPos = rand() % 13;
			pl[i][j] = cards[suit][randomCardPos]; //===Deals Random Card===
			suit++;
			if (suit == 3) //===Reaches 4 Suits Starts Over===
			{
				suit = 0;
			}
		}
	} //===outer for===
}
//===Shuffling===
void shuffleDeck()
{
	int randNum;
	int oldCardV;
	int i;
	//===Card Shuffle===
	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 13; j++)
		{
			randNum = rand() % 13; //===Random 0-12===
			oldCardV = cards[i][randNum]; //==Saves==
			cards[i][randNum] = cards[i][j]; //===Updates===
			cards[i][j] = oldCardV; //===Update with Old Value===
		}
	}
}
//===Loading a Saved Game===
void loadGame()
{
	printf("Game selection \n");
	//===SavedGames===
	filep = fopen("SavedGames.txt", "r");

	if (filep == NULL)
	{
		printf("The Saved Game Cannot be Opened\n");
	}
	else
	{
		while (!feof(filep))
		{
			num_char = fscanf(filep, "%s", gameNameAll);
			if (num_char > 0)
			{
				printf("%s\n", gameNameAll);
			}
		}
		printf("\n");

	}
	fclose(filep);
	//===^^^File Close^^^===

	printf("Please Enter the Saved Game you Would Like to Load\n");
	scanf("%s", loadSavedGame);
	strcpy(gameName, loadSavedGame);

	filep = fopen(loadSavedGame, "r");

	if (filep == NULL)
	{
		printf("The Saved Game Cannot be Opened\n");
	}
	else
	{
		while (!feof(filep))
		{
			fscanf(filep, "%d", &numOfPls);
			fscanf(filep, "%d", &currentRndNum);

			for (i = 0; i < numOfPls; i++)
			{
				for (j = 0; j < 13; j++)
				{
					fscanf(filep, "%d", &pl[i][j]);
				}
			}

			for (i = 0; i < numOfPls; i++)
			{
				fscanf(filep, "%d ", &plScore[i]);
			}

			printf("\nSaved Game %s has Loaded\n", gameName);
		} //===while===
		fclose(filep);
		//===^^^File Close^^^===

		displayGameStatus(plScore, i, numOfPls); //===Game Status===
	}
}

//===Game Status===

void displayGameStatus(int scores[], int rnd, int pls)
{
	int i;

	printf("\nRound: %d\n", rnd + 1);
	printf("Number of Players: %d\n\n", pls);
	printf("Scores \n");

	for (i = 0; i < pls; i++)
	{
		printf("Player %d: %d\n", i + 1, scores[i]);
	}
}

//===Game Options===

void gameSelectionOptions()
{
	printf("\n1 - Go To The Next Round\n2 - Save This Game\n3 - Show This Games Status\n4 - Exit This Game Without Saving\n");
	scanf("%d", &loadSelect);

	switch (loadSelect)
	{
	case 1:
		break;
	case 2:
		filep = fopen(gameName, "w");

		if (filep == NULL) //===Output Error===
		{
			printf("The Saved Game Could not be Opened\n");
		}
		else
		{
			fprintf(filep, "%d\n", numOfPls);
			fprintf(filep, "%d\n", i);

			for (j = 0; j < numOfPls; j++)
			{
				for (k = 0; k < 13; k++)
				{
					fprintf(filep, "%d ", pl[j][k]);
				}
				fprintf(filep, "\n");
			}

			for (j = 0; j < numOfPls; j++)
			{
				fprintf(filep, "%d ", plScore[j]);
			}

			fclose(filep);
			//===^^^File Close^^^===
		}
		if (ifNewGame == 1)
		{
			filep = fopen("SavedGames.txt", "a");

			if (filep == NULL)
			{
				printf("The Saved Game Could not be Opened\n");
			}
			else
			{
				fprintf(filep, "%s\n", gameName); //===Adds Saved Game To File===
				fclose(filep);
			}
		}
		break;
	case 3:
		displayGameStatus(plScore, i, numOfPls);
		break;
	case 4:
		printf("\n1 - Start a new Game\n2 - Load a Saved Game\n3 - Exit Program\n");
		scanf("%d", &exitSelect);

		if (exitSelect == 1) {
			NewGame();
			i = -1;
		}
		else if (exitSelect == 2)
		{
			loadGame();
			i = currentRndNum - 1;
		}
		else if (exitSelect == 3) {
			//===Closes Program===
			exit(0);
		}
		else {
			printf("Value entered is invald");
		}
		break;
	default:
		printf("Value entered is invald");
		break;
	} //===switch==
}//===main===