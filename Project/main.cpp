#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include <vector>
#include <algorithm>
using namespace std;


class Word {
	private: 
		string word;
		int occurence;
	public:
		Word(string w, int o) {
			word = w;
			occurence = o;
		}
		string getWord() {
			return word;
		}
		bool operator <(Word& obj) {
			return occurence < obj.getOccurence();
		}
		void setOccurence(int o) {
			occurence = o;
		}
		int getOccurence() {
			return occurence;
		}
		void toString() {
			cout << word << " " << occurence << endl;
		}
		void setWord(string s) {
			word = s;
		}
		friend class CompareWords;
};

vector<string> getStopwords();
void printArticle(const char* path, vector<Word> &words, vector<string> stopwords);
int main() 
{
	vector<Word> words;
	
	vector<string> stopwords = getStopwords();
	printArticle("/Users/user/Desktop/ds/reut2-001.sgm", words, stopwords);
	printArticle("/Users/user/Desktop/ds/reut2-003.sgm", words, stopwords);
	printArticle("/Users/user/Desktop/ds/reut2-004.sgm", words, stopwords);
	printArticle("/Users/user/Desktop/ds/reut2-005.sgm", words, stopwords);
	printArticle("/Users/user/Desktop/ds/reut2-006.sgm", words, stopwords);
	printArticle("/Users/user/Desktop/ds/reut2-007.sgm", words, stopwords);
	printArticle("/Users/user/Desktop/ds/reut2-008.sgm", words, stopwords);
	printArticle("/Users/user/Desktop/ds/reut2-009.sgm", words, stopwords);
	printArticle("/Users/user/Desktop/ds/reut2-010.sgm", words, stopwords);
	printArticle("/Users/user/Desktop/ds/reut2-011.sgm", words, stopwords);
	printArticle("/Users/user/Desktop/ds/reut2-012.sgm", words, stopwords);
	printArticle("/Users/user/Desktop/ds/reut2-013.sgm", words, stopwords);
	printArticle("/Users/user/Desktop/ds/reut2-014.sgm", words, stopwords);
	printArticle("/Users/user/Desktop/ds/reut2-015.sgm", words, stopwords);
	printArticle("/Users/user/Desktop/ds/reut2-016.sgm", words, stopwords);
	printArticle("/Users/user/Desktop/ds/reut2-017.sgm", words, stopwords);
	printArticle("/Users/user/Desktop/ds/reut2-018.sgm", words, stopwords);
	printArticle("/Users/user/Desktop/ds/reut2-019.sgm", words, stopwords);
	printArticle("/Users/user/Desktop/ds/reut2-020.sgm", words, stopwords);
	printArticle("/Users/user/Desktop/ds/reut2-021.sgm", words, stopwords);
	sort(words.begin(), words.end());

	for (int i = 0; i < words.size(); i++) {
		cout << words[i].getWord() << " " << words[i].getOccurence() << endl;
	}

	
}
void printArticle(const char* path, vector<Word> &words, vector<string> stopwords) {
	string line;
	ifstream file(path);
	string startTag = "<BODY>";
	string endTag = "</BODY>";
	string article = " ";
	bool shouldWrite = false;

	while (getline(file, line)) {
		size_t foundStart = line.find(startTag);
		size_t foundEnd = line.find(endTag);
		string text;
		if (foundStart != string::npos) {
			article += line.substr(foundStart + 6, line.length());
			text = line.substr(foundStart + 6, line.length());
			istringstream ss(text);
			string word;
			bool didFind = false;
			while (ss >> word) {
				// didnt found on stopwords
				if (find(stopwords.begin(), stopwords.end(), word) == stopwords.end()) {
					for (int i = 0; i < words.size(); i++) {
						if (words[i].getWord() == word) {
							words[i].setOccurence(words[i].getOccurence() + 1);
							didFind = true;
						}
					}
					if (!didFind) {
						words.push_back(Word(word, 1));
						didFind = false;
					}
				}
			}
			shouldWrite = true;
		}
		else if (foundEnd != string::npos) {
			article += line.substr(0, foundEnd);
			text = line.substr(0, foundEnd);
			istringstream ss(text);
			string word;
			bool didFind = false;
			while (ss >> word) {
				if (find(stopwords.begin(), stopwords.end(), word) == stopwords.end()) {
					for (int i = 0; i < words.size(); i++) {
						words[i].setOccurence(words[i].getOccurence() + 1);
						didFind = true;
					}
					if (!didFind) {
						words.push_back(Word(word, 1));
						didFind = false;
					}
				}				
			}
			shouldWrite = false;
		}
		else if (shouldWrite) {
			article += line;
			text = line;
			istringstream ss(text);
			string word;
			bool didFind = false;
			while (ss >> word) {
				if (find(stopwords.begin(), stopwords.end(), word) == stopwords.end()) {
					for (int i = 0; i < words.size(); i++) {
						words[i].setOccurence(words[i].getOccurence() + 1);
						didFind = true;
					}
					if (!didFind) {
						words.push_back(Word(word, 1));
						didFind = false;
					}
				}
			}
		}
	}	
}
vector<string> getStopwords() {

	const char* path = "/Users/user/Desktop/ds/stopwords.txt";
	ifstream file(path);
	vector<string> stopwords;
	string myText;
	while (getline(file, myText)) {
		stopwords.push_back(myText);
	}
	return stopwords;
}
