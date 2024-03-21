#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <queue>

std::ifstream in("input.txt");
std::ofstream out("output.txt");

int x, y, n, m, S, nrF, nrCuv;
char l;
std::set<int> final_states;
std::map<int, std::map<char, std::vector<int>>> states;
std::string str;

bool NFA(std::string& str) {
	//I assumed that the lambda letters that may appear in our string are noted with '*'

	//check for lambdas in our string
	str.erase(remove(str.begin(), str.end(), '*'), str.end());
	
	std::queue<std::pair<int, int>> possible_states; //the second element will be the string index  
	possible_states.push({ S,0 });
	while (!possible_states.empty()) {
		std::pair<int, int> state_index = possible_states.front();
		possible_states.pop();
		int state = state_index.first;
		int index = state_index.second;
		if (index < str.length()) {
			if (states[state][str[index]].empty()) {
				// std::cout << "State does not exist" << std::endl;
				continue;
			}
			// multiple states are possible for each letter
			for (auto& possible_state : states[state][str[index]]) {
				possible_states.push({ possible_state,index + 1 });
			}
		}
		else if (index == str.length()) {
			if (final_states.find(state) != final_states.end()) { return true; }
		}
	}
	return false;
}

int main() {

	in >> n;
	for (int i = 0; i < n; i++) {
		in >> x;
		states[x];
	}
	in >> m;
	for (int i = 0; i < m; i++) {
		in >> x >> y;
		in >> l;
		in.get();
		states[x][l].push_back(y);
	}
	in >> S;
	in >> nrF;
	for (int i = 0; i < nrF; i++) {
		in >> x;
		final_states.insert(x);
	}
	in >> nrCuv;
	for (int i = 0; i < nrCuv; i++) {
		in >> str;
		if (NFA(str)) { out << "DA" << std::endl; }
		else { out << "NU" << std::endl; }
	}
	return 0;
}

