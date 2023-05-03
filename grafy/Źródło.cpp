#include<iostream>
#include<cstdlib>
#include<array>
#include<chrono>
#include<fstream>
using namespace std;

 int i = 5;
const int test = 2; //co zamiast -1
const int druk = 1;
int** a;
int** d;
int* stack;
int* stack2;
int* stack3;
int last = 0;
void must() {
	a = new int* [i+1];
	for (int p = 0; p < i; p++) {
		a[p] = new int[i+1];
	}
	d = new int* [i+3];
	for (int p = 0; p < i+2; p++) {
		d[p] = new int[i+1]; 
	}
	stack = new int[i + 1];
	for (int a = 0; a < i + 1; a++) {
		stack[a] = 0;
	}
	stack2 = new int[i + 1];
	for (int a = 0; a < i + 1; a++) {
		stack2[a] = 0;
	}
	stack3 = new int[i + 1];
	for (int a = 0; a < i + 1; a++) {
		stack3[a] = 0;
	}
	for (int q = 0; q < i; q++) {
		for (int w = 0; w < i; w++) {
			a[q][w] = 0;
		}
	}
}
//int a[i][i];
//int d[i][i + 3];
void load1() {
	fstream newfile;
	newfile.open("input.txt", ios::in);
	if (newfile.is_open()) {
		/*cout << "Otwarto plik input.txt\n";
		int q = 0;
		int m = 0;
		newfile << q << m;
		i = q;
		must();
		for (int v = 0; v < m; v++) {
			int w;
			newfile >> q >> w;
			cout << q << w;
		}*/
		int line;
		int line2;
		int line3;
		newfile >> line;
		i = line;
		must();
		newfile >> line;
		for (int q = 0; q < line; q++) {
			newfile >> line2;
			newfile >> line3;
			a[line2-1][line3-1] = 1;
		}
		newfile.close();
	}
	else {
		cout << "Plik nie znaleziony\n";
	}
}
//good
void load2() {
	load1();
	for (int q = 0; q < i; q++) {
		int minnext = i + 1;
		int minprev = i + 1;
		int maxnext = -1;
		int maxprev = -1;
		int minnull = i + 1;
		int maxnull = -1;
		for (int w = 0; w < i; w++) {
			if (a[q][w] == 1) {
				maxnext = w;
				if (minnext > w) {
					minnext = w;
				}
			}
			else if (a[w][q] == 1) {
				maxprev = w;
				if (minprev > w) {
					minprev = w;
				}
			}
		}
		d[q][i + 2] = -1;

		if (minnext == i + 1) {
			d[q][i] = 0;
		}
		else {
			d[q][i] = minnext + 1;
		}
		if (minprev == i + 1) {
			d[q][i + 1] = 0;
		}
		else {
			d[q][i + 1] = minprev + 1;
		}
		for (int w = 0; w < i; w++) {
			if (a[q][w] == 1) {
				d[q][w] = maxnext + 1;
			}
			else if (a[w][q] == 1) {
				d[q][w] = maxprev + i + 1;
			}
			else if (a[q][w] == 0) {
				d[q][w] = -1;
			}
		}
		for (int w = 0; w < i; w++) {
			if (d[q][w] == -1) {
				maxnull = w;
				if (minnull > w) {
					minnull = w;
				}
			}
		}
		for (int w = 0; w < i; w++) {
			if (d[q][w] == -1) {
				if (maxnull != i + 1) {
					d[q][w] = -(maxnull + 1);
				}
				else {
					d[q][w] = 0;
				}
			}
		}
		if (minnull != -1) {
			d[q][i + 2] = minnull + 1;
		}
		else {
			d[q][i + 2] = 0;
		}
	}
}


void macierz1() {
	for (int q = 0; q < i; q++) {
		for (int w = 0; w < i; w++) {
			a[q][w] = 0;
		}
	}
	srand((unsigned)time(NULL));
	for (int q = 1; q < i; q++) {
		for (int w = 0; w < q; w++) {
			if ((rand() % 2) == 1) {
				a[w][q] = 1;
				a[q][w] = 0;
			}
			else {
				a[w][q] = 0;
				a[q][w] = 0;
			}
		}
	}
	//print
	if (druk == 1) {
		for (int q = 0; q < i; q++) {
			for (int w = 0; w < i; w++) {
				cout << a[q][w] << " ";
			}
			cout << "\n";
		}
	}
} 
//good
void macierz2() {
	for (int q = 0; q < i; q++) {
		for (int w = 0; w < i; w++) {
			a[q][w] = 0;
		}
	}
	srand((unsigned)time(NULL));
	for (int q = 1; q < i; q++) {
		for (int w = 0; w < q; w++) {
			if ((rand() % 2) == 1) {
				a[w][q] = 1;
				a[q][w] = 0;
			}
			else {
				a[w][q] = 0;
				a[q][w] = 0;
			}
		}
	}
	for (int q = 0; q < i; q++) {
		int minnext = i + 1;
		int minprev = i + 1;
		int maxnext = -1;
		int maxprev = -1;
		int minnull = i + 1;
		int maxnull = -1;
		for (int w = 0; w < i; w++) {
			if (a[q][w] == 1) {
				maxnext = w;
				if (minnext > w) {
					minnext = w;
				}
			}
			else if (a[w][q] == 1) {
				maxprev = w;
				if (minprev > w) {
					minprev = w;
				}
			}
		}
		d[q][i + 2] = -1;

		if (minnext == i + 1) {
			d[q][i] = 0;
		}
		else {
			d[q][i] = minnext +1;
		}
		if (minprev == i + 1) {
			d[q][i + 1] = 0;
		}
		else {
			d[q][i + 1] = minprev+1;
		}
		for (int w = 0; w < i; w++) {
			if (a[q][w] == 1) {
				d[q][w] = maxnext+1;
			}
			else if (a[w][q] == 1) {
				d[q][w] = maxprev + i + 1;
			}
			else if (a[q][w] == 0) {
				d[q][w] = -1;
			}
		}
		for (int w = 0; w < i; w++) {
			if (d[q][w] == -1) {
				maxnull = w;
				if (minnull > w) {
					minnull = w;
				}
			}
		}
		for (int w = 0; w < i; w++) {
			if (d[q][w] == -1) {
				if (maxnull != i + 1) {
					d[q][w] = -(maxnull + 1);
				}
				else {
					d[q][w] = 0;
				}
			}
		}
		if (minnull != -1) {
			d[q][i + 2] = minnull + 1;
		}
		else {
			d[q][i + 2] = 0;
		}
	}
	if (druk == 1) {
		for (int q = 0; q < i; q++) {
			for (int w = 0; w < i + 3; w++) {
				cout << d[q][w] << " ";
			}
			cout << "\n";
		}
		cout << "\n";
		for (int q = 0; q < i; q++) {
			for (int w = 0; w < i; w++) {
				cout << a[q][w] << " ";
			}
			cout << "\n";
		}
	}
}
//good
void macierz1dfs() {
	bool end = false;
	int counter = 0;
	int counter2 = -1;
	int counter3 = -1;
	int value = 0;
	int value1 = -1; //temporary value holding
	//stack - 0 - bia³y, 1 - szary, 2 - czarny
	//stack 2- the result
	//stack 3- current nod order
	while (true) {
		if (counter2 >= i) {
			cout << "Loop detected\n";
			return;
		}
		if (counter2 == -1) {
			for (int p = i - 1; p >= 0; --p) {
				if (stack[p] == 0) {
					value1 = p;
				}
			}
			if (value1 == -1) {
				cout << "end";
				return;
			}
			else {
				counter2 += 1;
				value = value1;
			}
		}
		if (stack[value] != 2) {
			counter2++;
			value1 = -1;
			stack[value] = 1;
			stack3[counter2] = value;
		}
		for (int n = i - 1; n >= 0; n--) {
			if (a[value][n] == 1 && stack[n] != 2) {
				value1 = n;
				//cout << "Value1" << value1 + 1 << " ";
			}
		}
		if (value1 == -1) {
			stack[value] = 2;
			if (counter3 != value) {
				if (druk == 1) { cout << " " << value + 1 << " "; }
			}
			counter3 = value;
			//stack2[counter] = value+1;
			//counter++;
			counter2 -= 1;
			if (counter2 != 0) {
				value = stack3[counter2];
			}
			else {
				counter2 = -1;
			}
		}
		else {
			value = value1;
			value1 = -1;
		}
		//cout << "counter->" << counter2 << "\n";
	}
}
void macierz2dfs() {

}
void macierz1del() {
	//stack -> 0 - niewypisane, 1 - wypisane
	int value = -1;
	int value1 = -1;
	int counter = 1;
	int printed = -1;
	while (true) {
		for (int p = i-1; p >= 0; --p) {
			for (int d = i-1; d >= 0; d--) {
				if (a[d][p] == 1 && stack[p] != 1) {
					value1 = 1;
				}
			}
			if (value1 == -1) {
				if (stack[p] != 1) {
					value = p;
				}
			}
			value1 = -1;
		}
		if (value == -1) {
			cout << "Loop detected\n";
			return;
		}
		stack[value] = 1;
		if (druk == 1) {
			if (printed != value) {
				cout << value + 1 << " "; printed = value;
			}
			else {
				cout << "Loop detected\n";
				return;
			}
		}
		for (int p = i-1; p >= 0; --p) {
			a[value][p] = 0;
		}
		for (int p = i-1; p >= 0; --p) {
			if (stack[p] == 0) {
				counter = 0;
			}
		}
		if (counter == 1) {
			cout << " Done\n";
			return;
		}
		counter = 1;
	}
}
void macierz2del() {

}



int main() {
	load2();
	for (int q = 0; q < i; q++) {
		for (int w = 0; w < i+3; w++) {
			cout << d[q][w] << " ";
		}
		cout << "\n";
	}
	
}