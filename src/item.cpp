#include "item.hpp"

float Item::baseAssemblerSpeed = -1;
float Item::baseDrillSpeed = -1;
float Item::basePlantSpeed = 1;
float Item::baseFurnaceSpeed = -1;
float Item::speedModMultiplier = -1;
float Item::productivityModMultiplier = -1;
float Item::efficiencyModMultiplier = -1;
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
Item::Item(const string& name,const string& craftFacility) : Item(name,craftFacility,1,1,vector<Item*>(),vector<int>()) {}

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

void Item::load_settings(const string& filename)
{
	ifstream input(filename);
	string line;
	vector<string> words;
	
	while (getline(input,line))
	{
		if (!line.empty() && line[0] != '#')
		{
			words = delim_split(line,",");
			
			if (words[0] == "assemblerlvl")
			{
				int lvl = stoi(words[1]);
				
				switch(lvl)
				{
					case 1:
						Item::baseAssemblerSpeed = 0.5;
						break;
					case 2:
						Item::baseAssemblerSpeed = 0.75;
						break;
					case 3:
						Item::baseAssemblerSpeed = 1;
						break;
				}
			}
			else if (words[0] == "furnacelvl")
			{
				if (words[1] == "stone")
					Item::baseFurnaceSpeed = 1;
				if (words[1] == "steel")
					Item::baseFurnaceSpeed = 2;
				if (words[1] == "electric")
					Item::baseFurnaceSpeed = 2;
			}
			else if (words[0] == "drilllvl")
			{
				if (words[1] == "burner")
					Item::baseDrillSpeed = 0.25;
				if (words[1] == "electric")
					Item::baseDrillSpeed = 0.5;
			}
			else if (words[0] == "speedmodlvl")
			{
				int lvl = stoi(words[1]);
				
				switch (lvl)
				{
					case 1:
						Item::speedModMultiplier = 1.2;
					case 2:
						Item::speedModMultiplier = 1.3;
					case 3:
						Item::speedModMultiplier = 1.5;
				}
			}
			else if (words[0] == "productivitymodlvl")
			{
				int lvl = stoi(words[1]);
				
				switch (lvl)
				{
					case 1:
						Item::productivityModMultiplier = 1.04;
					case 2:
						Item::productivityModMultiplier = 1.06;
					case 3:
						Item::productivityModMultiplier = 1.1;
				}
			}
			else if (words[0] == "efficiencymodlvl")
			{
				int lvl = stoi(words[1]);
				
				switch (lvl)
				{
					case 1:
						Item::efficiencyModMultiplier = 0.7;
					case 2:
						Item::efficiencyModMultiplier = 0.6;
					case 3:
						Item::efficiencyModMultiplier = 0.5;
				}
			}
		}
	}
	
	if (Item::baseAssemblerSpeed == -1)
		cout << "WARNING: Assembling machine upgrade level not set" << endl;
	
	if (Item::baseDrillSpeed == -1)
		cout << "WARNING: Mining Drill upgrade level not set" << endl;

	if (Item::baseFurnaceSpeed == -1)
		cout << "WARNING: Furnace upgrade level not set" << endl;
	
	if (Item::speedModMultiplier == -1)
		cout << "WARNING: Speed module upgrade level not set" << endl;

	if (Item::productivityModMultiplier == -1)
		cout << "WARNING: Productivity module upgrade level not set" << endl;

	if (Item::efficiencyModMultiplier == -1)
		cout << "WARNING: Efficiency upgrade level not set" << endl;
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
				
				Item tempItem(name,craftFacility,craftTime,craftedQuantity,mats,quantities);
				
				itemList.insert(pair<string,Item>(tempItem.name,tempItem));
			}
			else
			{
				Item tempItem(name,craftFacility);
				
				itemList.insert(pair<string,Item>(tempItem.name,tempItem));
			}
		}
	}
}

string Item::get_facility_count(const float& requiredRate)
{
	string type = craftFacility;
	
	float facilitySpeed;
	if (type == "assembler")
		facilitySpeed = Item::baseAssemblerSpeed;
	else if (type == "drill")
		facilitySpeed = Item::baseDrillSpeed;
	else if (type == "plant")
		facilitySpeed = Item::basePlantSpeed;
	else if (type == "furnace")
		facilitySpeed = Item::baseFurnaceSpeed;
	
	float facilityRate = facilitySpeed * craftedQuantity * 60 / craftTime;
	
	int number = ceil(requiredRate / facilityRate);
	
	if (number > 1)
		type = type + "s";
	
	string output;
	if (type != "ignore")
		output = " - needs at least " + to_string(number) + " " + type;
	else
		output = "";
	return output;
}