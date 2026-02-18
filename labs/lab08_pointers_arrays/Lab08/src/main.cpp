
#include <iostream>


using namespace std;

//void test(int& refA, int* ptrB) {
//	refA += 10;
//	*ptrB -= 5;
//}

#define N 10
//
//int main() {
//    
//    int ar1[N], ar2[N];
//    int *ar3 = new int[N];
//    int *ar4 = new int[N];
//    int *p2, *p4;
//  
//    p2 = ar2;
//    p4 = ar4;
//
//    for (int i = 0; i < N; i++)
//    {
//        ar1[i] = i * i;
//        ar3[i] = i * i;
//        *p2 = i * i;
//        p2++;
//        *p4 = i * i;
//        p4++;
//    }
//    
//    p2 = ar2;
//    p4 = ar4;
//
//    for (int i = 0; i < N; i++)
//    {
//        cout << ar1[i] << endl;
//        cout << ar3[i] << endl;
//        cout << *p2 << endl;
//        p2++;
//        cout << *p4 << endl;
//        p4++;
//
//    }
//    
//
//    delete[] ar3;
//    delete[] ar4;
//
//    return 0;
//}



//int main() {
//	int n = 5;
//	int m = 7;
//	int d;
//	d = n + m;
//	int *ar1 = new int[n]{ 2, 7, 9, 14, 18 };
//	int *ar2 = new int[m]{ 3, 3, 5, 7, 14, 20, 22};
//	int *ar3 = new int [d];
//
//	int j = 0;
//	int l = 0;
//	int i = 0;
//	//while ((l < m) && (j < n)) {
//	//		if (ar1[j] >= ar2[l]) {
//	//			ar3[i] = ar2[l];
//	//			l++;
//	//		}
//	//		else {
//	//			ar3[i] = ar1[j];
//	//			j++;
//	//		}
//	//		i++;
//	//}
//	//while (l < m) {
//	//		ar3[i] = ar2[l];
//	//		l++;
//	//		i++;
//	//}
//	//while (j < n) {
//	//		ar3[i] = ar1[j];
//	//		j++;
//	//		i++;
//	//}
//
//	int* p1, * p2, * p3;
//	p1 = ar1;
//	p2 = ar2;
//	p3 = ar3;
//
//	while ((l < m) && (j < n)) {
//		if (*p1 >= *p2) {
//			*p3 = *p2;
//			p2++;
//			p3++;
//			l++;
//		}
//		else {
//			*p3 = *p1;
//			p1++;
//			p3++;
//			j++;
//		}
//		i++;
//	}
//	while (l < m) {
//		*p3 = *p2;
//		p2++;
//		p3++;
//		l++;
//		i++;
//	}
//	while (j < n) {
//		*p3 = *p1;
//		p1++;
//		p3++;
//		j++;
//		i++;
//	}
//
//
//	for (int i = 0; i < d; i++) {
//		        cout << ar3[i] << endl;
//	}
//
//	delete[] ar1;
//	delete[] ar2;
//	delete[] ar3;
//	
//
//	return 0;
//}



struct List { int value; List *prev; List *next;};

int main() {

	List* head;
	List* tail;
	List* newlist;
	List* temp;

	newlist = new List;
	newlist->value = 1;
	temp = newlist;
	head = newlist;
	head->prev = NULL;
	tail = newlist;

	for (int i = 2; i <= 10; i++) {
		newlist = new List;
		newlist->value = i;
		temp->next = newlist;
		tail = newlist;
		tail->prev = temp;
		temp = newlist;
	}
	

	newlist->next = NULL;

	//temp = head;
	//for (int i = 1; i <= 10; i++)
	//{
	//	if (temp->value == 5) {
	//		newlist = new List;
	//		newlist->value = 14;
	//		newlist->next = temp->next;
	//		temp->next = newlist;
	//		newlist->prev = temp;
	//		temp = newlist->next;
	//		temp->prev = newlist;
	//	}
	//	else { temp = temp->next; }
	//}


	cout << "";
	List *current = head;
	while (current != nullptr) {
		cout << current->value << " ";
		current = current->next;
	}
	cout << endl;

	//cout << "";
	//List* current = tail;
	//while (current != nullptr) {
	//	cout << current->value << " ";
	//	current = current->prev;
	//}
	//cout << endl;



	return 0;
}
