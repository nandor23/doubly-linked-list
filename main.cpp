#include <iostream>
#include <iomanip>
#include <ctime>
#include "list.h"

using namespace std;

struct deck
{
	list<int> card, color;
};

struct game_card
{
	int number, color;
};

void introduction()
{
	cout << "You can continue by hitting enter!\n\n";
	cout << "  Start: ";
	cin.get();
	system("cls");
}

void read_name(char name[])
{
	cout << "  Name: ";
	cin >> name;
	cout << endl;
}

void print_card(game_card card1, game_card card2, char colors[], int n, int m, char name[], bool isWar)
{
	cout << "\x1B[2J\x1B[H";
	if (isWar) {
		cout << "\n\n\n " << setw(73) << "War!\n\n";
		cout << setw(33) << "Enemy: " << n << " cards\n\n\n\n\n";
	}
	else
		cout << "\n\n\n\n" << setw(33) << "Enemy: " << n << " cards\n\n\n\n\n";
	cout << setw(15) << char(218);
	for (int j = 0; j < 12; ++j)
		cout << char(196);

	cout << char(191) << setw(7) << char(218);
	for (int j = 0; j < 12; ++j)
		cout << char(196);
	cout << char(191) << "\n";

	if (card1.number > 9 && card2.number > 9) {
		cout << setw(15) << char(179) << "  " << card1.number << "     " << colors[card1.color] << "  " << char(179);
		cout << "      " << char(179) << "  " << card2.number << "     " << colors[card2.color] << "  " << char(179) << "\n";
	}
	else
		if (card1.number > 9) {
			cout << setw(15) << char(179) << "  " << card1.number << "     " << colors[card1.color] << "  " << char(179);
			cout << "      " << char(179) << "  " << card2.number << "      " << colors[card2.color] << "  " << char(179) << "\n";
		}
		else
			if (card2.number > 9) {
				cout << setw(15) << char(179) << "  " << card1.number << "      " << colors[card1.color] << "  " << char(179);
				cout << "      " << char(179) << "  " << card2.number << "     " << colors[card2.color] << "  " << char(179) << "\n";
			}
			else {
				cout << setw(15) << char(179) << "  " << card1.number << "      " << colors[card1.color] << "  " << char(179);
				cout << "      " << char(179) << "  " << card2.number << "      " << colors[card2.color] << "  " << char(179) << "\n";
			}

	for (int i = 0; i < 5; ++i) {
		cout << setw(15) << char(179) << setw(13) << char(179) << "      ";
		cout << char(179) << setw(13) << char(179) << "\n";
	}

	if (card1.number > 9 && card2.number > 9) {
		cout << setw(15) << char(179) << "  " << colors[card1.color] << "     " << card1.number << "  " << char(179);
		cout << "      " << char(179) << "  " << colors[card2.color] << "     " << card2.number << "  " << char(179) << "\n";
	}
	else
		if (card1.number > 9) {
			cout << setw(15) << char(179) << "  " << colors[card1.color] << "     " << card1.number << "  " << char(179);
			cout << "      " << char(179) << "  " << colors[card2.color] << "      " << card2.number << "  " << char(179) << "\n";
		}
		else
			if (card2.number > 9) {
				cout << setw(15) << char(179) << "  " << colors[card1.color] << "      " << card1.number << "  " << char(179);
				cout << "      " << char(179) << "  " << colors[card2.color] << "     " << card2.number << "  " << char(179) << "\n";
			}
			else {
				cout << setw(15) << char(179) << "  " << colors[card1.color] << "      " << card1.number << "  " << char(179);
				cout << "      " << char(179) << "  " << colors[card2.color] << "      " << card2.number << "  " << char(179) << "\n";
			}

	cout << setw(15) << char(192);
	for (int j = 0; j < 12; ++j)
		cout << char(196);

	cout << char(217) << "      " << char(192);
	for (int j = 0; j < 12; ++j)
		cout << char(196);
	cout << char(217) << "\n\n\n\n\n" << setw(29) << name << ": " << m << " cards\n\n\n\n";
}


void print_turned_card(game_card card1, game_card card2, char colors[], int n, int m, char name[])
{
	cout << "\x1B[2J\x1B[H";
	cout << "\n\n\n" << setw(73) << "War!";
	cout << "\n\n" << setw(33) << "Enemy: " << n << " cards\n\n\n\n\n";

	cout << setw(15) << char(218);
	for (int j = 0; j < 12; ++j)
		cout << char(196);

	cout << char(191) << "      " << char(218);
	for (int j = 0; j < 12; ++j)
		cout << char(196);
	cout << char(191) << "\n";

	for (int i = 0; i < 7; ++i)
	{
		cout << setw(15) << char(179) << setw(13) << char(179) << "      ";
		cout << char(179) << setw(13) << char(179) << "\n";
	}

	cout << setw(15) << char(192);
	for (int j = 0; j < 12; ++j)
		cout << char(196);

	cout << char(217) << "      " << char(192);
	for (int j = 0; j < 12; ++j)
		cout << char(196);
	cout << char(217) << "\n\n\n\n\n" << setw(29) << name << ": " << m << " cards\n\n\n\n";
}

//shuffle cards effectively
void generate_deck(deck& player, int& n, int* used)
{
	int x;
	for (int i = 0; i < 26; ++i)
	{
		x = rand() % n;
		player.card.push_back(used[x] % 13 + 1);
		player.color.push_back(used[x] / 13 + 1);
		used[x] = used[n - 1];
		--n;
	}
}

//divides the deck
void divide_deck(deck& player1, deck& player2)
{
	int n = 52;
	int* volt = new int[n];
	for (int i = 0; i < n; ++i)
		volt[i] = i;

	srand(time(NULL));
	generate_deck(player1, n, volt);
	generate_deck(player2, n, volt);

	delete[] volt;
}

void fill_colors(char colors[])
{
	colors[1] = '#';
	colors[2] = '$';
	colors[3] = '@';
	colors[4] = '%';
}

//Both players put a card to the table
void put_to_table(deck& player1, deck& on_table1, game_card& card1, deck& player2, deck& on_table2, game_card& card2, int& n, int& m)
{
	card1.number = player1.card.front();
	card1.color = player1.color.front();
	on_table1.card.push_front(card1.number);
	on_table1.color.push_front(card1.color);
	player1.card.pop_front();
	player1.color.pop_front();

	cout << "  Next card: ";
	cin.get();

	card2.number = player2.card.front();
	card2.color = player2.color.front();
	on_table2.card.push_front(card2.number);
	on_table2.color.push_front(card2.color);
	player2.card.pop_front();
	player2.color.pop_front();

	--n;
	--m;
}

//the player who won the round puts the cards at the back of his deck
void put_back(deck& player, deck& on_table1, deck& on_table2, int& db)
{
	db = db + on_table1.card.size() + on_table2.card.size();

	while (!on_table2.card.empty())
	{
		player.card.push_back(on_table2.card.back());
		player.color.push_back(on_table2.color.back());
		on_table2.card.pop_back();
		on_table2.color.pop_back();
	}
	while (!on_table1.card.empty())
	{
		player.card.push_back(on_table1.card.back());
		player.color.push_back(on_table1.color.back());
		on_table1.card.pop_back();
		on_table1.color.pop_back();
	}
}

void game(deck& player1, deck& player2, char name[])
{
	int n = 26, m = 26;        //n = player1's card number      m = player2's card number
	char colors[5];
	fill_colors(colors);
	game_card card1, card2;
	deck on_table1, on_table2;
	while (n != 0 && m != 0)
	{
		put_to_table(player1, on_table1, card1, player2, on_table2, card2, n, m);
		print_card(card1, card2, colors, n, m, name, 0);

		if (card1.number == card2.number)			//war
		{
			while (n >= 4 && m >= 4 && card1.number == card2.number)
			{
				for (int i = 0; i < 3; ++i)
				{
					put_to_table(player1, on_table1, card1, player2, on_table2, card2, n, m);
					print_turned_card(card1, card2, colors, n, m, name);
				}
				put_to_table(player1, on_table1, card1, player2, on_table2, card2, n, m);
				print_card(card1, card2, colors, n, m, name, 1);
			}
			if (card1.number == card2.number)
			{
				if (n < 4 && m < 4)
					cout << "\n\n   Tie!\n\n";
				else
					if (n < 4)
						cout << "\n\n   You won!\n\n";
					else
						if (m < 4)
							cout << "\n\n   You lost!\n\n";
				return;
			}
			else
				if ((card1.number > card2.number && card2.number != 1) || card1.number == 1)
					put_back(player1, on_table1, on_table2, n);
				else
					put_back(player2, on_table2, on_table1, m);
		}
		else
			if ((card1.number > card2.number && card2.number != 1) || card1.number == 1)
				put_back(player1, on_table1, on_table2, n);
			else
				put_back(player2, on_table2, on_table1, m);
	}

	if (m > 0)
		cout << "\n\n   You won!\n\n";
	else
		cout << "\n\n   You lost!\n\n";
}

int main()
{
	char name[50];
	deck player1, player2;
	introduction();
	read_name(name);
	divide_deck(player1, player2);
	game(player1, player2, name);
	return 0;
}