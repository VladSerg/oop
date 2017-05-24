#include "article.hpp"
#include "messages.hpp"

Article::Article(std::string const & _title, int _pages, int _formulas)
	: title(_title), pages(_pages), formulas(_formulas)
{
	if (title.empty())
		throw std::logic_error(Messages::InvalidTitle);
	if (pages < 0)
		throw std::logic_error(Messages::InvalidPagesCount);
	if (formulas < 0)
		throw std::logic_error(Messages::InvalidFormulasCount);
};

Article::Article(std::string const & _title,
	int _pages,
	int _formulas,
	std::initializer_list<Scientist const *> _scientists,
	std::initializer_list<Article const *> _articles
	)
	: title(_title), pages(_pages), formulas(_formulas), scientists(_scientists), articles(_articles)
{
	if (title.empty())
		throw std::logic_error(Messages::InvalidTitle);
	if (pages < 0)
		throw std::logic_error(Messages::InvalidPagesCount);
	if (formulas < 0)
		throw std::logic_error(Messages::InvalidFormulasCount);
};

void Article::addScientist(Scientist const & _scientist) 
{
	scientists.push_back(&_scientist); 
};

void Article::addArticleLink(Article const & _link) 
{
	articles.push_back(&_link); 
};
