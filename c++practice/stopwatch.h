//get 함수를 갖는 전용 데이터 필드 starttime, endtime
/*
stime을 현재시간으로 초기화하는 인수없는 생성자
stime을 현재 시간으로 재설정하는 start()함수
etime을 현재시간으로 설정하는 stop() 함수
스탑워치 경과시간을 ms로 반환하는 getElapsedtime() 함수
버블 정렬을 사용하여 100,000개의 숫자를 정렬하는데 걸린 시간 측정
*/
#include <time.h>


class stopwatch
{
	double startTime, endTime;

public:
	double getStime() { return startTime; }
	double getEtime() { return endTime; }
	stopwatch() : startTime( clock()) {}
	void start()
	{
		startTime = clock();
	}
	void stop()
	{
		endTime =clock();
	}
	double getElapsedTime()
	{
		return (endTime - startTime);
	}
};

