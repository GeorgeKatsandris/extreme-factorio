#ifndef NUM_HPP
#define NUM_HPP

#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include <string>
#include <cmath>
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
		string get_facility_count(const float&);
		
		static void initialise_itemList(const string&);
		static void load_settings(const string&);
		
		static map<string,Item> itemList;
		static float baseAssemblerSpeed;
		static float baseDrillSpeed;
		static float basePlantSpeed;
		static float baseFurnaceSpeed;
		static float speedModMultiplier;
		static float productivityModMultiplier;
		static float efficiencyModMultiplier;
};

#endif