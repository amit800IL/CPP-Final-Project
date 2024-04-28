#ifndef IPRINTABLE_H
#define IPRINTABLE_H
#include <iostream>
using namespace std;

#pragma once
class IPrintable
{
public:
	virtual void Print(ostream& os) const = 0;
	virtual ~IPrintable() = default;
};

#endif