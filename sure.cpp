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
		        passwd ="";//��ʼ���ַ��� 
		        length = 0;//��ʼ���ַ������� 
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
   cout<<"���������Ա���룺"<<endl;
   while(true)
   {
   	ps = getch();//ֱ�ӻ���û�������ַ� 
     if(ps!=13)//�ж��û�������Ƿ���enter���������ֱ��ֹͣ��ǰwhileѭ���� 
	 {
	switch(ps)//��switch������ж��û�����ļ�����ʵ����Ӧ���ܡ� 
	{
		case 8: //����û��������BACKSPACE������ʵ���˸��ܡ�
		if(length!=0) //���length������0�Ļ�ʵ���˸��ܡ� 
		{
			cout<<"\b \b";//��һ��\b�ǽ������ǰ�ƶ�һ��Ȼ�����һ���ո��ַ�" "��֮ǰ������ַ����ǣ��ڶ���\b�ٽ������ǰ�ƶ�һ��ʵ�����˸��ܡ� 
			passwd = passwd.substr(0,length-1);	//��passwd�ַ���ȡ��0λ���ַ������ȼ���1λ��ֵ��password���൱�ڵ�password�������һλ�� 
			length--;  //�ַ������ȼ���һ�� 
		}
		     else;// ���length����0���޷�ʵ���˸��ܡ�ֱ����ֹswitch��䡣 
			  break;
		default:  cout<<"*";//����û����������ļ��Ļ�������ʾ*�� 
		          length++;//�ַ�����������1. 
		          passwd +=ps;//���û�������ַ��ӵ�passwd�ַ���� 
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

     //�����ʱ�����Ĵ�С
     int i = MultiByteToWideChar(CP_UTF8, 0, str, -1, NULL, 0);
     strSrc = new WCHAR[i+1];
     MultiByteToWideChar(CP_UTF8, 0, str, -1, strSrc, i);

     //�����ʱ�����Ĵ�С
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
		cout << "�޷��򿪴��ļ�" << endl;
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
	cout<<"\n\n\t �Բ����û��ļ���ʧ�� �� ��\n\n\t"; 
	system("pause"); 
	return; 
	} 
	cout<<"�û���¼�� "<<endl; 
	cout<<"�������û����� "; 
	cin>>username; 
	cout<<"���������룺 "; 
	cin>>passport; 
	bool flag=false; 
	while(storeFile>>username1>>passport1>>name1) 
	{ 
		if(username1==username&&passport1==passport) 
		{ 
		flag=true; 
		system("cls"); 
		cout<<"��¼�ɹ��� "
		<<endl;
		cout<<"��ӭ�� ,"
		<<name1<<"^_^"
		<<endl; 
		system("pause"); 
		} 
		else 
			if(username1==username||passport1==passport)
			{ 
				cout<<"�û������������ "
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
	cout << "������Ҫ�޸ĵ�������" << endl;
	cin >> r;
	cout << "��������Ʒ���" << endl;
	cin >> a;
	cout << "��������Ʒ����" << endl;
	cin >> b;
	cout << "��������Ʒ�۸�" << endl;
	cin >> c;
	cout << "��������Ʒ��ɫ" << endl;
	cin >> d;
	cout << "��������Ʒ�������" << endl;
	cin >> e;
	cout << "��������Ʒ�ͺ�" << endl;
	cin >> f;
	cout << "�������޸�ʱ��" << endl;
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
	cout<<"�Ƿ񷵻أ�Y/N��"<<endl;
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
	cout << "������Ҫ�������Ʒ���"; 
	cout<< endl;
	cin >> a;
	cout << "������Ҫ�������Ʒ����";
	cout<< endl;
	cin >> b;
	cout << "������Ҫ�������Ʒ�۸�";
	cout<< endl;
	cin >> c;
	cout << "������Ҫ�������Ʒ��ɫ";
	cout<< endl;
	cin >> d;
	cout << "������Ҫ�������Ʒ�������";
	cout<< endl;
	cin >> e;
	cout << "������Ҫ�������Ʒ�ͺ�" ;
	cout<< endl;
	cin >> f;
	cout<<"��������ӵ�ʱ��";
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
		cout << "��ӳɹ����Ƿ������Y\N" << endl;
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
	char line[100];//���ڴ洢��ȡһ�е�����
	while (!file.eof())
	{
		file.getline(line,100);
		msg=UTF8ToGB(line);
		cout << msg ;
		cout<< endl;
	}
	do
	{
		cout << "�Ƿ񷵻�(N/Y)" ;
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
		cout << "�Ƿ񷵻�N/Y" << endl;
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
    char line[1024];  //���ڿմ� �����岢��ʼ�������顣 
    in.open(filename);  //�������ļ�������ΪfileName���ļ� 
    int i=0;  
    string tempStr;  
    while(in.getline(line,sizeof(line)))  //ÿ��ִ��whileѭ��ʱ����ִ�������е���䣬ʹ��line������ԭ�ļ�һ�е����ݣ��ַ������� 
    {  
        i++;  
        if(lineNum!=i)  //�ж�Ҫ���ĵ����������Ƿ���line���鵱ǰ��õ����ݡ�//�������Ҫ���ĵ����ݼ����tempStr�ַ����У�������ǣ���ԭ�ļ�i�е����ݼ��뵽tempStr�ַ����С� 
        {  
           tempStr+=char_to_string(line);
		   tempStr+='\n'; //ÿ�μ���һ�����ݺ󣬽������С�
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
	cout << "������Ҫɾ��������";
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
		cout << "ɾ���ɹ����Ƿ����Y/N" << endl;
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
		cout << "������ȷ" ;
		cout<< endl;
		cout<<"��ӭ�� ,"<<"^_^";
		cout<<endl; 
		cout << "�����������" ;
		cout<< endl;
		system("pause");
		system("cls");
		string username,passport,passport1,name,miyao,jiami; 
		cout<<"�������û����� "; 
		cin>>username; 
		cout<<"���������룺 "; 
		cin>>passport; 
		cout<<"���ٴ��������룺 "; 
		cin>>passport1; 
		if(passport==passport1)
		{ 
			cout<<"���������������� "; 
			cin>>name; 
		} 
		else 
			if(passport!=passport1)
			{ 
			string passport1;
				cout<<"������������벻һ�£����������룡 "<<endl;
	 			while(passport!=passport1) 
				{ 
					cout<<"���������룺 "; 
					cin>>passport; 
					cout<<" ���ٴ��������룺 "; 
					cin>>passport1; 
				} 
				cout<<"���������������� "; 
				cin>>name; 
			} 
		ofstream storeFile("userdate.txt", ios::app); 
		storeFile<<setiosflags(ios::left)<<setw(15)<<username<<" " 
		<<setw(15)<<passport<<" "<<setw(10)<<name<<endl; 
		storeFile.close(); 
		system("cls");
		cout<<"�˻������ɹ�����ӭ���� ";
		cout<<name<<endl; 
		system("pause"); 
		system("cls"); 
		admin();
	}
	else
	{ 
	cout<<endl;
	cout<<"������������"<<endl;
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
		cout<<"��Ҫ�����𣿣�������"<<endl; 
	}
	while(!file.eof());
}

void admin()
{
	system("cls");
	cout<<"--*--*--*--*--*--*--*--*--*--*--*--*--*--*"<<endl;
	cout<<"--*--*--*--*--*--*--*--*--*--*--*--*--*--*"<<endl;
	cout << "��ӭʹ�ÿ�����ϵͳ" << endl;
	cout << "1-�����Ʒ��Ϣ" << endl;
	cout<<"2-ɾ����Ʒ��Ϣ" << endl;
	cout << "3-�޸���Ʒ��Ϣ" << endl;
	cout<<"4-��ѯ��Ʒ��Ϣ" << endl;
	cout<<"5-����" << endl;
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
		cout << "�����������������" << endl;
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
		cout << "������ȷ" << endl;
		cout<<"��ӭ�� ,"<<"^_^"<<endl; 
		cout << "�����������" << endl;
		system("pause");
		admin();
	}
	else
	{
		cout << "�������" << endl;
		cout << "��������" << endl;
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
		cout << "������ȷ" << endl;
		cout<<"��ӭ�� ,"<<"^_^"<<endl; 
		cout << "�����������" << endl;
		system("pause");
	}
}

void user()
{
	system("cls");
	cout<<"--*--*--*--*--*--*--*--*--*--*--*--*--*--*"<<endl;
	cout << "��ӭʹ�ÿ�����ϵͳ" << endl;
	cout << "1-��ѯ�·���Ϣ" << endl;
	cout << "2-���ص�¼����" << endl;
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
		cout << "�����������������" << endl;
		user();
		break;
	}
}

void log_in()
{
	system("cls");
	cout<<"--*--*--*--*--*--*--*--*--*--*--*--*--*--*"<<endl;
	cout<<"--*--*--*--*--*--*--*--*--*--*--*--*--*--*"<<endl;
	cout << "��ӭʹ�ÿ�����ϵͳ" << endl;
	cout << "1-���ع���Ա" << endl;
	cout << "2-ע������û�" << endl;
	cout << "3-��ӹ���Ա" ;
	cout<<"����ע������û�"<< endl;
	cout << "4-�û�" << endl;
	cout << "5-�˳�" << endl;
	cout<<"--*--*--*--*--*--*--*--*--*--*--*--*--*--*"<<endl;
	cout<<"--*--*--*--*--*--*--*--*--*--*--*--*--*--*"<<endl;
	cout<<" Technical support ��Nick Wiber"<<endl;
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

	default: cout << "���벻��ȷ������������" << endl;
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
