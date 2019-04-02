#include "main.hpp"

int main()
{
	Item::initialise_itemList("itemdb.txt");
	
	string itemName;
	float requiredProductionRate;
	cout << "Please enter the item you want to mass-produce:" << endl << "    >";

	//getline(cin,itemName);
	itemName = "copper cable";
	
	if (Item::itemList.count(itemName) != 0)
	{
		cout << "how many per minute?" << endl << "    >";
		//cin >> requiredProductionRate;
		requiredProductionRate = 100;
		cout << endl;
		
		cout << "=== Production rate requirement analysis: ===" << endl;
		auto totalMats = Item::itemList.at(itemName).calculate_production_requirements(requiredProductionRate);
		cout << endl;
		
		cout << "=== Total required production rate of each material: ===" << endl;
		for (auto it = totalMats.cbegin(); it != totalMats.cend(); it++)
		{
			string facility_count = Item::itemList.at(it->first).get_facility_count(it->second);
			
			cout << it->first << " @" << it->second <<"/min" << facility_count << endl;
		}
	}
	else
		cout << "Invalid item name." << endl;
	
	//system("pause");
	return 0;
}