/*****************************************************************************
* 								PhysicalGroup.cpp
* 								=================
*
* AUTHOR: Sumeet Kumar Sinha (sumeet.kumar507@gmail.com)
* CREATED: 28-06-2015
*******************************************************************************/

#include "PhysicalGroup.h"
#include <iostream>
#include <string>
#include <algorithm>
using namespace::std;

/******************************************************************************
****************************** Constructor ************************************
******************************************************************************/

PhysicalGroup::PhysicalGroup(){}

PhysicalGroup::PhysicalGroup(const string& PhysicDes){

	this->setContents(PhysicDes);
}

PhysicalGroup::~PhysicalGroup(){}

/******************************************************************************
**************************** Public Functions *********************************
******************************************************************************/

void PhysicalGroup::setPhysicalGroup(const string& PhysicDes){

	this->setContents(PhysicDes);
}

void PhysicalGroup::setId(const int& id){

	this->Id=id;
}
void PhysicalGroup::setType(const int& type){

	this->Type = type;
}
void PhysicalGroup::setPhysicTag(const string& physicTag){

	this->PhysicTag = physicTag;
}

int PhysicalGroup::getId(){

	return this->Id;
}
int PhysicalGroup::getType(){

	return this->Type;
}
string PhysicalGroup::getPhysicTag(){

	return this->PhysicTag;
}
vector<string> PhysicalGroup::PhysicalGroup::getCommandList(){

	return this->CommandList;
}
vector<vector<string>> PhysicalGroup::getVariableList(){

	return this->VariableList;
}

vector<int> PhysicalGroup::getNofVariables(){

	return this->NofVariables;
}

/******************************************************************************
**************************** Private Functions ********************************
******************************************************************************/		

void PhysicalGroup::setContents(const string& PhysicDes){

	Tokenizer str = Tokenizer(PhysicDes,"  \t\v\n\r\f\"$");
	this->Type = stoi(str.nextToken());
	this->Id = stoi(str.nextToken());
	this->PhysicTag = str.nextToken();

	while(str.hasMoreTokens()){

		str.setDelimiter("<>");
		if(! this->delSpaces(str.nextToken()).compare("\""))
			break;
		if(!str.hasMoreTokens())
			break;

		this->Process(this->delSpaces(str.nextToken()));
	}

}

void PhysicalGroup::Process(const string& Command ){

	int nofTokens = 0, nofVariables=0; 
	vector<string> varList;
	string essiTag="";
	Tokenizer inpString = Tokenizer(Command," {,;}()");
	nofTokens = inpString.countTokens()-1;
	nofVariables = nofTokens-1;
	essiTag = essiTag + inpString.nextToken() + "{";
	
	for( int i=0 ;i<nofTokens-1; i++){

		string variable= this->delSpaces(inpString.nextToken());
		varList.push_back(variable);
		essiTag = essiTag + " ,";
	}

	string variable= this->delSpaces(inpString.nextToken());
	varList.push_back(variable);

	if(variable.compare("")){
		nofVariables++;
	}

	essiTag = essiTag + " }"+to_string(nofVariables);
	this->VariableList.push_back(varList);
	this->CommandList.push_back(essiTag);
	this->NofVariables.push_back(nofVariables);

}

string PhysicalGroup::delSpaces(string str){
   str.erase(std::remove(str.begin(), str.end(), ' '), str.end());
   return str;
}
