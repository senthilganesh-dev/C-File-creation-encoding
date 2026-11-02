#include<iostream>
#include"huffman_coding.h"







void getdata(string *input){
    cout<<"Enter an msg:";
    
    getline(cin,*input);
}

//Constrian to sort

bool constrain(const pair<char, int>& a, const pair<char, int>& b) {
    if(a.second!=b.second)return a.second < b.second; else return (a.first < b.second);
}

bool constrain_node(hauffman_tree *a,hauffman_tree *b){
    return (a->frequency < b->frequency);
}

//Frequency checker and assign
map<char,int> frequency_count(string &data){
    map<char,int>result;
    for(const auto &x: data){
            
            result[x]++;
          
    }

return result;
}

//Linking nodes

void link(vector<hauffman_tree*> &nodes,vector<pair<char,int>> sorted_frequency){
   int i=0;
    for(auto [key,freq]: sorted_frequency)
        nodes[i++]=(new hauffman_tree(key,freq));
        
    
    
    
    
    while(nodes.size()>1){
        hauffman_tree *a=nodes[0],*b=nodes[1],*c;
     
        int n=a->frequency+b->frequency;
    
        c=new hauffman_tree((char)n,n);
        
        c->lc=a;
        c->rc=b;
         nodes.erase(nodes.begin(), nodes.begin() + 2);
        
         auto pos = lower_bound(nodes.begin(), nodes.end(), c,
            [](hauffman_tree *x, hauffman_tree *y) {
            return x->frequency < y->frequency;
             });
            
         nodes.insert(pos, c);
        

    }
    
   
    return;
}
//Generating of huffman code

void hauffman_code(hauffman_tree*node,string & message,map<char,string>&hauffman_map){
    string code;
    
    for(auto x : message){
        code="";
        search(node,x,code);
        if(code.empty()) code='0';
        hauffman_map[x]=code;
    }
}
//Traversing the path by searching of element
bool search(hauffman_tree * root,char ch,string &code){

    if(!root) return false;
    if(!root->lc && !root->rc) return root->letter == ch;

    code=code+'0';
    if(search(root->lc,ch,code)) return true;
    code.pop_back();
    
    code=code+'1';
    if(search(root->rc,ch,code)) return true;
    code.pop_back();
    
    return false;
}
//Actual encryption

map<char,string> encrypt(string data)
{

   

    int n=data.size();
    
    
    //sorting the char based on frequency
    map<char,int>frequency=frequency_count(data);
    vector<pair<char,int>> sorted_frequency(frequency.begin(),frequency.end());
    sort(sorted_frequency.begin(),sorted_frequency.end(),constrain);

   

   //creation of nodes vector
    
    vector<hauffman_tree*>nodes(sorted_frequency.size());
   
  /*  for(auto [ch,freq] : sorted_frequency){
        cout<<ch<<" : "<<freq<<endl;
    }*/

    link(nodes,sorted_frequency); //to link all the nodes to form a tree
   // cout<<"Linked\n";
    nodes.shrink_to_fit();
    if(nodes.empty()) return{{'\0',"\0"}};
    hauffman_tree *temp=nodes[0];
    
  
    map<char,string>hauffman_map;
    hauffman_code(nodes[0],data,hauffman_map); //creating of code
   // cout<<"Code Created\n";

    //displayung code
    for(auto [ch,code] : hauffman_map){
        cout<<ch<<" : "<<code<<" : "<<code.size()<<endl;
    }

   

  
   return hauffman_map;
}
#ifndef HUFFMAN_NO_MAIN
int main(){
    
    return 0;
}
#endif