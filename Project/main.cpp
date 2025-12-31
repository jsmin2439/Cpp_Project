#include <cstring>
#include <iostream>
using namespace std;
class Team{
    int id;
    char* name;
public:
    Team(int id, char* name){
        this->id=id;
        this->name = new char[strlen(name) + 1];
        strcpy(this->name,name);
    }
    ~Team(){
        delete[] name;
    }
    void showdata();
    int getid();
    char* getname();
};
void Team::showdata(){
    cout<<" 팀("<<id<<", "<<name<<")"<<endl;
}
int Team::getid(){
    return id;
}
char* Team::getname(){
    return name;
}

class Teamman{
    Team* tList[50];
    int index;
public:
    Teamman(){
        index=0;
    }
    void Teamadd(Team* team);
    void showall();
    Team* findteam(int id);
};
void Teamman::Teamadd(Team* team){
    if(index<50){
        tList[index++]=team;
    }
}
void Teamman::showall(){
    for(int i=0;i<index;i++){
        tList[i]->showdata();
    }
}
Team* Teamman::findteam(int id){
    for(int i=0;i<index;i++){
        if(tList[i]->getid()==id){
            return tList[i];
        }
    }
    return 0;
}

class Member{
protected:
    int id;
    char* name;
    Team* team;
public:
    Member(int id, char* name, Team* team){
        this->id=id;
        this->name=new char[strlen(name)+1];
        strcpy(this->name,name);
        this->team=team;
    }
    virtual ~Member(){
        delete [] name;
    }
    virtual void menteeshowdata(){}
    virtual void mentorshowdata(){}
    
};
class mentee:public Member{
    char* major;
    int grade;
public:
    mentee(int id, char* name, Team* team, char* major, int grade):Member(id, name, team){
        this->major=new char[strlen(major)+1];
        strcpy(this->major,major);
        this->grade=grade;
    }
    ~mentee(){
        delete [] major;
    }
    void menteeshowdata(){
        cout<<"멘티("<<id<<", "<<name<<", "<<team->getname()<<", "<<major<<", "<<grade<<")"<<endl;
    }
};
class mentor:public Member{
    char* org;
    char* jobtitle;
public:
    mentor(int id, char* name, Team* team, char* org, char* jobtitle):Member(id, name, team){
        this->org=new char[strlen(org)+1];
        strcpy(this->org,org);
        this->jobtitle=new char[strlen(jobtitle)+1];
        strcpy(this->jobtitle,jobtitle);
    }
    ~mentor(){
        delete [] org;
        delete [] jobtitle;
    }
    void mentorshowdata(){
        cout<<"멘토("<<id<<", "<<name<<", "<<team->getname()<<", "<<org<<", "<<jobtitle<<")"<<endl;
    }
};
class Memberman{
    Member* mList[50];
    int index;
public:
    Memberman(){
        index=0;
    }
    void addmember(Member* member);
    void menteeshowall();
    void mentorshowall();
};
void Memberman::addmember(Member* member){
    if(index<50){
        mList[index++]=member;
    }
}
void Memberman::menteeshowall(){
    for(int i=0;i<index;i++){
        mList[i]->menteeshowdata();
    }
}
void Memberman::mentorshowall(){
    for(int i=0;i<index;i++){
        mList[i]->mentorshowdata();
    }
}

class mainmeu{
    int curMenu;
public:
    int issue();
};
int mainmeu::issue(){
    cout<<"--------< 메 뉴 >---------"<<endl;
    cout<<"  1. 팀 등록"<<endl;
    cout<<"  2. 팀 목록 출력"<<endl;
    cout<<endl;
    cout<<"  3. 멘티 추가"<<endl;
    cout<<"  4. 멘토 추가"<<endl;
    cout<<endl;
    cout<<"  5. 멘티목록 출력"<<endl;
    cout<<"  6. 멘토목록 출력"<<endl;
    cout<<endl;
    cout<<"  7. 전체 구성원 출력"<<endl;
    cout<<"  8. 팀별 구성원 출력"<<endl;
    cout<<endl;
    cout<<"  9. 화면정리"<<endl;
    cout<<"  0. 종료"<<endl;
    cout<<"-------------------------"<<endl;
    cout<<"  선택>>";
    cin>>curMenu;
    return curMenu;
}
class mainctrl{
    mainmeu mm;
    Teamman t;
    Memberman m;
public:
    void run();
};
void mainctrl::run(){
    int id;
    int t_id;
    char name[32];
    int grade;
    char major[32];
    char org[32];
    char jobtitle[32];
    int menu=0;
    while(1){
        switch (menu=mm.issue()) {
            case 1:
                cout<<"-------------------------"<<endl;
                cout<<" - id:";
                cin>>id;
                cout<<" - 이름:";
                cin>>name;
                t.Teamadd(new Team(id, name));
                cout<<">>"<<name<<": 새로운 팀을 등록 하였습니다"<<endl;
                break;
            case 2:
                cout<<"-------------------------"<<endl;
                cout<<"팀(ID, 이름) :"<<endl;
                cout<<"-------------------------"<<endl;
                t.showall();
                break;
            case 3:
                cout<<"-------------------------"<<endl;
                cout<<" - id:";
                cin>>id;
                cout<<" - 이름:";
                cin>>name;
                cout<<"-------------------------"<<endl;
                t.showall();
                cout<<">> 팀 id: ";
                cin>>t_id;
                cout<<" - 전공:";
                cin>>major;
                cout<<" - 학년:";
                cin>>grade;
                m.addmember(new mentee(id,name,t.findteam(t_id),major,grade));
                cout<<">>"<<name<<": 새로운 멘티를 등록 하였습니다"<<endl;
                break;
            case 4:
                cout<<"-------------------------"<<endl;
                cout<<" - id:";
                cin>>id;
                cout<<" - 이름:";
                cin>>name;
                cout<<"-------------------------"<<endl;
                t.showall();
                cout<<">> 팀 id: ";
                cin>>t_id;
                cout<<" - 소속:";
                cin>>org;
                cout<<" - 직위:";
                cin>>jobtitle;
                m.addmember(new mentor(id,name,t.findteam(t_id),org,jobtitle));
                cout<<">>"<<name<<": 새로운 멘토를 등록 하였습니다"<<endl;
                break;
            case 5:
                cout<<"-------------------------"<<endl;
                cout<<"팀(ID, 이름, 팀 이름 전공, 학년) :"<<endl;
                cout<<"-------------------------"<<endl;
                m.menteeshowall();
                break;
            case 6:
                cout<<"-------------------------"<<endl;
                cout<<"팀(ID, 이름, 팀 이름, 소속, 직위) :"<<endl;
                cout<<"-------------------------"<<endl;
                m.mentorshowall();
                break;
            case 7:
                cout<<"-------------------------"<<endl;
                cout<<"팀(ID, 이름, 팀 이름, 전공/소속, 학년/직위) :"<<endl;
                cout<<"-------------------------"<<endl;
                m.menteeshowall();
                m.mentorshowall();
                break;
            case 8:
                cout<<"-------------------------"<<endl;
                cout<<"팀(ID, 이름) :"<<endl;
                cout<<"-------------------------"<<endl;
                t.showall();
                cout<<">> 팀 id: ";
                cin>>t_id;
                break;
            case 9:
                system("clear");
                break;
            case 0:
                exit(1);
                break;
            default:
                break;
        }
    }
}
int main(){
    mainctrl mc;
    mc.run();
    return 0;
}

