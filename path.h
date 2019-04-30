#ifndef PATH_H
#define PATH_H
#include "constructable.h"

class Address;

class Path: public Constructable {
	int pathValue;

	public:
		Path(int pathValue);

		int getPathValue();

		void doBuild() override;

		void notify(Address &whoNotified) override;
		void notify(Path &whoNotified) override;
		void notifyObservers() override;

		void printSaveFormat(std::ostream &out) override;
		
	friend std::ostream &operator<<(std::ostream &out, Path &path);
};

#endif
