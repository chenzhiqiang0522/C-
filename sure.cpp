#include <iostream> 
#include<Windows.h>
#include <conio.h> 
#include <string>
#include <iomanip> 
#include <fstream>
using namespace std;
void user();
void log_in();
void admin(); 

class password {
	public :
		      password()
			  {
		        passwd ="";//初始化字符串 
		        length = 0;//初始化字符串长度 
			  }
			  void input();
			  string get();
			  
	private :
		      string passwd;
		      int length;
};
void password::input()
{
   char ps;
   cout<<"请输入管理员密码："<<endl;
   while(true)
   {
   	ps = getch();//直接获得用户输入的字符 
     if(ps!=13)//判断用户输入的是否是enter键，如果是直接停止当前while循环。 
	 {
	switch(ps)//用switch语句来判断用户输入的键，来实现相应功能。 
	{
		case 8: //如果用户输入的是BACKSPACE键，则实现退格功能。
		if(length!=0) //如果length不等于0的话实现退格功能。 
		{
			cout<<"\b \b";//第一个\b是将光标向前移动一格，然后输出一个空格字符" "将之前输出的字符覆盖，第二个\b再将光标向前移动一格，实现了退格功能。 
			passwd = passwd.substr(0,length-1);	//将passwd字符串取从0位到字符串长度减少1位赋值给password，相当于的password减少最后一位。 
			length--;  //字符串长度减少一。 
		}
		     else;// 如果length等于0，无法实现退格功能。直接终止switch语句。 
			  break;
		default:  cout<<"*";//如果用户输入其他的键的话，则显示*。 
		          length++;//字符串长度自增1. 
		          passwd +=ps;//将用户输入的字符加到passwd字符串里。 
		          break;	        
	}
	 }
	 else break;
     
   } 	
}
string password::get()
{
   return passwd;	
}

string char_to_string(char *contentChar)
{
	string tempStr;
	for (int i = 0; contentChar[i] != '\0'; i++)
	{
		tempStr += contentChar[i];
	}
	return tempStr;
}

string UTF8ToGB(const char* str)
{
     string result;
     WCHAR *strSrc;
     LPSTR szRes;

     //获得临时变量的大小
     int i = MultiByteToWideChar(CP_UTF8, 0, str, -1, NULL, 0);
     strSrc = new WCHAR[i+1];
     MultiByteToWideChar(CP_UTF8, 0, str, -1, strSrc, i);

     //获得临时变量的大小
     i = WideCharToMultiByte(CP_ACP, 0, strSrc, -1, NULL, 0, NULL, NULL);
     szRes = new CHAR[i+1];
     WideCharToMultiByte(CP_ACP, 0, strSrc, -1, szRes, i, NULL, NULL);

     result = szRes;
     delete []strSrc;
     delete []szRes;
	 return result;
}


void modifyContentInFile1(char *fileName, int lineNum, string content)
{
	ifstream in;
	string tempStr;
	if (!in)
	{
		cout << "无法打开此文件" << endl;
	}
	else
	{
		in.open(fileName);
		int i;
		char line[1024];
		while (in.getline(line, sizeof(line)))
		{
			i++;
			if (lineNum != i)
			{
				tempStr += char_to_string(line);
			}
			else
			{
				tempStr += content;
			}
			tempStr += '\n';
		}
		in.close();
		ofstream out;
		out.flush();
		out.open(fileName);
		out << tempStr;
		out.close();
	}
}

void administrator1() 
{ 
	string username1,passport1,name1; 
	string username,passport; 
	ifstream storeFile("userdate.txt"); 
	if(!storeFile) 
	{	 
	cout<<"\n\n\t 对不起，用户文件丢失。 。 。\n\n\t"; 
	system("pause"); 
	return; 
	} 
	cout<<"用户登录： "<<endl; 
	cout<<"请输入用户名： "; 
	cin>>username; 
	cout<<"请输入密码： "; 
	cin>>passport; 
	bool flag=false; 
	while(storeFile>>username1>>passport1>>name1) 
	{ 
		if(username1==username&&passport1==passport) 
		{ 
		flag=true; 
		system("cls"); 
		cout<<"登录成功！ "
		<<endl;
		cout<<"欢迎您 ,"
		<<name1<<"^_^"
		<<endl; 
		system("pause"); 
		} 
		else 
			if(username1==username||passport1==passport)
			{ 
				cout<<"用户名或密码错误！ "
				<<endl; 
				log_in(); 
			} 
	} 
	storeFile.close(); 
	admin(); 
} 
 
void revise()
{
	system("cls");
	int r;
	string a, b, c,d, e, f, g,time,msg,msg1,choice;
	fstream file1("scoresheet.txt");
	while (!file1.eof())
	{
		char temp[100];
		file1.getline(temp,100);
		msg=UTF8ToGB(temp);
		cout << msg << endl;
	}
	cout << "请输入要修改的行数：" << endl;
	cin >> r;
	cout << "请输入商品编号" << endl;
	cin >> a;
	cout << "请输入商品名字" << endl;
	cin >> b;
	cout << "请输入商品价格" << endl;
	cin >> c;
	cout << "请输入商品颜色" << endl;
	cin >> d;
	cout << "请输入商品库存数量" << endl;
	cin >> e;
	cout << "请输入商品型号" << endl;
	cin >> f;
	cout << "请输入修改时间" << endl;
	cin >> time;
	g= a + "\t" + b + "\t" + c + "\t" + d + "\t" + e + "\t" + f+"\t"+time;
	modifyContentInFile1("scoresheet.txt", r, g);
	ifstream file("scoresheet.txt");
	while (!file.eof())
	{
		char temp[100];
		file.getline(temp,100);
		msg=UTF8ToGB(temp);
		cout << msg << endl;
	}
	file.close();
	cout<<"是否返回（Y/N）"<<endl;
	cin>>choice;
	if(choice=="y"||choice=="Y")
		admin();
	else
		exit(0); 
} 

void add()
{
	system("cls");
	ofstream newfile;
	newfile.open("scoresheet.txt", ios::app );
	string a, b, c, d, e, f,time,msg;
	cout << "请输入要加入的商品编号"; 
	cout<< endl;
	cin >> a;
	cout << "请输入要加入的商品名字";
	cout<< endl;
	cin >> b;
	cout << "请输入要加入的商品价格";
	cout<< endl;
	cin >> c;
	cout << "请输入要加入的商品颜色";
	cout<< endl;
	cin >> d;
	cout << "请输入要加入的商品库存数量";
	cout<< endl;
	cin >> e;
	cout << "请输入要加入的商品型号" ;
	cout<< endl;
	cin >> f;
	cout<<"请输入添加的时间";
	cout<<endl;
	cin>>time; 
	cout << endl;
	newfile << a << "\t" << b << "\t" << c << "\t" << d << "\t" << e << "\t" << f <<"\t"<<time<< endl;
	newfile.close();
	ifstream file("scoresheet.txt");
	while (!file.eof())
	{
		char newtemp[100];
		file.getline(newtemp, 100);
		msg=UTF8ToGB(newtemp);
		cout << msg << endl;
	}
	do 
	{
		cout << "添加成功，是否继续？Y\N" << endl;
		char p;
		cin >> p;

		if (p == 'y' || p == 'Y')
		{
			add();
		}
		else if (p == 'n' || p == 'N')
		{
			admin();
		}
	} while (true);
} 

void find()
{
	string msg;
	system("cls");
	ifstream file;
	file.open("scoresheet.txt", ios::out|ios::in);
	char line[100];//用于存储读取一行的内容
	while (!file.eof())
	{
		file.getline(line,100);
		msg=UTF8ToGB(line);
		cout << msg ;
		cout<< endl;
	}
	do
	{
		cout << "是否返回(N/Y)" ;
		cout<< endl;
		char p;
		cin >> p;
		if (p == 'y' || p == 'Y')
		{
			admin();
		}
		else
			break;
	} while (true);
}

void find1()
{
	string msg;
	system("cls");
	ifstream file;
	char line[2000];
	file.open("scoresheet.txt", ios::out|ios::in);
	while (!file.eof())
	{
		file.getline(line, 2000);
		msg=UTF8ToGB(line);
		cout << msg ;
		cout<< endl;
	}
	do
	{
		cout << "是否返回N/Y" << endl;
		char p;
		cin >> p;
		if (p == 'y' || p == 'Y')
		{
			user();
		}
	} while (true);
}


void modifyContentInFile(char* filename, int lineNum)
{
  ifstream in;  
    char line[1024];  //等于空串 ，定义并初始化了数组。 
    in.open(filename);  //用输入文件流打开名为fileName的文件 
    int i=0;  
    string tempStr;  
    while(in.getline(line,sizeof(line)))  //每次执行while循环时，先执行括号中的语句，使其line数组获得原文件一行的内容（字符串）。 
    {  
        i++;  
        if(lineNum!=i)  //判断要更改的内容行数是否是line数组当前获得的内容。//如果是则将要更改的内容加入进tempStr字符串中；如果不是，则将原文件i行的内容加入到tempStr字符串中。 
        {  
           tempStr+=char_to_string(line);
		   tempStr+='\n'; //每次加入一行内容后，进行提行。
        }   
    } 
		in.close();
		ofstream out;
		out.open(filename);
		out.flush();
		out << tempStr;
		out.close();

}

void deletex()
{
	string msg;
	system("cls");
	cout << "请输入要删除的行数";
	cout << endl;
	int x;
	cin >> x;
	x++ ;
	modifyContentInFile("scoresheet.txt",x);
	ifstream file("scoresheet.txt");
	while (!file.eof())
	{
		char temp[100];
		file.getline(temp, 100);
		msg=UTF8ToGB(temp);
		cout << msg << endl;
	}
	file.close();
	do
	{
		cout << "删除成功，是否继续Y/N" << endl;
		char p;
		cin >> p;
		if (p == 'y' || p == 'Y')
		{
			deletex();
		}
		else
			if (p == 'n' || p == 'N')
			{
				admin();
			}
	} while (true); 
}

void registerID( )
{ 
	system("cls");
	int j;
	string p;
	password password1;
	string password="Nick2019";
	password1.input();
	p=password1.get();
	if (string(password) == string(p))
	{
		cout<<endl;
		cout << "密码正确" ;
		cout<< endl;
		cout<<"欢迎您 ,"<<"^_^";
		cout<<endl; 
		cout << "按任意键继续" ;
		cout<< endl;
		system("pause");
		system("cls");
		string username,passport,passport1,name,miyao,jiami; 
		cout<<"请输入用户名： "; 
		cin>>username; 
		cout<<"请输入密码： "; 
		cin>>passport; 
		cout<<"请再次输入密码： "; 
		cin>>passport1; 
		if(passport==passport1)
		{ 
			cout<<"请输入您的姓名： "; 
			cin>>name; 
		} 
		else 
			if(passport!=passport1)
			{ 
			string passport1;
				cout<<"两次输入的密码不一致，请重新输入！ "<<endl;
	 			while(passport!=passport1) 
				{ 
					cout<<"请输入密码： "; 
					cin>>passport; 
					cout<<" 请再次输入密码： "; 
					cin>>passport1; 
				} 
				cout<<"请输入您的姓名： "; 
				cin>>name; 
			} 
		ofstream storeFile("userdate.txt", ios::app); 
		storeFile<<setiosflags(ios::left)<<setw(15)<<username<<" " 
		<<setw(15)<<passport<<" "<<setw(10)<<name<<endl; 
		storeFile.close(); 
		system("cls");
		cout<<"账户创建成功！欢迎您， ";
		cout<<name<<endl; 
		system("pause"); 
		system("cls"); 
		admin();
	}
	else
	{ 
	cout<<endl;
	cout<<"密码输入有误"<<endl;
	exit(0);
	}  
} 

void get_data()
{
	ifstream file;
	file.open("scoresheet.txt");
	do
	{
		char temp[100];
		file.getline(temp,100);
		cout<<temp<<endl;
		system("pause");
		cout<<"需要进货吗？？？？？"<<endl; 
	}
	while(!file.eof());
}

void admin()
{
	system("cls");
	cout<<"--*--*--*--*--*--*--*--*--*--*--*--*--*--*"<<endl;
	cout<<"--*--*--*--*--*--*--*--*--*--*--*--*--*--*"<<endl;
	cout << "欢迎使用库存管理系统" << endl;
	cout << "1-添加商品信息" << endl;
	cout<<"2-删除商品信息" << endl;
	cout << "3-修改商品信息" << endl;
	cout<<"4-查询商品信息" << endl;
	cout<<"5-返回" << endl;
	cout<<"--*--*--*--*--*--*--*--*--*--*--*--*--*--*"<<endl;
	cout<<"--*--*--*--*--*--*--*--*--*--*--*--*--*--*"<<endl;
	int w;
	cin >> w;
	switch (w)
	{
	case 1:
		add();
		break;
	case 2:
		deletex();
		break;
	case 3:
		revise();
		break;
	case 4:
		find();
		break;
	case 5:
		log_in();
		break; 
	default:
		cout << "输入错误，请重新输入" << endl;
		break;
	}
}

void administrator()
{
	int j;
	system("cls");
	string p;
	password password1;
	string password="Nick2019";
	password1.input();
	p=password1.get();
	if (string(password) == string(p))
	{
		cout<<endl;
		cout << "密码正确" << endl;
		cout<<"欢迎您 ,"<<"^_^"<<endl; 
		cout << "按任意键继续" << endl;
		system("pause");
		admin();
	}
	else
	{
		cout << "密码错误" << endl;
		cout << "重新输入" << endl;
		system("pause");
		administrator();
	}
	 
}

void yanzheng()
{
	int j;
	system("cls");
	string p;
	password password1;
	string password="Nick2019";
	password1.input();
	p=password1.get();
	if (string(password) == string(p))
	{
		cout<<endl;
		cout << "密码正确" << endl;
		cout<<"欢迎您 ,"<<"^_^"<<endl; 
		cout << "按任意键继续" << endl;
		system("pause");
	}
}

void user()
{
	system("cls");
	cout<<"--*--*--*--*--*--*--*--*--*--*--*--*--*--*"<<endl;
	cout << "欢迎使用库存管理系统" << endl;
	cout << "1-查询衣服信息" << endl;
	cout << "2-返回登录界面" << endl;
	cout<<"--*--*--*--*--*--*--*--*--*--*--*--*--*--*"<<endl;
	int w;
	cin >> w;
	switch (w)
	{
	case 1:
		find1();
		break;
	case 2:
		log_in();
		break;

	default:
		cout << "输入错误，请重新输入" << endl;
		user();
		break;
	}
}

void log_in()
{
	system("cls");
	cout<<"--*--*--*--*--*--*--*--*--*--*--*--*--*--*"<<endl;
	cout<<"--*--*--*--*--*--*--*--*--*--*--*--*--*--*"<<endl;
	cout << "欢迎使用库存管理系统" << endl;
	cout << "1-本地管理员" << endl;
	cout << "2-注册管理用户" << endl;
	cout << "3-添加管理员" ;
	cout<<"请先注册管理用户"<< endl;
	cout << "4-用户" << endl;
	cout << "5-退出" << endl;
	cout<<"--*--*--*--*--*--*--*--*--*--*--*--*--*--*"<<endl;
	cout<<"--*--*--*--*--*--*--*--*--*--*--*--*--*--*"<<endl;
	cout<<" Technical support ：Nick Wiber"<<endl;
	int q;
	cin >> q;
	switch (q)
	{
	case 1:
		administrator();
		break;
	case 2:
		registerID();
		 break;
	case 3:
		 administrator1();
		 break; 
	case 4:
		user();
		break;
	case 5:
		exit(1);
		break;

	default: cout << "输入不正确，请重新输入" << endl;
		system("cls");
		log_in();
		break;
	}
}

int main()
{
	log_in();
	return 0;
}
