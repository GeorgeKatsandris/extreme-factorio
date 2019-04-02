#ifndef NUM_HPP
#define NUM_HPP

#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include "util.hpp"

using namespace std;

class Item
{
	public:
		string name;
		string craftFacility;
		float craftTime;
		int craftedQuantity;
		vector<Item*> mats;
		vector<int> quantities;
		
		Item();
		Item(const string&,const string&,const float&,const int& craftedQuantity,const vector<Item*>&,const vector<int>&);
		Item(const string&,const string&);
		void print_info();
		bool is_basic_resource();
		map<string,float> calculate_production_requirements(const float&);
		
		static void initialise_itemList(const string&);
		static void get_facility_count(const string&,const float&);
		
		static map<string,Item> itemList;
};

#endif