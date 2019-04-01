#include "main.hpp"

int main()
{
	Item::initialise_itemList("itemdb.txt");
	auto test = Item::itemList.at("processing unit").calculate_production_requirements(6);
	print_map(test);
	//Item::itemList.at("processing unit").print_info();
	
	//system("pause");
	return 0;
}