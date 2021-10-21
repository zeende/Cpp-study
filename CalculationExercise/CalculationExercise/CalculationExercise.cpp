#include<iostream>
#include<cstdlib>
#include<ctime>


struct QuData
{
	int A; 
	int B;
	int Symbol; //�������  0- 1+ 2/ 3*
	double correct_answer;//��ȷ��
	double usr_answer;//�û���
	bool state;//��ȷ���
	int using_time;
};

void CreateExercise(QuData *d, int qu_num, int* _range, int method);
void CheckAnswer(QuData *d, int qu_num);
void PrintQuestion(int i, int A, int B, int flag);
int main()
{
	int qu_num = 10;
	int usr_range[2] = { 0,100 };//�������� ��Χ����
	int method = 0;//���㷽�����Ƿ��г˳���
	std::cout << "��ʼ���м�����ϰ" << std::endl;
	std::cout << "�Ƿ���Ĭ�Ϸ�ʽ(100���ڼӼ�)������ ���� 0--��  1---��" << std::endl;
	int rule = 1;
	std::cin >> rule;
	if (!rule) {
		std::cout << "������Ŀ������   ------>  " << std::flush;
		std::cin >> qu_num;
		std::cout << "����������Сֵ���ƣ�   ------>  " << std::flush;
		std::cin >> usr_range[0];
		std::cout << "�����������ֵ���ƣ�   ------>  " << std::flush;
		std::cin >> usr_range[1];
		std::cout << "�Ƿ��г˳����� ���� 0--��  1---��   ------>  " << std::flush;
		std::cin >> method;
		std::cout << "\n ------���������------" << std::endl;
	}
	else std::cout << "\n----��Ĭ�Ϸ�ʽ(100���ڼӼ�)����----" << std::endl;




	QuData *data = new QuData[qu_num];
	CreateExercise(data, qu_num, usr_range, method);
	CheckAnswer(data, qu_num);

	return 0;
}

//������ϰ �����������Ŀ��Ϣ�Ľṹ�����飬��Ŀ���������㷶Χ���Ƿ��г˳�
void CreateExercise(QuData *d, int qu_num, int* _range, int method)
{
	srand((unsigned)time(0));//ʹ��ϵͳʱ��time(0)��Ϊ��������Ӳ�����ֵͬ�������
	int start;
	int end;
	int A;
	int B;
	int flag = -1;// 0Ϊ- 1Ϊ+ 2/ 3*
	double answer_in = -1.;
	double answer_true = -1.;
	int rand_range = _range[1] - _range[0];
	int rand_flag = 2;//������������ɵ�ʱ�򣬷����Ƿ��г˳���
	if(method)rand_flag = 4;

	for (int i = 0; i < qu_num; i++)
	{
		while (true)
		{
			A = (rand() % rand_range) + _range[0];
			B = (rand() % rand_range) + _range[0];
			//�������3 2 1 0
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
		if(flag == 2) std::cout << "��Ĵ���(������λС��)��" << std::flush;
		else std::cout << "��Ĵ��ǣ�" << std::flush;

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

//����
void CheckAnswer(QuData *d, int qu_num)
{
	std::cout << "----------------------\n������Ŀ����" << std::endl;
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
			//std::cout << "��" << i + 1 << "��: ";
			PrintQuestion(i, d[i].A, d[i].B, d[i].Symbol);
			std::cout << "��ȷ�𰸣�" << d[i].correct_answer << "\t\t��Ĵ�: " << d[i].usr_answer << std::endl;
			num_wrong++;
		}

	}
	average_time = total_time / qu_num;
	if (!num_wrong) std::cout << "ȫ�ԣ�����"  << " ���յ÷�Ϊ��100��" << std::endl;
	std::cout << "\n������" << qu_num - num_wrong << "�⣬" << "���յ÷�Ϊ��" << (qu_num - num_wrong ) * (100/qu_num) << " ��" << std::endl;
	std::cout << "ƽ����ʱ: " << average_time << "ms" << "    �����ʱ��" << min_time << "ms" << std::endl;
}

void PrintQuestion(int i,int A, int B, int flag)
{
	std::cout << "��" << i + 1 << "��: ";
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