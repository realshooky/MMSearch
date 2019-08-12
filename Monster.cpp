#include "Monster.hpp"

Monster::Monster()
{
  name = size = type = armors = "";
  alignment = HP_Dice = speeds = "";
  AC = CR = XP = 0;
}

// setters
void Monster::setName(char * name)
{
  this->name = name;
}

void Monster::setName(std::string& name)
{
  this->name = name;
}

void Monster::setSize(char * size)
{
  this->size = size;
}

void Monster::setSize(std::string& size)
{
  this->size = size;
}

void Monster::setType(char *type)
{
  this->type = type;
}

void Monster::setType(std::string &type)
{
  this->type = type;
}

void Monster::setAlignment(char * alignment)
{
  this->alignment = alignment;
}

void Monster::setAlignment(std::string& alignment)
{
  this->alignment = alignment;
}

void Monster::setHP_Dice(char * HP_Dice)
{
  this->HP_Dice = HP_Dice;
}

void Monster::setHP_Dice(std::string& HP_Dice)
{
  this->HP_Dice = HP_Dice;
}

void Monster::setSpeeds(char * speeds)
{
  this->speeds = speeds;
}

void Monster::setSpeeds(std::string& speeds)
{
  this->speeds = speeds;
}

void Monster::setHP(int& HP)
{
  this->HP = HP;
}

void Monster::setAC(int& AC)
{
  this->AC = AC;
}

void Monster::setCR(double& CR)
{
  this->CR = CR;
}

void Monster::setXP(int& XP)
{
  this->XP = XP;
}

void Monster::setArmors(char * armors)
{
  this->armors = armors;
}

void Monster::setArmors(std::string& armors)
{
  this->armors = armors;
}

// getters
const char * Monster::getName() const
{
  return name.c_str();
}

const char * Monster::getSize() const
{
  return size.c_str();
}

const char * Monster::getType() const
{
  return type.c_str();
}

const char * Monster::getAlignment() const
{
  return alignment.c_str();
}

const char * Monster::getHP_Dice() const
{
  return HP_Dice.c_str();
}

const char * Monster::getSpeeds() const
{
  return speeds.c_str();
}

int Monster::getHP() const
{
  return HP;
}

int Monster::getAC() const
{
  return AC;
}

double Monster::getCR() const
{
  return CR;
}

int Monster::getXP() const
{
  return XP;
}

const char * Monster::getArmors() const
{
  return armors.c_str();
}

std::string Monster::getNameString() const
{
  return name;
}

bool operator<(const Monster& lhs, const Monster& rhs)
{
  return lhs.name < rhs.name;
}

bool operator==(const Monster& lhs, const Monster& rhs)
{
  return lhs.name == rhs.name;
}