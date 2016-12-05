#include "aj_techtree.h"
#include "numeric"

AJ_TechTree::AJ_TechTree()
{

}

vector<string> AJ_TechTree::getAllTech()
{
  cout<<__FUNCTION__<<endl;
  vector<string> res;
  XMLElement* root = doc.RootElement();
  XMLNode* ele = root->FirstChild();
  while(ele){
      res.push_back(string(ele->ToElement()->Name()));
      cout<<res.back()<<":";
      const XMLAttribute* att = ele->ToElement()->FirstAttribute();
      while(att){
          cout<<att->Name()<<":"<<att->Value()<<" ";
          att = att->Next();
        }
      cout<<endl;
      ele = ele->NextSibling();
    }
  return res;
}

vector<string> AJ_TechTree::getAllReachableTech()
{
  cout<<__FUNCTION__<<endl;
  vector<string> res;
  XMLElement* root = doc.RootElement();
  XMLNode* ele = root->FirstChild();
  while(ele){
      int lv = ele->ToElement()->IntAttribute("Lv");
      int maxLv = ele->ToElement()->IntAttribute("MaxLv");
      //cout<<lv<<"*"<<maxLv<<"*"<<string(ele->ToElement()->Attribute("Lv"))<<endl;
      if(lv<maxLv){
          res.push_back(string(ele->ToElement()->Name()));
          cout<<res.back()<<":";
          cout<<endl;
        }
      ele = ele->NextSibling();
    }
  return res;
}

map<string, int> AJ_TechTree::getRandomReachableTechRate()
{
  cout<<__FUNCTION__<<endl;
  map<string, int> res;
  XMLElement* root = doc.RootElement();
  XMLNode* ele = root->FirstChild();
  while(ele){
      int lv = ele->ToElement()->IntAttribute("Lv");
      int maxLv = ele->ToElement()->IntAttribute("MaxLv");
      //cout<<lv<<"*"<<maxLv<<"*"<<string(ele->ToElement()->Attribute("Lv"))<<endl;
      if(lv<maxLv){
          res[(string(ele->ToElement()->Name()))] = ele->ToElement()->IntAttribute("Rate");
        }
      ele = ele->NextSibling();
    }
  return res;
}

string AJ_TechTree::randomRateSelect(map<string, int> rateMap)
{
  int sum = accumulate(rateMap.begin(),rateMap.end(),0, [] (int value, const std::map<string, int>::value_type& p)
  { return value + p.second; });
  int rv = rand()%sum;
  int csum = 0;
  for(auto itr = rateMap.begin();itr!=rateMap.end();itr++){
      csum+=itr->second;
      if(csum>=rv){
          return itr->first;
        }
    }
  return string("");
}

vector<string> AJ_TechTree::getRandomReachableTech(int cnt)
{
  cout<<__FUNCTION__<<endl;
  vector<string> res;
  map<string, int> rateMap = getRandomReachableTechRate();
  for(int i = 0;i<cnt;i++){
      string getString = randomRateSelect(rateMap);
      res.push_back(getString);
      rateMap.erase(rateMap.find(getString));
      cout<<getString<<endl;
    }
  return res;
}

string AJ_TechTree::getTechInfo(string techID)
{
  XMLElement* root = doc.RootElement();
  XMLNode* ele = root->FirstChildElement(techID.c_str());
  if(ele){
      string text(ele->FirstChild()->FirstChild()->ToText()->Value());
      return text;
    }
  return string("none info!!!");
}

void AJ_TechTree::setTech(string tech)
{
  XMLElement* root = doc.RootElement();
  XMLNode* ele = root->FirstChild();
  while(ele){
      if(string(ele->ToElement()->Name()) == tech){
          int lv = ele->ToElement()->IntAttribute("Lv");
          int mlv = ele->ToElement()->IntAttribute("MaxLv");
          if(lv<mlv){
              lv++;
            }
          stringstream ss;
          ss<<lv;
          ele->ToElement()->SetAttribute("Lv",ss.str().c_str());
        }
      ele = ele->NextSibling();
    }
}
