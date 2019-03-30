#include "main.hpp"
//sorry
int main()
{
	Item::initialise_itemList("itemdb.txt");
	auto test = Item::itemList.at("processing unit").calculate_production_requirements(2);
	print_map(test);
	
	//system("pause");
	return 0;
}