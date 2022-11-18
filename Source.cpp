#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <string>
#include <list>
#include <iomanip>
#include <sstream>
using namespace std;

struct RScontain {
	RScontain() {
		canDo = false;
		empty = true;
		operatorr = ' ';
	}
	string a, b;
	char operatorr;
	bool canDo;
	bool empty;
	int howOld;
	string toRob;
};

struct ROBcontain {
	ROBcontain() {
		hasValue = false;
		commited = false;
		error = false;
	}
	bool commited;
	string rd;
	bool error;
	double value;
	bool hasValue ;
};

struct execution {
	execution() {
		empty = true;
	}
	char operatorr;
	int a, b;
	int startCycle;
	bool empty;
	string s;
	string rd;
};

int whichRScanDo(vector<RScontain>RS, bool mulType, int cycle) {
	int tem = 99999, NeedReturn = 0;
	if (mulType) {
		for (int i = 4; i < 6; i++)
			if (!RS[i].empty && RS[i].canDo && RS[i].howOld < cycle)
				if (tem > RS[i].howOld) {
					tem = RS[i].howOld;
					NeedReturn = i;
				}
		return NeedReturn;
	}
	else {
		for (int i = 1; i < 4; i++)
			if (!RS[i].empty && RS[i].canDo && RS[i].howOld < cycle)
				if (tem > RS[i].howOld) {
					tem = RS[i].howOld;
					NeedReturn = i;
				}
		return NeedReturn;
	}
	return 0;
}

int RsEmpty(vector<RScontain>RS, bool mulType) {
	if (mulType)
		for (int i = 4; i < 6; i++) {
			if (RS[i].empty)
				return i;
		}
	else
		for (int i = 1; i < 4; i++)
			if (RS[i].empty)
				return i;
	return 0;
}

void output(map<string, double>RF, map<string, string>RAT, map<string, ROBcontain>ROB, vector<RScontain>RS, execution add, execution mul, int cycle) {
	system("cls");
	cout << fixed << setprecision(1);
	cout << "Cycle " << cycle << endl << endl;
	cout << "   --RF---            --RAT--\n";
	cout << fixed << setprecision(1) << "F1 |" << setw(5) << RF["F1"] << "|         " << "F1 |" << setw(5) << RAT["F1"] << "|\n";
	cout << fixed << setprecision(1) << "F2 |" << setw(5) << RF["F2"] << "|         " << "F2 |" << setw(5) << RAT["F2"] << "|\n";
	cout << fixed << setprecision(1) << "F3 |" << setw(5) << RF["F3"] << "|         " << "F3 |" << setw(5) << RAT["F3"] << "|\n";
	cout << fixed << setprecision(1) << "F4 |" << setw(5) << RF["F4"] << "|         " << "F4 |" << setw(5) << RAT["F4"] << "|\n";
	cout << fixed << setprecision(1) << "F5 |" << setw(5) << RF["F5"] << "|         " << "F5 |" << setw(5) << RAT["F5"] << "|\n";
	cout << "   -------            -------\n\n";
	cout << fixed << setprecision(1);
	cout << "    -----RS-------------------         -----RS-------------------\n";
	cout << fixed << setprecision(1) << "RS1 |" << setw(4) << RS[1].operatorr << "|" << setw(9) << RS[1].a << "|" << setw(9) << RS[1].b << "|     " << "RS4 |" << setw(4) << RS[4].operatorr << "|" << setw(9) << RS[4].a << "|" << setw(9) << RS[4].b << "|\n";
	cout << fixed << setprecision(1) << "RS2 |" << setw(4) << RS[2].operatorr << "|" << setw(9) << RS[2].a << "|" << setw(9) << RS[2].b << "|     " << "RS5 |" << setw(4) << RS[5].operatorr << "|" << setw(9) << RS[5].a << "|" << setw(9) << RS[5].b << "|\n";
	cout << fixed << setprecision(1) << "RS3 |" << setw(4) << RS[3].operatorr << "|" << setw(9) << RS[3].a << "|" << setw(9) << RS[3].b << "|         --------------------------\n";
	cout << fixed << setprecision(1) << "    --------------------------     BUFFER: " << mul.s << endl;
	cout << fixed << setprecision(1) << "BUFFER: " << add.s << endl << endl;
	cout << fixed << setprecision(1);
	cout << "     ---ROB-------------------\n";
	for (map<string, ROBcontain>::iterator it = ROB.begin(); it != ROB.end(); ++it) {
		cout << it->first << "|" << setw(3) << it->second.rd << "|" << setw(9);
		if (it->second.hasValue)
			cout << fixed << setprecision(1) << it->second.value;
		else
			cout << " ";
		cout << "|";
		if (it->second.commited && !it->second.error)
			cout << "         O|\n";
		else if (it->second.commited && it->second.error)
			cout << "unexecuted|\n";
		else
			cout << "         X|\n";
	}
	cout << "    --------------------------\n\n";

	system("pause");
}

int main()
{
	map<string, double>RF;
	map<string, string>RAT;
	vector<string>IQ;
	map<string, ROBcontain>ROB;
	vector<RScontain>RS(6, RScontain());
	execution add;
	execution mul;

	RS[0].empty = 0;
	stringstream ss;
	string s;
	for (int i = 1, j = 0; i < 6; i++, j += 2) { //初始RF RAT的內容
		ss.clear();
		ss << i;
		ss >> s;
		s.insert(s.begin(), 'F');
		RF[s] = j;
		RAT[s] = "";
	}

	while (getline(cin, s)) { //讀所有code
		if (s == "-1")
			break;
		IQ.push_back(s);
	}
	for (int i = 0; i < IQ.size(); i++) {
		string ROB1 = "ROB" + to_string(i);
		ROBcontain nRob;
		ROB[ROB1] = nRob;
	}
	output(RF, RAT, ROB, RS, add, mul, 0);

	bool errorDectect = false;
	int cycle = 1;
	for (int i = 0, y = 0; y < ROB.size(); ) { //i=issue pointer j=commited pointer
		bool anychange = false;
		//commit
		string s = "ROB" + to_string(y);
		if (ROB[s].error) {
			ROB[s].commited = true;
			y++;
			anychange = true;
		}
		else  if (ROB[s].hasValue) {
			RF[ROB[s].rd] = ROB[s].value;
			ROB[s].commited = true;
			y++;
			anychange = true;
		}

		if (errorDectect) {
			output(RF, RAT, ROB, RS, add, mul, cycle);
			continue;
		}
			
		//issue
		if (i < IQ.size() && (RsEmpty(RS, false) || RsEmpty(RS, true))) {
			string code = IQ[i];
			for (int k = 0; k < code.size(); k++)
				if (code[k] == ',')
					code[k] = ' ';
			ss.clear();
			ss << code;
			string operat, Rd, Rs1, Rs2;
			ss >> operat >> Rd >> Rs1 >> Rs2;

			int count;
			if ((operat == "ADDI" || operat == "ADD" || operat == "SUB"))  //issue
				count = RsEmpty(RS, false);
			if ((operat == "MUL" || operat == "DIV"))
				count = RsEmpty(RS, true);

			if (count != 0) {
				bool canDo = true;
				if (RAT[Rs1] != Rs1 && RAT[Rs1] != "") {
					Rs1 = RAT[Rs1];
					if (!ROB[Rs1].hasValue)
						canDo = false;
					else
						Rs1 = to_string(ROB[Rs1].value);
				}
				if (RAT[Rs2] != Rs2 && RAT[Rs2] != "") {
					Rs2 = RAT[Rs2];
					if (!ROB[Rs2].hasValue)
						canDo = false;
					else
						Rs2 = to_string(ROB[Rs2].value);
				}
				if (RF.count(Rs1)) {
					ss.clear();
					ss << RF[Rs1];
					ss >> Rs1;
				}
				if (RF.count(Rs2)) {
					ss.clear();
					ss << RF[Rs2];
					ss >> Rs2;
				}
				RS[count].a = Rs1;
				RS[count].b = Rs2;
				RS[count].empty = false;
				RS[count].canDo = canDo;
				RS[count].howOld = cycle;

				ss.clear();
				ss << i;
				string tmp, R = "ROB";
				ss >> tmp;
				R += tmp;
				RAT[Rd] = R;
				RS[count].toRob = R;
				ROB[R].rd = Rd;
				if (operat == "ADDI" || operat == "ADD")
					RS[count].operatorr = '+';
				else if (operat == "MUL")
					RS[count].operatorr = '*';
				else if (operat == "DIV")
					RS[count].operatorr = '/';
				else
					RS[count].operatorr = '-';

				i++;
				anychange = true;
			}
		}

		//dispatch
		int count = whichRScanDo(RS, false, cycle); //做加法的
		if (count && add.empty) {
			double ans;
			add.a = stod(RS[count].a);
			add.b = stod(RS[count].b);
			add.empty = false;
			add.s = "(RS" + to_string(count) + ")" + RS[count].a + RS[count].operatorr + RS[count].b;
			add.startCycle = cycle;
			add.rd = RS[count].toRob;
			RS[count].empty = true;

			if (RS[count].operatorr == '+')
				add.operatorr = '+';
			else
				add.operatorr = '-';

			//clear RS
			RS[count].operatorr = ' ';
			RS[count].a = RS[count].b = "";

			anychange = true;
		}

		count = whichRScanDo(RS, true, cycle);
		if (count && mul.empty) {
			double ans;
			mul.a = stod(RS[count].a);
			mul.b = stod(RS[count].b);
			mul.empty = false;
			mul.s = "(RS" + to_string(count) + ")" + RS[count].a + RS[count].operatorr + RS[count].b;
			mul.startCycle = cycle;
			mul.rd = RS[count].toRob;
			RS[count].empty = true;

			if (RS[count].operatorr == '*')
				mul.operatorr = '*';
			else
				mul.operatorr = '/';

			//clear RS
			RS[count].operatorr = ' ';
			RS[count].a = RS[count].b = "";

			anychange = true;
		}


		//excute 同時在最後一個cycle writeResult
		if (add.startCycle + 1 == cycle) {
			double ans;
			if (add.operatorr == '+')
				ans = add.a + add.b;
			else
				ans = add.a - add.b;
			ROB[add.rd].value = ans;
			ROB[add.rd].hasValue = true;
			add.empty = true;
			add.s = "";

			string c = add.rd;
			//capture
			for (int i = 1; i < RS.size(); i++) {
				if (!RS[i].canDo) {
					if (RS[i].a == c) {
						RS[i].a = to_string(ans);
						bool canDo = true;
						if (ROB.count(RS[i].b))
							canDo = false;
						RS[i].canDo = canDo;
					}
					if (RS[i].b == c) {
						RS[i].b = to_string(ans);
						bool canDo = true;
						if (ROB.count(RS[i].a))
							canDo = false;
						RS[i].canDo = canDo;
					}
				}
			}

			anychange = true;
			//clear RAT
			if (RAT[ROB[add.rd].rd] == add.rd)
				RAT[ROB[add.rd].rd] = "";
		}
		count = (mul.operatorr == '*') ? 7 : 15;
		if (mul.startCycle + count == cycle) {
			double ans;
			if (mul.operatorr == '*')
				ans = mul.a * mul.b;
			else
				if (mul.b == 0) {
					ROB[mul.rd].error = true;
					for (int j = y; j < ROB.size(); j++) {
						string ROB2 = "ROB" + to_string(j);
						ROB[ROB2].error = true;
					}
					errorDectect = true;
					continue;
					ans = 0;
				}
				else
					ans = mul.a / mul.b;
			ROB[mul.rd].value = ans;
			ROB[mul.rd].hasValue = true;
			mul.empty = true;
			mul.s = "";

			string c = mul.rd;
			//capture
			for (int i = 1; i < RS.size(); i++) {
				if (!RS[i].canDo) {
					if (RS[i].a == c) {
						RS[i].a = to_string(ans);
						bool canDo = true;
						if (ROB.count(RS[i].b))
							canDo = false;
						RS[i].canDo = canDo;
					}
					if (RS[i].b == c) {
						RS[i].b = to_string(ans);
						bool canDo = true;
						if (ROB.count(RS[i].a))
							canDo = false;
						RS[i].canDo = canDo;
					}
				}
			}

			anychange = true;
			//clear RAT
			if (RAT[ROB[mul.rd].rd] == mul.rd)
				RAT[ROB[mul.rd].rd] = "";
		}

		if (anychange)
			output(RF, RAT, ROB, RS, add, mul, cycle);
		cycle++;
	}
}