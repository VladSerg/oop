#include "journalrelease.hpp"
#include "messages.hpp"

JournalRelease::JournalRelease(int _id, Date _date)
	:id(_id), date(_date)
{
	if (id < 0)
		throw std::logic_error(Messages::InvalidId);
};

JournalRelease::JournalRelease (int _id, Date _date, std::initializer_list<Article *> _articles)
	:id(_id), date(_date)
{
	if (id < 0)
		throw std::logic_error(Messages::InvalidId);

	for (Article * curent : _articles)
		addArticle(std::unique_ptr<Article>(curent));
};

void JournalRelease::addArticle(std::unique_ptr <Article> _article) 
{
	articles.push_back(std::move(_article)); 
};
