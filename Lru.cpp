#include <iostream>
#include <list>
#include <string>
#include <unordered_map>
using namespace std;

class Node
{
public:
	
	string key;
	int value;

	Node(string key, int value){
		this->key=key;
		this->value=value;
	}


	
};

class Lru
{
public:

	int maxSize;
	list<Node>l;

	unordered_map<string,list<Node>::iterator>m;

	Lru(int maxSize){
		this->maxSize=maxSize>1?maxSize:1;
	}

	void insertKeyValue(string key, int value){

		// 2 cases

		if(m.count(key)!=0){
			//replace the old value and update

			auto it=m[key];
			it->value=value;
		}
		else{
			//check if cache is full or not
			//agar full hai toh list sur map dono se last 
			//ke element ko htaa do

			if(l.size()==maxSize){
				Node last=l.back();
				//now remove this last node from map 
				m.erase(last.key);

				// rmove from list

				l.pop_back();

			}


			Node n(key,value);
			l.push_front(n);
			m[key]=l.begin();

		}

	}
	
	int* getValue(string Key){

		if(m.count(key)!=0){
			auto it=m[key];

			int value= it->value;
			l.push_front(*it);
			l.erase(it);
			m[key]=l.begin();

			return &l.begin()->value;
		}

		return NULL;

	}

	string mostRecentKey(){

		return l.front().key();

	}
	
};

int main(int argc, char const *argv[])
{
	/* code */
	Lru lru(3);
	lru.insertKeyValue("Adarsh",251);
	lru.insertKeyValue("Anusri",252);
	lru.insertKeyValue("Vishesh",253);

	cout<<lru.mostRecentKey()<<endl;

	lru.insertKeyValue("Adarsh",258);
	cout<<lru.mostRecentKey()<<endl;

	lru.insertKeyValue("Gautam",258);

	// Now perform any operation to test


	return 0;
}