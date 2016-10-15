#include <iostream>
#include <string>
#include <queue>
#include <list>
#include <fstream>
#include <sstream>

using std::cout; 
using std::cin; 
using std::endl; 
using std::string; 
using std::queue; 
using std::priority_queue; 
using std::list; 
using std::exception; 

struct Data
{
	string strWord; 
	int iCount; 
};

bool operator<(const Data& D1, const Data&D2)
{
	return D1.iCount < D2.iCount;
}

template <typename T>
class MyQueue: public queue<T>
{
public:
	void Clear()
	{
		while (!this->empty())
		{
			cout << "Top element: " << this->front() << endl;
			this->pop();
		}
	}
}; 

int main()
{
	try
	{
		cout << "Exercise: inheritance of STL: queue<>" << endl << endl;
		MyQueue<string> mQ;
		mQ.push("Hello");
		mQ.push("World");
		mQ.push("Everybody");
		mQ.Clear();
		if (mQ.empty())
			cout << "MyQueue is empty!" << endl << endl;


		cout << "Exercise: Transformation from STL:list<> to STL: queue<>" << endl << endl;
		cout << "Enter the path to your file (example: F:): ";
		string strPath;
		std::getline(cin, strPath);

		std::ifstream ifs(strPath);
		if (!ifs.is_open())
		{
			throw "Error opening file for reading!";
		}

		list<string>list_of_words;
		priority_queue<Data>pqWordsCount;

		//—читывание с файла 

		while (!ifs.eof())
		{
			string strTemp;
			ifs >> strTemp;
			list_of_words.push_back(strTemp);
		}

		//—ортировка списка по словам
		list_of_words.sort();

		for (auto cit = list_of_words.cbegin(); cit != list_of_words.cend(); ++cit)
			cout << *cit << " "; 
		cout << endl; 

		int count = 1;

		auto last_iter= list_of_words.cend();
		--last_iter; 

		for (auto rcit = list_of_words.cbegin(); rcit != last_iter; ++rcit)
		{
			auto rcit_next = ++rcit;
			--rcit;

			if (*rcit_next == *rcit)
			{
				count++;
				if (*rcit_next == list_of_words.back())
				{
					pqWordsCount.push(Data{ *rcit_next, count });
				}
			}
			if (*rcit_next != *rcit)
			{
				pqWordsCount.push(Data{ *rcit, count });
				count = 1;
				if (*rcit_next == list_of_words.back())
				{
					pqWordsCount.push(Data{ *rcit_next, count });
				}
			}
		}
		cout << pqWordsCount.size() << endl; 

		while (!pqWordsCount.empty())
		{
			cout << pqWordsCount.top().iCount << " " << pqWordsCount.top().strWord << endl;
			pqWordsCount.pop();
		}

		cout << "Done!" << endl;
	}
	catch (const char *msg)
	{
		cout << msg << endl;
	}
	catch (const exception &ex)
	{
		cout << ex.what() << endl;
	}
	catch (...)
	{
		cout << "Unhandled exception" << endl;
	}
	return 0;
}