#ifndef _JOURNALRELEASE_HPP_
#define _JOURNALRELEASE_HPP_

#include <vector>
#include <memory>
#include "unique_dereferencing_iterator.hpp"
#include "datetime.hpp"
//class Date;
#include "article.hpp"
//class Article;


class JournalRelease
{
private:
	const int id;
	const Date date;
	std::vector <std::unique_ptr <Article> > articles;
	
public:

	JournalRelease(int _id, Date _date);
	JournalRelease(int _id, Date _date, std::initializer_list<Article*> _articles);

	JournalRelease(const JournalRelease &) = delete;
	JournalRelease & operator = (const JournalRelease &) = delete;


	void addArticle(std::unique_ptr <Article> _article);

	int getArticlesCount() const { return articles.size(); };
	Article const & getArticle(int index) const { return *articles.at(index); };

	int getNumber() const { return id; };
	Date getDate() const { return date; };


	template< typename T >
	using Vector = std::vector< T >;

	typedef UniqueDereferencingIterator< Article, Vector > ArticleIterator;

	ArticleIterator articlesBegin() const { return articles.begin(); };
	ArticleIterator articlesEnd() const { return articles.end(); };
	class IterableArticles
	{
	public:

		IterableArticles(ArticleIterator _articlesBegin, ArticleIterator _articlesEnd)
			: m_begin(_articlesBegin), m_end(_articlesEnd)
		{}

		ArticleIterator begin() const { return m_begin; }
		ArticleIterator end() const { return m_end; }

	private:

		ArticleIterator m_begin, m_end;
	};
	IterableArticles iterArticles() const { return IterableArticles(articlesBegin(), articlesEnd()); };
};

#endif // _JOURNALRELEASE_HPP_