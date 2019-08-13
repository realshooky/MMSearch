#include <iostream>
#include <fstream>
#include <cctype>
#include <unordered_map>
#include <list>
#include <vector>
#include "Monster.hpp"

struct search
{
  bool active;
  std::string text;
  int num;

  search(std::string t = "", int n = -1, bool a = false)
  {
    active = a;
    text = t;
    num = n;
  }
};

void printMenu()
{
  std::cout << "Search by:\n";
  std::cout << "(A)dd a filter\n";
  std::cout << "(C)lear filters\n";
  std::cout << "Print the (F)ilters\n";
  std::cout << "Add result (S)orting options\n";
  std::cout << "Print (R)esults\n";
  std::cout << "Monster (L)ookup\n";
  std::cout << "Print the (M)enu\n";
  std::cout << "(Q)uit the program\n";
}

void addFilter(search terms[])
{
  std::cout << "Add which filter?\n";
  std::cout << "(N)ame\n";
  std::cout << "(T)ype\n";
  std::cout << "(S)ize\n";
  char choice;
  std::cout << ">> ";
  std::cin >> choice;
  std::cin.ignore();
  switch(choice)
  {
    case 'n':
    case 'N':
      std::cout << "Name selected. Enter the filter.\n>> ";
      std::getline(std::cin, terms[0].text);
      std::cout << terms[0].text << " name filter added.\n";
      terms[0].active = true;
      std::transform(terms[0].text.begin(), terms[0].text.end(),
                     terms[0].text.begin(), ::tolower);
      break;
    case 's':
    case 'S':
      char subchoice;
      std::cout << "Size selected. Choose from the list.\n";
      std::cout << "(T)iny\n(S)mall\n(M)edium\n(L)arge\n(H)uge\n(G)argantuan\n";
      std::cout << ">> ";
      std::cin >> subchoice;
      switch(subchoice)
      {
        case 't':
        case 'T':
          terms[1].text = "Tiny";
          terms[1].active = true;
          std::cout << terms[1].text + " selected." << '\n';
          break;
        case 's':
        case 'S':
          terms[1].text = "Small";
          terms[1].active = true;
          std::cout << terms[1].text + " selected." << '\n';
          break;
        case 'm':
        case 'M':
          terms[1].text = "Medium";
          terms[1].active = true;
          std::cout << terms[1].text + " selected." << '\n';
          break;
        case 'l':
        case 'L':
          terms[1].text = "Large";
          terms[1].active = true;
          std::cout << terms[1].text + " selected." << '\n';
          break;
        case 'h':
        case 'H':
          terms[1].text = "Huge";
          terms[1].active = true;
          std::cout << terms[1].text + " selected." << '\n';
          break;
        case 'g':
        case 'G':
          terms[1].text = "Gargantuan";
          terms[1].active = true;
          std::cout << terms[1].text + " selected." << '\n';
          break;
        default:
          std::cout << "No option chosen. No filters applied.\n";
          break;
      }
      break;
    case 't':
    case 'T':
      std::cout << "Enter the type of the monster.\n>> ";
      std::getline(std::cin, terms[2].text);
      std::cout << terms[2].text << " type filter added.\n";
      terms[2].active = true;
      std::transform(terms[2].text.begin(), terms[2].text.end(),
                     terms[2].text.begin(), ::tolower);
      break;
  }
}

void printFilters(search filters[])
{
  if (filters[0].active) std::cout << "Name filter: " << filters[0].text << std::endl;
  if (filters[1].active) std::cout << "Size filter: " << filters[1].text << std::endl;
  if (filters[2].active) std::cout << "Type filter: " << filters[2].text << std::endl;
  else if (!filters[0].active && !filters[1].active && !filters[2].active)
    std::cout << "No active filters.\n";
}

void clearFilters(search filters[])
{
  for (int i = 0; i < 3; i++)
  {
    filters[i].active = false;
    filters[i].num = -1;
    filters[i].text = "";
  }
}

bool compareHP(const Monster& lhs, const Monster& rhs)
{
  return lhs.getHP() < rhs.getHP();
}

bool compareCR(const Monster& lhs, const Monster& rhs)
{
  return lhs.getCR() < rhs.getCR();
}

void printResults(search filter[], char sortOp, std::unordered_map<std::string, std::list<Monster>> Maps[])
                  // NameMap,
                  // SizeMap,
                  // TypeMap)
{
    std::list<Monster> printList;
    if (filter[0].active)
    {
      // NameMap
      for (auto& x : Maps[0][filter[0].text])
      {
        // all 3 filters
        if (filter[1].active && filter[2].active)
        {
          for (auto& y : Maps[1][filter[1].text])
          {
            if (y.getNameString() == x.getNameString())
            {
              for (auto& z : Maps[2][filter[2].text])
                if (z.getNameString() == y.getNameString())
                  printList.push_back(x);
            }
          }
        }
        // name and size filter
        else if (!filter[1].active && filter[2].active)
        {
          for (auto& y : Maps[2][filter[2].text])
            if (y.getNameString() == x.getNameString())
              printList.push_back(x);
        }
        // name and type filter
        else if (filter[1].active && !filter[2].active)
        {
          for (auto &y : Maps[1][filter[1].text])
            if (y.getNameString() == x.getNameString())
              printList.push_back(x);
        }
        // name only
        else if (!filter[1].active && !filter[2].active)
        {
          printList.push_back(x);
        }
      }
    }
    else if (filter[1].active)
    {
      // SizeMap
      if (Maps[1][filter[1].text].empty()) std::cout << "empty\n"; 
      for (auto &x : Maps[1][filter[1].text])
      {
        // size and type filter
        if (!filter[0].active && filter[2].active)
        {
          for (auto &y : Maps[2][filter[2].text])
            if (y.getNameString() == x.getNameString())
              printList.push_back(x);
        }
        // size and name filter
        else if (filter[0].active && !filter[2].active)
        {
          for (auto &y : Maps[0][filter[0].text])
            if (y.getNameString() == x.getNameString())
              printList.push_back(x);
        }
        // size filter
        else if (!filter[0].active && !filter[2].active)
        {
          printList.push_back(x);
        }
      }
    }
    else if (filter[2].active)
    {
      if (!filter[1].active && !filter[0].active)
      {
        for (auto& x : Maps[2][filter[2].text])
          printList.push_back(x);
      }
    }

    if (!filter[0].active && !filter[1].active && !filter[2].active)
    {
      for (auto& x : Maps[0])
        for (auto&y : x.second)
        {
          printList.push_back(y);
        }
    }
  

  printList.sort();
  printList.unique();

  if (sortOp == 'A')
  {
    std::vector<std::list <Monster> > ACvector(25);
    for (auto& x : printList)
    {
      ACvector[x.getAC() - 5].push_back(x);
    }

    printList.clear();

    for (auto& x : ACvector)
      printList.splice(printList.end(), x);
  }
  else if (sortOp == 'H') printList.sort(compareHP);
  else if (sortOp == 'C') printList.sort(compareCR);

  std::cout << printList.size() << " results.\n";
  for (auto& x : printList)
  {
    std::cout << x.getName();
    if (sortOp == 'A') std::cout << " AC: " << x.getAC() << std::endl;
    else if (sortOp == 'H') std::cout << " HP: " << x.getHP() << std::endl;
    else if (sortOp == 'C') std::cout << " CR: " << x.getCR() << std::endl;
    else std::cout << std::endl;
  }
  
}

void monsterLookup(std::unordered_map<std::string, std::list<Monster> > NameMap)
{
  std::string name;
  Monster monster;

  std::cout << "Enter the full name of the monster:\n>> ";
  std::cin.ignore();
  std::getline(std::cin, name);

  std::transform(name.begin(), name.end(), name.begin(), ::tolower);
  if (NameMap.find(name) != NameMap.end())
  {
    monster = NameMap[name].front();

    if (NameMap[name].size() > 1)
      std::cout << "Not full name of monster. Returning to main menu.\n";
    else if (NameMap[name].size() == 1)
    {
      std::cout << monster.getName() << std::endl;
      std::cout << monster.getSize() << ' ' << monster.getType();
      std::cout << ", " << monster.getAlignment() << std::endl;
      std::cout << "Hit Points: " << monster.getHP() << ' ' 
                << monster.getHP_Dice() << std::endl;
      std::cout << "Armor Class: " << monster.getAC() << ' '
                << monster.getArmors() << std::endl;
      std::cout << "Speed: " << monster.getSpeeds() << std::endl;
      std::cout << "CR: " << monster.getCR() << " ("
                << monster.getXP() << " XP)" << std::endl;
    }
  }
  else
  {
    std::cout << "Monster does not exist in the Monster Manual.\n";
  }
  
}

char sortOption()
{
  char option;
  int num;
  std::cout << "Sort results by:\n";
  std::cout << "(C)hallenge Rating\n";
  std::cout << "(H)ealth Points\n";
  std::cout << "(A)rmor Class\n>> ";
  std::cin >> option;
  switch(option)
  {
    case 'c':
    case 'C':
      std::cout << "Sorting by CR.\n";
      return 'C';
    case 'h':
    case 'H':
      std::cout << "Sorting by HP.\n";
      return 'H';
    case 'a':
    case 'A':
      std::cout << "Sorting by AC.\n";
      return 'A';
    default:
      return '\0';
  } 
}

int main()
{
  std::unordered_map<std::string, std::list<Monster> > NameMap;
  std::unordered_map<std::string, std::list<Monster> > SizeMap;
  std::unordered_map<std::string, std::list<Monster> > TypeMap;
  
  // 0 == name
  // 1 == type
  // 2 == size
  search filters[3];

  std::fstream file;
  file.open("monster-manualv3.txt", std::fstream::in);

  Monster monster;
  std::string str;
  int x;

  int j = 0;
  while(++j < 325) // 324 entries in monster manual
  {
    if (file.peek() == '\n')
      file.ignore();
    std::getline(file, str);
    monster.setName(str);
   // std::cout << monster.getName() << std::endl;
    
    file >> str;
    monster.setSize(str);
    //std::cout << monster.getSize() << std::endl;

    file.ignore();
    std::getline(file, str, ',');
    monster.setType(str);
   // std::cout << monster.getType() << std::endl;

    file.ignore();
    std::getline(file, str);
    monster.setAlignment(str);
   // std::cout << monster.getAlignment() << std::endl;

    // ignoring "Hit Points:"
    file.ignore(12, ':');

    file >> x;
    monster.setHP(x);
    //std::cout << monster.getHP() << std::endl;

    file.ignore();
    if (file.peek() == '(')
      std::getline(file, str);
    else str.clear();
    monster.setHP_Dice(str);
   // std::cout << monster.getHP_Dice() << std::endl;

    std::getline(file, str, ':');

    file >> x;
    monster.setAC(x);
   // std::cout << monster.getAC() << std::endl;

    file.ignore();
    if (file.peek() == '(')
    {
      std::getline(file, str);
      monster.setArmors(str);
    }
    else
    {
      char empty[] = {""};
      monster.setArmors(empty);
    }
    //std::cout << monster.getArmors() << std::endl;
    
    file.ignore(7);

    std::getline(file, str);
    monster.setSpeeds(str);
    //std::cout << monster.getSpeeds() << std::endl;

    // ignoring "Challenge Rating:"
    file.ignore(128, ':');

    double CRval;
    file >> CRval;
    monster.setCR(CRval);
    //std::cout << monster.getCR() << std::endl;

    file.ignore(2, '(');

    file >> str;
    for (int i = 0; i < str.size(); i++)
      if (str[i] == ',') str.erase(i, i);
    x = std::stoi(str);
    monster.setXP(x);
    //std::cout << monster.getXP() << std::endl;

    file.ignore(5, ')');
    file.ignore();

    std::string sub, next = monster.getName();

    for (int i = 0; i < next.size(); i++)
      if (std::isupper(next[i])) next[i] = tolower(next[i]);

    for (int i = 0; i < strlen(monster.getName()); i++)
    {
      sub = next.substr(0, i+1);
      NameMap[sub].push_back(monster);
    }

    next = monster.getType();
    for (int i = 0; i < strlen(monster.getType()); i++)
    {
      sub = next.substr(0, i+1);
      TypeMap[sub].push_back(monster);
    }

    SizeMap[monster.getSize()].push_back(monster);
  };

  std::cout << "Welcome to the Monster Manual Search Engine!" << std::endl;
  printMenu();
  int sortVal = 0;
  char menuChoice = '\0', sortOp = '\0';
  bool loop = true;
  std::unordered_map<std::string, std::list<Monster>> maps[] = {NameMap, SizeMap, TypeMap};

  while (loop)
  {
    std::cout << ">> ";
    std::cin >> menuChoice;
    switch(menuChoice)
    {
      case 'a':
      case 'A':
        std::cout << "Adding a filter\n";
        addFilter(filters);
        break;
      case 'f':
      case 'F':
        std::cout << "Printing the applied filters:\n";
        printFilters(filters);
        break;
      case 'm':
      case 'M':
        printMenu();
        break;
      case 'q':
      case 'Q':
        loop = false;
        std::cout << "Quitting.\n";
        break;
      case 'c':
      case 'C':
        std::cout << "Clearing search results:\n";
        printFilters(filters);
        clearFilters(filters);
        break;
      case 'r':
      case 'R':
        printResults(filters, sortOp, maps);
        break;
      case 'l':
      case 'L':
        monsterLookup(NameMap);
        break;
      case 's':
      case 'S':
        sortOp = sortOption();
        break;
      default:
        std::cout << "No valid menu option selected. Try again.\n";
    }
  }
  
  file.close();
  return 0;
}