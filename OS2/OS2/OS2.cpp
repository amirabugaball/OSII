24
#include <unordered_set>
#include <queue>
#include <unordered_map>
#include<iostream>
#include<vector>
using namespace std;

void PF_FIFO(int page[],int x,int frames){
	//to store numbers
	unordered_set<int> y;
	//to store within fifo way
	queue<int> z;
	
	int faults = 0;

	for (int j = 0; j < x; j++){
		//checking if there's free space
		if(y.size() < frames){
			if (y.find(page[j]) == y.end()){

				y.insert(page[j]);

				faults++;

				z.push(page[j]);
			}
		}
		else {
			if (y.find(page[j]) == y.end()){
				
				int value = z.front();

				z.pop();

				y.erase(value);

				y.insert(page[j]);

				z.push(page[j]);

				faults++;
			}
		}
	}
	cout << "Page Faults:" << faults<< endl;
	cout << "Frames: ";
	while (!z.empty()) {
		cout << z.front() << " ";
		z.pop();
	}
	cout << endl;
}

void PF_LRU(int page[], int x, int frames) {

	unordered_map<int, int> y;
	unordered_set<int> z;
	int pageFaults = 0;
	for (int i = 0; i < x; i++) {
		if (z.size() < frames) {

			if (z.find(page[i]) == z.end()) {
				z.insert(page[i]);
				pageFaults++;
			}
			y[page[i]] = i;
		}
		else {
			if (z.find(page[i]) == z.end()) {
				int l = INT_MAX;
				int var;
				for (auto iterator = z.begin(); iterator != z.end(); iterator++) {
					if (y[*iterator] < l) {
						l = y[*iterator];
						var = *iterator;
					}
				}
				z.erase(var);
				z.insert(page[i]);
				pageFaults++;

			}
			y[page[i]] = i;

		}
	}
	cout << "Page Faults: " << pageFaults << endl;
	cout << "Frames: " << endl;
	for (auto iterator : y) {
		cout << iterator.first << " " << iterator.second << endl;
	}
}
bool search(int k, vector<int>& frames) {
	for (int i = 0; i < frames.size(); i++) {
		if (frames[i] == k) {
			return true;
		}
		return false;
	}
}
int predict(int page[], vector<int> frames, int p, int in) {
	int result = -1;
		int far = in;
	for (int i = 0; i < frames.size(); i++) {
		int j;
		for (j = in; j < p; j++) {
			if (frames[i] == page[i]) {
				if (j > far) {
					far = j;
					result = i;
				}
				break;
			}
		}
		if (j == p) {
			return i;
		}
	}
	return (result == -1) ? 0 : result;
}
void PF_OPTIMAL(int page[], int p, int f){
	vector<int> frames;
	int hit = 0;
	for (int j = 0; j < p; j++) {
		if (search(page[j], frames)) {
			hit++;
			continue;
		}
		if (frames.size() < f) {
			frames.push_back(page[j]);
		}
		else {
			int j = predict(page, frames, p, j + 1);
			frames[j] = page[j];
		}
	}
	cout << "Page Faults= " << p - hit << endl;
}

int main() {
	/*int* pages;
	cout << "Enter number of pages: ";
	int Size = 0;
	cin >> Size;
	pages = new int[Size]; 
	cout << "enter pages" << endl;
	for (int i = 0; i < Size; i++){
		cin >> pages[i];
	}*/
	int pages[]= { 1, 2, 3, 4, 5, 6, 0, 4, 2, 3, 15, 13, 11 };
	int frames=4;
	//cout << "Enter number of frames:" << endl;
	//cin >> frames;
	double x ;
	x = sizeof(pages) / sizeof(pages[0]);
	cout << "In which algorithm you would like to choose?" << endl;
	cout << "1 for FIFO" << endl;
	cout << "2 for LRU" << endl;
	cout << "3 for Optimal" << endl;
	int choice;
	cin >> choice;
		switch (choice)
		{
		case 1:
			PF_FIFO(pages, x, frames);
			break;
		case 2:
			PF_LRU(pages, x, frames);
			break;
		case 3:
			PF_OPTIMAL(pages, x, frames);
			break;
		}
}