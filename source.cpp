#include <vector>
#include <fstream>
#include <string>
#include <iostream>
#include <algorithm>

#define directions 4 //pocet stran u plusu (nahoru, dolu, pravo, levo)

using namespace std;

vector<string> split_string(string);

//funkcia pro overeni bunky (Pokud je "G")
bool accessible(int x, int y, vector<string> grid) {
	if (x < 0 || y < 0 || x >= grid.size() || y >= grid[0].size())
		return false;
	else if (grid[x][y] == 'G')
		return true;
	else
		return false;
}

//podobna funkce, jenom ze overi pokud v bunce je hvezda '*'
bool accessible2(int x, int y, vector<string> grid) {
	if (x < 0 || y < 0 || x >= grid.size() || y >= grid[0].size())
		return false;
	else if (grid[x][y] == '*')
		return true;
	else
		return false;
}


int twoPluses(vector<string> grid) {

	int product = 0;
	for (int i = 1; i < grid.size() - 1; i++) {
		for (int j = 1; j < grid[0].size() - 1; j++) {

			int firstPlus=0;

			while (accessible(i + firstPlus, j, grid) && accessible(i - firstPlus, j, grid) &&
				accessible(i, j + firstPlus, grid) && accessible(i, j - firstPlus, grid)) {
				grid[i + firstPlus][j] = '*';
				grid[i - firstPlus][j] = '*';
				grid[i][j + firstPlus] = '*';
				grid[i][j - firstPlus] = '*';

				for (int k = 1; k <= grid.size(); k++) {
					for (int z = 1; z <= grid[0].size(); z++) {
						int secondPlus = 0;

						while (accessible(k + secondPlus, z, grid) && accessible(k - secondPlus, z, grid) &&
							accessible(k, z + secondPlus, grid) && accessible(k, z - secondPlus, grid)) {
							product = max(product, (1 + directions * firstPlus)*(1 + directions * secondPlus));
							secondPlus++;
						}
					}
				}
				firstPlus++;
			}
			firstPlus = 0;

			while (accessible2(i + firstPlus, j, grid) && accessible2(i - firstPlus, j, grid) &&
				accessible2(i, j + firstPlus, grid) && accessible2(i, j - firstPlus, grid)) {
				grid[i + firstPlus][j] = 'G';
				grid[i - firstPlus][j] = 'G';
				grid[i][j + firstPlus] = 'G';
				grid[i][j - firstPlus] = 'G';
				firstPlus++;
			}
		}
	}
	cout << product << endl;
	return product;
}


int main()
{
	ofstream fout("output.txt", std::ofstream::out);

	string nm_temp;
	getline(cin, nm_temp);

	vector<string> nm = split_string(nm_temp);

	int n = stoi(nm[0]);

	int m = stoi(nm[1]);

	vector<string> grid(n);

	for (int i = 0; i < n; i++) {
		string grid_item;
		getline(cin, grid_item);

		grid[i] = grid_item;
	}

	int result = twoPluses(grid);

	fout << result << "\n";

	fout.close();

	return 0;
}

vector<string> split_string(string input_string) {
	string::iterator new_end = unique(input_string.begin(), input_string.end(), [](const char &x, const char &y) {
		return x == y and x == ' ';
	});

	input_string.erase(new_end, input_string.end());

	while (input_string[input_string.length() - 1] == ' ') {
		input_string.pop_back();
	}

	vector<string> splits;
	char delimiter = ' ';

	size_t i = 0;
	size_t pos = input_string.find(delimiter);

	while (pos != string::npos) {
		splits.push_back(input_string.substr(i, pos - i));

		i = pos + 1;
		pos = input_string.find(delimiter, i);
	}

	splits.push_back(input_string.substr(i, min(pos, input_string.length()) - i + 1));

	return splits;
}
