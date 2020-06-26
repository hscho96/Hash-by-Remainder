#include <iostream>
#include <cstdint>
#include <vector>
#include <fstream>
#include <string>
#include <boost/math/distributions/chi_squared.hpp>
using namespace std;

vector<int> hashes(65536);
vector<int> entry_size(65536);
ifstream file("words.txt");
string line;
boost::math::chi_squared c2d(65535.0);


void hash_by_remainder() {
	int counter = 0;
	while (file >> line) {
		uint16_t  hashed = 0;
		for (int i = 0; i < line.length(); i++) {
			cout << line << endl;
			uint16_t s_value = line.at(i);
			hashed = hashed + s_value;
			//  cout << "1st: " << hashed << endl;
			hashed = hashed % 65413;
			//  cout << "2nd: " << hashed << endl;
		}

		uint16_t hashed_value = hash<string>{}(line);
		hashes.at(hashed) = hashed_value;
		entry_size.at(hashed) += 1;
		counter++;
	}
	float  expected = counter / 65536.0;
	cout << "counter: " << counter << endl;
	cout << "expected value: " << expected << endl;
	float c2 = 0;
	for (int i = 0; i < 65536; i++) {
		c2 = c2 + (expected - entry_size[i])*(expected - entry_size[i]) / expected;
	}
	float p = boost::math::cdf(c2d, c2);
	cout << "c2: " << c2 << endl;
	cout << "p: " << p << endl; //checking the probability
}
