#include <iostream>
#include <vector>
#include <bits/stdc++.h>
#include <iomanip>
#include<cmath>
#include <bitset>
#include <string>
using namespace std;
 
 

 
struct MOS {
	string drain;
	string source;
	string gate;
};
struct combination {
	string ndrain;
	string nsource;
	vector<MOS> TRANS;
	int TRANS_c = 0;
};
 
int nMOSs_count = 0;
int PMOSs_count = 0;
int MOSs_print_c = 0;
 int wire_count=1; 


//########################################################################

 
void NOT(string valid_exp, string Result)
{
 
	cout << "M";
	cout<< valid_exp;
	cout<< "1";
	cout<< " ";
	cout<< Result;
	cout<< " ";
	cout<< valid_exp;
	cout<< " ";
	cout<< "vdd";
	cout<< " ";
	cout<< "vdd";
	cout<< " ";
	cout<< "PMOS";
	cout<< endl;
 
	cout << "M";
	cout<< valid_exp;
	cout<< "2";
	cout<< " ";
	cout<< Result;
	cout<< " ";
	cout<< valid_exp;
	cout<< " ";
	cout<< "0";
	cout<< " ";
	cout<< "0";
	cout<< " ";
	cout<< "NMOS";
	cout<< endl;
 
}


bool PDN_LESSTHAN4(string input)
{
string line="";

for(int i = 2 ; i<input.length(); i++)
line+=input[i]; 



vector <vector<string>> tokens; 
    stringstream check1(line);
    string intermediate; 
    while(getline(check1, intermediate, '|')) 
    { 
    	vector <string> tokens1;
    	stringstream check2(intermediate);
    	string intermediate1;
 
    	while(getline(check2, intermediate1, '&')) 
    	{
    		tokens1.push_back(intermediate1);
    	}
 
        tokens.push_back(tokens1);

}
int counter = 0; 
for(int i = 0; i < tokens.size(); i++){
    	for(int j = 0; j < tokens[i].size(); j++){
                counter++; 
    
    
        }
}
if(counter!=3)
    return true; 

for(int i = 0; i < tokens.size(); i++){
    	for(int j = 0; j < tokens[i].size(); j++){
            
            if(j==0)
            {
            if(tokens[i].size()>1 )
            cout << "M"<< ++MOSs_print_c<<" "<< input[0] << " " <<tokens[i][j]<< " wire_D" << wire_count++ << " wire_D" << wire_count-1<< " NMOS"<< endl; 
            else 
            cout << "M"<< ++MOSs_print_c<<" "<<input[0]<<  " " << tokens[i][j] << " 0 0" << " NMOS"<< endl; 
            }
    		else if(j== tokens[i].size()-1)
                			cout << "M"<< ++MOSs_print_c<<" wire_D"<< wire_count-1  << " "<<tokens[i][j]<< " "<<"0 0" << " "<< "NMOS"<< endl; 
            else 
            cout << "M"<< ++MOSs_print_c<< " wire_D"<<wire_count-1  << " "<<tokens[i][j]<< " wire_D"<< wire_count++ << " wire_D" << wire_count-1<< " "<< "NMOS"<< endl; 


        }
    }
    return false; 
}

//###################################################

void PDN(string valid_exp) {
 
	vector<combination> or_combinations;
	combination TMP_combination;
	TMP_combination.ndrain = valid_exp[0];//generic Result
	TMP_combination.nsource = "0";
	MOS TMP_MOS;
 
	int i = 2;
	while(i < valid_exp.length()) {
		if (valid_exp[i] == '&') {
			or_combinations.push_back(TMP_combination); 
			TMP_combination.ndrain = "";
			TMP_combination.nsource = "";
			TMP_combination.TRANS.erase(TMP_combination.TRANS.begin(), TMP_combination.TRANS.begin() + TMP_combination.TRANS_c);
			TMP_combination.TRANS_c = 0;
		}
		else if (isalpha(valid_exp[i])) {
			
			nMOSs_count++; 
			
			string t = "";
			if (valid_exp[i + 1] == 39){
				t = "'";
			}
			TMP_MOS.gate = char(valid_exp[i]) + t;
			
			if (or_combinations.size() == 0){
				TMP_combination.ndrain = valid_exp[0];
			}
			else{
				TMP_combination.ndrain = or_combinations.back().nsource;
			}
			TMP_combination.nsource = "Wire_D";
			TMP_combination.nsource+=to_string(or_combinations.size()+1);
			TMP_MOS.drain = TMP_combination.ndrain;
			TMP_MOS.source = TMP_combination.nsource;
			TMP_combination.TRANS.push_back(TMP_MOS);
			TMP_combination.TRANS_c++;
		}
		if (i+1 == valid_exp.length()){ 
			or_combinations.push_back(TMP_combination);
		}
		i++;
	}
 
	i=0;
	while (i < or_combinations.back().TRANS_c) {
		or_combinations.back().TRANS[i].source = "0";
		i++;
	}
 
	i=0;
	while(i < or_combinations.size()) { //loop over the and combinations
		int j = 0;
		while (j < or_combinations[i].TRANS_c) { //loop over the TRANS of each combination
				cout << "M" << ++MOSs_print_c << " ";
				cout<< or_combinations[i].TRANS[j].drain << " ";
				cout<<or_combinations[i].TRANS[j].gate << " ";
				cout<< or_combinations[i].TRANS[j].source << " ";
				cout<< or_combinations[i].TRANS[j].source << " NMOS\n";
				j++;
		}
		i++;
	}
}
 //######################################
void PUN(string valid_exp, string valid_exp2) {
 
	vector<combination> and_combinations;
	combination TMP_combination;
	TMP_combination.ndrain = valid_exp[0];
	TMP_combination.nsource = "vdd";
	MOS TMP_MOS;
 
	int i = 2; 
	while (i < valid_exp.length()) {
		if (valid_exp[i] == '|') {
			and_combinations.push_back(TMP_combination); //push the last and combination to the and combinations vector
			TMP_combination.ndrain = "";
			TMP_combination.nsource = "";
			int off=TMP_combination.TRANS_c;
			TMP_combination.TRANS.erase(TMP_combination.TRANS.begin(), TMP_combination.TRANS.begin() + off);
			TMP_combination.TRANS_c = 0;
		}
		else if (isalpha(valid_exp[i])) {
 
			PMOSs_count++;
			string t = "";
 
			if (valid_exp[i + 1] == 39){
				t = "'";
			}
 
			TMP_MOS.gate = char (valid_exp[i])+t;
 
			if (TMP_combination.TRANS.empty()) {
				TMP_MOS.source = "vdd";
			}
			else{
				TMP_MOS.source = TMP_combination.TRANS.back().drain;
			}
			if ((i + 1) >= valid_exp.size()-1 || valid_exp[i + 1] == '|' || valid_exp[i + 2] == '|'){
				TMP_MOS.drain = valid_exp[0];
			}
			else{
				TMP_MOS.drain = "wire_up";
				TMP_MOS.drain +=  to_string(and_combinations.size() + 1);
			}
 
			TMP_combination.TRANS.push_back(TMP_MOS);
			TMP_combination.TRANS_c++;
 
			if (i >= valid_exp.length()-2){
				and_combinations.push_back(TMP_combination);
			}
		}
 
		i++;
	}
 
	i=0;
	while (i < and_combinations.size()) {
		int j = 0;
		while(j < and_combinations[i].TRANS_c) {
				cout << "M" << ++MOSs_print_c << " ";
				cout<< and_combinations[i].TRANS[j].drain << " ";
				cout<<and_combinations[i].TRANS[j].gate << " ";
				cout<< and_combinations[i].TRANS[j].source << " ";
				cout<< and_combinations[i].TRANS[j].source << " PMOS\n";
				j++;
		}
		i++;
	}
 
	
	 i=0;
	while (i < valid_exp.length())
	{
		if (valid_exp[i] == '|')valid_exp[i] = '&';
		else if (valid_exp[i] == '&')valid_exp[i] = '|';
		i++;
	}
    i=0; 


    	while (i < valid_exp2.length())
	{
		if (valid_exp2[i] == '|')valid_exp2[i] = '&';
		else if (valid_exp2[i] == '&')valid_exp2[i] = '|';
		i++;
	}


	if(PDN_LESSTHAN4(valid_exp2)) PDN(valid_exp);
}
 

 //############################################
 bool is_valid(string s)
 {

     for(int i = 0 ; i<s.length() ; i++)
     {
            if(s[i] == ' ')
            return false; 
         if(s[i] != 39 && s[i] != '|' && s[i] != '&' && i>2)
         {  
             if(!isalpha(s[i]))
                return false; 
         }

     }
    return true; 

 }


void utlity() 
{




    string valid_exp;
	cout << "Can you Enter your Expression? " << endl;
	cin >> valid_exp;
vector<string>x; 

	stringstream ss(valid_exp);
string l ; 
	while(getline(ss,l,';'))
	{
		x.push_back(l);
	}
for(int i = 0 ; i<x.size() ; i++)
{
	valid_exp = x[i]; 
	cout << "The Expression Number "<< i+1 << endl; 
	
    if(is_valid(valid_exp))
    {

	string  w= valid_exp;
		for (int i = 2; i < valid_exp.length(); i++) {
			if (isalpha(valid_exp[i]) && valid_exp[i + 1] != 39) { //an valid_exp needs to be complemented
				 valid_exp.insert(i + 1, "'");
				 string x, y;
				 y+=valid_exp[i];
				 x += valid_exp[i]; 
				 x+="'";
				NOT(y, x);
			}
			else if(valid_exp[i+1]==39) {
				valid_exp.erase( i+ 1, 1);
			}
		}
		PUN(valid_exp,w); //PUN given. Process valid_exp, complement, call PDN at the end of PUN
    }
    else 
    {
        cout <<"Sorry, Your input is invalid.. Try again :) "<< endl; 
        utlity();
    }
}

}


int main() {

 utlity();	
	return 0;
}
 


 