#ifndef _SCIENTIST_HPP_
#define _SCIENTIST_HPP_

#include <string>

enum Degree { DG_NoDegree, DG_Doctorate, DG_DoctorOfScience };

class Scientist
{
public:
	
	Scientist(std::string const & _name, Degree _degree = DG_NoDegree);
	
	Scientist(const Scientist&) = delete;
	void operator = (const Scientist&) = delete;
	
	std::string const & getName() const { return name; };
	Degree getDegree() const { return degree; };

private:
	const std::string name;
	const Degree degree;
};



#endif // _SCIENTIST_HPP_