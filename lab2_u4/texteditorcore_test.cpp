#include "testslib.hpp"
#include "texteditorcore.hpp"
#include "messages.hpp"
#include <fstream>
#include <sstream>

#define initstream std::stringstream input("Emily McBride, Emerging Music Editor\nJimmy Eat World, “Carry You”\n\nI grew up on Saint Simons Island, a tiny island in southeast Georgia.\nI hit my major emo streak in high school, complete with black hair, checkered Vans, and the absolute certainty that no one understood me.\nI loved Jimmy Eat World all through those awkward years(still do, let’s be real), and in 2007, they came out with Chase This Light, conveniently the same year I got my first car—a 1986 Saab 900.\nIt was falling apart in all of the best ways, and you had to bang on the dashboard sometimes to get the ancient speakers to work(had to get them replaced in the first few months, because I blew them out).\nEvery time I listen to this album, specifically the song “Carry You, ” it takes me right back to driving around— windows down, always—blaring it in my treasure of a car with my best friend heading home from school, riding to the beach, or just aimlessly driving up and down the island.\nI swear I can smell the salt in the air every time I put this album on.\n\nEmily")

DECLARE_OOP_TEST(test_create_new_empty_object)
{
	TextEditorCore a;
	assert(a.CurentPointerPosition().x == 0 && a.CurentPointerPosition().y == 0);
}

/*****************************************************************************/

//DECLARE_OOP_TEST(test_open_empty_file)
//{
//	std::ifstream input1("");
//	TextEditorCore a(input1);
//	assert(a.CurentPointerPosition().x == 0 && a.CurentPointerPosition().y == 0);
//}

/*****************************************************************************/

DECLARE_OOP_TEST(test_open_stream)
{
	std::stringstream input2 ("asdfghjkl");
	TextEditorCore a(input2);
	assert(a.CurentPointerPosition().x == 0 && a.CurentPointerPosition().y == 9);
}

/*****************************************************************************/

DECLARE_OOP_TEST(test_open_file_with_chars)
{
	initstream;
	TextEditorCore a(input);

	assert(a.CurentPointerPosition().x == 10 && a.CurentPointerPosition().y == 5);
}

/*****************************************************************************/

DECLARE_OOP_TEST(test_move_pointer_1)
{
	initstream;
	TextEditorCore a(input);
	assert(a.CurentPointerPosition().x == 10 && a.CurentPointerPosition().y == 5);
	
	a.MovePointerRight();
	assert(a.CurentPointerPosition().x == 10 && a.CurentPointerPosition().y == 5);

	a.MovePointerDown();
	assert(a.CurentPointerPosition().x == 10 && a.CurentPointerPosition().y == 5);

	a.MovePointerLeft();
	assert(a.CurentPointerPosition().x == 10 && a.CurentPointerPosition().y == 4);

	a.MovePointerUp();
	assert(a.CurentPointerPosition().x == 9 && a.CurentPointerPosition().y == 0);
}

/*****************************************************************************/

DECLARE_OOP_TEST(test_move_pointer_2)
{
	initstream;
	TextEditorCore a(input);

	a.MovePointerTo(0, 0);

	a.MovePointerLeft();
	assert(a.CurentPointerPosition().x == 0 && a.CurentPointerPosition().y == 0);

	a.MovePointerUp();
	assert(a.CurentPointerPosition().x == 0 && a.CurentPointerPosition().y == 0);

	a.MovePointerRight();
	assert(a.CurentPointerPosition().x == 0 && a.CurentPointerPosition().y == 1);

	a.MovePointerDown();
	assert(a.CurentPointerPosition().x == 1 && a.CurentPointerPosition().y == 1);
	
	a.MovePointerLeft();
	assert(a.CurentPointerPosition().x == 1 && a.CurentPointerPosition().y == 0);

	a.MovePointerLeft();
	assert(a.CurentPointerPosition().x == 0 && a.CurentPointerPosition().y == 36);
}

/*****************************************************************************/

DECLARE_OOP_TEST(test_move_pointer_3)
{
	initstream;
	TextEditorCore a(input);

	a.MovePointerTo(7, 285);

	a.MovePointerRight();
	assert(a.CurentPointerPosition().x == 8 && a.CurentPointerPosition().y == 0);

	a.MovePointerTo(7, 285);

	a.MovePointerDown();
	assert(a.CurentPointerPosition().x == 8 && a.CurentPointerPosition().y == 71);
}

/*****************************************************************************/

DECLARE_OOP_TEST(test_move_to_invalid_pointer)
{
	initstream;
	TextEditorCore a(input);

	ASSERT_THROWS(
		a.MovePointerTo(6, 283)
		, Messages::InvalidPointerCoordinates
		)
}

/*****************************************************************************/

DECLARE_OOP_TEST(test_insert_new_line_character_1)
{
	initstream;
	TextEditorCore a(input);

	a.PushCharAfterPointer('\n');
	assert(a.CurentPointerPosition().x == 11 && a.CurentPointerPosition().y == 0);

	a.MovePointerTo(7, 284);
	a.PushCharAfterPointer('\n');
	assert(a.CurentPointerPosition().x == 8 && a.CurentPointerPosition().y == 0);
}

/*****************************************************************************/

DECLARE_OOP_TEST(test_insert_new_line_character_2)
{
	initstream;
	TextEditorCore a(input);

	a.MovePointerTo(7, 0);
	a.PushCharAfterPointer('\n');
	
	assert(a.CurentPointerPosition().x == 8 && a.CurentPointerPosition().y == 0);
}

/*****************************************************************************/

DECLARE_OOP_TEST(test_insert_new_line_character_3)
{
	initstream;
	TextEditorCore a(input);

	a.MovePointerTo(0, 8);
	a.PushCharAfterPointer('\n');
	
	assert(a.CurentPointerPosition().x == 1 && a.CurentPointerPosition().y == 0);
}

/*****************************************************************************/

DECLARE_OOP_TEST(test_insert_character_1)
{
	initstream;
	TextEditorCore a(input);

	a.MovePointerTo(0, 8);
	a.PushCharAfterPointer('1');

	assert(a.CurentPointerPosition().x == 0 && a.CurentPointerPosition().y == 9);
}

/*****************************************************************************/

DECLARE_OOP_TEST(test_delete_character_1)
{
	initstream;
	TextEditorCore a(input);

	a.MovePointerTo(1, 0);
	a.DeleteCharBeforePointer();

	assert(a.CurentPointerPosition().x == 0 && a.CurentPointerPosition().y == 36);
}

/*****************************************************************************/

DECLARE_OOP_TEST(test_delete_character_2)
{
	initstream;
	TextEditorCore a(input);

	a.MovePointerTo(0, 0);
	a.DeleteCharBeforePointer();

	assert(a.CurentPointerPosition().x == 0 && a.CurentPointerPosition().y == 0);
}

/*****************************************************************************/

DECLARE_OOP_TEST(test_delete_character_3)
{
	initstream;
	TextEditorCore a(input);

	a.DeleteCharBeforePointer();

	assert(a.CurentPointerPosition().x == 10 && a.CurentPointerPosition().y == 4);
}

/*****************************************************************************/

DECLARE_OOP_TEST(test_delete_character_4)
{
	initstream;
	TextEditorCore a(input);

	a.MovePointerTo(3, 0);
	a.DeleteCharBeforePointer();

	assert(a.CurentPointerPosition().x == 2 && a.CurentPointerPosition().y == 0);
}

/*****************************************************************************/

DECLARE_OOP_TEST(test_insert_string)
{
	initstream;
	TextEditorCore a(input);

	std::string insert("ABC\nCBA");
	a.PushStringAfterPointer(&insert);

	assert(a.CurentPointerPosition().x == 11 && a.CurentPointerPosition().y == 3);
}

/*****************************************************************************/

DECLARE_OOP_TEST(test_insert_string_2)
{
	initstream;
	TextEditorCore a(input);

	a.MovePointerTo(2, 0);
	std::string insert("ABC\nCBA");
	a.PushStringAfterPointer(&insert);

	assert(a.CurentPointerPosition().x == 3 && a.CurentPointerPosition().y == 3);
}

/*****************************************************************************/

DECLARE_OOP_TEST(test_move_pointer_4)
{
	initstream;
	TextEditorCore a(input);

	a.MovePointerHome();
	assert(a.CurentPointerPosition().x == 10 && a.CurentPointerPosition().y == 0);

	a.MovePointerCtrlHome();
	assert(a.CurentPointerPosition().x == 0 && a.CurentPointerPosition().y == 0);

	a.MovePointerEnd();
	assert(a.CurentPointerPosition().x == 0 && a.CurentPointerPosition().y == 36);

	a.MovePointerCtrlEnd();
	assert(a.CurentPointerPosition().x == 10 && a.CurentPointerPosition().y == 5);
}

/*****************************************************************************/

DECLARE_OOP_TEST(test_save_file)
{
	initstream;
	TextEditorCore a(input);

	std::stringstream output("");
	a.Save(output);
}

/*****************************************************************************/

DECLARE_OOP_TEST(test_save_file_to_stringstream)
{
	initstream;
	TextEditorCore a(input);

	std::stringstream output("");
	a.Save(output);
}

/*****************************************************************************/

DECLARE_OOP_TEST(test_save_empty_file)
{
	initstream;
	TextEditorCore a(input);

	std::stringstream output("");
	a.Save(output);
}

/*****************************************************************************/

DECLARE_OOP_TEST(test_highlighting_1)
{
	initstream;
	TextEditorCore a(input);

	a.MovePointerCtrlHome();
	a.StartMarking();
	a.MovePointerCtrlEnd();
	a.StopMarking();

	assert(a.ReturnHighlightingPoints().first.x == 0 &&
			a.ReturnHighlightingPoints().first.y == 0 &&
			a.ReturnHighlightingPoints().second.x == 10 &&
			a.ReturnHighlightingPoints().second.y == 5
			);

	a.MovePointerLeft();
	assert(a.ReturnHighlightingPoints().first.x == -1 &&
		a.ReturnHighlightingPoints().first.y == -1 &&
		a.ReturnHighlightingPoints().second.x == -1 &&
		a.ReturnHighlightingPoints().second.y == -1
		);

	a.MovePointerHome();
	a.StartMarking();
	a.MovePointerRight();
	a.MovePointerRight();
	a.StopMarking();
	assert(a.ReturnHighlightingPoints().first.x == 10 &&
		a.ReturnHighlightingPoints().first.y == 0 &&
		a.ReturnHighlightingPoints().second.x == 10 &&
		a.ReturnHighlightingPoints().second.y == 2
		);


	a.StartMarking();
	a.MovePointerRight();
	a.StopMarking();
	assert(a.ReturnHighlightingPoints().first.x == 10 &&
		a.ReturnHighlightingPoints().first.y == 0 &&
		a.ReturnHighlightingPoints().second.x == 10 &&
		a.ReturnHighlightingPoints().second.y == 3
		);
}

/*****************************************************************************/

DECLARE_OOP_TEST(test_erase_in_one_line)
{
	initstream;
	TextEditorCore a(input);

	a.MovePointerCtrlHome();
	a.StartMarking();
	a.MovePointerRight();
	a.MovePointerRight();
	a.StopMarking();
	a.DeleteMarkedPart();

	a.StartMarking();
	a.MovePointerEnd();
	a.StopMarking();
	a.DeleteMarkedPart();

	assert(a.CurentPointerPosition().x == 0 && a.CurentPointerPosition().y == 0);
	assert(a.ReturnHighlightingPoints().first.x == -1 &&
		a.ReturnHighlightingPoints().first.y == -1 &&
		a.ReturnHighlightingPoints().second.x == -1 &&
		a.ReturnHighlightingPoints().second.y == -1
		);
}

/*****************************************************************************/

DECLARE_OOP_TEST(test_erase_in_separated_lines)
{
	initstream;
	TextEditorCore a(input);

	a.MovePointerTo(5, 2);
	a.StartMarking();

	a.MovePointerTo(7, 2);
	a.StopMarking();
	a.DeleteMarkedPart();

	assert(a.CurentPointerPosition().x == 5 && a.CurentPointerPosition().y == 2);
	assert(a.ReturnHighlightingPoints().first.x == -1 &&
		a.ReturnHighlightingPoints().first.y == -1 &&
		a.ReturnHighlightingPoints().second.x == -1 &&
		a.ReturnHighlightingPoints().second.y == -1
		);
}

/*****************************************************************************/

DECLARE_OOP_TEST(test_erase_in_two_lines)
{
	initstream;
	TextEditorCore a(input);

	a.MovePointerTo(5, 2);
	a.StartMarking();

	a.MovePointerTo(6, 2);
	a.StopMarking();
	a.DeleteMarkedPart();

	assert(a.CurentPointerPosition().x == 5 && a.CurentPointerPosition().y == 2);
	assert(a.ReturnHighlightingPoints().first.x == -1 &&
		a.ReturnHighlightingPoints().first.y == -1 &&
		a.ReturnHighlightingPoints().second.x == -1 &&
		a.ReturnHighlightingPoints().second.y == -1
		);

}

/*****************************************************************************/

DECLARE_OOP_TEST(test_return_higlighted_data)
{
	initstream;
	TextEditorCore a(input);

	a.MovePointerTo(5, 2);
	a.StartMarking();

	a.MovePointerTo(7, 2);
	a.StopMarking();

	std::string temp("loved Jimmy Eat World all through those awkward years(still do, let’s be real), and in 2007, they came out with Chase This Light, conveniently the same year I got my first car—a 1986 Saab 900.\nIt was falling apart in all of the best ways, and you had to bang on the dashboard sometimes to get the ancient speakers to work(had to get them replaced in the first few months, because I blew them out).\nEv");
	std::string temp2 = a.ReturnMarkedText();
	assert(temp2 == temp);	
}

/*****************************************************************************/

DECLARE_OOP_TEST(test_find)
{
	initstream;
	TextEditorCore a(input);
	std::string find("Emily");
	
	assert(a.Find(find).x == 0 && a.Find(find).y == 0);
}

/*****************************************************************************/

DECLARE_OOP_TEST(test_find_next)
{
	initstream;
	TextEditorCore a(input);
	std::string find("Emily");
	Pointer x1 = a.Find(find);
	Pointer x2 = a.FindNext(x1, find);

	assert(x2.x == 10 && x2.y == 0);
}

/*****************************************************************************/

DECLARE_OOP_TEST(test_replace)
{
	initstream;
	TextEditorCore a(input);
	std::string find("Emily");
	std::string replace("Tomm");

	assert( a.Replace(find, replace) );
}

/*****************************************************************************/

DECLARE_OOP_TEST(test_replace_all)
{
	initstream;
	TextEditorCore a(input);
	std::string find("Emily");
	std::string replace("Tomm");

	assert(a.ReplaceAll(find, replace));
}

/*****************************************************************************/

DECLARE_OOP_TEST(test_replace_nothing)
{
	initstream;
	TextEditorCore a(input);
	std::string find("Abcdefg");
	std::string replace("Tomm");

	assert(!a.ReplaceAll(find, replace));
}

