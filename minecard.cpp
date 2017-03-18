#include <iostream>
#include <vector>
#include <random>
#include <stdlib.h>

using namespace std;

vector<int> deck;
int score = 0;
int mine_num = 1;
int point_empty = 10;
int point_tresure = 500;

enum card
{
	empty = 0,
	mine,
	tresure
};

struct result
{
	int empty;
	int mine;
	int tresure;
};

void print_result(result res)
{
	cout << "empty : " << res.empty << endl;
	cout << "mine : " << res.mine << endl;
	cout << "tresure : " << res.tresure << endl;
}

result search(int n)
{
	result res{0,0,0};
	for (int i=0; i<n; i++)
	{
		switch(deck[i])
		{
		case mine:
			res.mine ++;
			break;
		case empty:
			res.empty ++;
			break;
		case tresure:
			res.tresure ++;
			break;
		}
	}

	return res;
}

void create_deck(int size)
{

	int e = size;
	int m = mine_num;
	int t = 1;

	deck.clear();
	for (int i=0; i<e; i++)
	{
		deck.push_back(empty);
	}
	for (int i=0; i<m; i++)
	{
		deck.push_back(mine);
	}
	for (int i=0; i<t; i++)
	{
		deck.push_back(tresure);
	}

}

void shuffle()
{
	int shuffle_num = 100;

	random_device seed_gen;
	mt19937 engine(seed_gen());

	uniform_real_distribution<> dist(0, deck.size());

	for (int i=0; i<shuffle_num; i++)
	{
		int a = dist(engine);
		int b = dist(engine);
		if (a == b) continue;
		int tmp = deck[b];
		deck[b] = deck[a];
		deck[a] = tmp;
	}

}

bool safe(result res)
{
	if (res.mine == 0) 
		return true;
	return false;
}

void add_score(result res)
{
	score += res.empty * point_empty;
	score += res.tresure * point_tresure;
}

void print_state()
{
	cout << "" << endl;
	cout << "- - - -" << endl;
	cout << "deck_size : " << deck.size() << endl;
	cout << "score : " << score << endl;
}

enum role
{
	r_search = 0,
	r_draw,
	r_shuffle
};

void print_role()
{
	cout << "role{ ";
	cout << "serach : 0, draw : 1, shuffle : 2";
	cout << " }" << endl;

}

int main()
{

	cout << "empty num ? ";
	int size;
	cin >> size;
	cout << "mine num ? ";
	cin >> mine_num;

	create_deck(size);
	shuffle();

	cout << "* Hunt the tresure, the only one" << endl;

	int r;
	for(;;)
	{
		print_state();
		print_role();
		cout << "role ? ";
		cin >> r;

		switch (r)
		{
		case r_draw:
		 {
		 	cout << "How many ? ";
			int n;
			result res;
			cin >> n;

			cout << "カードを" << n << "枚ひきます" << endl;
			
			res = search(n);
			if ( safe(res) )
			{
				add_score(res);
				for (int i=n-1; i>=0; i--)
					deck.erase(deck.begin() + i);
				if (res.tresure) {
				  print_state();
					cout << "you hunt the tresure!" << endl;
					cout << "game clear" << endl;
					exit(1);
				}
			} 
			else
			{
				print_state();
				cout << "game over" << endl;
				exit(1);
			}
			
			break;
		 }
		case r_shuffle:
			
			cout << "デッキをシャッフルします" << endl;
			shuffle();
			
			break;
		case r_search:
		 {
		 	cout << "How many ? ";
		 	int n;
			cin >> n;
			
			cout << "デッキの上から" << n << "枚を調べます" << endl;

			print_result(search(n));
			
			break;
		 }
		}
	}
}
