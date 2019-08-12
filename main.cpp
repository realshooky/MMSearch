#include <iostream>
#include <fstream>
#include <cctype>
#include <unordered_map>
#include <list>
#include "Monster.hpp"

struct search
{
  bool active = false;
  std::string text = "";
  int num = -1;
};

void printMenu()
{
  std::cout << "Search by:\n";
  std::cout << "(A)dd a filter\n";
  std::cout << "(C)lear filters\n";
  std::cout << "Print the (F)ilters\n";
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
  switch(choice)
  {
    case 'n':
    case 'N':
      std::cout << "Name selected. Enter the filter.\n>> ";
      std::cin >> terms[0].text;
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
          terms[2].text = "Tiny";
          terms[2].active = true;
          std::cout << terms[2].text + " selected." << '\n';
          break;
        case 's':
        case 'S':
          terms[2].text = "Small";
          terms[2].active = true;
          std::cout << terms[2].text + " selected." << '\n';
          break;
        case 'm':
        case 'M':
          terms[2].text = "Medium";
          terms[2].active = true;
          std::cout << terms[2].text + " selected." << '\n';
          break;
        case 'l':
        case 'L':
          terms[2].text = "Large";
          terms[2].active = true;
          std::cout << terms[2].text + " selected." << '\n';
          break;
        case 'h':
        case 'H':
          terms[2].text = "Huge";
          terms[2].active = true;
          std::cout << terms[2].text + " selected." << '\n';
          break;
        case 'g':
        case 'G':
          terms[2].text = "Gargantuan";
          terms[2].active = true;
          std::cout << terms[2].text + " selected." << '\n';
          break;
        default:
          std::cout << "No option chosen. No filters applied.\n";
          break;
      }
      break;
    case 't':
    case 'T':
      std::cout << "Enter the type of the monster.\n>> ";
      std::cin >> terms[1].text;
      std::cout << terms[1].text << " type filter added.\n";
      terms[1].active = true;
      std::transform(terms[1].text.begin(), terms[1].text.end(),
                     terms[1].text.begin(), ::tolower);
      break;
  }
}

void printFilters(search filters[])
{
  if (filters[0].active) std::cout << "Name filter: " << filters[0].text << std::endl;
  if (filters[1].active) std::cout << "Type filter: " << filters[1].text << std::endl;
  if (filters[2].active) std::cout << "Size filter: " << filters[2].text << std::endl;
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

void printResults(search filter[],
                  std::unordered_map<std::string, std::list<Monster>> NameMap,
                  std::unordered_map<std::string, std::list<Monster>> SizeMap,
                  std::unordered_map<std::string, std::list<Monster>> TypeMap)
{
  std::list<Monster> printList;
  if (filter[0].active)
  {
    for (auto& x : NameMap[filter[0].text])
    {
      // all 3 filters
      if (filter[1].active && filter[2].active)
      {
        if (x.getType() == filter[1].text && x.getSize() == filter[2].text)
          printList.push_back(x);
      }
      // name and size filter
      else if (!filter[1].active && filter[2].active)
      {
        if (x.getType() != filter[1].text && x.getSize() == filter[2].text)
          printList.push_back(x);
      }
      // name and type filter
      else if (filter[1].active && !filter[2].active)
      {
        if (x.getType() == filter[1].text && x.getSize() != filter[2].text)
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
    for (auto &x : TypeMap[filter[1].text])
    {
      // all filters
      if (filter[0].active && filter[2].active)
      {
        if (x.getType() == filter[0].text && x.getSize() == filter[2].text)
          printList.push_back(x);
      }
      // type and size filter
      else if (!filter[0].active && filter[2].active)
      {
        if (x.getType() != filter[0].text && x.getSize() == filter[2].text)
          printList.push_back(x);
      }
      // name and type filter
      else if (filter[0].active && !filter[2].active)
      {
        if (x.getType() == filter[1].text && x.getSize() != filter[2].text)
          printList.push_back(x);
      }
      // type filter
      else if (!filter[0].active && !filter[2].active)
      {
        printList.push_back(x);
      }
    }
  }
  else if (filter[2].active)
  {
    for (auto &x : SizeMap[filter[2].text])
    {
      if (filter[1].active && filter[0].active)
      {
        if (x.getType() == filter[1].text && x.getSize() == filter[0].text)
          printList.push_back(x);
      }
      else if (!filter[1].active && filter[0].active)
      {
        if (x.getType() != filter[1].text && x.getSize() == filter[0].text)
          printList.push_back(x);
      }
      else if (filter[1].active && !filter[0].active)
      {
        if (x.getType() == filter[1].text && x.getSize() != filter[0].text)
          printList.push_back(x);
      }
      else if (!filter[1].active && !filter[0].active)
      {
        printList.push_back(x);
      }
    }
  }
  else
  {
    for (auto& x : NameMap)
      for (auto&y : x.second)
      {
        printList.push_back(y);
      }
  }

  printList.sort();
  printList.unique();

  std::cout << printList.size() << " results.\n";
  for (auto& x : printList)
    std::cout << x.getName() << std::endl;
  
}

void monsterLookup(std::unordered_map<std::string, std::list<Monster> > NameMap)
{
  std::string name;
  Monster monster;

  std::cout << "Enter the full name of the monster:\n>> ";
  std::cin >> name;

  std::transform(name.begin(), name.end(), name.begin(), ::tolower);
  monster = NameMap[name].front();

  if (NameMap[name].size() > 1)
    std::cout << "Not full name of monster. Returning to main menu.\n";
  else if (NameMap[name].size() == 1)
  {
    std::cout << monster.getName() << std::endl;
    std::cout << monster.getSize() << ' ' << monster.getType();
    std::cout << ", " << monster.getAlignment() << std::endl;
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
  file.open("monster-manual.txt", std::fstream::in);

  Monster monster;
  std::string str;
  int x;

  int j = 0;
  while(++j < 325)
  {
    if (file.peek() == '\n')
      file.ignore();
    std::getline(file, str);
    monster.setName(str);
    
    file >> str;
    monster.setSize(str);

    file.ignore();
    std::getline(file, str, ',');
    monster.setType(str);

    file.ignore();
    std::getline(file, str);
    monster.setAlignment(str);

    // ignoring "Hit Points:"
    file.ignore(12, ':');

    file >> x;
    monster.setHP(x);

    file.ignore();
    if (file.peek() == '(')
      std::getline(file, str);
    else str.clear();
    monster.setHP_Dice(str);

    std::getline(file, str, ':');

    file >> x;
    monster.setAC(x);

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
    
    file.ignore(8);

    std::getline(file, str);
    monster.setSpeeds(str);

    // junk
    file.ignore(128, '\n');

    // junk
    std::getline(file, str, '\n');

    double CRval;
    file >> CRval;
    monster.setCR(CRval);

    file.ignore(2, '(');

    file >> str;
    for (int i = 0; i < str.size(); i++)
      if (str[i] == ',') str.erase(i, i);
    x = std::stoi(str);
    monster.setXP(x);

    file.ignore(5, ')');

    std::string sub, next = monster.getName();

    for (int i = 0; i < next.size(); i++)
      if (std::isupper(next[i])) next[i] = tolower(next[i]);

    for (int i = 0; i < strlen(monster.getName()); i++)
    {
      sub = next.substr(0, i+1);
      NameMap[sub].push_back(monster);
    }

    TypeMap[monster.getType()].push_back(monster);
    SizeMap[monster.getSize()].push_back(monster);
  };

  std::cout << "Welcome to the Monster Manual Search Engine!" << std::endl;
  printMenu();
  char menuChoice;
  bool loop = true;
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
        printResults(filters, NameMap, SizeMap, TypeMap);
        break;
      case 'l':
      case 'L':
        monsterLookup(NameMap);
        break;
      default:
        std::cout << "No valid menu option selected. Try again.\n";
    }
  }
  
  file.close();
  return 0;
}