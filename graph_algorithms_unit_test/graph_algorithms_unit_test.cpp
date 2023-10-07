#include "pch.h"
#include "CppUnitTest.h"
#include "../graph_algorithms/graph_functions.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:

		TEST_METHOD(TestBFS)
		{
			vector<vector<pair<int, char>>> enter1;
			enter1 = { { {2, 'u'}, { 3, 'u' } },
				{},
				{ {0, 'u'}, {3, 'u'} },
				{ {0, 'u'}, {2, 'u'} } };
			vector<int> res1 = bfs(0, enter1);
			vector<int> real_res1 = { 0, INF, 1, 1 };
			Assert::IsTrue(real_res1 == res1, L"TEST 1 FAILED");

			vector<vector<pair<int, char>>> enter2;
			enter2 = { { {2, 's'}, { 3, 't' } },
				{},
				{ {0, 'u'}, {3, 't'} },
				{ {0, 's'}, {2, 'u'} } };
			vector<int> res2 = bfs(0, enter2);
			vector<int> real_res2 = { 0, INF, 1, 1 };
			Assert::IsTrue(real_res2 == res2, L"TEST 2 FAILED");

			vector<vector<pair<int, char>>> enter3;
			enter3 = { { {5, 's'} },
				{ {2, 's'} },
				{ {1, 'u'}, {3, 't'} },
				{ {2, 'u'}, {4, 't'} },
				{ {3, 'u'}, {5, 't'} },
				{ {4, 'u'}, {0, 't'} }, };
			vector<int> res3 = bfs(3, enter3);
			vector<int> real_res3 = { 3, 2, 1, 0, 1, 2 };
			Assert::IsTrue(real_res3 == res3, L"TEST 3 FAILED");

			vector<vector<pair<int, char>>> enter4;
			enter4 = { { {3, 's'} },
				{ {2, 's'}, {3, 't'} },
				{ {1, 'u'}, {4, 't'}, {5, 't'} },
				{ {1, 'u'}, {6, 't'}, {0, 't'} },
				{ {2, 'u'} },
				{ {2, 'u'} },
				{ {3, 'u'} } };
			vector<int> res4 = bfs(3, enter4);
			vector<int> real_res4 = { 1, 1, 2, 0, 3, 3, 1 };
			Assert::IsTrue(real_res4 == res4, L"TEST 4 FAILED");
		}
		TEST_METHOD(TestConnected)
		{
			Assert::IsTrue(1 == 1);
		}

		TEST_METHOD(Test3Colored)
		{
			Assert::IsTrue(1 == 1);
		}

		TEST_METHOD(TestFindCycle)
		{
			Assert::IsTrue(1 == 1);
		}
	};
}
