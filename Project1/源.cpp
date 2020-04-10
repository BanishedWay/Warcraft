#include<iostream>
#include<iomanip>

using namespace std;

constexpr auto num = 5;//���峣����ʿ������Ŀ

class Headquarter;//˾���
class Warrior//��ʿ��
{
private:
	Headquarter* pHeadquarter;
	int type;

public:
	static int value[num];
	static string warriortype[num];
	Warrior(Headquarter* p, int type);
	void Print(int Time);
};
class Headquarter
{
private:
	int lifeValue;
	int color;
	int warriorcount;//��ʿ������
	int flag;
	int cur;
	Warrior* pWarrior[1000];
	int warriornum[num];//˾���ĳһ��ʿ����
	static int seq[2][num];
public:
	friend class Warrior;//������Ԫ�����˽�г�Ա����
	void InitHeadQuarter(int color, int m);
	int Birth(int Time);
	string getColor();
	Headquarter();
	~Headquarter();
};

string Warrior::warriortype[num] = { "dragon","ninja","iceman","lion","wolf" };
int Headquarter::seq[2][num] = { {3,0,1,2,4},{ 2,3,4,1,0 } };
int Warrior::value[num];

int main()
{
	int count, m;
	cin >> count;
	int _case = 1;
	int n = 1;
	Headquarter RED, BLUE;
	while (n <= count)
	{
		cin >> m;
		for (int i = 0; i < num; i++)
		{
			cin >> Warrior::value[i];
		}
		cout << "case:" << n << endl << endl;
		n++;
		RED.InitHeadQuarter(1, m);
		BLUE.InitHeadQuarter(0, m);
		int Time = 0;
		while (1)
		{
			int t1 = RED.Birth(Time);
			int t2 = BLUE.Birth(Time);
			if (t1 == t2 && t1 == 0)
			{
				break;
			}
			Time++;
		}
	}
	return 0;
}

Warrior::Warrior(Headquarter* p, int type)
{
	pHeadquarter = p;
	this->type = type;
}

void Warrior::Print(int Time)
{
	string color = pHeadquarter->getColor();
	cout << setw(3) << setfill('0') << Time << " " << color << " " << warriortype[type] << " " << Time + 1 << " born with strength " << value[type] << "," << pHeadquarter->warriornum[type] << " " << warriortype[type] << " in " << color << " headquarter\n\n";
}

void Headquarter::InitHeadQuarter(int color, int m)
{
	this->color = color;
	lifeValue = m;
	warriorcount = 0;
	flag = 0;
	cur = 0;
	for (int i = 0; i < num; i++)
	{
		warriornum[i] = 0;
	}
}//����˾�

int Headquarter::Birth(int Time)
{
	if (flag)
		return 0;
	int t = 0;//ѭ���ж�����ֵ�Ƿ����޷�������ʿ
	while (Warrior::value[seq[color][cur]] > lifeValue && t < num)
	{
		cur = (cur + 1) % num;
		t++;
	}
	int type = seq[color][cur];
	if (Warrior::value[type] > lifeValue)
	{
		flag = 1;
		string c = "blue";
		if (color)
			c = "red";
		cout << setw(3) << Time << " " << c << " headquarter stops making warriors\n\n";
		return 0;
	}

	lifeValue -= Warrior::value[type];
	cur = (cur + 1) % num;
	pWarrior[warriorcount] = new Warrior(this, type);
	warriornum[type]++;
	pWarrior[warriorcount]->Print(Time);
	warriorcount++;
	return 1;
}//������ʿ
string Headquarter::getColor()
{
	if (color)
		return "red";
	return "blue";
}

Headquarter::Headquarter()
{
}

Headquarter::~Headquarter()
{
}

