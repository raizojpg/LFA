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


bool Lambda_NFA(std::string& str) {
	// It is cicleproof because we use a queue so each element will have it's chance to advance,
	//	 and we won't go back to states that we already visited if we don't make any progress
	// I assumed that the lambda states transitions are noted with '*' 
	// I assumed that the lambda letters that may appear in our string are noted with '*'
	
	//check for lambdas in our string
	str.erase(remove(str.begin(), str.end(), '*'), str.end());

	struct SIP {
		int state;
		int index;
		std::set<int> path; // discovered states without any progress
	};

	std::queue<SIP> possible_states;
	possible_states.push({ S,0,{} });
	while (!possible_states.empty()) {
		SIP sip = possible_states.front();
		possible_states.pop();
		int state = sip.state;
		int index = sip.index;
		std::set<int> discovered_states = sip.path;
		discovered_states.insert(state);
		if (index < str.length()) {
			// check for lambda states
			for (auto& possible_state : states[state]['*']) {
				if (discovered_states.find(possible_state) == discovered_states.end()) {
					possible_states.push({ possible_state,index,discovered_states });
				}
			}
			if (states[state][str[index]].empty()) {
				// std::cout << "State does not exist" << std::endl;
				continue;
			}
			// multiple states are possible for each letter
			for (auto& possible_state : states[state][str[index]]) {
				possible_states.push({ possible_state,index + 1,{} });
				// we advanced the iteration, therefore we could go back on the states that we have already visited
			}
		}
		else if (index == str.length()) {
			if (final_states.find(state) != final_states.end()) { return true; }
			// check for lambda states
			for (auto& possible_state : states[state]['*']) {
				if (discovered_states.find(possible_state) == discovered_states.end()) {
					possible_states.push({ possible_state,index,discovered_states });
				}
			}
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
		if (Lambda_NFA(str)) { out << "DA" << std::endl; }
		else { out << "NU" << std::endl; }
	}
	return 0;
}