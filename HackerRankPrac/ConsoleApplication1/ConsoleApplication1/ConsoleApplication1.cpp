#define _crt_secure_no_warnings

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
long long f_x(int n);
long long g_x(long long n);

int main() {
	
	long long q, n;
	long long m;
	long long result=0;

	cin >> q;
	while (q--)
	{
		cin >> n >> m;
		for(int i = 1; i<=n; i++)
			result += g_x(i);
		
		cout << result%m << endl;
	}

	return 0;
}

long long f_x(int n)
{
	long long res=0;
	long long rres = 0;
	long long divN;
	while (n)
	{
		divN = n % 10;
		while (divN)
		{
			if (divN != 1)
			{
				divN *= (divN - 1);
				
			}
			res += divN;
			divN--;
		} 
		
		n /= 10;
	}
	//////fn///////
	while (res)
	{
		divN = res % 10;
		rres += divN;
		res /= 10;
	}
	/////sfn/////
	return rres;
}
long long g_x(long long n)
{
	int i=0;
	long long res=0;
	while (1)
	{
		if (f_x(i) == n)
		{
			break;
		}
		else if (i >= 100000)
		{
			cout << "찾을수없음" << endl;
			return 0;
		}
		else
			i++;
	}
	////gi

	long long divN;
	while (i)
	{
		divN = i % 10;
		res += divN;
		i /= 10;
	}
	//sgi

	return res;
}





//#include <cmath>
//#include <cstdio>
//#include <vector>
//#include <iostream>
//#include <algorithm>
//#include <string>
//using namespace std;
//
//
//class Person {
//protected:
//	string name;
//	int age;
//	int cur_id;
//	virtual void getdata() { cin >> this->name >> this->age; }
//	virtual void putdata() {
//		cout << this->name << " " << this->age << endl;
//	}
//};
//
//class Professor : public Person {
//	Professor() { this->cur_id == ++id; }
//
//	int publications;
//	int cur_id;
//	static int id;
//
//	void getdata() // name age publications
//	{
//		cin >> this->name >> this->age >> this->publications;
//	}
//	void putdata() //print name age publications cur_id
//	{
//		cout
//	}
//};
//class Student : public Person {
//
//	int marks[6];
//	void getdata() //name age marks
//	{
//
//	}
//	void putdata()
//	{
//		
//	}
//};
//
//int main() {
//
//	int n, val;
//	cin >> n; //The number of objects that is going to be created.
//	Person *per[n];
//
//	for (int i = 0; i < n; i++) {
//
//		cin >> val;
//		if (val == 1) {
//			// If val is 1 current object is of type Professor
//			per[i] = new Professor;
//
//		}
//		else per[i] = new Student; // Else the current object is of type Student
//
//		per[i]->getdata(); // Get the data from the user.
//
//	}
//
//	for (int i = 0; i < n; i++)
//	{
//		per[i]->putdata(); // Print the required output for each object.
//		delete per[i];
//	}
//	return 0;
//
//}


//#include <iostream>
//#include <exception>
//#include <string>
//#include <stdexcept>
//#include <vector>
//#include <cmath>
//using namespace std;
//
//class Server {
//private:
//	static int load;
//public:
//	static int compute(long long A, long long B) {
//		load += 1;
//		if (A < 0) {
//			throw std::invalid_argument("A is negative");
//		}
//		vector<int> v(A, 0);
//		int real = -1, cmplx = sqrt(-1);
//		if (B == 0) throw 0;
//		real = (A / B)*real;
//		int ans = v.at(B);
//		return real + A - B * ans;
//	}
//	static int getLoad() {
//		return load;
//	}
//};
//int Server::load = 0;
//
//int main() {
//	int T; cin >> T;
//	while (T--) {
//		long long A, B;
//		cin >> A >> B;
//
//		try { cout << Server::compute(A, B) << endl; }
//		catch (bad_alloc& error)
//		{
//			cout << "Not enough memory" << endl;
//		}
//		catch (exception& error)
//		{
//			cout << "Exception: " << error.what() << endl;
//		}
//	/*	catch (...) {
//			cout << "Other Exception" << endl;
//		}*/
//		/* Enter your code here. */
//
//	}
//	cout << Server::getLoad() << endl;
//	return 0;
//}


//#include <iostream>
//#include <string>
//#include <sstream>
//#include <exception>
//using namespace std;
//
//
///* Define the exception here */
//class BadLengthException {
//	int a;
//public:
//	BadLengthException(int n) { a = n; }
//	int what()
//	{
//		return a;
//	}
//};
//
//bool checkUsername(string username) {
//	bool isValid = true;
//	int n = username.length();
//	if (n < 5) {
//		throw BadLengthException(n);
//	}
//	for (int i = 0; i < n - 1; i++) {
//		if (username[i] == 'w' && username[i + 1] == 'w') {
//			isValid = false;
//		}
//	}
//	return isValid;
//}
//
//int main() {
//	int T; cin >> T;
//	while (T--) {
//		string username;
//		cin >> username;
//		try {
//			bool isValid = checkUsername(username);
//			if (isValid) {
//				cout << "Valid" << '\n';
//			}
//			else {
//				cout << "Invalid" << '\n';
//			}
//		}
//		catch (BadLengthException e) {
//			cout << "Too short: " << e.what() << '\n';
//		}
//	}
//	return 0;
//}

//#include <iostream>
//
//using namespace std;
//
//bool isBeautiful(int a[], int n);
//int main()
//{
//	int q;
//	cin >> q; //total number of queries;
//
//	while (q)
//	{
//		int n; //number of each array's elemenets;
//		cin >> n;
//
//		int *a = new int[n];
//
//		for (int i = 0; i < n; i++)
//		{
//			cin >> a[i];
//		}
//		if (isBeautiful(a, n) == 1)
//			cout << "Beautiful" << endl;
//		else
//			cout << "Ugly" << endl;
//
//		q--;
//		delete[] a;
//	}
//
//	return 0;
//}
//
//bool isBeautiful(int a[], int n)
//{
//	int cnt = 0;
//	for (int i = 0; i < sizeof(a); i++)
//	{
//		if (a[i] > n)
//		{
//			return false;
//		}
//
//		for (int k = i+1; k < sizeof(a); k++)
//		{
//			if (a[i] == a[k])
//				return false;
//		}
//		if (i >= 1 && a[i] > a[i - 1])
//		{
//			cnt++;
//
//		}
//		if (i == sizeof(a)-1)
//		{
//			if (cnt == sizeof(a) - 1)
//				return false;
//			else
//				return true;
//		}
//	}
//}

