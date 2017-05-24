#include "testslib.hpp"
#include "controller.hpp"
#include "messages.hpp"
#include <sstream>

#define SetController Scientist & s1 = test.addScientist("Scientist1", DG_NoDegree); \
Scientist & s2 = test.addScientist("Scientist2", DG_Doctorate); \
Scientist & s3 = test.addScientist("Scientist3", DG_DoctorOfScience); \
Scientist & s4 = test.addScientist("Scientist4", DG_NoDegree); \
Scientist & s5 = test.addScientist("Scientist5", DG_Doctorate); \
Scientist & s6 = test.addScientist("Scientist6", DG_DoctorOfScience); \
 \
Journal & j1 = test.addJournal("Journal #1"); \
Journal & j2 = test.addJournal("Journal #2"); \
 \
JournalRelease & jr1 = test.addJournalRelease(j1, 1, { 2016,2 }); \
JournalRelease & jr2 = test.addJournalRelease(j1, 2, { 2016,4 }); \
JournalRelease & jr3 = test.addJournalRelease(j2, 1, { 2016,2 }); \
 \
Article & a1 = test.addArticle(jr1, "Article1", 1, 4); \
Article & a2 = test.addArticle(jr1, "Article2", 2, 3); \
Article & a3 = test.addArticle(jr2, "Article3", 3, 2); \
Article & a4 = test.addArticle(jr3, "Article4", 4, 1); \
 \
a1.addArticleLink(a2); \
a1.addArticleLink(a3); \
a1.addScientist(s1); \
a1.addScientist(s2); \
a1.addScientist(s3); \
 \
a2.addArticleLink(a3); \
a2.addScientist(s1); \
a2.addScientist(s2); \
a2.addScientist(s3); \
 \
a3.addArticleLink(a1); \
a3.addArticleLink(a2); \
a3.addScientist(s4); \
a3.addScientist(s5); \
a3.addScientist(s6); \
 \
a4.addArticleLink(a1); \
a4.addArticleLink(a4); \
a4.addScientist(s2); \
a4.addScientist(s3); \
a4.addScientist(s6)

DECLARE_OOP_TEST(test_of_controller)
{
	Controller test;
	SetController;

	std::stringstream a;
	test.PrintPagesCount(a);
	assert(a.str() == "Journal: Journal #1 Release: 1 Pages: 3\nJournal: Journal #1 Release: 2 Pages: 3\nJournal: Journal #2 Release: 1 Pages: 4\n");

	std::stringstream b;
	test.PrintActiveScientists(b);
	assert(b.str() == "Scientist3 3\nScientist2 3\nScientist6 2\nScientist1 2\nScientist5 1\n");

	std::stringstream c;
	test.PrintMathArticles(c);
	assert(c.str() == "Article1 4\nArticle2 3\nArticle3 2\nArticle4 1\n");

	std::stringstream d;
	test.PrintArticlesScientistN(d);
	assert(d.str() == "");

	std::stringstream e;
	test.PrintLinkedScientists(e);
	assert(e.str() == "Scientist1\nScientist2\nScientist3\nScientist4\nScientist5\nScientist6\n");

	std::stringstream f;
	test.PrintInvalidArticles(f);
	assert(f.str() == "Error \"Link to future\": Article1\nError \"Link to future\": Article1\nError \"Link to future\": Article2\nError \"Link to future\": Article4\nError \"Link to itself\": Article4\nError \"Link to future\": Article4\n");
}

DECLARE_OOP_TEST(test_of_controller_2)
{
	Controller test;
	Scientist & s = test.addScientist("Scientist", DG_NoDegree);
	Journal & j = test.addJournal("Journal #1");
	JournalRelease & jr = test.addJournalRelease(j, 1, { 2016,2 });
	Article & a = test.addArticle(jr, "Article1", 1, 4); \
		a.addScientist(s);

	std::stringstream d;
	test.PrintArticlesScientistN(d);
	assert(d.str() == "Article1\n");
}

DECLARE_OOP_TEST(test_of_throws_1)
{
	Controller test;
	ASSERT_THROWS(
		test.addJournal(""),
		Messages::InvalidTitle
		);
}

DECLARE_OOP_TEST(test_of_throws_2)
{
	Controller test;
	ASSERT_THROWS(
		test.addScientist("", DG_NoDegree),
		Messages::InvalidScientistName
		);
}

DECLARE_OOP_TEST(test_of_throws_3)
{
	Controller test;
	Journal & j1 = test.addJournal("Title");
	ASSERT_THROWS(
		test.addJournalRelease(j1, 0, {2016,13}),
		Messages::InvalidDateTime
		);
}

DECLARE_OOP_TEST(test_of_throws_4)
{
	Controller test;
	Journal & j1 = test.addJournal("Title");
	ASSERT_THROWS(
		test.addJournalRelease(j1, -11, { 2016,1 }),
		Messages::InvalidId
		);
}

DECLARE_OOP_TEST(test_of_throws_5)
{
	Controller test;
	Journal & j = test.addJournal("Title");
	JournalRelease & jr = test.addJournalRelease(j, 0, { 2016,1 });
	ASSERT_THROWS(
		test.addArticle(jr,"",0,0),
		Messages::InvalidTitle
		);
}

DECLARE_OOP_TEST(test_of_throws_6)
{
	Controller test;
	Journal & j = test.addJournal("Title");
	JournalRelease & jr = test.addJournalRelease(j, 0, { 2016,1 });
	ASSERT_THROWS(
		test.addArticle(jr, "Title", -1, 0),
		Messages::InvalidPagesCount
		);
}

DECLARE_OOP_TEST(test_of_throws_7)
{
	Controller test;
	Journal & j = test.addJournal("Title");
	JournalRelease & jr = test.addJournalRelease(j, 0, { 2016,1 });
	ASSERT_THROWS(
		test.addArticle(jr, "Title", 0, -1),
		Messages::InvalidFormulasCount
		);
}
