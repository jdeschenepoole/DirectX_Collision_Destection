#ifndef CLoadAABB_H
#define CLoadAABB_H

#include "CAABB.h"

class CLoadAABBFromFile
{
public:
	CLoadAABBFromFile(std::wstring file);
	~CLoadAABBFromFile();
	
private:
	void Load();
	bool ReadLine();

protected:
	std::wstring fileAABB;
};

#endif
