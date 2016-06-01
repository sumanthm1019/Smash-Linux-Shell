/*
 * source.cpp
 *
 *  Created on: May 24, 2016
 *      Author: sumanth
 */

#include <cstdio>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include "smsh.h"
#include "smsh.cpp"
#include <readline/readline.h>
#include <readline/history.h>
using namespace std;



int main() {

	cout << endl;
	vector<string> table;
	string cmd;
	string check;
	rl_bind_key('\t', rl_complete);
	char *cwd = (char *) malloc(sizeof(char) * 100);
	char *uname = (char *) malloc(sizeof(char) * 100);
	char *buf = (char *) malloc(sizeof(char) * 100);
	getlogin_r(uname, 100);
	while (1) {
		command in;
		cwd = getcwd(cwd, 100);
		sprintf(buf, "%s:%s$$ ", uname, cwd);
		cmd = readline(buf);
		if (cmd.length() == 0) {
			continue;
		}else if(find(builtin.begin(), builtin.end(), cmd.substr(0, cmd.find(' '))) != builtin.end()){
			in.builtin(cmd);
			continue;


		}else if (cmd == "history" || cmd == "history ") {

			in.printArgs();

			continue;
		} else if (cmd == "exit") {
			break;
		}

		add_history(cmd.c_str());
		if (cmd.find(" ") != string::npos) {
			check = cmd.substr(0, cmd.find(" "));
		} else {
			check = cmd;
		}
		if (find(v.begin(), v.end(), check) == v.end()) {
			cout << "Unknown command: " << check << endl;
			continue;
		}

		if (cmd.find('>') != string::npos || cmd.find(">>") != string::npos
				|| cmd.find('|') != string::npos) {
			scommand in;
			in.initSpecial(cmd);
			in.execSpecial();
			continue;
		}

		table = in.insertArg(cmd);

		in.execute(table);
		in.clearArgs();

	}
	free(cwd);
	free(uname);
	free(buf);
	table.clear();
	cmd.clear();
	check.clear();
	v.clear();
	hist.clear();
	return 0;
}
