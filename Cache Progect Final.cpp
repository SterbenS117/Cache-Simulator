// cache project.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <cstdio>
#include <cstdlib>
#include "stdio.h"
#include "stdlib.h"
#include <cmath>
#include <iostream>
#include "time.h"
#include <ctime>
#include <cmath>
#include "math.h"

using namespace std;

const int HIT_LATENCY = 40;
const int MISS_LATENCY = 200;
const int NUM_WAYS = 16;
const int NUM_SETS = 2048;
const int INTRUCTION_NUM = 500000;
int miss_int = 0;
int hit_int = 0;



struct block {

	int tag;
	int repl;
	bool valid;

};

block cache[2048][16];

int getTag(long int rand_addr);
int getIndex(long int rand_addr);
int random_address();
void miss();
void hit();
void access_cache(long int addr);
int get_replace(int index);

int main()
{
	//cout << "hello";

	srand(time(0));
	long int current_addr;
	double current_addr_d;
	int i, j, counter_int, rand_address_int;
	counter_int = 0;

	for (int i = 0; i < INTRUCTION_NUM; i++)
	{

		current_addr = (rand() % (int)pow(2, 16)) * (rand() % (int)pow(2, 16));

		access_cache(current_addr);
		//cout << cache[i][j] << endl;
		counter_int = counter_int + 1;

	}

	cout << "miss: " << miss_int << endl;
	cout << "hit: " << hit_int << endl;
	//rand_address_int = random_address();
	//cout << hit_int;
	//cout << endl << rand_address_int << endl;
	//cout << (rand_address_int >> 17);
	//cout << endl << cache[0][0] << endl;
	//cout << counter_int << endl;
	//cout << "Hello World!\n";
	return 0;
}

int random_address() {
	int i, j, address_int;
	srand(time(0));
	i = rand() % NUM_SETS;
	j = rand() % NUM_WAYS;

	address_int = cache[i][j].tag;

	return address_int;
}



void access_cache(long int addr) {
	long int rand_addr;
	int index_int, tag_int, i, replace;
	rand_addr = addr;
	index_int = getIndex(rand_addr);
	tag_int = getTag(rand_addr);
	rand_addr = random_address();
	//cout << tag_int;
	for (i = 0; i < NUM_WAYS; i++)
	{
		if (cache[index_int][i].tag == tag_int)
		{
			hit();
			cache[index_int][i].valid = 1;
			cache[index_int][i].tag = tag_int;
			// << "yes";
		}
		else
		{
			replace = get_replace(index_int);
			//cout << replace<< endl;
			cache[index_int][replace].tag = tag_int;
			cache[index_int][replace].valid = 1;
			miss();
		}
	}

}

int get_replace(int index) {
	for (int i = 0; i < NUM_WAYS; i++) {

		if (cache[index][i].valid == 0) {
			cache[index][i].valid = 1;
			//cout << "yes" << endl;
			return i;
		}

	}

	for (int i = 0; i < NUM_WAYS; i++) {
		if (cache[index][i].repl == NUM_WAYS - 1) {
			//cout << "hope" << endl;
			return i;
		}
	}
	//cout << "yes" << endl;
}

int getIndex(long int rand_addr) {
	int index;
	long int addr = rand_addr;
	index = (addr >> 6) % NUM_SETS - 1;
	//cout << index<< endl;
	//diagnostics cout 
	return index;
}

int getTag(long int rand_addr) {
	int tag;
	tag = rand_addr >> 17;
	//cout << tag<< endl;
	//diagnostics cout 
	return tag;
}


void hit() {
	hit_int++;
}

void miss() {
	long double warmup_int, total_miss;
	total_miss = 0;
	warmup_int = 0.10 * (5 * (int)pow(10, 7));
	total_miss++;
	if (total_miss <= warmup_int) {
		miss_int++;
	}
}




// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file


