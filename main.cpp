#include<string>
#include<iostream>
#include<vector>

using namespace std;

class Rule
{
	public:
		string input, output;
		
		Rule(string input, string output):input(input), output(output){};
		
		double match(string input)
		{
			if(this->input == input)
				return 1.0;
			if(this->input.find(input) != std::string::npos || input.find(this->input) != std::string::npos)
				return 0.5;
			return 0.0;
		};
};

vector<string> conversation;
vector<Rule> rules;

void learn(string input)
{
	if(!conversation.empty())
	{
		string last = conversation.back();
		Rule newRule(last, input);
		rules.push_back(newRule);
	}
	conversation.push_back(input);
}

string reply(string input)
{
	Rule bestRule(input, input);
	double bestScore = 0;
	for(Rule rule:rules)
	{
		double score = rule.match(input);
		if(score > bestScore)
		{
			bestScore = score;
			bestRule = rule;
		}
	}
	return bestRule.output;
}

//g++ -std=gnu++11 *.cpp -o AgentParlant
int main(int argc, char *argv[])
{
	cout<<"対話システム起動"<<endl;
	while(true)
	{
		cout<<"入力文：";
		string input;
		cin>>input;
		learn(input);
		string response = reply(input);
		
		cout<<"回答文："<<response<<endl;
	}
	cout<<"対話システム終了"<<endl;
	return 0;
}
