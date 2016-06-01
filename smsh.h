/*
 * smsh.h
 *
 *  Created on: May 24, 2016
 *      Author: sumanth
 */

#include <vector>
#include <string>

#ifndef SMSH_H_
#define SMSH_H_

//class definition
using namespace std;
/*char * dupstr (char* s);
static char** my_completion( const char * text , int start,  int end);
char* my_generator(const char* text, int state);
void * xmalloc (int size);*/
class command {

private:
	vector<string> table;

public:
	vector<string> insertArg(string);
	void printArgs();
	void execute(vector<string>);
	void clearArgs();
	void builtin(string);

};


class scommand : public command{

private:
	int isPipe;
	int fileStatus;
	string outFile;
	int inFileDesc;
	vector<vector<string>> sTable;
public:
	void initSpecial(string);
	void execSpecial();
	void setfd(int);
	int getfd();

};



#endif /* SMSH_H_ */
