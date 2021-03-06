/*
*
*Created by UnitedTimur
*
*/

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

using namespace std;

void error() {

	system("cls");
	cout << "Error. Try again ;(" << endl;
	system("pause");
	exit(-1);
}
bool operation(char operation) {

	if (operation == '+' ||
		operation == '-' ||
		operation == '*' ||
		operation == '/'
		) return true;

	return false;

}
unsigned int priority(char priority) {

	unsigned int value = 0;

	if (value == '+' || value == '-') value = 2;

	if (value == '*' || value == '/') value = 3;

	if (value == '(') value = 0;

	if (value == ')') value = 1;

	return value;
}

struct iden {

	char key;
	iden * next;

};
struct stack {

	iden * head;

	stack() : head(0) {}

	void push(char k) {

		iden * p = new iden;

		p->key = k;

		p->next = head;

		head = p;

	}
	char pop() {

		if (head) {

			iden * p = head;

			char k;

			k = p->key;

			head = head->next;

			delete p;

			return k;

		}

	}
	void delete_t() {

		iden * p;

		while (head) {

			p = head;

			head = head->next;

			delete p;

		}

	}
	void delete_head() {

		iden * p = head;

		head = head->next;

		delete p;

	}
	bool empty() {

		return head ? true : false;

	}
	void print() {

		for (iden * p = head; p != nullptr; p = p->next) {

			cout << p->key << " ";

		}

	}
	char top() {

		char k;

		if (head) {

			k = head->key;

			return k;

		}

	}

};
struct iden_double {

	float key = 0;
	iden_double * next;

};
struct stack_double {

	iden_double * head;

	stack_double() : head(0) {}

	void push(double k) {

		iden_double * p = new iden_double;

		p->key = k;

		p->next = head;

		head = p;

	}
	double pop() {

		double k = 0;

		if (head) {

			iden_double * p = head;

			k = p->key;

			head = head->next;

			delete p;

		}

		return k;

	}
	void delete_t() {

		iden_double * p;

		while (head) {

			p = head;

			head = head->next;

			delete p;

		}

	}
	void delete_head() {

		iden_double * p = head;

		head = head->next;

		delete p;

	}
	bool empty() {

		return head ? true : false;

	}
	void print() {

		for (iden_double *pt = head; pt != nullptr; pt = pt->next) {

			cout << pt->key << " ";

		}

	}
	double top() {

		double k = 0;

		if (head) {

			k = head->key;

		}

		return k;

	}

};

void main() {


	char poliz[100] = {};
	char array[100] = {};

	stack *st = new stack;
	stack_double * st_db = new stack_double;

	gets_s(array);

	unsigned int prior_first = 0;
	unsigned int prior_second = 0;
	unsigned int use = 0;
	unsigned int i = 0;
	unsigned int j = 0;

	bool next = true;

	/*--------------------------POLIS-------------------------------------*/
	while (array[i]) {

		if (isalpha(array[i])) {

			if (next) {

				poliz[j++] = array[i];
				next = false;

			}
			else error();

		}
		else if (isdigit(array[i])) {

			if (next) {
				//the first symbol != 0 else error
				if (array[i] == 0)	error();

				while (isdigit(array[i])) {

					poliz[j++] = array[i++];

				}

				i--;

				next = false;

				poliz[j++] = '?';

			}
			else error();

		}
		else if (operation(array[i])) {

			if (st->empty() && !next) {

				prior_first = priority(array[i]);
				prior_second = priority(st->top());

				while (prior_first < prior_second) {

					poliz[j++] = st->pop();
					prior_second = priority(st->top());

				}

				st->push(array[i]);

			}
			else {

				if (!st->empty()) st->push(array[i]);
				else error();

			}

			next = true;

		}
		else if (array[i] == '(' && next) {

			st->push(array[i]);
			
			use++;

		}
		else {
			if (use == 0)	error();

			while (st->top() != '(') {

				poliz[j++] = st->pop();

			}

			st->pop();

			use--;

		}

		i++;

	}
	while (st->empty()) {

		poliz[j++] = st->pop();

	}
	cout << "Polis" << endl;
	for (int i = 0; poliz[i]; i++) {

		cout << poliz[i];

	}
	cout <<  endl;
	/*--------------------------------------------------------------------*/

	i = 0;

	double first = 0;
	double second = 0;
	double middle = 0;

	while (poliz[i]) {

		if (isalpha(poliz[i])) {

			cout << "Enter value " << poliz[i] << " = ";
			cin >> first;
			st_db->push(first);

		}
		else if (isdigit(poliz[i])) {

			middle = 0;

			while (isdigit(poliz[i])){

				middle = middle * 10 + ((float)(poliz[i++]) - '0');

			}

			st_db->push((float)middle);

		}
		else if (operation(poliz[i])) {

			second = st_db->pop();
			first = st_db->pop();

			switch (poliz[i])
			{

			case '+': {

				st_db->push((double)(first + second));
				break;

			}
			case '-': {

				st_db->push((double)(first - second));
				break;

			}
			case '*': {

				st_db->push((double)(first * second));
				break;

			}
			case '/': {

				if (second == 0) error();

				st_db->push((double)(first / second));
				break;

			}

			}

		}

		i++;
	}

	cout << "Answer = " << (double)st_db->top() << endl;

	std::system("pause");

}
