#ifndef IUPDATEABLE_H
#define IUPDATEABLE_H

class IUpdateable
{
public:
	virtual ~IUpdateable(){}
	virtual void Update(const float timePassed) = 0;
};

#endif