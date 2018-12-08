#include <iostream>
#include <string>
#include <map>
#include <vector>

class Solver;

template <typename RegType>
class Registry {
public:
	static RegType* Find(const std::string &name) {
    auto &fmap = Get()->fmap_; 
    auto p = fmap.find(name);
    if (p != fmap.end()) {
		  return p->second;
    } else {
      // log or throw error
      return nullptr;
    }
	}

  static std::vector<std::string> ListAllName() {
    auto &fmap = Get()->fmap_; 
    std::vector<std::string> names;
    for (auto p = fmap.begin(); p !=fmap.end(); ++p) {
      names.push_back(p->first);
    }
    return names;
  }

	RegType& Register(const std::string& name, RegType* obj) {
		fmap_[name] = obj;
    return *obj;
	}

  static Registry* Get();

private:
  std::map<std::string, RegType*> fmap_;
};


class Solver {
public:
	virtual void Run() = 0;
};

class SimpleSolver : public Solver {
public:
	void Run() override  {
    std::cout << "SimpleSolver run!" << std::endl;
	}
};


class NewtonSolver : public Solver {
public:
	void Run() override {
    std::cout << "NewtonSolver run!" << std::endl;
	}
};


#define REGISTER_TYPE(name) \
template<> \
Registry<name>* Registry<name>::Get() { \
  static Registry<name> inst; \
  return &inst; \
}

#define OBJECT_REGISTER(RegType, name) \
  static RegType& tempname_##name = \
  Registry<RegType>::Get()->Register(#name, new name());

#define SOLVER_REGISTER(name) \
  OBJECT_REGISTER(Solver, name)


// register factory class
REGISTER_TYPE(Solver);

// register singleton
//OBJECT_REGISTER(Solver, SimpleSolver);
//OBJECT_REGISTER(Solver, NewtonSolver);
SOLVER_REGISTER(SimpleSolver);
SOLVER_REGISTER(NewtonSolver);

int main() {

	Solver *p = Registry<Solver>::Find("SimpleSolver");

  if (p != nullptr) {
	  p->Run();
  }

	p = Registry<Solver>::Find("NewtonSolver");

  if (p != nullptr) {
	  p->Run();
  }

  return 0;
}

