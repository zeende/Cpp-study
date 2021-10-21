#include<iostream>
#include<cstdlib>
#include<ctime>


struct QuData
{
	int A; 
	int B;
	int Symbol; //运算符号  0- 1+ 2/ 3*
	double correct_answer;//正确答案
	double usr_answer;//用户答案
	bool state;//正确与否
	int using_time;
};

void CreateExercise(QuData *d, int qu_num, int* _range, int method);
void CheckAnswer(QuData *d, int qu_num);
void PrintQuestion(int i, int A, int B, int flag);
int main()
{
	int qu_num = 10;
	int usr_range[2] = { 0,100 };//数据与结果 范围限制
	int method = 0;//计算方法（是否含有乘除）
	std::cout << "开始进行计算练习" << std::endl;
	std::cout << "是否以默认方式(100以内加减)启动？ 输入 0--否  1---是" << std::endl;
	int rule = 1;
	std::cin >> rule;
	if (!rule) {
		std::cout << "输入题目数量：   ------>  " << std::flush;
		std::cin >> qu_num;
		std::cout << "输入数据最小值限制：   ------>  " << std::flush;
		std::cin >> usr_range[0];
		std::cout << "输入数据最大值限制：   ------>  " << std::flush;
		std::cin >> usr_range[1];
		std::cout << "是否含有乘除法？ 输入 0--否  1---是   ------>  " << std::flush;
		std::cin >> method;
		std::cout << "\n ------已设置完成------" << std::endl;
	}
	else std::cout << "\n----以默认方式(100以内加减)出题----" << std::endl;




	QuData *data = new QuData[qu_num];
	CreateExercise(data, qu_num, usr_range, method);
	CheckAnswer(data, qu_num);

	return 0;
}

//生成练习 参数：存放题目信息的结构体数组，题目数量，运算范围，是否含有乘除
void CreateExercise(QuData *d, int qu_num, int* _range, int method)
{
	srand((unsigned)time(0));//使用系统时间time(0)作为随机数种子产生不同值的随机数
	int start;
	int end;
	int A;
	int B;
	int flag = -1;// 0为- 1为+ 2/ 3*
	double answer_in = -1.;
	double answer_true = -1.;
	int rand_range = _range[1] - _range[0];
	int rand_flag = 2;//控制随机数生成的时候，符号是否含有乘除法
	if(method)rand_flag = 4;

	for (int i = 0; i < qu_num; i++)
	{
		while (true)
		{
			A = (rand() % rand_range) + _range[0];
			B = (rand() % rand_range) + _range[0];
			//随机生成3 2 1 0
			flag = rand() % rand_flag;
			if (flag == 0) { if (A - B >= _range[0]) break; }
			else if (flag == 1) { if (A + B <=_range[1]) break; }
			else if (flag == 2) { if ((A / B <= _range[1]) && (A / B >= _range[0]) && B != 0) break; }
			else if (flag == 3) { if ((A * B <= _range[1]) && (A * B >= _range[0])) break; }
			else {};
		}

		PrintQuestion(i, A, B, flag);

		if (flag == 0)  answer_true = A - B;
		else if (flag == 1) answer_true = A + B;
		else if (flag == 2) { 
			answer_true = double(A) / double(B);
			answer_true = round(answer_true * 100.0) / 100.0;
		}
		else if (flag == 3)  answer_true = A * B;
		else {};

		d[i].A = A;
		d[i].B = B;
		d[i].Symbol = flag;
		d[i].correct_answer = answer_true;
		if(flag == 2) std::cout << "你的答案是(保留两位小数)：" << std::flush;
		else std::cout << "你的答案是：" << std::flush;

		start = clock();
		std::cin >> d[i].usr_answer;
		end = clock();
		d[i].using_time = end - start;

		d[i].usr_answer = round(d[i].usr_answer * 100.0) / 100.0;
	    //std::cout << " \t \t use time -----   " << d[i].using_time << std::flush;

		if(answer_true == d[i].usr_answer) d[i].state = true;
		else d[i].state = false;
		std::cout << std::endl;
	}

}

//检查答案
void CheckAnswer(QuData *d, int qu_num)
{
	std::cout << "----------------------\n以下题目错误：" << std::endl;
	int num_wrong = 0;
	int min_time = d[0].using_time;
	int average_time = -1;
	int total_time = 0;
	for (int i = 0; i < qu_num; i++)
	{
		total_time += d[i].using_time;
		if (min_time > d[i].using_time) min_time = d[i].using_time;

		if (!d[i].state)
		{
			//std::cout << "第" << i + 1 << "题: ";
			PrintQuestion(i, d[i].A, d[i].B, d[i].Symbol);
			std::cout << "正确答案：" << d[i].correct_answer << "\t\t你的答案: " << d[i].usr_answer << std::endl;
			num_wrong++;
		}

	}
	average_time = total_time / qu_num;
	if (!num_wrong) std::cout << "全对！！！"  << " 最终得分为：100分" << std::endl;
	std::cout << "\n你答对了" << qu_num - num_wrong << "题，" << "最终得分为：" << (qu_num - num_wrong ) * (100/qu_num) << " 分" << std::endl;
	std::cout << "平均用时: " << average_time << "ms" << "    最短用时：" << min_time << "ms" << std::endl;
}

void PrintQuestion(int i,int A, int B, int flag)
{
	std::cout << "第" << i + 1 << "题: ";
	if (A >= 0) std::cout << A;
	else std::cout <<"("<<A<< ")";

	if (flag == 0) {
		std::cout << " - ";
	}
	else if (flag == 1) {
		std::cout << " + ";
	}
	else if (flag == 2) {
		std::cout << " / ";
	}
	else if (flag == 3) {
		std::cout << " * ";
	}
	else {};

	if (B >= 0) std::cout << B << " =   \t" << std::flush;
	else std::cout << "(" << B << ")" << " =   \t" << std::flush;;

}