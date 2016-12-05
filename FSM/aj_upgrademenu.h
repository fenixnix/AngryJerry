#ifndef AJ_UPGRADEMENU_H
#define AJ_UPGRADEMENU_H

#include "FSM/stateuibase.h"

class AJ_UpgradeMenu : public StateUIBase
{
public:
  AJ_UpgradeMenu();
  void setButtonList(vector<string> bl);
  bool onEnter();
  bool onExit();
  void update();
  std::string getStateID();

  static void buttonButton(const CEGUI::EventArgs&);
  static void buttonInfo(const CEGUI::EventArgs&);
  static void buttonCancel(const CEGUI::EventArgs&);
private:
  vector<string> buttonList;
};

#endif // AJ_UPGRADEMENU_H
