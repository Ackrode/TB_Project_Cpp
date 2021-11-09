#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <regex>
#include <vector>
#include <array>
#include <algorithm>
#include <map>
#include <cstdlib>
using namespace std;
 

/////////////////////
auto split(const std::string& str, const std::string& delim)
{
	std::vector<std::string> vs;
	size_t pos {};
    for (size_t fd = 0; (fd = str.find(delim, pos)) != std::string::npos; pos = fd + delim.size())
		vs.emplace_back(str.data() + pos, str.data() + fd);

	vs.emplace_back(str.data() + pos, str.data() + str.size());
	return vs;
}
////////////////////////////
// function to get the input and output ports of the module

array<map<string,array<int,2>>,2> get_inouts(string Path)
{   //////////////////////////////variables///////////////////////////////
    map<string,array<int,2>> inputS,outputS;            ///////////input and output maps
     array<int,2 > n;
    
    vector<string> matches,nuevo;  
    vector<string> type_name={"input","output","inout","fatal error inputs/outputs"};
    vector<string> inputs,inputs_bus,outputs,outputs_bus,inoutputs,inoutputs_bus;
    vector<string> insize,insize_bus,outsize,outsize_bus,inoutsize,inoutsize_bus;
    int modep;
    std::vector<std::string> prueba,prueba1,contenedor,sizec,sizec_bus; 
////////////////////////////read design.sv file
    ifstream f;
    f.open(Path, ios::in);
    stringstream text;
    text << f.rdbuf();
    f.close();
    string des= text.str();
/////////////////////////get occurrences
    regex re1("(input|output)[\\s]+([^;)]+)*");   
    sregex_iterator rit ( des.begin(), des.end(), re1 );
    sregex_iterator rend;
    while (rit!=rend) {
   matches.push_back(rit->str());
          ++rit;  }   

////////////////Regular expresion
    regex re2("[^\\,]");
    regex re3("([a-zA-Z_a-zA-Z])([^,\\s])*");
    regex re4("(reg|wire)");
    regex re5("([^:\\s\\[\\]\\n])\\b");
    regex re6("([\\[\\]*])");
////////get the inputs and outputs
 for(int t=0; t<matches.size(); t++){
 
 std::string e,e1;
prueba.clear();
prueba1.clear();
contenedor.clear();
sizec.clear();
sizec_bus.clear();
modep=0; 

 const auto vs {split(matches[t], ",")};  ///function split, separate words when find a ","

	for (const auto& e : vs){
  	prueba.push_back(e);}

 const auto vs1 {split(prueba[0], " ")};  ///function split, separate words when find a " "
     	for (const auto& e1 : vs1){
 		 prueba1.push_back(e1);}

 contenedor.insert(contenedor.end(), prueba1.begin(), prueba1.end());
 contenedor.insert(contenedor.end(), prueba.begin()+1, prueba.end()); // get all words
////////////////decide if is a input or output
if(contenedor[0]==type_name[0]){modep=1;}
else if (contenedor[0]==type_name[1] ){ modep=2;}
else if (contenedor[0]==type_name[2]){  modep=3;}
else{ std::cout<<type_name[3];} 
//////////////////////////////////get the names ports.                                          
vector<string> cont{},cont_bus{};
int b=0,p=0; 
                                               
if (std::regex_match (contenedor[1], re4) ){ b=1; } //get type of inputs/outpus[wire,reg]
else{ for(int l=1; l<contenedor.size(); l++){
     cont.push_back(contenedor[l]);
	 sizec.push_back("0");}	 	}
  
////////////////////////////////////////////////////
if (b==1){                                           //if there is a bus     
  if(std::regex_search(contenedor[2], re6) ){
     for(int l=3; l<contenedor.size(); l++) {
     cont_bus.push_back(contenedor[l]);
     sregex_iterator rit1( contenedor[2].begin(), contenedor[2].end(), re5 );
     sregex_iterator rend1;                    
     while (rit1!=rend1){
         sizec_bus.push_back(rit1->str());
            ++rit1;  }    }                         
                              }               
  else{                                          //if there isn't a bus
 	 for(int l=2; l<contenedor.size(); l++){ 
      cont.push_back(contenedor[l]);
	   sizec.push_back("0");}
 	 	} }

///////assign inputs and outputs with bus
if(std::regex_search(contenedor[2], re6) ){
if(modep==1){ for(int n=0; n<cont_bus.size();n++){
		inputs_bus.push_back(cont_bus[n]); 
	}
for(int n=0; n<sizec_bus.size();n++){
		insize_bus.push_back(sizec_bus[n]); 	} }
else if (modep==2)
    {   for(int n=0; n<cont_bus.size();n++){
		outputs_bus.push_back(cont_bus[n]); 	} 
    for(int n=0; n<sizec_bus.size();n++){
		outsize_bus.push_back(sizec_bus[n]);  }  }
else{
      for(int n=0; n<cont_bus.size();n++){
	inoutputs_bus.push_back(cont_bus[n]); } 
     for(int n=0; n<sizec_bus.size();n++){
		inoutsize_bus.push_back(sizec_bus[n]); 	} }}

///////assign inputs and outputs without bus
if(modep==1){
    for(int n=0; n<cont.size();n++){
		inputs.push_back(cont[n]); 	}
    for(int n=0; n<sizec.size();n++){
		insize.push_back(sizec[n]); 	}     }
else if (modep==2)
    {   for(int n=0; n<cont.size();n++){
		outputs.push_back(cont[n]); 	} 
    for(int n=0; n<sizec.size();n++){
		outsize.push_back(sizec[n]);     }  }
else{
    for(int n=0; n<cont.size();n++){
		inoutputs.push_back(cont[n]);	} 
     for(int n=0; n<sizec.size();n++){
		inoutsize.push_back(sizec[n]); 	} } }
///////////////////// assing all inputs and output to maps
 for(int i=0; i<inputs.size(); i++){
    n[0]=atoi(insize[i].c_str());
    inputS.insert(pair<string,array<int,2>>(inputs[i],{0,n[0]}));
 } 
 for(int i=0; i<outputs.size(); i++){
    n[0]=atoi(insize[i].c_str());
    outputS.insert(pair<string,array<int,2>>(inputs[i],{0,n[0]}));
 } 

 for(int i=0; i<inputs_bus.size(); i++){
    n[1]=atoi(insize_bus[2*i].c_str());
    n[0]=atoi(insize_bus[(2*i)+1].c_str());
    inputS.insert(pair<string,array<int,2>>(inputs_bus[i],{n[1],n[0]}));
 } 
 for(int i=0; i<outputs_bus.size(); i++){
    n[1]=atoi(outsize_bus[2*i].c_str());
    n[0]=atoi(outsize_bus[(2*i)+1].c_str());
    outputS.insert(pair<string,array<int,2>>(outputs[i],{0,n[0]}));
 } 

//////// inputS, outputS  are maps
 ///////////print outs and inputs
/*cout<<"Inputs:"<<endl;
for(auto it=inputS.begin(); it!=inputS.end();it++){
    cout<<it->first<<" "<<it->second[0]<<" "<<it->second[1]<<endl;
}
cout<<"Outputs:"<<endl;
for(auto it=outputS.begin(); it!=outputS.end();it++){
    cout<<it->first<<" "<<it->second[0]<<" "<<it->second[1]<<endl;
}*/
  // Return inputs and outputs
  return {inputS, outputS};

}