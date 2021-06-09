#define _CRT_SECURE_NO_WARNINGS
























/*

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

