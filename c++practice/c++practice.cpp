#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>

using namespace std;

class DFS
{
public:
	int num;
	string name;
	DFS *right;
	DFS *left;
	DFS *up;
};
//전역 변수
DFS *head = NULL;
int cnt = 0;


void menu();
void insert();
void substract();
void search();
void print();
void printTree();

void compare1(DFS *pa, DFS *ch);
void deleteData(DFS *list);
void print1(DFS *list);
void search1(DFS *pa, int n);
DFS *search2(DFS*pa, int n);
void subs(DFS *pa, int n);
DFS *subs2(DFS *find);

int main()
{
		menu();

		//할당 해제
		DFS *list = head;
		deleteData(list);
		delete list;


	return 0;
}

void insert()
{
	DFS *dfs = NULL;
	dfs = new DFS();

	cout << "삽입하는 데이터를 입력하세요." << endl;

	cout << "번호 : ";
	cin >> dfs->num;
	cout << "이름 : ";
	cin >> dfs->name;

		if (head == NULL )
		{
		head = dfs; //처음일경우
		cout << head->num << " " << head->name<<endl;
		}
		else
		{
			compare1(head, dfs); //부모 노드와 자식노드 관계 비교
		}
		cnt++;
}
void compare1(DFS *pa, DFS *ch) //부모 자식
{
	if (ch->num < pa->num) //더 작을경우
	{
		if (pa->left == NULL)//왼쪽이 NULL이라면 삽입
		{
			pa->left = ch;
			ch->up = pa;
			cout << pa->left->num << " " << pa->left->name << endl;
		}
		else //왼쪽에 자식 노드가 있는 경우에는 다시 찾기
			compare1(pa->left, ch);
	}
	else if (ch->num > pa->num)//더 클 경우
	{
		if (pa->right == NULL)//오른쪽이 NULL이라면 삽입
		{
			pa->right = ch;
			ch->up = pa;
			cout << pa->right->num << " " << pa->right->name << endl;
		}
		else//자식노드가 있다면 하위에서 다시 찾기
			compare1(pa->right, ch);
	}
}
void substract()
{
	int n;
	cout << "삭제하는 데이터를 입력하세요.\n" << "번호 : ";
	cin >> n;
	subs(head, n);
	
}

DFS *subs2(DFS *find)		//왼쪽트리에서 가장 큰 값을 찾기위함
{
	if (find->right != NULL) //오른쪽에 값이 있으면
		subs2(find->right); //다시 찾으러 ㄱㄱ
	else //없으면 너 리턴
		return find;
}
void subs(DFS *pa, int n)
{
	DFS *find;
		find = search2(pa, n); //해당 위치 찾기
		if (find == NULL)
		{
			cout << "데이터를 찾을 수 없습니다." << endl;
			return;
		}
	if (find->left == NULL && find->right == NULL)//해당 노드 자식이 없는경우
	{
		if (find->num < find->up->num)	//부모보다 작으면 왼쪽연결끊기
			find->up->left == NULL;
		else
			find->up->right == NULL; //부모보다 크면 오른쪽연결 끊기
	}
	else if (find->left != NULL && find->right != NULL)//해당 노드 자식이 2개인경우
	{
		DFS *find2 = subs2(find->left); //자식중 가장 큰 값
		if (find2->up->num != find->num)//바로 아래 자식이 아니었다면
		{
			if (find2->left != NULL)//자식이 있었다면
			{
				find2->up->right = find2->left; //다른 자식 가리키기
				find2->left->up = find2->up;
			}

			find2->up = find->up;
			if (find->up->left->num == find->num) //왼쪽자식이었으면
				find->up->left = find2;
			else
				find->up->right = find2;

			find->left->up = find2;
			find->right->up = find2;
			find2->left = find->left;
			find2->right = find->right;

		}
	
	}
	else //해당 노드 자식이 1개인 경우
	{
		if (find->left != NULL) //왼쪽자식있는경우 부모가 여기로 연결
		{
			if (find->up->left->num == find->num) //왼쪽자식이었으면
				find->up->left = find->left;//왼쪽으로연결
			else
				find->up->right = find->left;
		}
		else//오른쪽으로 연결
		{
			if (find->up->left->num == find->num) //왼쪽자식이었으면
				find->up->left = find->right;//왼쪽으로연결
			else
				find->up->right = find->right;
		}
	}
	cnt--;
	delete find;
}
DFS *search2(DFS*pa,int n) {
	if (pa == NULL)//없는 경우
		return NULL;
	else if (n < pa->num) //작은값일경우
		search2(pa->left, n);
	else if (n > pa->num)//큰값일경우
		search2(pa->right, n);

	else //일치하는경우
		return pa;
}
void search()
{
	int n;
	string Name;
	
	cout << "검색하는 데이터를 입력하세요.\n" << "번호 : ";
	cin >> n;
	if (head->num != n)
		search1(head, n);
	else
	{
		Name = head->name;
		cout << "번호 : " << n << ", 이름 : " << Name << endl;
	}
}
void search1(DFS *pa, int n)
{
	static int flag = 1;
	if (pa == NULL)
	{
		cout << "해당 데이터가 존재하지 않습니다." << endl;
		return;
	}
	else {
	if (n < pa->num) //작은값일경우
	search1(pa->left, n);
	else if (n > pa->num)//큰값일경우
	search1(pa->right, n);

	}
	while (flag)
	{
		cout << "번호 : " << pa->num << ", 이름 : " << pa->name << endl;
		flag = 0;
	}
	return;
}
void print()
{
	cout << "[모든 노드 출력]" << endl;
	print1(head);
}
void print1(DFS *list)
{
	if (list != NULL)
	{
		if(list->left!=NULL)
		print1(list->left);
		cout << list->num << "번 " << list->name << endl;
		if(list->right!=NULL)
		print1(list->right);
	}
	else {}
}
void deleteData(DFS *list)
{
	if (list != NULL) {
		delete list->right;
		delete list->left;
		deleteData(list->left);
		deleteData(list->right);
	}
}

void menu()
{
	int n = 1;

	while (n != 0)
	{
		cout << endl << "(1)삽입 (2)삭제 (3)검색 (4)출력 (0)종료 : ";
		cin >> n;
		switch (n)
		{
		case 1:
			insert();
			break;
		case 2:
			substract();
			break;
		case 3:
			search();
			break;
		case 4:
			print();
			break;
		case 0:
			break;
		default: cout << "유효한 숫자를 입력하세요" << endl;
		}
	}
}

void printTree()
{
	
}






//#include <iostream>
//#include <string>
//
//using namespace std;
//
//class Hash
//{
//public:
//	int num;
//	string name;
//	Hash *up;
//	Hash *down;
//};
//
//
//Hash *arr = new Hash[13]{};
//
//void menu();
//void insert();
//void substract();
//void search();
//void print();
//void compare1(Hash *pa, Hash *ch);
//void search2(Hash *pa, int n);
//void subs2(Hash *pa, int n);
//
//
//int main()
//{
//
//
//	menu();
//
//			//할당 해제
//
//	delete[] arr;
//	return 0;
//}
//void insert()
//{
//	Hash *hash = NULL;
//	hash = new Hash();
//	
//	cout << "삽입하는 데이터를 입력하세요." << endl;
//	cout << "번호 : ";
//	cin >> hash->num;
//	cout << "이름 : ";
//	cin >> hash->name;
//
//	if (arr[hash->num % 13].down == NULL) //처음들어오는 숫자
//	{
//		arr[hash->num % 13].down = hash;	//배열 바로 밑으로 보냄	 
//	}
//	else  //나중에 들어오는 숫자
//	{
//		compare1(arr[hash->num % 13].down, hash);
//	}
//
//	//cout << arr[hash->num % 13].down->name << " " << arr[hash->num % 13].down->num << endl;
//}
//
//void compare1(Hash *pa, Hash *ch)
//{
//	if (pa->num < ch->num)  //더 큰 경우에는 다음 연결과 비교
//	{
//		if(pa->down !=NULL) //다음 연결이 있는경우에 비교
//		compare1(pa->down, ch);
//		else //없으면 바로 연결
//		{
//			pa->down = ch;
//			ch->up = pa;
//		}
//	}
//	else //작은경우에는 이전연결 끊고 거기다 집어넣기
//	{
//		if (pa->up != NULL) //pa 이전에 데이터가 있는경우
//		{
//			pa->up->down = ch; //pa 이전이 ch을 가리키고
//			ch->up = pa->up; //ch 이전이 pa 이전 가리키고
//			ch->down = pa; //ch 다음이 pa로 오게 정렬
//		}
//	}
//
//}
//
//void substract()
//{
//	int n;
//	cout << "삭제할 번호를 입력하세요 : ";
//	cin >> n;
//	subs2(arr[n%13].down,n);
//}
//void subs2(Hash *pa, int n)
//{
//	if (pa != NULL)
//	{
//		if (pa->num == n)
//		{
//			if (pa->down == NULL) //밑에 연결이 없는경우
//			{
//				if (pa->up != NULL) //위에 연결 있는경우(처음은 없음)
//					pa->up->down = NULL; //아래 연결끊기
//				pa = NULL;
//			}
//			else //밑에 연결이 있는경우
//			{
//				if (pa->up != NULL)
//				{
//					pa->up->down = pa->down; //이전과 다음연결시키기
//					pa->down->up = pa->up;
//				}
//				else //다음연결로바로
//					arr[n % 13].down = pa->down;
//				pa = NULL;
//
//			}
//		}
//		else //다음연결에서 찾기
//		{
//			if (pa->down == NULL)
//				cout << "삭제할 데이터를 찾지 못했습니다." << endl;
//			else
//				subs2(pa->down, n);
//		}
//	}
//	else
//		cout << "삭제할 데이터를 찾지 못했습니다." << endl;
//}
//void search()
//{
//	int n;
//	cout << "검색할 번호를 입력하세요 : ";
//	cin >> n;
//	search2(arr[n % 13].down, n);
//}
//void search2(Hash *pa, int n)
//{
//	if (pa != NULL)
//	{
//		if (pa->num == n)
//			cout << "검색에 성공했습니다 : " << n << " " << pa->name << endl;
//		else
//		{
//			if (pa->down == NULL)
//				cout << "검색에 실패했습니다!" << endl;
//			else
//				search2(pa->down, n);
//		}
//	}
//	else
//		cout << "검색에 실패했습니다!" << endl;
//}
//void print()
//{
//	Hash *list = 0;
//	for (int i = 0; i < 13; i++)
//	{
//		cout << i<<" : ";
//		for (list = arr[i].down; list != NULL; list = list->down)
//		{
//			cout << "->" << list->num << "(" << list->name << ")";
//		}
//		cout << endl;
//	}
//
//}
//
//void menu()
//{
//	int n = 1;
//
//	while (n != 0)
//	{
//		cout << endl << "(1)삽입 (2)삭제 (3)검색 (4)덤프 (0)종료 : ";
//		cin >> n;
//		switch (n)
//		{
//		case 1:
//			insert();
//			break;
//		case 2:
//			substract();
//			break;
//		case 3:
//			search();
//			break;
//		case 4:
//			print();
//			break;
//		case 0:
//			break;
//		default: cout << "유효한 숫자를 입력하세요" << endl;
//		}
//	}
//}





































//#include <iostream>
//#include <string>
//
//using namespace std;
//
//class DFS
//{
//public:
//	int num;
//	string name;
//	DFS *right;
//	DFS *left;
//	DFS *up;
//};
////전역 변수
//DFS *head = NULL;
//int cnt = 0;
//
//
//void menu();
//void insert();
//void substract();
//void search();
//void print();
//void printTree();
//
//void compare1(DFS *pa, DFS *ch);
//void deleteData(DFS *list);
//void print1(DFS *list);
//void search1(DFS *pa, int n);
//DFS *search2(DFS*pa, int n);
//void subs(DFS *pa, int n);
//DFS *subs2(DFS *find);
//
//int main()
//{
//		menu();
//
//		//할당 해제
//		DFS *list = head;
//		deleteData(list);
//		delete list;
//
//
//	return 0;
//}
//
//void insert()
//{
//	DFS *dfs = NULL;
//	dfs = new DFS();
//
//	cout << "삽입하는 데이터를 입력하세요." << endl;
//
//	cout << "번호 : ";
//	cin >> dfs->num;
//	cout << "이름 : ";
//	cin >> dfs->name;
//
//		if (head == NULL )
//		{
//		head = dfs; //처음일경우
//		cout << head->num << " " << head->name<<endl;
//		}
//		else
//		{
//			compare1(head, dfs); //부모 노드와 자식노드 관계 비교
//		}
//		cnt++;
//}
//void compare1(DFS *pa, DFS *ch) //부모 자식
//{
//	if (ch->num < pa->num) //더 작을경우
//	{
//		if (pa->left == NULL)//왼쪽이 NULL이라면 삽입
//		{
//			pa->left = ch;
//			ch->up = pa;
//			cout << pa->left->num << " " << pa->left->name << endl;
//		}
//		else //왼쪽에 자식 노드가 있는 경우에는 다시 찾기
//			compare1(pa->left, ch);
//	}
//	else if (ch->num > pa->num)//더 클 경우
//	{
//		if (pa->right == NULL)//오른쪽이 NULL이라면 삽입
//		{
//			pa->right = ch;
//			ch->up = pa;
//			cout << pa->right->num << " " << pa->right->name << endl;
//		}
//		else//자식노드가 있다면 하위에서 다시 찾기
//			compare1(pa->right, ch);
//	}
//}
//void substract()
//{
//	int n;
//	cout << "삭제하는 데이터를 입력하세요.\n" << "번호 : ";
//	cin >> n;
//	subs(head, n);
//	cnt--;
//}
//
//DFS *subs2(DFS *find)		//왼쪽트리에서 가장 큰 값을 찾기위함
//{
//	if (find->right != NULL) //오른쪽에 값이 있으면
//		subs2(find->right); //다시 찾으러 ㄱㄱ
//	else //없으면 너 리턴
//		return find;
//}
//void subs(DFS *pa, int n)
//{
//	DFS *find;
//		find = search2(pa, n); //해당 위치 찾기
//
//	if (find->left == NULL && find->right == NULL)//해당 노드 자식이 없는경우
//	{
//		if (find->num < find->up->num)	//부모보다 작으면 왼쪽연결끊기
//			find->up->left == NULL;
//		else
//			find->up->right == NULL; //부모보다 크면 오른쪽연결 끊기
//	}
//	else if (find->left != NULL && find->right != NULL)//해당 노드 자식이 2개인경우
//	{
//		DFS *find2 = subs2(find->left); //자식중 가장 큰 값
//		if (find2->up->num != find->num)//바로 아래 자식이 아니었다면
//		{
//			if (find2->left != NULL)//자식이 있었다면
//			{
//				find2->up->right = find2->left; //다른 자식 가리키기
//				find2->left->up = find2->up;
//			}
//
//			find2->up = find->up;
//			if (find->up->left->num == find->num) //왼쪽자식이었으면
//				find->up->left = find2;
//			else
//				find->up->right = find2;
//
//			find->left->up = find2;
//			find->right->up = find2;
//			find2->left = find->left;
//			find2->right = find->right;
//
//		}
//	
//	}
//	else //해당 노드 자식이 1개인 경우
//	{
//		if (find->left != NULL) //왼쪽자식있는경우 부모가 여기로 연결
//		{
//			if (find->up->left->num == find->num) //왼쪽자식이었으면
//				find->up->left = find->left;//왼쪽으로연결
//			else
//				find->up->right = find->left;
//		}
//		else//오른쪽으로 연결
//		{
//			if (find->up->left->num == find->num) //왼쪽자식이었으면
//				find->up->left = find->right;//왼쪽으로연결
//			else
//				find->up->right = find->right;
//		}
//	}
//	delete find;
//}
//DFS *search2(DFS*pa,int n) {
//	if (n < pa->num) //작은값일경우
//		search2(pa->left, n);
//	else if (n > pa->num)//큰값일경우
//		search2(pa->right, n);
//	else if (pa->num == NULL)//없는 경우
//		cout << "해당 데이터가 존재하지 않습니다." << endl;
//	else //일치하는경우
//		return pa;
//}
//void search()
//{
//	int n;
//	string Name;
//	
//	cout << "검색하는 데이터를 입력하세요.\n" << "번호 : ";
//	cin >> n;
//	if (head->num != n)
//		search1(head, n);
//	else
//	{
//		Name = head->name;
//		cout << "번호 : " << n << ", 이름 : " << Name << endl;
//	}
//}
//void search1(DFS *pa, int n)
//{
//	if (n < pa->num) //작은값일경우
//		search1(pa->left, n);
//	else if (n > pa->num)//큰값일경우
//		search1(pa->right, n);
//	else if (pa->num == NULL)//없는 경우
//		cout << "해당 데이터가 존재하지 않습니다." << endl;
//	else //일치하는경우
//		cout<<"번호 : "<<pa->num<<", 이름 : "<<pa->name<<endl;
//}
//void print()
//{
//	cout << "[모든 노드 출력]" << endl;
//	print1(head);
//}
//void print1(DFS *list)
//{
//	if (list != NULL)
//	{
//		print1(list->left);
//		cout << list->num << "번 " << list->name << endl;
//		print1(list->right);
//	}
//	else {}
//}
//void deleteData(DFS *list)
//{
//	if (list != NULL) {
//		delete list->right;
//		delete list->left;
//		deleteData(list->left);
//		deleteData(list->right);
//	}
//}
//
//void menu()
//{
//	int n = 1;
//
//	while (n != 0)
//	{
//		cout << endl << "(1)삽입 (2)삭제 (3)검색 (4)출력 (0)종료 : ";
//		cin >> n;
//		switch (n)
//		{
//		case 1:
//			insert();
//			break;
//		case 2:
//			substract();
//			break;
//		case 3:
//			search();
//			break;
//		case 4:
//			print();
//			break;
//		case 0:
//			break;
//		default: cout << "유효한 숫자를 입력하세요" << endl;
//		}
//	}
//}
//
//void printTree()
//{
//	
//}
















//
//#define _CRT_SECURE_NO_WARNINGS
//
//#include <iostream>
//#include <string>
//
//using namespace std;
//
//class DFS
//{
//public:
//	int num;
//	string name;
//	DFS *right;
//	DFS *left;
//	DFS *up;
//};
//DFS *head = NULL;
//
//void menu();
//void insert();
//void substract();
//void search();
//void print();
//void printTree();
//
//void compare1(DFS *pa, DFS *ch);
//void deleteData(DFS *list);
//void print1(DFS *list);
//void search1(DFS *pa, int n);
//DFS *search2(DFS*pa, int n);
//void subs(DFS *pa, int n);
//DFS *subs2(DFS *find);
//
//int main()
//{
//	menu();
//
//	//할당 해제
//	DFS *list = head;
//	deleteData(list);
//	delete list;
//
//	return 0;
//}
//
//void insert()
//{
//	DFS *dfs = NULL;
//	dfs = new DFS();
//
//	cout << "삽입하는 데이터를 입력하세요." << endl;
//
//	cout << "번호 : ";
//	cin >> dfs->num;
//	cout << "이름 : ";
//	cin >> dfs->name;
//
//	if (head == NULL)
//	{
//		head = dfs; //처음일경우
//		cout << head->num << " " << head->name << endl;
//	}
//	else
//	{
//		compare1(head, dfs); //부모 노드와 자식노드 관계 비교
//	}
//
//}
//void compare1(DFS *pa, DFS *ch) //부모 자식
//{
//	if (ch->num < pa->num) //더 작을경우
//	{
//		if (pa->left == NULL)//왼쪽이 NULL이라면 삽입
//		{
//			pa->left = ch;
//			ch->up = pa;
//			cout << pa->left->num << " " << pa->left->name << endl;
//		}
//		else //왼쪽에 자식 노드가 있는 경우에는 다시 찾기
//			compare1(pa->left, ch);
//	}
//	else if (ch->num > pa->num)//더 클 경우
//	{
//		if (pa->right == NULL)//오른쪽이 NULL이라면 삽입
//		{
//			pa->right = ch;
//			ch->up = pa;
//			cout << pa->right->num << " " << pa->right->name << endl;
//		}
//		else//자식노드가 있다면 하위에서 다시 찾기
//			compare1(pa->right, ch);
//	}
//}
//void substract()
//{
//	int n;
//	cout << "삭제하는 데이터를 입력하세요.\n" << "번호 : ";
//	cin >> n;
//	subs(head, n);
//}
//
//DFS *subs2(DFS *find)		//왼쪽트리에서 가장 큰 값을 찾기위함
//{
//	if (find->right != NULL) //오른쪽에 값이 있으면
//		subs2(find->right); //다시 찾으러 ㄱㄱ
//	else //없으면 너 리턴
//		return find;
//}
//void subs(DFS *pa, int n)
//{
//	DFS *find;
//	find = search2(pa, n); //해당 위치 찾기
//
//	if (find->left == NULL && find->right == NULL)//해당 노드 자식이 없는경우
//	{
//		if (find->num < find->up->num)	//부모보다 작으면 왼쪽연결끊기
//			find->up->left == NULL;
//		else
//			find->up->right == NULL; //부모보다 크면 오른쪽연결 끊기
//	}
//	else if (find->left != NULL && find->right != NULL)//해당 노드 자식이 2개인경우
//	{
//		DFS *find2 = subs2(find->left); //자식중 가장 큰 값
//		if (find2->up->num != find->num)//바로 아래 자식이 아니었다면
//		{
//			if (find2->left != NULL)//자식이 있었다면
//			{
//				find2->up->right = find2->left; //다른 자식 가리키기
//				find2->left->up = find2->up;
//			}
//
//			find2->up = find->up;
//			if (find->up->left->num == find->num) //왼쪽자식이었으면
//				find->up->left = find2;
//			else
//				find->up->right = find2;
//
//			find->left->up = find2;
//			find->right->up = find2;
//			find2->left = find->left;
//			find2->right = find->right;
//
//		}
//
//	}
//	else //해당 노드 자식이 1개인 경우
//	{
//		if (find->left != NULL) //왼쪽자식있는경우 부모가 여기로 연결
//		{
//			if (find->up->left->num == find->num) //왼쪽자식이었으면
//				find->up->left = find->left;//왼쪽으로연결
//			else
//				find->up->right = find->left;
//		}
//		else//오른쪽으로 연결
//		{
//			if (find->up->left->num == find->num) //왼쪽자식이었으면
//				find->up->left = find->right;//왼쪽으로연결
//			else
//				find->up->right = find->right;
//		}
//	}
//	delete find;
//}
//DFS *search2(DFS*pa, int n) {
//	if (n < pa->num) //작은값일경우
//		search2(pa->left, n);
//	else if (n > pa->num)//큰값일경우
//		search2(pa->right, n);
//	else if (pa->num == NULL)//없는 경우
//		cout << "해당 데이터가 존재하지 않습니다." << endl;
//	else //일치하는경우
//		return pa;
//}
//void search()
//{
//	int n;
//	string Name;
//
//	cout << "검색하는 데이터를 입력하세요.\n" << "번호 : ";
//	cin >> n;
//	if (head->num != n)
//		search1(head, n);
//	else
//	{
//		Name = head->name;
//		cout << "번호 : " << n << ", 이름 : " << Name << endl;
//	}
//}
//void search1(DFS *pa, int n)
//{
//	if (n < pa->num) //작은값일경우
//		search1(pa->left, n);
//	else if (n > pa->num)//큰값일경우
//		search1(pa->right, n);
//	else if (pa->num == NULL)//없는 경우
//		cout << "해당 데이터가 존재하지 않습니다." << endl;
//	else //일치하는경우
//		cout << "번호 : " << pa->num << ", 이름 : " << pa->name << endl;
//}
//void print()
//{
//	cout << "[모든 노드 출력]" << endl;
//	print1(head);
//}
//void print1(DFS *list)
//{
//	if (list != NULL)
//	{
//		print1(list->left);
//		cout << list->num << "번 " << list->name << endl;
//		print1(list->right);
//	}
//	else {}
//}
//void deleteData(DFS *list)
//{
//	if (list != NULL) {
//		delete list->right;
//		delete list->left;
//		deleteData(list->left);
//		deleteData(list->right);
//	}
//}
//
//void menu()
//{
//	int n = 1;
//
//	while (n != 0)
//	{
//		cout << endl << "(1)삽입 (2)삭제 (3)검색 (4)출력 (0)종료 : ";
//		cin >> n;
//		switch (n)
//		{
//		case 1:
//			insert();
//			break;
//		case 2:
//			substract();
//			break;
//		case 3:
//			search();
//			break;
//		case 4:
//			print();
//			break;
//		case 0:
//			break;
//		default: cout << "유효한 숫자를 입력하세요" << endl;
//		}
//	}
//}

//#include <iostream>
//#include <string>
////입력순서와 상관없이 번호 순서대로 정렬된 리스트를 구현하는 프로그램을 작성하라.
////리스트 초기화 /노드추가-제일 앞에 추가, 맨 뒤에 추가, 노드 사이에 추가 / 노드 삭제-제일앞,맨뒤,노드사이
////검색-번호받아서 번호이름출력 / 리스트전체데이터 ㄹ출력
//using namespace std;
//
//class student
//{
//public:
//	int num;
//	string name;
//	student *next;
//	student *prev;
//};
//
//student *head, *tail=NULL;
//
//
//	void menu();
//	void insert();
//	void print();
//	void search();
//	void Initialize();
//	void substract();
//
//	int cnt = 0;
//	int avg = 0;
//
//
//int main()
//{
//	Initialize(); //초기화
//	menu();
//	//메모리 해제하기
//	student *list = head;
//	while (list->next)
//	{
//		list = list->next;
//		delete list->prev;
//	}
//	delete list;
//	return 0;
//}
//
//
//void menu()
//{
//
//	int n=1;
//
//	while (n != 0)
//	{
//		cout <<endl<< "메뉴 선택 : " << endl << "1. 학생 추가" << endl << "2. 학생 삭제" << endl <<
//			"3. 학생 검색" << endl << "4.전체 출력" << endl << "9.리스트 초기화" << endl << "0.종료\n" << endl;
//		cin >> n;
//		switch (n)
//		{
//		case 1:
//
//			insert();
//			break;
//		case 2:
//			substract();
//			break;
//		case 3:
//			search();
//				break; 
//		case 4:
//			print();
//			break;
//		case 9:
//			Initialize();
//			break;
//		case 0: 
//			break;
//		default: cout << "유효한 숫자를 입력하세요" << endl;
//		}
//	}
//}
//
//void insert()
//{
//	
//	student *stu = NULL;
//	stu = new student();
//	cout << "학생 번호 : ";
//	cin >> stu->num;
//	cout << "학생 이름 : ";
//	cin >> stu->name;
//
//
//
//
//	if (head == NULL )
//	{
//		head ->next= stu; //처음일경우 그대로
//
//		stu->next = tail;
//		tail->prev = stu;
//	}
//	else if (stu->num < head->next->num) //head보다 작은경우
//	{
//		head ->next->prev=stu;
//		stu->next = head->next;
//		head->next = stu;
//	}
//	else if (stu->num>tail->prev->num)
//	{
//		tail->next = stu; //마지막 번호일 경우 
//
//		stu->next = tail;
//		stu->prev = tail->prev;
//		tail->prev->next = stu;
//		tail->prev = stu;
//	}
//	else { //중간값이 들어온 경우
//		student *list;
//		if (stu->num < avg/cnt)		//중앙값보다 작을경우 앞에서부터 찾는다 
//		{
//			for (list = head->next; list != tail; list = list->next)
//			{
//				if (stu->num < list->num) //더 큰값을 발견한 경우 그 전단계에 삽입
//				{
//					stu->prev = list->prev;
//					stu->next = list;
//					list->prev->next = stu;
//					list->prev = stu;
//					break;
//				}
//			}
//		}
//		else
//		{
//			for (list = tail->prev; list != head; list = list->prev)
//			{
//				if (stu->num > list->num) //더 작은 값을 발견한 경우 그 다음단계에 삽입
//				{
//					stu->prev = list;
//					stu->next = list->next;
//					list->next->prev = stu;
//					list->next = stu;
//
//					break;
//				}
//			}
//		}
//	}
//	avg += stu->num;
//	cnt++;
//}
//
//void print()
//{
//	student *list = 0;
//	for (list = head->next; list != tail; list = list->next)
//	{
//		cout << list->num << "번 " << list->name << endl;
//	}
//}
//void Initialize()
//{
//	head = new student;
//	tail = new student;
//	head->next = tail;
//	tail->prev = head;
//	head->prev = NULL;
//	tail->next = NULL;
//}
//void search()
//{
//	int n = 0;
//	cout << "학생 번호 : ";
//		cin >> n;
//		student *stu;
//		if (n < avg/cnt)		//중앙값보다 작을경우 앞에서부터 찾는다 
//		{
//			for (stu = head->next; stu != tail; stu = stu->next)
//			{
//				if (stu->num == n)
//				{
//					cout << stu->num << "번 " << stu->name << endl;
//					return;
//				}
//			}
//		}
//		else
//		{
//			for (stu = tail->prev; stu != head; stu = stu->prev)
//			{
//				if (stu->num == n)
//				{
//					cout << stu->num << "번 " << stu->name << endl;
//					return;
//				}
//			}
//		}
//		cout << "해당 번호가 없습니다." << endl;
//}
//void substract()
//{
//	
//	int n;
//	cout << "학생 번호 : ";
//	cin >> n;
//	if (head != NULL)
//	{
//		student *stu;
//		if (n < avg/cnt)		//중앙값보다 작을경우 앞에서부터 찾는다 
//		{
//			for (stu = head->next; stu != tail; stu = stu->next)
//			{
//				if (stu->num == n)
//				{
//					stu->prev->next = stu->next;
//					stu->next->prev = stu->prev;
//					delete stu;
//					cnt--;
//					avg -= stu->num;
//					return;
//				}
//			}
//		}
//		else
//		{
//			for (stu = tail->prev; stu != head; stu = stu->prev)
//			{
//				if (stu->num == n)
//				{
//					stu->prev->next = stu->next;
//					stu->next->prev = stu->prev;
//					delete stu;
//					cnt--;
//					avg -= stu->num;
//					return;
//				}
//			}
//		}
//		cout << "해당 번호가 없습니다." << endl;
//	}
//
//}
















//#include "stopwatch.h"
//using namespace std;
//
//int brute_force(const char data[], const char pat[]);
//int kmp(const char data[], const char pat[]);
//int BoyerMoore(const char data[], const char pat[]);
//
//int main()
//{
//	char *data = new char[10000000];
//	char *pattern = new char[100];
//	srand((unsigned)time(0));
//	cout << "데이터 입력 : ";
//	for (int i = 0; i < 10000000; i++)
//	{
//		data[i]= 'a' + rand() % 26;
//		//cout << data[i];
//	}
//
//	//char *data = new char[10000];
//	//char *pattern = new char[100];
//	//srand((unsigned)time(0));
//	//cout << "데이터 입력 : ";
//	//cin >> data;
//
//		cout <<endl<< "패턴 입력 : ";
//		cin >> pattern;
//	int bn = brute_force(data, pattern);
//
//	if (bn != -1)
//		cout << bn << "번째에서 발견!"<<endl;
//	else
//		cout << "발견하지 못했습니다!"<<endl;
//	
//	int kn = kmp(data, pattern);
//	if (kn != -1)
//		cout << kn << "번째에서 발견!"<<endl;
//	else
//		cout << "발견하지 못했습니다!"<<endl;
//
//	int bmn = BoyerMoore(data, pattern);
//	if (bmn != -1)
//		cout << bmn << "번째에서 발견!" << endl;
//	else
//		cout << "발견하지 못했습니다!" << endl;
//
//	delete[] data;
//	delete[] pattern;
//		return 0;
//}
//int BoyerMoore(const char data[], const char pat[])
//{
//	stopwatch timecheck;
//	timecheck.start();
//	int dat_size = strlen(data);
//	int pat_size = strlen(pat);
//	int i = pat_size - 1;
//	int icnt = 0;
//
//	while (1)
//	{
//
//		int dcnt = 0;		//데이터 얼마나 넘길지 카운트
//
//		for (int j = pat_size-1-icnt; j >= 0; j--)	//패턴 뒤에서부터 비교
//		{
//			if (pat[j] != data[i])		//틀리면 카운트 ++
//			{
//				/////////////출력부////////////////
//				//cout << data << endl;
//				//for (int k = 0; k < i; k++)
//				//	cout << " ";
//				//cout << "|" << endl;
//				//for (int k = 0; k < i-j; k++)
//				//	cout << " ";
//				//cout << pat << endl;
//				//cout << endl;
//				/////////////////////////////////
//				dcnt++;
//			}
//			else if (j != pat_size - 1 && pat[j] == data[i] && dcnt>0)	//맞았는데 패턴 마지막이 아니면서 카운트가 있다면
//			{
//				//////////////출력부////////////////
//				//cout << data << endl;
//				//for (int k = 0; k < i; k++)
//				//	cout << " ";
//				//cout << "o" << endl;
//				//for (int k = 0; k < i - j; k++)
//				//	cout << " ";
//				//cout << pat << endl;
//				//cout << endl;
//				//////////////////////////////////
//				i += dcnt;
//				i += icnt;
//				goto CON;
//			}
//			else
//			{
//				//////////////출력부////////////////
//				//cout << data << endl;
//				//for (int k = 0; k < i ; k++)
//				//	cout << " ";
//				//cout << "+" << endl;
//				//for (int k = 0; k < i -j; k++)
//				//	cout << " ";
//				//cout << pat << endl;
//				//cout << endl;
//				//////////////////////////////////
//				i--;	// 패턴과 일치하는 경우에 데이터의 앞부분과 비교
//				icnt++; // 패턴을 찾지 못할경우 대비
//				continue;
//			}
//		}
//			i += dcnt;
//			i += icnt; //i-- 손해본 것 복구
//			icnt = 0; //icnt 초기화
//		if (i > dat_size || dcnt == 0) break;
//	CON: continue;
//	}
//
//	timecheck.stop();
//	cout << "Boyer-Moore 총 걸린 시간 " << timecheck.getElapsedTime() << "ms" << endl;
//	if (i < dat_size)
//		return i -1;
//	else
//		return -1;
//}
//int kmp(const char data[], const char pat[])
//{
//	stopwatch timecheck;
//	timecheck.start();
//
//	int i = 0;
//	int dat_size = strlen(data);
//	int pat_size = strlen(pat);
//
//	for (i; i < dat_size; i++)
//	{
//		int cnt = 0; //반복되는 경우 넘기기 위한 카운트
//		for (int j = 0; j < pat_size; j++)
//		{
//			
//			if (pat[j] != data[i + j])
//			{
//				///////////////////출력부////////////////
//				//cout << data << endl;
//				//for (int k = 0; k < i + j; k++)
//				//	cout << " ";
//				//cout << "|" << endl;
//				//for (int k = 0; k < i; k++)
//				//	cout << " ";
//				//cout << pat << endl;
//				//cout << endl;
//				///////////////////////////////////////
//				if(cnt!=0)
//				i += cnt-1; //불일치하는경우 카운트를 더해서 건너뜀/ 다음 i++고려해서 -1;
//				goto CON;
//			}
//			else
//			{
//				cnt++;	//일치하는 경우 카운트++;
//				//////////////출력부////////////////
//				//cout << data << endl;
//				//for (int k = 0; k < i + j; k++)
//				//	cout << " ";
//				//cout << "+" << endl;
//				//for (int k = 0; k < i; k++)
//				//	cout << " ";
//				//cout << pat << endl;
//				//cout << endl;
//				//////////////////////////////////
//			}
//
//		}
//		break;
//	CON:continue;
//
//	}
//	timecheck.stop();
//	cout << "kmp 총 걸린 시간 " << timecheck.getElapsedTime() << "ms" << endl;
//	if (i < dat_size - 1)
//
//		return i + 1;
//	else
//		return -1;
//}
//
//int brute_force(const char data[], const char pat[])
//{
//	stopwatch timecheck;
//timecheck.start();
//
//	int i = 0;
//	int dat_size = strlen(data);
//	int pat_size = strlen(pat);
//
//		for (i; i < dat_size; i++)
//	{
//			for (int j = 0; j < pat_size; j++)
//			{
//				if (pat[j] != data[i + j])
//				{
//					//cout << data << endl;
//					//for (int k = 0; k < i + j; k++)
//					//	cout << " ";
//					//cout << "|"<<endl;
//					//for (int k = 0; k < i; k++)
//					//	cout << " ";
//					//cout << pat << endl;
//					//cout << endl;
//					goto CON;
//				}
//				else
//				{
//					//cout << data << endl;
//					//for (int k = 0; k < i + j; k++)
//					//	cout << " ";
//					//cout << "+" << endl;
//					//for (int k = 0; k < i ; k++)
//					//	cout << " ";
//					//cout << pat << endl;
//					//cout << endl;
//				}
//
//			}
//			break;
//		CON:continue;
//	
//
//	}
//		timecheck.stop();
//cout << "brute_force 총 걸린 시간 " << timecheck.getElapsedTime() << "ms" << endl;
//		if (i < dat_size - 1)
//
//			return i + 1;
//		else
//			return -1;
//}


















//파일 내의 모든 바이트에 5를 더하도록 해서 부호화(encoding) 하여라
//사용자가 입력 파일 이름과 출력 파일 이름을 입력하면 입력 파일의 암호화된
//버전을 출력 파일로 저장하는 프로그램을 작성
//input source filename : source.txt
//input encoding filename : encoding.txt
//암호화된 파일으 복호화(decoding)하는 프로그램을 작성 사용자가 입력 파일
//이름과 출력 파일 이름을 입력하면 입력 파일의 암호가 풀린 출력 파일로 저장하는
//프로그램을 작성

//#include <iostream>
//#include <fstream>
//#include <iomanip>
//#include <cstdlib>
//#include <string>
//#include <filesystem>
//using namespace std;
//
//int main()
//{
//	cout << fixed;
//	cout << "Input source filename : ";
//	string sourceFileName;
//	cin >> sourceFileName;
//
//	cout << "Input encoding filename : ";
//	string encodingFileName;
//	cin >> encodingFileName;
//
//	ifstream fin;
//	fin.open(sourceFileName, ios_base::in | ios_base::binary);
//	long long orgSize;
//
//	fin.seekg(0, fin.end);			//끝으로가서
//	orgSize = fin.tellg();			//파일 길이 알아오기
//	cout << "Entire file size : " << orgSize << endl;
//	fin.seekg(0, ios::beg);		//다시 처음으로와서
//
//	char **ptr = nullptr;		//전체크기*6 메모리에 저장 or 2중으로?
//	ptr = new char*[orgSize];
//	for (int i = 0; i <orgSize ; i++)
//		ptr[i] = new char[6];
//
//	for(int i =0; i<orgSize; i++)
//	fin.read(ptr[i], 1);
//		fin.close();
//
//	ofstream fout;
//	fout.open(encodingFileName, ios_base::out | ios_base::binary);
//	for (int i = 0; i < orgSize; i++)
//	{
//		fout.write(ptr[i], 6);
//	}
//	fout.close();
//
//
//	for (int i = 0; i < orgSize; i++)
//		delete[] ptr[i];
//	delete[] ptr;
//
//	////////////////////////복호화//////////////////////////////
//	cout << "Input encoded filename : ";
//	string encodedFileName;
//	cin >> encodedFileName;
//
//	cout << "Input decoding filename : ";
//	string decodingFileName;
//	cin >> decodingFileName;
//
//	ifstream fin;
//	fin.open(encodedFileName, ios_base::in | ios_base::binary);
//	long long orgSize;
//
//	fin.seekg(0, fin.end);			//끝으로가서
//	orgSize = fin.tellg();			//파일 길이 알아오기
//	cout << "Entire file size : " << orgSize << endl;
//	fin.seekg(0, ios::beg);		//다시 처음으로와서
//
//	char **buf = nullptr;		
//	buf = new char*[orgSize/6];
//	for (int i = 0; i < orgSize/6; i++)
//		buf[i] = new char[6];
//
//	for (int i = 0; i < orgSize; i++)
//		fin.read(buf[i], 6);
//	fin.close();
//
//	ofstream fout;
//	fout.open(encodingFileName, ios_base::out | ios_base::binary);
//	for (int i = 0; i < orgSize; i++)
//	{
//		fout.write(buf[i], 1);
//	}
//	fout.close();
//
//
//	for (int i = 0; i < orgSize; i++)
//		delete[] buf[i];
//	delete[] buf;
//
//	return 0;
//}






//#include <iostream>
//#include "stopwatch.h"
//using namespace std;
//
//int brute_force(const char data[], const char pat[]);
//int kmp(const char data[], const char pat[]);
//
//int main()
//{
//	char *data = new char[100000000];
//	char *pattern = new char[100];
//	srand((unsigned)time(0));
//	cout << "데이터 입력 : ";
//	for (int i = 0; i < 100000000; i++)
//	{
//		data[i]= 'a' + rand() % 26;
//		//cout << data[i];
//	}
//
//	//char *data = new char[10000];
//	//char *pattern = new char[100];
//	//srand((unsigned)time(0));
//	//cout << "데이터 입력 : ";
//	//cin >> data;	
//		cout <<endl<< "패턴 입력 : ";
//		cin >> pattern;
//	int bn = brute_force(data, pattern);
//
//	if (bn != -1)
//		cout << bn << "번째에서 발견!"<<endl;
//	else
//		cout << "발견하지 못했습니다!"<<endl;
//	
//	int kn = kmp(data, pattern);
//	if (kn != -1)
//		cout << kn << "번째에서 발견!"<<endl;
//	else
//		cout << "발견하지 못했습니다!"<<endl;
//
//
//	delete[] data;
//	delete[] pattern;
//		return 0;
//}
//
//int kmp(const char data[], const char pat[])
//{
//	stopwatch timecheck;
//	timecheck.start();
//
//	int i = 0;
//	int dat_size = strlen(data);
//	int pat_size = strlen(pat);
//
//	for (i; i < dat_size; i++)
//	{
//		int cnt = 0; //반복되는 경우 넘기기 위한 카운트
//		for (int j = 0; j < pat_size; j++)
//		{
//			
//			if (pat[j] != data[i + j])
//			{
//				///////////////////출력부////////////////
//				//cout << data << endl;
//				//for (int k = 0; k < i + j; k++)
//				//	cout << " ";
//				//cout << "|" << endl;
//				//for (int k = 0; k < i; k++)
//				//	cout << " ";
//				//cout << pat << endl;
//				//cout << endl;
//				///////////////////////////////////////
//				if(cnt!=0)
//				i += cnt-1; //불일치하는경우 카운트를 더해서 건너뜀/ 다음 i++고려해서 -1;
//				goto CON;
//			}
//			else
//			{
//				cnt++;	//일치하는 경우 카운트++;
//				//////////////출력부////////////////
//				//cout << data << endl;
//				//for (int k = 0; k < i + j; k++)
//				//	cout << " ";
//				//cout << "+" << endl;
//				//for (int k = 0; k < i; k++)
//				//	cout << " ";
//				//cout << pat << endl;
//				//cout << endl;
//				//////////////////////////////////
//			}
//
//		}
//		break;
//	CON:continue;
//
//	}
//	timecheck.stop();
//	cout << "kmp 총 걸린 시간 " << timecheck.getElapsedTime() << "ms" << endl;
//	if (i < dat_size - 1)
//
//		return i + 1;
//	else
//		return -1;
//}
//
//int brute_force(const char data[], const char pat[])
//{
//	stopwatch timecheck;
//timecheck.start();
//
//	int i = 0;
//	int dat_size = strlen(data);
//	int pat_size = strlen(pat);
//
//		for (i; i < dat_size; i++)
//	{
//			for (int j = 0; j < pat_size; j++)
//			{
//				if (pat[j] != data[i + j])
//				{
//					//cout << data << endl;
//					//for (int k = 0; k < i + j; k++)
//					//	cout << " ";
//					//cout << "|"<<endl;
//					//for (int k = 0; k < i; k++)
//					//	cout << " ";
//					//cout << pat << endl;
//					//cout << endl;
//					goto CON;
//				}
//				else
//				{
//					//cout << data << endl;
//					//for (int k = 0; k < i + j; k++)
//					//	cout << " ";
//					//cout << "+" << endl;
//					//for (int k = 0; k < i ; k++)
//					//	cout << " ";
//					//cout << pat << endl;
//					//cout << endl;
//				}
//
//			}
//			break;
//		CON:continue;
//	
//
//	}
//		timecheck.stop();
//cout << "brute_force 총 걸린 시간 " << timecheck.getElapsedTime() << "ms" << endl;
//		if (i < dat_size - 1)
//
//			return i + 1;
//		else
//			return -1;
//}













//용량이 큰 파일을 작은 용량으로 분할해서 작은 단위의 파일로 나누는 유틸리티 프로그램을 작성
//사용자로부터 소스 파일을 입력받은 후 각각 분할된 작은 파일의 바이트 값을 입력받아
//해당 크기만큼 파일로 분할한다.
//enter file name : test.zip
//enter file size : 1024
//-> file test0.div
//file test1.div ... split done!
//문2. 사용자로부터 분할된 소스파일의 개수, 소스파일의 이름, 목적 파일의 이름을 입력받아
//새로운 하나의 파일로 조합하는 프로그램을 작성
//enter file number : 2
//enter source file name 1 :Test0.div, Test1.div
//enter target filename : Temp.zip
//.... combine done!


//#include <iostream>
//#include <fstream>
//#include <iomanip>
//#include <cstdlib>
//#include <string>
//#include <filesystem>
//using namespace std;
//
//int main()
//{
//	cout << fixed;
//	int fileNumber;
//	cout << "Enter file number : ";
//	cin >> fileNumber;
//	string *filename = new string[fileNumber];
//	for (int i = 0; i < fileNumber; i++)
//	{
//		cout << "Enter source file name : ";
//			cin >> filename[i];
//			ifstream fin;
//			fin.open(filename[i], ios_base::in | ios_base::binary);
//
//			char **buf = nullptr;
//			buf = new char*[fileNumber];
//			for (int i = 0; i < fileNumber; i++)
//				buf[i] = new char[fileNumber];
//	}
//	
//	string TargetName;
//	cout << "Enter target file name : ";
//	cin >> TargetName;
//
//
//	delete[] filename;
//}

//#include <iostream>
//#include <fstream>
//#include <iomanip>
//#include <cstdlib>
//#include <string>
//#include <filesystem>
//using namespace std;
//
//int main()
//{
//	cout << fixed;
//	cout << "Enter file name : ";
//	string fileName;
//	cin >> fileName;
//
//	cout << "Enter file size : ";
//	long long fileSize;
//	cin >> fileSize;
//
//	ifstream fin;
//	fin.open(fileName, ios_base::in | ios_base::binary);
//	long long orgSize;
//	long long div;
//
//
//		fin.seekg(0, fin.end);			//끝으로가서
//		orgSize = fin.tellg();			//파일 길이 알아오기
//		cout << "Entire file size : " << orgSize << endl;
//		div = orgSize / fileSize;
//		cout << "Number of files : " << div+1 << endl;
//		fin.seekg(0, ios::beg);		//다시 처음으로와서
//		char *buf = new char[orgSize]; //전체크기 메모리에 저장
//		fin.read(buf, orgSize);
//
//		fin.close();
//
//	for (int i = 0; i < div + 1; i++)
//	{
//		ofstream fout;
//		fout.open("Test" + to_string(i+1) + ".txt", ios_base::out | ios_base::binary);
//		if (i != div)
//			fout.write(buf + i * fileSize, fileSize);
//		else
//			fout.write(buf + i * fileSize, orgSize%fileSize);
//		fout.close();
//	}
//	delete[] buf;
//}



//#include <iostream>
//
//using namespace std;
//
//int brute_force(const char data[], const char pat[]);
//int main()
//{
//	char *data = new char[1000];
//	char *pattern = new char[100];
//
//	cout << "데이터 입력 : ";
//		cin >> data;
//		cout << "패턴 입력 : ";
//		cin >> pattern;
//	int n = brute_force(data, pattern);
//	if (n != -1)
//		cout << n << "번째에서 발견!";
//	else
//		cout << "발견하지 못했습니다!";
//
//	delete[] data;
//	delete[] pattern;
//		return 0;
//}
//
//int brute_force(const char data[], const char pat[])
//{
//	int i = 0;
//	int dat_size = strlen(data);
//	int pat_size = strlen(pat);
//
//		for (i; i < dat_size; i++)
//	{
//			for (int j = 0; j < pat_size; j++)
//			{
//				if (pat[j] != data[i + j])
//				{
//					cout << data << endl;
//					for (int k = 0; k < i + j; k++)
//						cout << " ";
//					cout << "|"<<endl;
//					for (int k = 0; k < i; k++)
//						cout << " ";
//					cout << pat << endl;
//					cout << endl;
//					goto CON;
//				}
//				else
//				{
//					cout << data << endl;
//					for (int k = 0; k < i + j; k++)
//						cout << " ";
//					cout << "+" << endl;
//					for (int k = 0; k < i ; k++)
//						cout << " ";
//					cout << pat << endl;
//					cout << endl;
//				}
//
//			}
//			break;
//		CON:continue;
//	
//
//	}
//		if (i < dat_size - 1)
//
//			return i + 1;
//		else
//			return -1;
//}





//#define _CRT_SECURE_NO_WARNINGS
//
//#include <iostream>
//
//using namespace std;
//
//int brute_force(const char data[], const char pat[]);
//int main()
//{
//	char *data = new char[1000];
//	char *pattern = new char[100];
//
//	cout << "데이터 입력 : ";
//	cin >> data;
//	cout << "패턴 입력 : ";
//	cin >> pattern;
//	int n = brute_force(data, pattern);
//	if (n != -1)
//		cout << n << "번째에서 발견!";
//	else
//		cout << "발견하지 못했습니다!";
//
//	delete[] data;
//	delete[] pattern;
//	return 0;
//}
//
//int brute_force(const char data[], const char pat[])
//{
//	int i = 0;
//	int dat_size = strlen(data);
//	int pat_size = strlen(pat);
//
//	for (i; i < dat_size; i++)
//	{
//		for (int j = 0; j < pat_size; j++)
//		{
//			if (pat[j] != data[i + j])
//				goto CON;
//
//		}
//		break;
//	CON:continue;
//
//
//	}
//	if (i < dat_size - 1)
//
//		return i + 1;
//	else
//		return -1;
//}


//int main()
//{
//	char data[100] = "akfnelingolenjenvaejnfabcaskfeqlihng";
//	char abc[100] = "abc";
//	int i = 0;
//	for (i = 0; i < 100; i++)
//	{
//		if (abc[i] != data[i])
//			continue;
//		if (abc[i + 1] != data[i + 1])
//			continue;
//		if (abc[i + 2] != data[i + 2])
//			continue;
//		else
//			break;
//	}
//
//	cout << i - 2 << "번째에서 발견!" << endl;
//	return 0;
//}

//#include <iostream>
//#include "stopwatch.h"
//
//using namespace std;
//void dosu(int *str, int n, int score);
//int main()
//{
//
//	//srand((unsigned)time(0));
//	int n;
//	int score;
//	cout << "입력받을 점수 개수 : ";
//	cin >> n;
//	cout << "최대 점수 : ";
//		cin >> score;
//	cout << "임의 점수 입력 : ";
//	int *str = new int[n];
//	for (int i = 0; i < n; i++)
//		cin >> str[i];
//	dosu(str, n, score);
//
//	delete[] str;
//
//
//	return 0;
//}
//void dosu(int *str, int n, int score)
//{
//	stopwatch timecheck;
//	timecheck.start();
//	int cnt = 0;
//	int swap = 0;
//	int *arr = new int[score+1] {};
//	for (int i = 0; i < n; i++)
//	{
//		(arr[str[i]])++;
//	}
//
//
//
//
//	timecheck.stop();
//	cout << endl;
//	for (int i = 0; i < score+1; i++)
//		cout << "arr["<<i<<"] : "<< arr[i] <<endl;
//	for (int i = 0; i < score+1; i++)
//	{
//		
//			while(arr[i]--)
//			cout << i << " ";
//		
//	}
//	cout << endl << "총 " << cnt << "번 시도" << endl;
//	cout << "총 " << swap << "번 교환" << endl;
//	cout << "총 걸린 시간 " << timecheck.getElapsedTime() << "ms" << endl;
//	delete[] arr;
//}






//#include <iostream>
//#include <fstream>
//#include <iomanip>
//#include <cstdlib>
//
//const int LIM = 20;
//inline void eatline() { while (std::cin.get() != '\n') continue; }
//struct planet
//{
//	char name[20];
//	double population;
//	double g;
//};
//const char *file = "planets.dat";
//int main()
//{
//	using namespace std;
//	planet pl;
//	cout << fixed;
//
//	ifstream fin;
//	fin.open(file, ios_base::in | ios_base::binary);
//	int ct = 0;
//	if (fin.is_open())
//	{
//		fin.seekg(0);
//		cout << file << " 파일의 현재 내용은 다음과 같습니다:\n";
//		while (fin.read((char *)&pl, sizeof pl))
//		{
//			cout << ct++ << ": " << setw(LIM) << pl.name << ": "
//				<< setprecision(0) << setw(12) << pl.population
//				<< setprecision(2) << setw(6) << pl.g << endl;
//		}
//		if (fin.eof())
//			fin.clear();
//		else
//		{
//			cerr << file << " 파일을 읽다가 에러 발생.\n";
//			exit(EXIT_FAILURE);
//		}
//	}
//	else
//	{
//		cerr << file << " 파일을 열 수 없습니다. \n";
//		exit(EXIT_FAILURE);
//	}
//	cout << "수정할 레코드 번호를 입력하십시오: ";
//	long rec;
//	cin >> rec;
//	eatline();
//	if (rec < 0 || rec >= ct)
//	{
//		cerr << "잘못된 레코드 번호입니다. 종료.\n";
//		exit(EXIT_FAILURE);
//	}
//	streampos place = rec * sizeof pl;
//	fin.seekg(place);
//	if (fin.fail())
//	{
//		cerr << "레코드를 찾다가 에러 발생.\n";
//		exit(EXIT_FAILURE);
//	}
//	fin.read((char *)&pl, sizeof pl);
//	cout << "현재 레코드의 내용 \n";
//	cout<<rec<<": "<<setw(LIM) <<pl.name<<": "
//		<< setprecision(0) << setw(12) << pl.population
//		<< setprecision(2) << setw(6) << pl.g << endl;
//	if (fin.eof())
//		fin.clear();
//
//	cout << "행성의 이름을 입력하십시오(끝내려면 빈 줄 입력) : \n";
//	cin.get(pl.name, LIM);
//		eatline();
//		cout << "행성의 인구를 입력하십시오: ";
//		cin >> pl.population;
//		cout << "행성의 중력가속도를 입력하십시오: ";
//		cin >> pl.g;
//		fin.seekp(place);
//		fin.write((char *)&pl, sizeof pl) << flush;
//		if (fin.fail())
//		{
//			cerr << "쓰다가 에러 발생\n";
//			exit(EXIT_FAILURE);
//		}
//	fout.close();
//
//	fin.clear();
//	fin.open(file, ios_base::in | ios_base::binary);
//	if (fin.is_open())
//	{
//		cout << file << "파일의 개정된 내용은 다음과 같습니다.:\n";
//		while (fin.read((char *) &pl, sizeof pl))
//		{
//		cout << setw(20) << pl.name << ": "
//			<< setprecision(0) << setw(12) << pl.population
//			<< setprecision(2) << setw(6) << pl.g << endl;
//		}
//		fin.close();
//
//	}
//	cout << "프로그램을 종료합니다.\n";
//	return 0;
//}





//#include <iostream>
//#include <fstream>
//#include <string>
//#include <cstdlib>
//
//
//const char * file = "guests.txt";
//int main()
//{
//	using namespace std;
//	char ch;
//
//	ifstream fin;
//	fin.open(file);
//	if (fin.is_open())
//	{
//		cout << file << "파이르이 현재 내용은 다음과 같습니다:\n";
//		while (fin.get(ch))
//			cout << ch;
//		fin.close();
//	}
//	ofstream fout(file, ios_base::out | ios_base::app);
//	if (!fout.is_open())
//	{
//		cerr << "출력을 위해 " << file << " 파일을 열 수 없습니다.\n";
//		exit(EXIT_FAILURE);
//
//	}
//	cout << "새로운 손님 이름들을 입력하십시오(끝내려면 빈 줄 입력): \n";
//	string name;
//	while (getline(cin, name) && name.size() > 0)
//	{
//		fout << name << endl;
//	}
//	fout.close();
//
//	fin.clear();
//	fin.open(file);
//	if (fin.is_open())
//	{
//		cout << file << " 파일의 개졍된 내용은 다음과 같습니다:\n";
//		while (fin.get(ch))
//			cout << ch;
//		fin.close();
//	}
//	cout << "프로그램을 종료합니다.\n";
//	return 0;
//}
//
//
















////dynamic cast
////RTTI run time type information
//#include <iostream>
//#include <math.h>
//const double PI = 3.141592;
//using namespace std;
////순수 가상함수
//class Shape {
//public:
//	virtual double GetArea() const = 0;
//	virtual void Resize(double k) = 0;
//};
//class Circle : public Shape{
//public:
//	Circle(double r) :r(r) {}
//	double GetArea() const {
//		return PI * r*r;
//	}
//	void Resize(double k) {
//		r *= k;
//	}
//private:
//	double r;
//};
//
//class Rectangel : public Shape{
//public:
//	Rectangel(double a, double b) : a(a), b(b) {}
//	double GetArea() const {
//		return a * b;
//	}
//	void Resize(double k) {
//		a *= k;
//		b *= k;
//	}
//	double GetDiag() const {
//		return sqrt(a*a + b * b);
//	}
//private:
//	double a, b;
//};
//
//int main()
//{
//	Shape *shapes[] = {
//		new Circle(1),
//		new Rectangel(1, 2)
//	};
//	for (Shape *s : shapes)
//		s->Resize(2);
//	for (int i = 0; i<2; i++)
//	{
//		cout << "도형의 넓이 : "<<shapes[i]->GetArea() << endl;
//		Rectangel *r = dynamic_cast<Rectangel*>(shapes[i]);
//		if (r != NULL)
//		{
//			cout << "대각선의 길이 : " << r->GetDiag() << endl;
//		}
//	}
//	for (Shape *s : shapes) { delete s; }
//}


//#include <iostream>
//using namespace std;
//
////다운캐스팅 static
//
//class Base {
//public :
//	int a = 1;
//};
//class Drv1 : public Base {
//public:
//	float b = 3.14;
//	void f() {
//		cout << "Drv::f()" << endl;
//		cout << b << endl;
//	}
//};
//class Drv2 : public Base {
//public:
//	int c = 3;
//	void f() {
//		cout << "Drv2::f()" << endl;
//		cout << c << endl;
//	}
//};
//int main()
//{
//	Base *b = new Drv1;
//	int *a = new int(5);
//	Drv2 *d2 = static_cast<Drv2*>(b);
//	d2->f();
//	delete a;
//	delete b;
//}









//#include <iostream>
//using namespace std;
//
////업캐스팅
//class Animal {
//public:
//	float xpos=1;
//	float ypos=2;
//};
//void printAnimals(Animal **a, int n) {
//	for (int i = 0; i < n; i++)
//	{
//		cout << "(" << a[i]->xpos << ", " << a[i]->ypos << ")" << endl;
//	}
//}
//class FlyingAnimal : public Animal {
//public:
//	float zpos = 3;
//};
//int main()
//{
//	Animal **a = new Animal*[10];
//	for (int i = 0; i < 10; i++)
//	{
//		a[i] = new FlyingAnimal;
//	}
//	printAnimals(a, 10);
//	for (int i = 0; i < 10; i++) {
//		delete a[i];
//	}
//	delete[]a;
//}




//using namespace std;
////가상소멸자
//class Ice {
//public:
//	Ice() { cout << "Ice()" << endl; }
//	~Ice() { cout << "~Ice()" << endl; }
//};
//class Pat {
//public:
//	Pat() { cout << "Pat()" << endl; }
//	~Pat() { cout << "~Pat()" << endl; }
//};
//class Bingsoo {
//public :
//	Bingsoo() { cout << "Bingsoo() " << endl; 
//	ice = new Ice;
//	}
//	virtual ~Bingsoo() { cout << "~Bingsoo() " << endl;
//	delete ice;
//	}
//private:
//	Ice *ice;
//};
//class PatBingsoo : public Bingsoo {
//public :
//	PatBingsoo() { cout << "PatBingsoo() " << endl; 
//	pat = new Pat;
//	}
//	~PatBingsoo() { cout << "~PatBingsoo() " << endl;
//	delete pat;
//	}
//private:
//	Pat *pat;
//};
//int main()
//{
//	Bingsoo *p = new PatBingsoo;
//	delete p;
//}


//#include <iostream>
//
//const double PI = 3.141592;
//using namespace std;
////순수 가상함수
//class Shape {
//public:
//	virtual double GetArea() = 0;
//	virtual void Resize(double f) = 0;
//};
//class Circle : public Shape{
//public:
//	Circle(double r) :r(r) {}
//	double GetArea() {
//		return PI * r*r;
//	}
//	void Resize(double f) {
//		r *= f;
//	}
//private:
//	double r;
//};
//
//class Rectangel : public Shape{
//public:
//	Rectangel(double a, double b) : a(a), b(b) {}
//	double GetArea() {
//		return a * b;
//	}
//	void Resize(double f) {
//		a *= f;
//		b *= f;
//	}
//private:
//	double a, b;
//};
//
//int main()
//{
//	Shape *shapes[] = {
//		new Circle(10),
//		new Rectangel(20, 30)
//	};
//	for (Shape *s : shapes)
//		s->Resize(2);
//	for (Shape *s : shapes)
//		cout << s->GetArea() << endl;
//	for (Shape *s : shapes) { delete s; }
//}

//#define _CRT_SECURE_NO_WARNINGS
//#include <iostream>
//#include "stopwatch.h"
//
//using namespace std;
//void heap(int *str, int n);
//int main()
//{
//
//	//srand((unsigned)time(0));
//	int n;
//	cout << "입력받을 정수 개수 : ";
//	cin >> n;
//	cout << "임의 수열 입력 : ";
//	int *str = new int[n];
//	for (int i = 0; i < n; i++)
//		cin >> str[i];
//	heap(str, n);
//
//	delete[] str;
//
//
//	return 0;
//}
//void heap(int *str, int n)
//{
//	stopwatch timecheck;
//	timecheck.start();
//	int cnt = 0;
//	int swap = 0;
//	//부모 str[(i-1)/2] , 자식 str[i*2+1], str[i*2+2]
//	int orgN = n;
//
//
//while(1)
//{
//	//층수 구하기 
//	int floor = 0;
//	int n_floor = n;
//	while (n_floor != 0)
//	{
//		floor++;
//		n_floor /= 2;
//	}
//	//힙 만들기 (층수만큼 반복)
//	for (int k = 0; k < floor; k++)
//	{
//		cnt++;
//		for (int i = 1; i < n; i += 2)
//		{
//			cnt++;
//			int p = str[(i - 1) / 2];
//			int cl = str[i * 2 + 1];
//			int cr = str[i * 2 + 2];
//			if (i + 1 != n || (n - 1) % 2 == 0)		//마지막 요소가 아니거나 짝이 있는경우
//			{
//				if (p < str[i] || p < str[i + 1])	//부모가 자식보다 작으면
//				{
//					if (str[i] > str[i + 1])	//자식중에 큰거랑 교환
//					{
//						str[(i - 1) / 2] = str[i];
//						str[i] = p;
//						swap++;
//					}
//					else
//					{
//						str[(i - 1) / 2] = str[i + 1];
//						str[i + 1] = p;
//						swap++;
//					}
//				}
//
//			}
//			else		//마지막 요소이면서 짝이 없는 경우
//			{
//				if (p < str[i]) //부모가 자식보다 작으면 교환
//				{
//					str[(i - 1) / 2] = str[i];
//					str[i] = p;
//					swap++;
//				}
//
//			}
//		}
//	}
//
//	//힙에서 가장 큰 값 꺼내 옮기고 마지막 요소를 다시 올려놓기
//	int temp = str[0];
//	str[0] = str[n - 1];
//	str[n - 1] = temp;
//	n--; //배열 줄여서 다시 루프
//	if (n == 1) break; //n=1이면 종료
//}
//
//
//	timecheck.stop();
//	cout << endl;
//	for (int i = 0; i < orgN; i++)
//		cout << str[i] << " ";
//	cout << endl << "총 " << cnt << "번 시도" << endl;
//	cout << "총 " << swap << "번 교환" << endl;
//	cout << "총 걸린 시간 " << timecheck.getElapsedTime() << "ms" << endl;
//
//}





//#include <iostream>
//#include <string>
//
//using namespace std;
//
//class Image {
//public:
//	operator string() {
//		return "사진";
//	}
//};
//class Message {
//public:
//	Message(int sendTime, string sendName)
//		:sendTime(sendTime), sendName(sendName) {}
//
//	int GetSendTime() const { return sendTime; }
//	string GetSendName() const { return sendName; }
//	virtual string GetContent() const { return ""; }
//private:
//	int sendTime;
//	string sendName;
//};
//class TextMessage : public Message {
//public:
//	TextMessage(int sendTime, string sendName, string text)
//		: Message(sendTime, sendName), text(text) {}
//	string GetText() const { return text; }
//	string GetContent() const { return text; }
//private:
//	string text;
//};
//class ImageMessage : public Message {
//public:
//	ImageMessage(int sendTime, string sendName, Image *image)
//		:Message(sendTime, sendName), p_image(image) {}
//	Image *GetImage() const { return p_image; }
//	string GetContent() const { return (string)*p_image; }
//private:
//	Image *p_image;
//};
//
//void printMessage(const Message &m) {
//	cout << "보낸 시간 : " << m.GetSendTime() << endl;
//	cout << "보낸 사람 : " << m.GetSendName() << endl;
//	cout << "  내  용  : " << m.GetContent() << endl;
//	cout << endl;
//}
//
//int main()
//{
//	Image *p_dogImage = new Image();
//
//	Message *messages[] = {
//
//	new TextMessage(10, "두들", "안녕"),
//	new TextMessage(11, "두들", "안녕"),
//	new TextMessage(12, "두들", "안녕"),
//	new ImageMessage(20, "두들", p_dogImage)
//	};
//	for (Message *m : messages) {
//		printMessage(*m);
//	}
//
//
//
//	delete p_dogImage;
//}





//#include <iostream>
//
//using namespace std;
//
//class Weapon {
//public:
//	Weapon(int power) : power(power) {
//		cout << "Weapon(int)" << endl;
//	}
//	virtual void Use() {
//		cout << "Weapon::Use()" << endl;
//	}
//protected:
//	int power;
//};
//class Sword : public Weapon {
//public:
//	Sword(int power) : Weapon(power) {
//		cout << "Sowrd(int)" << endl;
//	}
//	void Use() {
//		cout << "Sword::Use()" << endl;
//		Swing();
//	}
//private:
//	void Swing() {
//		cout << "Swing sword" << endl;
//	}
//};
//class Magic : public Weapon {
//public:
//	Magic(int power, int manaCost) : Weapon(power), manaCost(manaCost) {
//		cout << "Magic(int, int)" << endl;
//	}
//	void Use() {
//		cout << "Magic::Use()" << endl;
//		Cast();
//	}
//private:
//	void Cast() {
//		cout << "Cast Magic" << endl;
//	}
//	int manaCost;
//};
//int main()
//{
//	Sword mySword(10);
//	Magic myMagic(15, 7);
//
//	mySword.Use();
//	myMagic.Use();
//
//	Weapon *currentWeapon;
//
//	currentWeapon = &mySword;
//
//	currentWeapon->Use();
//	currentWeapon = &myMagic;
//	currentWeapon->Use();
//}



//#include <iostream>
//
//int main()
//{
//	using std::cout;
//	using std::endl;
//	using std::ios_base;
//
//	int temperature = 63;
//	cout << "오늘의 수온 ";
//	cout.setf(ios_base::showpos);
//	cout << temperature << endl;
//
//	cout << "프로그래머들에게 그 값은\n";
//	cout << std::hex << temperature<<endl;
//	cout.setf(ios_base::uppercase);
//		cout.setf(ios_base::showbase);
//		cout << "또는\n";
//		cout << temperature << endl;
//		cout << true << "!의 값은";
//		cout.setf(ios_base::boolalpha);
//		cout << true << "이다.\n";
//		return 0;
//}


//using namespace std;
//vector<int> Lotto(int tot_num, int sel_num);
//int main()
//{
//
//	int tot_num, sel_num;
//	cout << "복권번호 자리수 : ";
//cin >> tot_num;
//	cout << "선택가능 자리수 : ";
//	cin >> sel_num;
//	vector<int> winners;
//	winners = Lotto(tot_num, sel_num);
//	cout << "당첨번호 : ";
//	vector<int>::iterator iter;
//	for (iter = winners.begin(); iter != winners.end(); iter++)
//		cout << *iter << " ";
//		cout << endl;
//	return 0;
//}
//vector<int> Lotto(int tot_num, int sel_num)
//{
//	vector<int> Lotto;
//	for (int i = 0; i < tot_num; i++)
//		Lotto.push_back(i+1);
//	random_shuffle(Lotto.begin(), Lotto.end());
//	Lotto.resize(6);
//	return Lotto;
//}
//#include <iostream>
//#include <string>
//#include <vector>
//#include <set>
//#include <map>
//#include <iterator>
//#include <algorithm>
//#include <cctype>
//using namespace std;
//
//char toLower(char ch) { return tolower(ch); }
//string & ToLower(string & st);
//void display(const string & s);
//
//int main()
//{
//	vector<string> words;
//	cout << "단어들을 입력하십시오 (끝내려면 quit) : \n";
//	string input;
//	while (cin >> input && input != "quit");
//	words.push_back(input);
//
//	cout << "다음과 같은 단어들을 입력하셨습니다.\n";
//	for_each(words.begin(), words.end(), display);
//	cout << endl;
//
//	set<string> wordset;
//	transform(words.begin(), words.end(),
//		insert_iterator<set<string> >(wordset, wordset.begin()), ToLower);
//	cout << "\n단어들의 알파벳순 리스트: \n";
//	for_each(wordset.begin(), wordset.end(), display);
//	cout << endl;
//
//	map<string, int> wordmap;
//	set<string>::iterator si;
//	for (si = wordset.begin(); si != wordset.end(); si++)
//		wordmap[*si] = count(words.begin(), words.end(), *si);
//
//	cout << "\n단어별 빈도:\n";
//	for (si = wordset.begin(); si != wordset.end(); si++)
//		cout << *si << ": " << wordmap[*si] << endl;
//	return 0;
//}
//string & ToLower(string & st)
//{
//	transform(st.begin(), st.end(), st.begin(), toLower);
//	return st;
//}
//void  display(const string & s)
//{
//	cout << s << " ";
//}

//#include <iostream>
//#include <list>
//#include <algorithm>
//
//void Show(int);
//const int LIM = 10;
//int main()
//{
//	using namespace std;
//	int ar[LIM] = { 4, 5, 4, 2, 2, 3, 4, 8, 1, 4 };
//	list<int> la(ar, ar + LIM);
//	list <int> lb(la);
//
//	cout << "오리지널 리스트의 내용 : \n\t";
//	for_each(la.begin(), la.end(), Show);
//	cout << endl;
//	cout << sizeof(la) << endl;
//	la.remove(4);
//	cout << "remove() 메서드를 사용한 후 :\n";
//	cout << "la:\t";
//	for_each(la.begin(), la.end(), Show);
//	cout << endl;
//	cout << sizeof(la) << endl;
//	list<int> ::iterator last;
//	cout << sizeof(lb) << endl;
//	last = remove(lb.begin(), lb.end(), 4);
//	cout << "revmove() 하수를 사용한 후 : \n";
//	cout << "lb:\t";
//	cout << sizeof(lb) << endl;
//	for_each(lb.begin(), lb.end(), Show);
//	cout << endl;
//	cout << sizeof(lb) << endl;
//	lb.erase(last, lb.end());
//	cout << "erase() 메서드를 사용한 후:\n";
//	cout << "lb:\t";
//	cout << sizeof(lb) << endl;
//	for_each(lb.begin(), lb.end(), Show);
//	cout << endl;
//	return 0;
//}
//
//void Show(int v)
//{
//	std::cout << v << ' ';
//}


//#include <iostream>
//#include <list>
//#include <iterator>
//#include <algorithm>
//
//template<class T>
//class TooBig
//{
//private:
//	T cutoff;
//public:
//	TooBig(const T & t) : cutoff(t) {}
//	bool operator () (const T & v) { return v > cutoff; }
//};
//void outint(int n) { std::cout << n << " "; }
//int main()
//{
//	using std::list;
//	using std::cout;
//	using std::endl;
//	TooBig<int> f100(100);
//	int vals[10] = { 50, 100, 90, 180, 60, 210, 415, 88, 188, 201 };
//	list<int> yadayada(vals, vals + 10);
//	list<int> etcetera(vals, vals + 10);
//	cout << "원래의 리스트:\n";
//	for_each(yadayada.begin(), yadayada.end(), outint);
//	cout << endl;
//	for_each(etcetera.begin(), etcetera.end(), outint);
//	cout << endl;
//	yadayada.remove_if(f100);
//	etcetera.remove_if(TooBig<int>(200));
//	cout << "정비된 리스트:\n";
//	for_each(yadayada.begin(), yadayada.end(), outint);
//	cout << endl;
//	for_each(etcetera.begin(), etcetera.end(), outint);
//	cout << endl;
//	return 0;
//}



//#include <iostream>
//#include "stopwatch.h"
//using namespace std;
//void merge(int n, int *str);
//
//int main()
//{
//	int n;
//	cout << "입력할 배열 수 : ";
//	cin >> n;
//	int *str = new int[n];
//	cout << "임의 배열 입력 : ";
//	for (int i = 0; i < n; i++)
//		cin >> str[i];
//	merge(n, str);
//	delete[] str;
//	return 0;
//}
//void merge(int n, int *str)
//{
//	stopwatch timecheck;
//	timecheck.start();
//	int *merge = new int[n];
//	int cnt = 0;
//	int swap = 0;
//	int divcnt = 0;
//	int div=n;
//	while (div >= 2)
//	{
//		div /= 2;
//		divcnt++;
//	}
//	int gap = n / (2 * divcnt);
//	for(int i = 0; i < n / 2; i++)
//	{
//		
//	}
//	}
//	for (int i = 0; i < n / 2; i++)
//	{
//		int temp;
//		if (str[i] < temp)
//		{
//			merge[i] = str[i];
//			temp = str[n / 2 + i];
//	}
//
//	timecheck.stop();
//	cout << endl;
//	for (int i = 0; i < n; i++)
//		cout << merge[i] << " ";
//	cout << endl << "총 " << cnt << "번 시도" << endl;
//	cout << "총 " << swap << "번 교환" << endl;
//
//	delete[] merge;
//	cout << "총 걸린 시간 " << timecheck.getElapsedTime() << "ms" << endl;
//}







//#include <iostream>
//#include <string>
//#include <map>
//#include <algorithm>
//
//typedef int KeyType;
//typedef std::pair<const KeyType, std::string> Pair;
//typedef std::multimap<KeyType, std::string> Mapcode;
//
//int main()
//{
//	using namespace std;
//	Mapcode codes;
//
//	codes.insert(Pair(415, "SF"));
//	codes.insert(Pair(510, "OA"));
//	codes.insert(Pair(718, "BK"));
//	codes.insert(Pair(415, "SR"));
//	codes.insert(Pair(510, "BU"));
//	cout << "지역 코드가 415 인 도시 수 : "
//		<< codes.count(415) << endl;
//	cout << "지역 코드가 718인 도시 수: "
//		<< codes.count(718) << endl;
//	cout << "지역코드 도시\n";
//	Mapcode::iterator it;
//	for (it = codes.begin(); it != codes.end(); ++it)
//		cout << " " << (*it).first << " " << (*it).second << endl;
//
//	pair<Mapcode::iterator, Mapcode::iterator> range = codes.equal_range(718);
//	cout << "지역 코드가 718인 도시들: \n";
//	for (it = range.first; it != range.second; ++it)
//		cout << (*it).second << endl;
//
//	return 0;
//}


//#include <iostream>
//#include <string>
//#include <set>
//#include <algorithm>
//#include <iterator>
//
//int main()
//{
//	using namespace std;
//	const int N = 6;
//	string s1[N] = { "buffon", "gerrard", "Lebrone", "curry", "for", "paul" };
//	string s2[N] = { "westbrook", "pujols", "mama", "mamba", "for", "sexy" };
//	set <string> A(s1, s1 + N);
//	set<string> B(s2, s2 + N);
//	ostream_iterator<string, char> out(cout, " ");
//	cout << "집합 A: ";
//	copy(A.begin(), A.end(), out);
//	cout << endl;
//	cout << "집합 B: ";
//	copy(B.begin(), B.end(), out);
//	cout << endl;
//
//	cout << "A와 B의 합집합:\n";
//	set_union(A.begin(), A.end(), B.begin(), B.end(), out);
//	cout << endl;
//
//	cout << "A와 B의 교집합:\n";
//	set_intersection(A.begin(), A.end(), B.begin(), B.end(), out);
//	cout << endl;
//
//	cout << "A와 B의 차집합:\n";
//	set_difference(A.begin(), A.end(), B.begin(), B.end(), out);
//	cout << endl;
//
//	set<string> C;
//	cout << "집합 C:\n";
//	set_union(A.begin(), A.end(), B.begin(), B.end(), insert_iterator<set<string>>(C, C.begin()));
//	copy(C.begin(), C.end(), out);
//	cout << endl;
//
//	string s3("grungy");
//	C.insert(s3);
//	cout << "삽입한 후의 집합 C:\n";
//	copy(C.begin(), C.end(), out);
//	cout << endl;
//	cout << "특정한 범위를 표시:\n";
//	copy(C.lower_bound("ghost"), C.upper_bound("spook"), out);
//	cout << endl;
//
//	return 0;
//}

//#include <iostream>
//#include <list>
//#include <iterator>
//#include <algorithm>
//
//void outint(int n) { std::cout << n << " "; }
//
//int main()
//{
//	using namespace std;
//	list<int> one(5, 2);
//	int stuff[5] = { 1, 2, 4, 8, 6 };
//	list<int> two;
//	two.insert(two.begin(), stuff, stuff + 5);
//	int more[6] = { 6, 4, 2, 4, 6, 5 };
//	list<int> three(two);
//	three.insert(three.end(), more, more + 6);
//
//	cout << "리스트 one : ";
//	for_each(one.begin(), one.end(), outint);
//	cout << endl << "리스트 two : ";
//	for_each(two.begin(), two.end(), outint);
//	cout << endl << "리스트 three : ";
//	for_each(three.begin(), three.end(), outint);
//}


//#include <iostream>
//#include <string>
//#include <iterator>
//#include <vector>
//#include <algorithm>
//
//void output (const std::string &s) {std::cout<<s<<" " ;}
//int main()
//{
//	using namespace std;
//	string s1[4] = { "fine", "fish", "fashion", "fate" };
//	string s2[2] = { "busy", "bats" };
//	string s3[2] = { "silly", "singers" };
//	vector<string> words(4);
//	copy(s1, s1 + 4, words.begin());
//	for_each(words.begin(), words.end(), output);
//	cout << endl;
//
//
//	copy(s2, s2 + 2, back_insert_iterator<vector<string>>(words));
//	for_each(words.begin(), words.end(), output);
//	cout << endl;
//
//	copy(s3, s3 + 2, insert_iterator<vector<string>>(words, words.begin()));
//	for_each(words.begin(), words.end(), output);
//	cout << endl;
//	return 0;
//}










//#include <iostream>
//
//using namespace std;
//
//class Base
//{
//public :
//	int a = 10;
//	void Print()
//	{
//		cout << "From Base!" << endl;
//
//	}
//};
//class Derived : public Base
//{
//public:
//	void Print()
//	{
//		cout << "From Derived!" << endl;
//	}
//	int a = 20;
//};
//
//int main()
//{
//	Base b;
//	Derived d;
//	//cout << b.a << endl;
//	//cout << d.a << endl;
//	//cout << d.Base::a << endl;
//	//cout << d.Derived::a << endl;
//	//cout << d.Derived::Base::a << endl;
//	d.Print();
//	d.Base::Print();
//}


//#include <iostream>
//#include "stopwatch.h"
//
//using namespace std;
//void quick(int *str, int n);
//int main()
//{
//
//	srand((unsigned)time(0));
//	int n;
//	cout << "입력받을 정수 개수 : ";
//	cin >> n;
//	cout << "임의 수열 입력 : ";
//	int *str = new int[n];
//	for (int i = 0; i < n; i++)
//		cin >> str[i];
//	quick(str, n);
//
//	delete[] str;
//
//
//	return 0;
//}
//void quick(int *str, int n)
//{
//	stopwatch timecheck;
//	timecheck.start();
//	int cnt = 0;
//	int swap = 0;
//	
//	for (int i = 0; i < n / 2; i++)
//	{
//		int pivot = n / 2 - 1;
//		int pl = i;
//		int pr = n - 1-i;
//		if (str[pl] > str[pivot])
//		{
//			if (str[pr] < str[pivot])
//			{
//				int temp = str[pr];
//				str[pr] = str[pl];
//				str[pl] = temp;
//			}
//		}
//	}
//	int pivot = 0;
//	while (1)
//	{
//		for (int i = n - 1; i > 0; i--)
//		{
//			if (str[i] < str[pivot])
//			{
//				int temp = str[i];
//				str[i] = str[pivot];
//				str[pivot] = temp;
//				pivot = i;
//				break;
//			}
//		}
//		for(int j = 1;)
//	}
//
//	timecheck.stop();
//	cout << endl;
//	for (int i = 0; i < n; i++)
//		cout << str[i] << " ";
//	cout << endl << "총 " << cnt << "번 시도" << endl;
//	cout << "총 " << swap << "번 교환" << endl;
//
//	timecheck.stop();
//	cout << "총 걸린 시간 " << timecheck.getElapsedTime() << "ms" << endl;
//
//}





















/*
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

struct Review {
	std::string title;
	int rating;
};
bool operator<(const Review & r1, const Review & r2);
bool worseThan(const Review & r1, const Review & r2);
bool FillReview(Review & rr);
void ShowReview(const Review & rr);

int main()
{
	using namespace std;

	vector<Review> books;
	Review temp;
	while (FillReview(temp))
		books.push_back(temp);
	if (books.size() > 0)
	{
		cout << "감사합니다. 당신은 다음과 같이 "
			<< books.size() << "개의 책 등급을 입력하셨습니다.\n" << "등급\t제목\n";
		for_each(books.begin(), books.end(), ShowReview);

		sort(books.begin(), books.end());
		cout << "책 제목을 기준으로 정렬:\n등급\t제목\n";
		for_each(books.begin(), books.end(), ShowReview);

		sort(books.begin(), books.end(), worseThan);
		cout << "책 등급을 기준으로 정렬:\n등급\t제목\n";
		for_each(books.begin(), books.end(), ShowReview);

		random_shuffle(books.begin(), books.end());
		cout << "무작위 순서로 다시 배치:\n등급\t제목\n";
		for_each(books.begin(), books.end(), ShowReview);

	}
	else
		cout << "프로그램을 종료합니다.\n";
	return 0;
}
bool operator<(const Review & r1, const Review & r2)
{
	if (r1.title < r2.title)
		return true;
	else if (r1.title == r2.title && r1.rating < r2.rating)
		return true;
	else
		return false;
}
bool worseThan(const Review & r1, const Review & r2)
{
	if (r1.rating < r2.rating)
		return true;
	else
		return false;
}
bool FillReview(Review & rr)
{
	std::cout << "책 제목을 입력하십시오(끝내려면 quit를 입력): ";
	std::getline(std::cin, rr.title);
	if (rr.title == "quit")
		return false;
	std::cout << "책 등급(0-10을 입력하십시오: ";
	std::cin >> rr.rating;
	if (!std::cin)
		return false;
	while (std::cin.get() != '\n')
		continue;
	return true;
}
void ShowReview(const Review & rr)
{
	std::cout << rr.rating << "\t" << rr.title << std::endl;
}



#include <iostream>
#include <string>
#include <vector>

struct Review {
	std::string title;
	int rating;
};
bool FillReview(Review & rr);
void ShowReview(const Review & rr);

int main()
{
	using std::cout;
	using std::vector;
	vector<Review> books;
	Review temp;
	while (FillReview(temp))
		books.push_back(temp);
	int num = books.size();
	if (num > 0)
	{
		cout << "감사합니다. 당신은 다음과 같이 입력하셨습니다.\n"
			<< "등급\t제목\n";
		for (int i = 0; i < num; i++)
			ShowReview(books[i]);
		cout << "한 번 더 출력한다:\n"
			<< "등급\t제목\n";
		vector<Review>::iterator pr;
		for (pr = books.begin(); pr != books.end(); pr++)
			ShowReview(*pr);
		vector<Review> oldlist(books);
		if (num > 3)
		{
			books.erase(books.begin() + 1, books.begin() + 3);
			cout << "삭제한 후:\n";
			for (pr = books.begin(); pr != books.end(); pr++)
				ShowReview(*pr);
			books.insert(books.begin(), oldlist.begin() + 1, oldlist.begin() + 2);
			cout << "삽입한 후:\n";
			for (pr = books.begin(); pr != books.end(); pr++)
				ShowReview(*pr);
		}
		books.swap(oldlist);
		cout << "oldlist와 books를 교환한 후: \n";
		for (pr = books.begin(); pr != books.end(); pr++)
			ShowReview(*pr);
	}
	else
		cout << "입력한 것이 없어, 얻은 것이 없습니다.\n";
	return 0;
}
bool FillReview(Review & rr)
{
	std::cout << "책 제목을 입력하십시오(끝내려면 quit를 입력): ";
	std::getline(std::cin, rr.title);
	if (rr.title == "quit")
		return false;
	std::cout << "책 등급(0-10을 입력하십시오: ";
	std::cin >> rr.rating;
	if (!std::cin)
		return false;
	while (std::cin.get() != '\n')
		continue;
		return true;
}

void ShowReview(const Review & rr)
{
	std::cout << rr.rating << "\t" << rr.title << std::endl;
}


#include <iostream>
#include <cstdlib>
#include <ctime>

using std::cout;

class Grand
{
private:
	int hold;

public:
	Grand(int h = 0) : hold(h) {}
	virtual void Speak() const { cout << "나는 Grand 클래스이다!\n"; }
	virtual int Value() const { return hold; }
};
class Superb : public Grand
{
public:
	Superb(int h = 0) : Grand(h) {}
	void Speak() const { cout << "나는 Superb 클래스이다!\n"; }
	virtual void Say() const
	{
		cout << "내가 가지고 있는 Superb 값은 " << Value() << "이다.\n";
	}
};
class Magnificent : public Superb {
private: char ch;
public :
	Magnificent(int h = 0, char c = 'A') : Superb(h), ch(c) {}
	void Speak() const { cout << "나는 Magnificent 클래스이다!!\n"; }
	void Say() const {
		cout << "내가 가지고 있는 문자는 " << ch << "이고, 정수는"
			<< Value() << "이다.\n";
	}
};
Grand * GetOne();

int main()
{
	std::srand(std::time(0));
	Grand *pg;
	Superb * ps;
	for (int i = 0; i < 5; i++)
	{
		pg = GetOne();
		pg->Speak();
		if (ps = dynamic_cast<Superb *>(pg))
			ps->Say();
		else
		{

		}

	}
	return 0;
}

Grand * GetOne()
{
	Grand * p;
	switch (std::rand() % 3)
	{
	case 0:p = new Grand(std::rand() % 100);
		break;
	case 1: p = new Superb(std::rand() % 100);
		break;
	case 2: p = new Magnificent(std::rand() % 100, 'A' + std::rand() % 26);
		break;
	}
	return p;
}

#include <string>
#include <iostream>
#include <fstream>
#include <ctime>
#include <cctype>
using std::string;
const int NUM = 26;
const string wordlist[NUM] = { "apiary", "beetle", "cereal", "danger", "ensign",
"florid", "garage", "health", "insult", "jackal", "keeper", "loaner", "manage",
"nonce", "onset", "plaid", "quilt", "remote", "stolid", "train", "useful", "valid",
"whence", "xenon", "yearn", "zippy" };


int main()
{
///hangman
	using std::cout;
	using std::cin;
	using std::tolower;
	using std::endl;
	std::srand(std::time(0));
	char play;
	cout << "영어 단어 게임을 하시겠습니까? <y/n> ";
	cin >> play;
	play = tolower(play);
	while (play == 'y')
	{
		string target = wordlist[std::rand() % NUM];
		int length = target.length();
		string attempt(length, '-');
		string badchars;
		int guesses = 6;
		cout << "수수께끼 단어를 추측해 보십시오.\n"
			<< length << "개의 문자로 이루어져 있습니다.\n"
			<< "한 번에 한 문자씩 추측하십시오.\n" << "틀릴 수 있는 기회: "
			<< guesses << "번\n";
		cout << "추측하는 단어: " << attempt << endl;
		while (guesses > 0 && attempt != target)
		{
			char letter;
			cout << "문자를 추측하십시오: ";
			cin >> letter;
			if (badchars.find(letter) != string::npos || attempt.find(letter) != string::npos)
			{
				cout << "이미 추측한 문자입니다. 다시 하십시오.\n";
				continue;
			}
			int loc = target.find(letter);
			if (loc == string::npos)
			{
				cout << "땡! 틀렸습니다. \n";
				--guesses;
				badchars += letter;
			}
			else
			{
				cout << "딩동댕! 맞았습니다. \n";
				attempt[loc] = letter;
				loc = target.find(letter, loc + 1);
				while (loc != string::npos)
				{
					attempt[loc] = letter;
					loc = target.find(letter, loc + 1);
				}
			}
			cout << "추측하는 단어: " << attempt << endl;
			if (attempt != target)
			{
				if (badchars.length() > 0)
					cout << "틀리게 추측한 문자들: " << badchars << endl;

					cout << "틀릴 수 있는 기회: " << guesses << "번\n";
			}
		}
		if (guesses > 0)
			cout << "그렇습니다. 그것이 수수께끼 단어입니다.\n";
		else
			cout << "안타깝습니다. 수수께끼 단어는 " << target << "입니다.\n";
		cout << "게임을 다시 하시겠습니까? <y/n> ";
		cin >> play;
		play = towlower(play);
	}
	cout << "프로그램을 종료합니다.\n";
	return 0;

}



#include <iostream>
#include <cmath>
#include "exc_mean.h"

double hmean(double a, double b)throw (bad_hmean)
{
	if (a == -b)
		throw bad_hmean(a, b);
	return 2.0 * a * b / (a + b);
}
double gmean(double a, double b) throw(bad_gmean);
int main()
{
	using std::cout;
	using std::cin;
	using std::endl;

	double x, y, z;

	std::cout << "두 수를 입력하십시오: ";
	while (std::cin >> x >> y)
	{
		try {
			z = hmean(x, y);
			cout << x << ", " << y << "의 조화평균은 "
				<< z << "입니다.\n";
			cout << x << ", " << y << "의 기하평균은 " << gmean(x, y) << "입니다.\n";
			cout << "다른 두 수를 입력하십시오(끝내려면 q) : ";
		}
		catch (bad_hmean & bg)
		{
			bg.mesg();
			cout << "다시 하십시오.\n";
			continue;
		}
		catch (bad_gmean &hg)
		{
			hg.mesg();
			cout << "Values used: " << hg.v1 << ", " << hg.v2 << endl;
			cout << "죄송합니다. 더 이상 진행할 수 없습니다.\n";
			break;
		}
	}
	cout << "프로그램을 종료합니다.\n";
	return 0;
}
double gmean(double a, double b)
{
	if (a < 0 || b < 0)
		throw bad_gmean(a, b);
	return std::sqrt(a*b);
}

#include <iostream>
double hmean(double a, double b);

int main()
{
	double x, y, z;

	std::cout << "두 수를 입력하십시오: ";
	while (std::cin >> x >> y)
	{
		try {
			z = hmean(x, y);
		}
		catch (const char * s)
		{
			std::cout << s << std::endl;
			std::cout << "두 수를 새로 입력하십시오: ";
			continue;
		}
		std::cout << x << ", " << y << "의 조화평균은 "
			<< z << "입니다.\n";
		std::cout << "다른 두 수를 입력하십시오(끝내려면 q) : ";
	}
	std::cout << "프로그램을 종료합니다.\n";
	return 0;
}
double hmean(double a, double b)
{
	if (a == -b)
		throw "잘못된 hmean() 매개변수: a = -b는 허용되지 않습니다. ";
	return 2.0 * a * b / (a + b);
}



#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include "tvfm.h"

int main()
{
	using std::cout;
	tv s42;

	cout << "42\" TV의 초기 설정값: \n";
	s42.settings();
	s42.onoff();
	s42.chanup();
	cout << "\n42\"TV의 변경된 설정값 :\n";
	s42.settings();

	Remote grey;

	grey.set_chan(s42, 10);
	grey.volup(s42);
	grey.volup(s42);
	cout << "\n리모콘 사용 후 42\" TV의 설정값:\n";
	s42.settings();

	tv s58(tv::On);
	s58.set_mode();
	grey.set_chan(s58, 28);
	cout << "\n58\" TV의 설정값:\n";
	s58.settings();

	cout << "58번 채널 리모트모드 조정\n";
	grey.show_remotemode();
	s58.remotemodecontrol(grey);
	grey.show_remotemode();
	s58.remotemodecontrol(grey);
	grey.show_remotemode();
	cout << "tv 전원 종료\n";
		s58.onoff();
		s58.settings();
	s58.remotemodecontrol(grey);
	grey.show_remotemode();


	return 0;
}
#include <iostream>
#include "tv.h"

int main()
{
	using std::cout;
	tv s42;

	cout << "42\" TV의 초기 설정값: \n";
	s42.settings();
	s42.onoff();
	s42.chanup();
	cout << "\n42\"TV의 변경된 설정값 :\n";
	s42.settings();

	Remote grey;

	grey.set_chan(s42, 10);
	grey.volup(s42);
	grey.volup(s42);
	cout << "\n리모콘 사용 후 42\" TV의 설정값:\n";
	s42.settings();

	tv s58(tv::On);
	s58.set_mode();
	grey.set_chan(s58, 28);
	cout << "\n58\" TV의 설정값:\n";
	s58.settings();


	return 0;
}


#define _CRT_SECURE_NO_WARNINGS
#include <sstream>
#include <vector>
#include <iostream>
#include <string>
using namespace std;

class String {
public:
	String() {
		cout << "String() : " << this << endl;
		strData = NULL;
		len = 0;
	}
	String(const char * str) {
		cout << "String(const char *) : " << this << endl;
		len = strlen(str);
		alloc(len);
	}
	String(const String &rhs) {
		cout << "String(const String&) : " << this << endl;
		len = rhs.len;
		alloc(len);
		strcpy(strData, rhs.strData);
	}
//	String(String &&rhs) {
//
//	}
	~String() {
		cout << "~String(): " << this << endl;
		release();
		strData = NULL;
	}
	String &operator=(const String &rhs) {
		cout << "String &operator=)const String &) : " << this << endl;
		if (this != &rhs)
		{
			release();
			len = rhs.len;
			alloc(len);
			strcpy(strData, rhs.strData);
		}
		return *this;
	}
	char * GetStrData() const {
		return strData;
	}
	int GetLen() const {
		return len;
	}
	void SetStrData(const char *str)
	{
		cout << "void SetStrData(const char*) : " << this
			<<", "<<str<<endl;
		len = strlen(str);
		alloc(len);
		strcpy(strData, str);
	}
private:
	void alloc(int len) {
		strData = new char[len + 1];
		cout << "strData allocated : " << (void*)strData << endl;
	}
	void release() {
		delete[] strData;
		if (strData) cout << "strData released : " << (void*)strData << endl;
	}
	char *strData;
	int len;
};
String getName() {
	cout << "======2=====" << endl;
	String res("Doodle");
	cout << "=====3=====" << endl;
	return res;
}
int main()
{
	String a;
	cout << "=====1=====" << endl;
	a = getName();
	cout << "=====4=====" << endl;
}







#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "stopwatch.h"

using namespace std;
void insert(int *str, int n);
int main()
{

	//srand((unsigned)time(0));
	int n;
	cout << "입력받을 정수 개수 : ";
	cin >> n;
	cout << "임의 수열 입력 : ";
	int *str = new int[n];
	for (int i = 0; i < n; i++)
		cin >> str[i];
	insert(str, n);

	delete[] str;


	return 0;
}
void insert(int *str, int n)
{
	stopwatch timecheck;
	timecheck.start();
	int cnt=0;
	int swap = 0;
	for (int i = 0; i < n - 1; i++)//ex 5개인경우 4번까지만
	{
		if(i<n-2)
		{
		cout << " ";
		for (int k = 0; k < n; k++)
			cout << str[k] << "  ";
		cout << endl;
		}
		int for_print=-1;


		int temp = str[i];
		if (str[i]>str[i+1])	//앞선번호가 더 큰경우 교환
		{


			temp = str[i];
			str[i] = str[i + 1];
			str[i + 1] = temp;
			swap++;
			for_print = i;
		}
		cnt++;
		for (int j = i; j > 0; j--)//이전 번호보다 더 큰지 비교
		{
			cnt++;
			int temp_ = str[j];
			if (str[j-1] > str[j])//앞선번호가 더 큰경우 교환
			{

				temp_ = str[j-1];
				str[j-1] = str[j];
				str[j] = temp_;
				swap++;
				for_print = j - 1;
			}
			else break;	//작은경우 만나면 break
		}


	//출력부 2
			if (i <n-2)
			{
			if (for_print != -1)
			{
				for (int k = 0; k < for_print + 1; k++)
					cout << " ";
				cout << "^";
				for (int k = for_print + 1; k <= i+1; k++)
					cout << "---";
				cout << "+" << endl;
			}
			else
			{
				cout << "   ";
				for (int k = 0; k < i; k++)
					cout << "    ";
				cout << "+" << endl;
			}
		}


	}
	timecheck.stop();
	cout << endl;
	for (int i = 0; i < n; i++)
		cout << str[i] << " ";
	cout << endl << "총 " << cnt << "번 시도" << endl;
	cout << "총 " << swap << "번 교환" << endl;

	timecheck.stop();
	cout << "총 걸린 시간 " << timecheck.getElapsedTime() << "ms" << endl;

}



#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "stopwatch.h"
#include <string>


using namespace std;
//문1. 실수를 입력하고 이것을 문자열로 변환하여 천단위로 ','를 추가하고
//소수점을 출력하는 프로그램

//문2. 사용자가 실수를 입력하면 그 실수를 분수로 화면을 출력하는 프로그램
//문자열을 읽어, 문자열로부터 정수부와 소수부를 추출하고
//실수에 대한 유리수를 구하라 실수:3.25입하면 분수:13/4
string numtostr(string *str, double n);
void divVer(double n);
long long maxSameDivNum(long long a, long long b);
int main()
{

	//string *str = new string[100];
	double input;
	cout << "실수 하나를 입력하세요 : ";
	cin >> input;


	//cout << numtostr(str, input) << endl;
	divVer(input);
	//delete[] str;
}
void divVer(double n)
{
	long long nu = long long(n);		//정수부
	double nd = n - (double)nu;	//소수부
	int i = 0;
		while (1)
		{
			i++;
			if (nd * pow(10,i) - (int)(nd * pow(10,i)) == 0)
				break;//소수자리 남은거 없으면 break
		}
	long long msdn = maxSameDivNum(nd*pow(10, i), pow(10, i));//최대공약수ㄱㄱ
	cout << "실수 : " << n << endl;
	cout << "분수 : " << nu * (pow(10, i) / msdn) + nd * pow(10, i) / msdn << "/"
		<< pow(10, i) / msdn << endl;
}
long long maxSameDivNum(long long a, long long b) //최대공약수 찾기
{
	long long msdn;
	while (b != 0)
	{
		msdn = a % b;
		a = b;
		b = msdn;
	}
	return a;
}
string numtostr(string *str, double n)
{

	long long nu = long long(n);		//정수부
	double nd = n - (double)nu;	//소수부
	int i = 0;
	while (1)
	{
		if (i % 3 == 0 && i != 0)	//4번째마다 ,
			(*str) += ',';

			if (nu / 10 != 0)			//정수부 10 나머지
			{
				(*str) += to_string(nu % 10);

			}
			else	//10나누고 0이면 마지막
			{
				(*str) += to_string(nu);
				break;
			}

		nu /= 10;
		i++;
	}

	reverse((*str).begin(), (*str).end());
	(*str) += to_string(nd).erase(0,1);
	return *str;
}



const int LIM = 4;
int main()
{
	Waiter bob("홍길동", 314L, 5);
	Singer bev("조수미", 522L, 3);
	Waiter w_temp;
	Singer s_temp;

	Worker * pw[LIM] = { &bob, &bev, &w_temp, &s_temp };

	int i;
	for (i = 2; i < LIM; i++)
		pw[i]->Set();
	for (i = 0; i < LIM; i++)
	{
		pw[i]->Show();
		std::cout << std::endl;
	}
	return 0;
}



//sns 각 이용자의 친구 수 분석
//3 1 2 4 5 =>  2 3 4 3 2
using namespace std;

int solution(int N, int **relation);
int main()
{
	int N;
	cout << "전체 이용 자 수 : ";
	cin >> N;
	int *(*relation) = new int*[2] ();	//행
	for (int i = 0; i < 2; i++)
		relation[i] = new int[N*(N - 1) / 2]();	//열
	 //0으로 초기화
	int an = 0; //수열 첫번째
	int sum = 0; //계차수열 합 (N=5일때 0 4 7 9 10)
	for (int i = 0; i < N-1; i++)
	{
		int n;
		cout << i+1 << "번의 친구 수 : ";
		cin >> n;
		
		for (int j = 0; j < n; j++)
		{
			int fn; //friend number
			cout << j + 1 << "번째 친구 번호 : ";
			cin >> fn; 
			if (fn>i+1)//중복 제외한 경우만 
			{
				relation[0][sum+(fn-i-1)-1] = i+1; //(i+1, fn)
				relation[1][sum + (fn - i - 1) - 1] = fn;
			}	   					
		}
		an = N -1 -i;	//등차 공차=-1
		sum += an;		//등차 합 ->계차
	}
	solution(N, relation);
	for (int i = 0; i < 2; i++)
		delete[] relation[i];
	delete[] relation;
}
int solution(int N, int **relation)
{
	int cnt = 1; //친구 1~N
	int *(*friendArr) = new int*[N]();	//친구배열
	for (int i = 0; i < N; i++)
		friendArr[i] = new int[N]();	//열
	while (cnt <= 5)
	{
		int dcnt = 0; //직접친구
		cout << cnt << "의 직접친구 : ";
		for (int i = 0; i < N*(N - 1) / 2; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				if (relation[j][i] == cnt)	//해당번호가 나오면
				{
					dcnt++;
					if (j == 0)	//해당번호의 같은열 다른행(친구)를 출력
					{
						cout << relation[1][i] << " ";
						friendArr[cnt - 1][relation[1][i] - 1] = relation[1][i];//자기목록에 친구추가
						friendArr[relation[1][i] - 1][cnt - 1] = cnt; //친구목록에 자신추가
					}
					else
					{
						cout << relation[0][i] << " ";
						friendArr[cnt - 1][relation[0][i] - 1] = relation[0][i];
						friendArr[relation[1][i] - 1][cnt - 1] = cnt;
					}
				}
			}
		}
		cout << endl << cnt << "의 직접친구는 총 " << dcnt << "명" << endl;
		cnt++;
	}
	cout << "----------------------------------------" << endl;
	for (int i = 0; i < 5; i++)
		{
		cout << i + 1 << "의 친구는 ";
		for (int j = 0; j < 5; j++)
			{
				//if (friendArr[i][j] != 0)
					cout << friendArr[i][j] << " ";
			}
		cout << endl;
		}
	
	cout << "----------------------------------------" << endl;
	cnt = 1; //초기화
	while (cnt <= 5)
	{
		int fcnt = 0; //최종친구
		cout << cnt << "의 최종친구 : ";
		for (int i = 0; i < N*(N - 1) / 2; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				if (relation[j][i] == cnt)	//해당번호가 나오면
				{
					fcnt++;
					if (j == 0)	//해당번호의 같은열 다른행(친구)를 출력
					{
						cout << relation[1][i] << " ";
						for (int k = 0; k < 5; k++) //친구의 친구
						{
							if (friendArr[relation[1][i]-1][k] == 0) break; //친구없으면 break
							if (friendArr[relation[1][i]-1][k] != cnt) //자신과 친구는 포함x
							{
								cout << friendArr[relation[1][i]-1][k] << " ";
								fcnt++;
							}
						}
					}
					else
					{
						cout << relation[0][i] << " ";
						for (int k = 0; k < 5; k++) //친구의 친구
						{
							if (friendArr[relation[1][i]-1][k] == 0) break; //친구없으면 break
							if (friendArr[relation[1][i]-1][k] != cnt)
							{
								cout << friendArr[relation[1][i]-1][k] << " ";
								fcnt++;
							}
						}
					}
				}
			}
		}
		cout << endl << cnt << "의 최종친구는 총 " << fcnt << "명" << endl;
		cnt++;

	}
	for (int i = 0; i < N; i++)
		delete[] friendArr[i];
	delete[] friendArr;
	return 0;
}
*/
	
/*
cout << "(";
for(int j=0; j<2; j++)
cout << relation[j][i] << " ";
cout << ") ";
*/
// 0 8 14 18 20=\0
	/*문. GeometricObject 베이스 클래스를 설계하라.
	Circle2D, Rectangle2D, MyPoint, Triangle2D 클래스에서 공통된 요소로
	추상 클래스 GeometricObject를 만들고 이를 상속 받은 형태로 클래스를 재정의하라.
	위치, 넓이 구하기 등의 함수를 가상 함수로 정의하라.
	각 클래스를 기존 코드에 적용 시켜서 잘 작동하는지 테스트 하라.
	UML 클래스 다이어 그램도 작성.

		MyPoint point;
	MyPoint point2{10, 30.5};
	Circle2D circle1{ 5, 5, 5 };
	std::cout << point.IsIn(circle1) << std::endl;

	std::cout << "거리: " << point.GetDistance(point2) << std::endl;
	
using namespace std;
void compare(int *str, int n);
int main()
{
	
	int n;
	cout << "입력받을 정수 개수 : ";
	cin >> n;
	cout << "임의 수열 입력 : ";
	int *str = new int[n];
	for (int i = 0; i < n; i++)
		cin >> str[i];
	compare(str, n);
	
	delete[] str;
	return 0;
}
void compare(int *str, int n)
{
	int swap = 0;
	int cnt = 0;
	int loopnum = 0;
	int loopcnt=n-1;
	for (int j = 0; j < n-1; j++)
	{
		if (loopnum == n - 1) break;
		for (int i = n - 1; i > loopnum; i--)//다음부터 loopnum 이하 loop 돌릴 필요 x
		{
			cout << endl;;		//출력부
		/*	for (int i = 0; i < n - loopnum; i++)
				cout << "  ";
			cout << "|" << endl;
			cout << "  ";
			for (int k = 0; k < n; k++) 
				cout << str[i] << " ";
			cout << endl;
			for (int k = 0; k < n; k++)
				cout << "  ";
			cout << "< >" << endl;


			int temp = str[i];
			if (str[i] < str[i - 1])
			{
				str[i] = str[i - 1];
				str[i - 1] = temp;
				loopcnt = i;		//마지막 i 저장
				swap++;
			}
			cnt++;
		}
		loopnum = loopcnt;
	}

	cout << endl;
		for (int i = 0; i < n; i++)
			cout << str[i]<<" ";
		cout << endl << "총 " << cnt << "번 시도" << endl;
		cout << "총 " << swap << "번 교환" << endl;
}
*/
	/*

	dma
		using std::cout;
	using std::endl;

	baseDMA shirt("Portabelly", 8);
	lacksDMA balloon("red", "Blimpo", 4);
	hasDMA map("Mercator", "Buffalo Keys", 5);
	cout << "baseDMA 객체를 출력한다:\n";
	cout << shirt << endl;
	cout << "lacksDMA 객체를 출력한다.\n";
	cout << balloon << endl;
	cout << "hasDMA 객체를 출력한다.\n";
	cout << map << endl;
	lacksDMA balloon2(balloon);
	cout << "lacksDMA 복사 결과:\n";
	cout << balloon2 << endl;
	hasDMA map2;
	map2 = map;
	cout << "hasDMA 대입결과:\n";
	cout << map2 << endl;
		return 0;
		/////////////////
	userbrass3
		using std::cin;
	using std::cout;
	using std::endl;

	AcctABC *p_client[CLIENTS];
	std::string temp;
	long tempnum;
	double tempbal;
	char kind;

	for (int i = 0; i < CLIENTS; i++)
	{
		cout << "고객의 이름을 입력하십시오: ";
		getline(cin, temp);
		cout << "고객의 계좌 번호를 입력하십시오: ";
		cin >> tempnum;
		cout << "계좌 개설 잔액을 입력하십시오: $";
		cin >> tempbal;
		cout << "Brass 계좌는 1, "
			<< "BrassPlus 계좌는 2를 입력하십시오: ";
		while (cin >> kind && (kind != '1' && kind != '2'))
			cout << "1 아니면 2, 둘 중 하나를 입력하십시오: ";
		if (kind == '1')
			p_client[i] = new Brass(temp, tempnum, tempbal);
		else
		{
			double tmax, trate;
			cout << "당좌 대월 한도를 입력하십시오: $";
			cin >> tmax;
			cout << "당좌 대월 이자율을 소수점 형식으로 입력하십시오: ";
			cin >> trate;
			p_client[i] = new BrassPlus(temp, tempnum, tempbal, tmax, trate);
		}
		while (cin.get() != '\n')
			continue;
	}
	cout << endl;
	for (int i = 0; i < CLIENTS; i++)
	{
		p_client[i]->ViewAcct();
		cout << endl;
	}
	for (int i = 0; i < CLIENTS; i++)
	{
		delete p_client[i];
	}
	cout << "프로그램을 종료합니다.\n";
	/////////////////////
	usebrass2
	using std::cin;
	using std::cout;
	using std::endl;
	//use brass2
	Brass *p_client[CLIENTS];
	std::string temp;
	long tempnum;
	double tempbal;
	char kind;

	for (int i = 0; i < CLIENTS; i++)
	{
		cout << "고객의 이름을 입력하십시오: ";
		getline(cin, temp);
		cout << "고객의 계좌 번호를 입력하십시오: ";
		cin >> tempnum;
		cout << "계좌 개설 잔액을 입력하십시오: $";
		cin >> tempbal;
		cout << "Brass 계좌는 1, "
			<< "BrassPlus 계좌는 2를 입력하십시오: ";
		while (cin >> kind && (kind != '1' && kind != '2'))
			cout << "1 아니면 2, 둘 중 하나를 입력하십시오: ";
		if (kind == '1')
			p_client[i] = new Brass(temp, tempnum, tempbal);
		else
		{
			double tmax, trate;
			cout << "당좌 대월 한도를 입력하십시오: $";
			cin >> tmax;
			cout << "당좌 대월 이자율을 소수점 형식으로 입력하십시오: ";
			cin >> trate;
			p_client[i] = new BrassPlus(temp, tempnum, tempbal, tmax, trate);
		}
		while (cin.get() != '\n')
			continue;
	}
	cout << endl;
	for (int i = 0; i < CLIENTS; i++)
	{
		p_client[i]->ViewAcct();
		cout << endl;
	}
	for (int i = 0; i < CLIENTS; i++)
	{
		delete p_client[i];
	}
	cout << "프로그램을 종료합니다.\n";
		*/
		/* usebrass1
	Brass Piggy("Porcelot Pigg", 381299, 4000.00);
	BrassPlus Hoggy("Horatio Hogg", 382288, 3000.00);
	Piggy.ViewAcct();
	cout << endl;
	Hoggy.ViewAcct();
	cout << endl;
	cout << "Hogg씨의 계좌에 $1000 입금:\n";
	Hoggy.Deposit(1000.00);
	cout << "Hogg씨의 현재 잔액: $" << Piggy.Balance() << endl;
	cout << "Pigg씨의 계좌에서 $4200 인출:\n";
	Piggy.Withdraw(4200.00);
	cout << "Pigg씨의 현재 잔액: $" << Piggy.Balance() << endl;
	cout << "Hogg씨의 계좌에서 $4200 인출: \n";
	Hoggy.Withdraw(4200.00);
	Hoggy.ViewAcct();
	*/

