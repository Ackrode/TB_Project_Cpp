#include <string>
#include <map>
#include <array>
#include <cmath>

using namespace std;
// convert number to binary whitout using bitset
string to_binary(int num)
{
	string binary = "";
	if(num == 0)
		return "0";
	while (num > 0)
	{
		binary = to_string(num % 2) + binary;
		num = num / 2;
	}
	return binary;
}


string stimulus(int n, map <string,array<int,2>> inputs){
string stimulus;
for (int i=0; i<pow(2,n); i++ ){
	for (auto it = inputs.begin(); it != inputs.end(); ++it){
		if (inputs.size()==1){
			stimulus.append("{"+it->first);
			//cout<<i<<endl;
		}
	else
	{
		if (it==inputs.begin()){
			//cout<<it->first<<endl;
			stimulus.append("{"+it->first+", ");
		}
		//last element that it takes
		else{
			//cout<<it->first<<endl;
			stimulus.append(it->first+", ");
		}
	}
		} 
	//delete last comma
	stimulus.erase(stimulus.end()-2);
	stimulus.append("}="+to_string(n)+"'b"+to_binary(i)+"; #1\n");	  
	}
return stimulus;
}



