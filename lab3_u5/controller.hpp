#ifndef _CONTROLLER_HPP_
#define _CONTROLLER_HPP_

#include "journal.hpp"
#include "scientist.hpp"

#include <vector>
#include <memory>
#include <functional>
class Controller
{
private:
	std::vector<std::unique_ptr <Journal>> journals;
	std::vector<std::unique_ptr <Scientist>> scientists;
public:
	Controller() = default;

	Journal & Controller::addJournal(std::string const & _str);
	Scientist & Controller::addScientist(std::string const & _str, Degree _dg);
	JournalRelease & Controller::addJournalRelease(Journal & _journal, int _id, Date _date);
	Article & Controller::addArticle(JournalRelease & _journalrel, std::string const & _str, int _pages, int _formulas);
	
	void Controller::addArticleLinkToScientist(Article & _article, Scientist & _scientist);
	void Controller::addArticleLinkToArticle(Article & _article, Article & _link);
	
	Controller(const Controller &) = delete;
	Controller & operator = (const Controller &) = delete;
	
	// ����������� ���������� ������� � ������ ������� �������;
	void PrintPagesCount(std::ostream & _stream);
	
	// ����������� ������ �� 5 �������� ��������� ������ ������� � ������� ��������;
	void PrintActiveScientists(std::ostream & _stream); 

	// ����������� ������ �� 5 �������� ������������������ ������, ���� �� ���������� ������;
	void PrintMathArticles(std::ostream & _stream);
	
	// ����������� ������ ������, ��� ��� �������� �� �������� ������� ������ ��������;
	void PrintArticlesScientistN(std::ostream & _stream);
	
	// ����������� ������ ���������, �� ������� ���� �� ��� ��������� ������ ��������;
	void PrintLinkedScientists(std::ostream & _stream);
	
	// ����������� ������ ������, ���������� ������� ������ � ��������� � ���������� � ���� ������������ ��������� �� ������� :
	//		������ �� ������ � ��� �� ������� ��� � ������� �������;
	//		������ ������ �� ���� ����;
	void PrintInvalidArticles(std::ostream & _stream);

	void Controller::ForEachArticle(std::function< void(Article const &, JournalRelease const &)> _action) const;
};


#endif // _CONTROLLER_HPP_
