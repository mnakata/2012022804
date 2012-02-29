#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <sstream>


class ServiceNames {
public:
  std::vector<std::string> makeList(std::vector<std::string> services);
};

std::vector<std::string> ServiceNames::makeList(std::vector<std::string> services)
{
  std::vector<std::string> list;

  std::map<std::string, std::vector<std::string> > map;

  for (std::vector<std::string>::iterator it = services.begin(); it != services.end(); ++ it) {
    std::stringstream ss(*it);

    std::string service;

    ss >> service;

    while (! ss.eof()) {
      std::string kind;

      ss >> kind;

      if (kind.size()) {
	if (map.find(kind) == map.end()) {
	  std::vector<std::string> values;
	  
	  values.push_back(service);

	  map.insert(std::make_pair(kind, values));
	}
	else {
	  map.find(kind)->second.push_back(service);
	}
      }
    }
  }

  std::vector<std::string> keys;

  for (std::map<std::string, std::vector<std::string> >::iterator it = map.begin();
       it != map.end();
       ++ it) {

    keys.push_back(it->first);
  }

  std::sort(keys.begin(), keys.end());

  for (std::vector<std::string>::iterator it = keys.begin(); it != keys.end(); ++ it) {
    std::vector<std::string>& values = map[*it];

    std::sort(values.begin(), values.end());

    std::stringstream ss;

    ss << *it << " ==> ";

    for (int i = 0; i < values.size(); i ++) {
      ss << values[i];

      if (i < values.size() - 1)
	ss << ", ";
    }

    list.push_back(ss.str());
  }

  return list;
}


int main(int argc, char** argv)
{
  std::vector<std::string> services;

  while (! std::cin.eof()) {
    std::string service;

    std::getline(std::cin, service);

    if (service.size())
      services.push_back(service);
  }

  std::vector<std::string> list = ServiceNames().makeList(services);

  for (std::vector<std::string>::iterator it = list.begin(); it != list.end(); ++ it)
    std::cout << *it << std::endl;
}
