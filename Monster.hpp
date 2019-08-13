#include <string>

class Monster
{
  public:
  Monster();

  // setters
  void setName(char *);
  void setName(std::string&);
  void setSize(char *);
  void setSize(std::string&);
  void setType(char *);
  void setType(std::string&);
  void setAlignment(char *);
  void setAlignment(std::string&);
  void setHP_Dice(char *);
  void setHP_Dice(std::string&);
  void setSpeeds(char *);
  void setSpeeds(std::string&);
  
  void setHP(int&);
  void setAC(int&);
  void setCR(double&);
  void setXP(int&);

  void setArmors(char *);
  void setArmors(std::string&);

  //getters
  const char * getName() const;
  const char * getSize() const;
  const char * getType() const;
  const char * getAlignment() const;
  const char * getHP_Dice() const;
  const char * getSpeeds() const;

  std::string getNameString() const;
  
  int getHP() const;
  int getAC() const;
  double getCR() const;
  int getXP() const;

  const char * getArmors() const;

  friend bool operator<(const Monster&, const Monster&);
  friend bool operator==(const Monster&, const Monster&);

  private:
    std::string name, size, type, armors;
    std::string alignment, HP_Dice, speeds;
    // Armor Class, Challenge Rating, Experience Points
    int HP, AC, XP;
    double CR;
    // Natural Armor?
};