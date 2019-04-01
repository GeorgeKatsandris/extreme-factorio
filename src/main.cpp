#include "main.hpp"

int main()
{
	Item::initialise_itemList("itemdb.txt");
	
	string itemName;
	float requiredProductionRate;
	cout << "Please enter the item you want to mass-produce:" << endl << "    ";

	getline(cin,itemName);
	
	if (Item::itemList.count(itemName) != 0)
	{
		cout << "how many per minute?" << endl << "    ";
		cin >> requiredProductionRate;
		
		auto totalMats = Item::itemList.at(itemName).calculate_production_requirements(requiredProductionRate);
		cout << endl;
		
		cout << "Total production rate of each material:" << endl;
		for (auto it = totalMats.cbegin(); it != totalMats.cend(); it++)
		{
			cout << it->first << " @" << it->second <<"/min" << endl;
		}
		
	}
	else
		cout << "Invalid item name." << endl;
	
	system("pause");
	return 0;
}