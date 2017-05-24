#ifndef _ARTICLE_HPP_
#define _ARTICLE_HPP_

#include <string>
#include <vector>
#include <iterator>
class Scientist;


class Article
{

private:
	const std::string title;
	const int pages;
	const int formulas;
	std::vector <Scientist const *> scientists;
	std::vector <Article const *> articles;

public:
	
	typedef 
		std::vector<Scientist const*>::const_iterator 
		constItVS;

	typedef 
		std::vector<Article const*>::const_iterator 
		constItVA;


	Article(std::string const & _title, int _pages = 0, int _formulas = 0);

	Article(std::string const & _title, 
		int _pages, 
		int _formulas, 
		std::initializer_list<Scientist const *> _scientists, 
		std::initializer_list<Article const *> _articles
		);
	
	Article(const Article &) = delete;
	Article & operator = (const Article &) = delete;

	void addScientist(Scientist const & _scientist);
	void addArticleLink(Article const & _link);

	int getScientistCount() const { return scientists.size(); };
	Scientist const & getScientist(int index) const { return * scientists.at(index); };

	int getArticlesCount() const { return articles.size(); };
	Article const & getArticle(int index) const { return *articles.at(index); };

	std::string const & getTitle() const { return title; };
	int getPagesCount() const { return pages; };
	int getFormulasCount() const { return formulas; };
	int getLinksCount() const { return articles.size(); };
	constItVS scientistsBegin() const { return scientists.begin(); };
	constItVS scientistsEnd() const { return scientists.end(); };
	constItVA articlesBegin() const { return articles.begin(); };
	constItVA articlesEnd() const { return articles.end(); };
	
	class IterableArticles
	{
	public:
		IterableArticles(constItVA _articlesBegin, constItVA _articlesEnd)
			: m_begin(_articlesBegin), m_end(_articlesEnd)
		{}
		constItVA begin() const { return m_begin; }
		constItVA end() const { return m_end; }

	private:
		constItVA m_begin, m_end;
	};
	IterableArticles iterArticles() const { return IterableArticles(articlesBegin(), articlesEnd()); };


	class IterableScientists
	{
	public:
		IterableScientists(constItVS _Begin, constItVS _End)
			: m_begin(_Begin), m_end(_End)
		{}
		constItVS begin() const { return m_begin; }
		constItVS end() const { return m_end; }

	private:
		constItVS m_begin, m_end;
	};
	IterableScientists iterScientists() const { return IterableScientists(scientistsBegin(), scientistsEnd()); };

};


#endif // _ARTICLE_HPP_