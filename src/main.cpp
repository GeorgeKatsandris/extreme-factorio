#include "main.hpp"

int main()
{
	Item::initialise_itemList("itemdb.txt");
	auto test = Item::itemList.at("processing unit").calculate_production_requirements(6);
	
	cout << endl;
	print_map(test);
	
	system("pause");
	return 0;
}