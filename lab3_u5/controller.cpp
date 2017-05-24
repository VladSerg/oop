#include "controller.hpp"
#include "messages.hpp"
#include <map>
#include <string>
#include <set>
#include <algorithm>

Journal & Controller::addJournal(std::string const & _str)
{
	Journal * result = new Journal(_str);
	journals.push_back(std::unique_ptr<Journal>(result));
	return *result;
}

Scientist & Controller::addScientist(std::string const & _str, Degree _dg)
{
	Scientist * result = new Scientist(_str, _dg);
	scientists.push_back(std::unique_ptr<Scientist>(result));
	return *result;
}

JournalRelease & Controller::addJournalRelease(Journal & _journal, int _id, Date _date)
{
	JournalRelease * result = new JournalRelease(_id, _date);
	_journal.addJournalRelise(std::unique_ptr<JournalRelease>(result));
	return *result;
}

Article & Controller::addArticle(JournalRelease & _journalrel, std::string const & _str, int _pages, int _formulas)
{
	Article * result = new Article(_str, _pages, _formulas);
	_journalrel.addArticle(std::unique_ptr<Article>(result));
	return *result;
}

void Controller::addArticleLinkToScientist(Article & _article, Scientist & _scientist)
{
	_article.addScientist(_scientist);
}

void Controller::addArticleLinkToArticle(Article & _article, Article & _link)
{
	_article.addArticleLink(_link);
}


void Controller::PrintPagesCount(std::ostream & _stream)
{
	for (int i = 0; i < (int)journals.size(); i++)
		for (JournalRelease const & curent : journals[i]->iterJournalReleases())
		{
			int j = 0;
			for (Article const & curentArticle : curent.iterArticles())
				j += curentArticle.getPagesCount();
			_stream << "Journal: " << journals[i]->GetTitle() << " Release: " << curent.getNumber() << " Pages: " << j << std::endl;
		}
}

void Controller::PrintActiveScientists(std::ostream & _stream)
{
	std::map<std::string, int> result;
	ForEachArticle([&](Article const & curentArticle, JournalRelease const & extra)
					{
						for (Scientist const * curentScientist : curentArticle.iterScientists())
						{
							if (result.count(curentScientist->getName()))
								result[curentScientist->getName()]++;
							else
								result[curentScientist->getName()] = 1;
						}
					});
	
	std::vector< std::pair<std::string, int>> vec(result.begin(), result.end());

	std::sort(vec.begin(), vec.end(), 
		[](const std::pair<std::string, int > & a, const std::pair<std::string, int> & b)
		{ return a.second < b.second; });
		
	auto it = vec.rbegin();
	while (it != vec.rbegin() + 5)
	{
		_stream << it->first << ' ' << it->second << std::endl;
		++it;
	}
}

void Controller::PrintMathArticles(std::ostream & _stream)
{
	std::map<std::string, int> result;
	ForEachArticle([&](Article const & curentArticle, JournalRelease const & extra)
					{
						result[curentArticle.getTitle()] = curentArticle.getFormulasCount(); 
					});

	std::vector< std::pair<std::string, int>> vec(result.begin(), result.end());

	std::sort(vec.begin(), vec.end(),
		[](const std::pair<std::string, int > & a, const std::pair<std::string, int> & b)
	{ return a.second < b.second; });

	auto it = vec.rbegin();
	while (it != vec.rbegin() + 4)
	{
		_stream << it->first << ' ' << it->second << std::endl;
		++it;
	}
}

void Controller::PrintArticlesScientistN(std::ostream & _stream)
{
	ForEachArticle(	[&]( Article const & _curentArticle, JournalRelease const & extra)
			{
				bool flag = false;
				for (Scientist const * curentScientist : _curentArticle.iterScientists())
				{
					if (curentScientist->getDegree() != DG_NoDegree)
					{
						flag = true;
						break;
					}
				}
				if (!flag)
					_stream << _curentArticle.getTitle() << std::endl;
	});
}

void Controller::PrintLinkedScientists(std::ostream & _stream)
{
	std::set<std::string> result;
	ForEachArticle([&](Article const & curentArticle, JournalRelease const & curent)
					{			
						for (Scientist const * curentScientist : curentArticle.iterScientists())
							result.insert(curentScientist->getName());
					});
	for (std::string curent : result)
		_stream << curent << std::endl;
}

void Controller::PrintInvalidArticles(std::ostream & _stream)
{
	std::map<std::string, Date> dates;
	ForEachArticle([&](Article const & curentArticle, JournalRelease const & curent)
					{
						dates.insert(std::pair<std::string, Date>(curentArticle.getTitle(), curent.getDate()));
					});


	ForEachArticle([&](Article const & curentArticle, JournalRelease const & curent)
					{			
						for (Article const * curentArticleFromList : curentArticle.iterArticles())
						{
							if (curentArticleFromList == &curentArticle)
							{
								_stream << "Error \"Link to itself\": " << curentArticleFromList->getTitle() << std::endl;
							}
							if (dates.at(curentArticleFromList->getTitle()) > curent.getDate())
							{
								_stream << "Error \"Link to future\": " << curentArticle.getTitle() << std::endl;
							}
						}
					});
}

void Controller::ForEachArticle(std::function< void(Article const &, JournalRelease const &)> _action) const
{
	for (int i = 0; i < (int)journals.size(); i++)
		for (JournalRelease const & curent : journals[i]->iterJournalReleases())
			for (Article const & curentArticle : curent.iterArticles())
				_action(curentArticle, curent);
}