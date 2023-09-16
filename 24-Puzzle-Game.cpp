#include<iostream>
#include<time.h>
#include <iomanip>
#include <conio.h>
#include <fstream>
using namespace std;

//global keys
char key;


//ARRAYS DECLARATIONS
int initial[25], goal_array[25];
char path[200];	// for path 
int z = 0;



//FUNCTIONS DECLARATIONS
void init();
void goal();
void printpath();
int inversion(int inv[25]);
bool is_solveable(int in, int go);
void show(int array[25]);
void make_move(int a[25], char m);
int legal_move(int initial[25]);
bool is_goal(int current_state[25], int goal_reached[25]);


int main()
{
	srand((unsigned)time(0));
	fstream myhandler;
	int resumegame;
	cout << "Do you want to resume your game? Enter 1 for Yes OR any other number for NEW GAME";
	cin >> resumegame;	//ENTERING THE CHOICE FROM THE USER 
	if (resumegame == 1)	//IF YES THEN RELOADING DATA FROM OUR TXT FILE
	{
		myhandler.open("resumegame.txt", ios::in);
		if (!myhandler) //CHECKING IF THE PLAYER IS PLAIYNG FOR FIRST TIME AND THERE IS NO SAVED GAME
		{
			cout << "No Previous Game Data Found! Restart and Create a New Game and Save it!";
			exit(0);
		}
		else {
			for (int i = 0; i < 25; i++)
			{
				myhandler >> initial[i];		//COPYING FROM FILE THE PREVIOUS INITIAL STATE 
			}
			for (int i = 0; i < 25; i++)
			{
				myhandler >> goal_array[i];		//COPYING FROM FILE THE PREVIOUS GOAL STATE
			}
			myhandler.close();
		}
	}

	//IF USER CHOSE NOT TO RESUME THE GAME A RANDOM BOARD WILL BE GENERATED
	if (resumegame != 1)
	{
		goal();
		do
		{
			init();
		} while (!is_solveable(inversion(initial), inversion(goal_array)));
	}

	//gameplay
	do
	{
		cout << endl;
		cout << setw(5) << "The goal state : " << endl;
		show(goal_array);
		cout << "\n\n" << setw(5) << "The Initial State : " << endl;
		show(initial); cout << endl;
		legal_move(initial);
		cout << "Press Arrow UP to go up" << endl;
		cout << "Press Arrow DOWN go down " << endl;
		cout << "Press Arrow LEFT to go left " << endl;
		cout << "Press ARROW RIGHT to go right " << endl;
		cout << "Press E if you want to exit" << endl;
		key = _getch();		//USER INPUT IS TAKEN
		make_move(initial, key);		//THE INPUT IS SENT TO MAKE MOVE
		system("CLS");
	} while (!(is_goal(initial, goal_array) || key == 'E' || key == 'e')); //WILL EXIT IF THE USER PRESS E OR WINS THE GAME

	if (key == 'E' || key == 'e')		//UPON EXIT USER IS ASKED IF HE WANTS TO SAVE THE GAME
	{
		int choice = 1;
		cout << "Do you want to save the current game? Press 1 for YES and 2 for NO";
		cin >> choice;
		if (choice == 1)
		{
			myhandler.open("resumegame.txt", ios::out);
			{
				for (int i = 0; i < 25; i++)
				{
					myhandler << initial[i] << " ";

				}

				for (int i = 0; i < 25; i++)
				{
					myhandler << goal_array[i] << " ";

				}
				myhandler.close();
				printpath();
			}
		}
		else
			printpath();
	}
}

bool is_goal(int current_state[25], int goal_reached[25])
{
	int reached = 1;
	for (int i = 0; i < 25; i++)
	{
		if (initial[i] != goal_array[i])
		{
			reached = 2;
			break;
		}
	}
	if (reached == 1)
		return true;
	else
		return false;

}
void show(int array[25])
{
	for (int i = 0; i < 25; i++)
	{
		if (array[i] == 25)
		{
			cout << setw(3) << "-" << setw(2) << "";
		}
		else
		{
			cout << setw(3) << array[i] << setw(2) << "";
		}
		if (i == 4 || i == 9 || i == 14 || i == 19)
		{

			cout << endl;
			cout << "";
			cout << endl;
		}
	}
}

int inversion(int inv[25])
{

	int count = 0;
	for (int i = 0; i < 25; i++)
	{
		for (int j = i + 1; j < 25; j++)
			if (inv[i] > inv[j])
				count++;
	}
	cout << count << " ";
	return count;
}

bool is_solveable(int in, int go)
{
	if (in % 2 == go % 2)
		return true;
	else
		return false;
}
void init()
{
	int count, n;
	for (int i = 0; i < 25; i++)
	{
		initial[i] = 0;

	}
	cout << endl << endl;
	for (int j = 0; j < 25; j++)
	{
		count = 0;
		n = 1 + rand() % 25;
		initial[j] = n;
		for (int k = 0; k < 25; k++)
		{
			if (initial[j] == initial[k])
			{
				count++;
			}
		}
		if (count != 1)
		{
			j--;
		}
	}
}
void goal()
{
	int count, n;
	for (int i = 0; i < 25; i++)
	{
		goal_array[i] = 0;
	}
	cout << endl << endl;
	for (int j = 0; j < 25; j++)
	{
		count = 0;
		n = 1 + rand() % 25;
		goal_array[j] = n;
		for (int k = 0; k < 25; k++)
		{
			if (goal_array[j] == goal_array[k])
			{
				count++;
			}
		}
		if (count != 1)
		{
			j--;
		}
	}

}
int legal_move(int initial[25])
{
	cout << "****LEGAL MOVES WARNINGS****" << endl;
	for (int i = 0; i < 25; i++)
	{
		if (initial[i] == 25)
		{
			if (i <= 4)
			{
				cout << endl << "It can not move upward " << endl;
			}
			if (i >= 20)
			{
				cout << endl << "It can not move downward" << endl;
			}
			if (i == 0 || i == 5 || i == 10 || i == 15 || i == 20)
			{
				cout << endl << "It can not move left " << endl;
			}
			if (i == 4 || i == 9 || i == 14 || i == 19 || i == 24)
			{
				cout << endl << "It can not move right " << endl;
			}

			break;
		}
	}
	return 0;
}
void make_move(int a[25], char m)
{
	int r, c;
	for (int i = 0; i < 25; i++)
	{
		if (initial[i] == 25)
		{
			r = i;
			break;
		}
	}
	int i = r;
	int temp = 0;
	switch (m)
	{
	case 72://up
		if (i >= 5)
		{
			int temp = initial[i];
			initial[i] = initial[i - 5];
			initial[i - 5] = temp;
			path[z] = key;
			z++;
		}
		break;
	case 80://down
		if (i <= 19)
		{
			int temp = initial[i];
			initial[i] = initial[i + 5];
			initial[i + 5] = temp;
			path[z] = key;
			z++;
		}
		break;
	case 77://right
		if (i != 4 && i != 9 && i != 14 && i != 19 && i != 24)
		{
			int temp = initial[i];
			initial[i] = initial[i + 1];
			initial[i + 1] = temp;
			path[z] = key;
			z++;
		}
		break;
	case 75:
		if (i != 0 && i != 5 && i != 10 && i != 15 && i != 20)
		{
			int temp = initial[i];
			initial[i] = initial[i - 1];
			initial[i - 1] = temp;
			path[z] = key;
			z++;
		}
		break;
	}
}
void printpath()
{
	int counter = 0;
	int con = 1;
	int b = 1;
	if (path[counter] != '\0')
	{
		cout << "The path you followed is : " << endl;
	}
	else
	{
		cout << "There is no path to be shown because you have exited without playing : " << endl;
	}
	for (int i = 0; path[i] != '\0'; i++)
	{
		if (path[i] != 't' && path[i] != 'T')
		{
			if (path[i] == 72)
			{
				cout << b << "." << "Up" << " ";
			}
			else if (path[i] == 75)
			{
				cout << b << "." << "Left" << " ";
			}
			else if (path[i] == 80)
			{
				cout << b << "." << "Down" << " ";
			}
			else if (path[i] == 77)
			{
				cout << b << "." << "Right" << " ";
			}
			if (con == 10)
			{
				cout << endl << endl;
				con = 0;
			}
			counter++;
			con++;
			b++;

		}
		else
		{
			break;
		}
	}
	cout << endl << endl;
	if (counter > 0)
	{
		cout << "Total Moves Played = " << counter << "\n";
	}
	else
	{
		cout << "You haven't taken any move ! " << endl;
	}
}
