#include "item.hpp"

map<string,Item> Item::itemList = {};

Item::Item(const string& name,const float& craftTime,const int& craftedQuantity,const vector<Item*>& mats,const vector<int>& quantities)
{
	this->name = name;
	this->craftTime = craftTime;
	this->craftedQuantity = craftedQuantity;
	this->mats = mats;
	this->quantities = quantities;
}
Item::Item(const string& name) : Item(name,0,1,vector<Item*>(),vector<int>()) {}

void Item::print_info()
{
	cout << "Info for: " << name << endl;
	
	if (!mats.empty())
	{
		cout << "Time to craft (@1.0 speed): " << craftTime << endl;
		if (craftedQuantity > 1)
			cout << "(" << craftedQuantity << " crafted at once)" << endl;
		
		cout << "mats: ";
		cout<< quantities[0] << " x " << mats[0]->name;
		for (int i = 1; i < mats.size(); i++)
		{
			cout<< ", " << quantities[i] << " x " << mats[i]->name;
		}
		cout << endl;
	}
	else
	{
		cout << "It is a basic material." << endl;
	}
	
	cout << endl;
}

bool Item::is_basic_resource() {return mats.empty();}

map<string,float> Item::calculate_production_requirements(const float& rate)
{
	static int indentLength = 0;
	map<string,float> totalRates;
	
	if (totalRates.count(name) == 0)
		totalRates.insert(pair<string,float>(name,rate));
	else
	{
		totalRates[name] += rate;
	}
	
	//cout << indent(indentLength) << name << " @" << rate <<"/min" << endl;
	
	if (!is_basic_resource())
	{
		for (int i = 0; i < mats.size(); i++)
		{
			float requiredRate = rate * quantities[i];
			map<string,float> submaterialTotalRates;
			
			indentLength++;
			submaterialTotalRates = mats[i]->calculate_production_requirements(requiredRate);
			indentLength--;
			//mats[i]->print_info();
			
			for (auto it = submaterialTotalRates.cbegin(); it != submaterialTotalRates.cend(); it++)
			{
				if (totalRates.count(name) == 0)
					totalRates.insert(pair<string,float>(name,rate));
				else
				{
					totalRates[name] += rate;
				}
			}
		}
	}
	
	return totalRates;
}

void Item::initialise_itemList(string filename)
{
	ifstream input("itemdb.txt");
	string line;
	vector<string> words;
	
	while (getline(input,line))
	{
		if (!line.empty() && line[0] != '#')
		{
			string name;
			float craftTime;
			int craftedQuantity;
			vector<Item*> mats;
			vector<int> quantities;
			
			words = delim_split(line,",");
			
			
			name = words[0];
			
			if (words.size() > 1)
			{
				craftTime = stof(words[1]);
				craftedQuantity = stoi(words[2]);
				
				for (int i = 3; i < words.size(); i += 2)
				{
					string mat_name = words[i];
					int mat_quantity = stoi(words[i+1]);
					
					map<string,Item>::iterator it;
					it = itemList.find(mat_name);
					
					if (it != itemList.end())
					{
						Item* mat = &(it->second);
						
						mats.push_back(mat);
						quantities.push_back(mat_quantity);
					}
				}
			}
			
			Item tempItem(name,craftTime,craftedQuantity,mats,quantities);
			
			itemList.insert(pair<string,Item>(tempItem.name,tempItem));
		}
	}
}