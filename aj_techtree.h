#ifndef AJ_TECHTREE_H
#define AJ_TECHTREE_H

#include "ntechtree.h"

class AJ_TechTree : public NTechTreeBase
{
public:
  AJ_TechTree();
  //bool loadTree(string fileName);
  vector<string> getAllTech();
  vector<string> getAllReachableTech();
  map<string,int> getRandomReachableTechRate();
  string randomRateSelect(map<string,int> rateMap);
  vector<string> getRandomReachableTech(int cnt);
  string getTechInfo(string techID);
  void setTech(string tech);
};

#endif // AJ_TECHTREE_H
