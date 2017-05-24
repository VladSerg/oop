#ifndef _JOURNAL_HPP_
#define _JOURNAL_HPP_

#include <string>
#include <vector>
#include <memory>
#include "unique_dereferencing_iterator.hpp"
#include "journalrelease.hpp"
//class JournalRelease;


class Journal
{
private:
	const std::string title; 
	std::vector <std::unique_ptr <JournalRelease> > journalreleases;
	//JournalRelease & getJournalRelise(int index) { return *journalreleases.at(index); };

public:
	typedef 
		std::vector <std::unique_ptr <JournalRelease> >::const_iterator 
		ItJR;

	Journal(std::string const & _title);
	Journal(std::string const & _title, std::initializer_list<JournalRelease*> _journalrelizes);

	Journal(const Journal &) = delete;
	Journal & operator = (const Journal &) = delete;


	void addJournalRelise(std::unique_ptr <JournalRelease> _jrelise);

	int getJournalRelisesCount() const { return journalreleases.size(); };
	JournalRelease const & getJournalRelise(int index) const { return *journalreleases.at(index); };

	std::string const & GetTitle() const { return title; };

	template< typename T >
	using Vector = std::vector< T >;

	typedef UniqueDereferencingIterator< JournalRelease, Vector > JournalReleaseIterator;

	JournalReleaseIterator journalReleaseBegin() const { return journalreleases.begin(); };
	JournalReleaseIterator journalReleaseEnd() const { return journalreleases.end(); };
	class IterableJournalReleases
	{
	public:

		IterableJournalReleases(JournalReleaseIterator _Begin, JournalReleaseIterator _End)
			: m_begin(_Begin), m_end(_End)
		{}

		JournalReleaseIterator begin() const { return m_begin; }
		JournalReleaseIterator end() const { return m_end; }

	private:

		JournalReleaseIterator m_begin, m_end;
	};

	IterableJournalReleases iterJournalReleases() const { return IterableJournalReleases(journalReleaseBegin(), journalReleaseEnd()); };

};

#endif // _JOURNAL_HPP_