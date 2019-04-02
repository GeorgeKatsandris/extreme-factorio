#include "item.hpp"

map<string,Item> Item::itemList = {};

Item::Item(const string& name,const string& craftFacility,const float& craftTime,const int& craftedQuantity,const vector<Item*>& mats,const vector<int>& quantities)
{
	this->name = name;
	this->craftFacility = craftFacility;
	this->craftTime = craftTime;
	this->craftedQuantity = craftedQuantity;
	this->mats = mats;
	this->quantities = quantities;
}
Item::Item(const string& name,const string& craftFacility) : Item(name,craftFacility,0,1,vector<Item*>(),vector<int>()) {}

void Item::print_info()
{
	cout << "=== Info for: " << name << " ===" << endl;
	cout << "    Made in: " << craftFacility << endl;
	
	if (!mats.empty())
	{
		cout << "    Time to craft (@1.0 speed): " << craftTime << endl;
		if (craftedQuantity > 1)
			cout << "(" << craftedQuantity << " crafted at once)" << endl;
		
		cout << "    mats: ";
		cout<< quantities[0] << " x " << mats[0]->name;
		for (int i = 1; i < mats.size(); i++)
		{
			cout<< ", " << quantities[i] << " x " << mats[i]->name;
		}
		cout << endl;
	}
	
	cout << endl;
}

bool Item::is_basic_resource() {return mats.empty();}

map<string,float> Item::calculate_production_requirements(const float& requiredRate)
{
	static int indentLength = 0;
	map<string,float> totalRates;
	
	cout << indent(indentLength) << name << " @" << requiredRate <<"/min" << endl;
	
	if (!is_basic_resource())
	{
		map<string,float> submaterialTotalRates;
		
		for (int i = 0; i < mats.size(); i++)
		{
			float submaterialRequiredRate = (requiredRate / craftedQuantity) * quantities[i];
			
			indentLength++;
			submaterialTotalRates = mats[i]->calculate_production_requirements(submaterialRequiredRate);
			indentLength--;
			
			for (auto it = submaterialTotalRates.cbegin(); it != submaterialTotalRates.cend(); it++)
			{
				if (totalRates.count(it->first) == 0)
				{
					totalRates.insert(pair<string,float>(it->first,it->second));
				}
				else
				{
					totalRates[it->first] += it->second;
				}
			}
		}
	}
	
	if (totalRates.count(name) == 0)
	{
		totalRates.insert(pair<string,float>(name,requiredRate));
	}
	else
	{
		totalRates[name] += requiredRate;
	}
	
	return totalRates;
}

void Item::initialise_itemList(const string& filename)
{
	ifstream input(filename);
	string line;
	vector<string> words;
	
	while (getline(input,line))
	{
		if (!line.empty() && line[0] != '#')
		{
			string name;
			string craftFacility;
			float craftTime;
			int craftedQuantity;
			vector<Item*> mats;
			vector<int> quantities;
			
			words = delim_split(line,",");
			
			
			name = words[0];
			craftFacility = words[1];
			
			if (words.size() > 2)
			{
				craftTime = stof(words[2]);
				craftedQuantity = stoi(words[3]);
				
				for (int i = 4; i < words.size(); i += 2)
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
			
			Item tempItem(name,craftFacility,craftTime,craftedQuantity,mats,quantities);
			
			itemList.insert(pair<string,Item>(tempItem.name,tempItem));
		}
	}
}