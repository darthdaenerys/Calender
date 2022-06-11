#include<bits/stdc++.h>
using namespace std;
unordered_map<int,string> yearstart={{0,"Sun"},{1,"Tue"},{2,"Wed"},{3,"Thr"},{4,"Fri"},{5,"Sun"},{6,"Mon"},{7,"Tue"},{8,"Wed"},{9,"Fri"},{10,"Sat"},{11,"Sun"},{12,"Mon"},{13,"Wed"},{14,"Thr"},{15,"Fri"},{16,"Sat"},{17,"Mon"},{18,"Tue"},{19,"Wed"},{20,"Thr"},{21,"Sat"},{22,"Sun"},{23,"Mon"},{24,"Tue"},{25,"Thr"},{26,"Fri"},{27,"Sat"}};
int monthstartdate[12]={1,1,1,1,1,1,1,1,1,1,1,1};
int monthenddate[12]={31,28,31,30,31,30,31,31,30,31,30,31};
void reset()
{
    for(int i=0;i<12;i++)
        monthstartdate[i]=1;
    monthenddate[0]=monthenddate[2]=monthenddate[4]=monthenddate[6]=monthenddate[7]=monthenddate[9]=monthenddate[11]=31;
    monthenddate[1]=28;
    monthenddate[3]=monthenddate[5]=monthenddate[8]=monthenddate[10]=30;
}
unordered_map<int,string> weekday={{0,"Sat"},{1,"Sun"},{2,"Mon"},{3,"Tue"},{4,"Wed"},{5,"Thu"},{6,"Fri"}};
unordered_map<int,string> monthmap={{0,"January"},{1,"February"},{2,"March"},{3,"April"},{4,"May"},{5,"June"},{6,"July"},{7,"August"},{8,"September"},{9,"October"},{10,"November"},{11,"December"}};
map<int,pair<int,string>> monthstartday;  // {day index,day name}
string getstartday(int year)
{
    int base=year-2012;
    while(base<0) base+=28;
    return yearstart[base%28];
}
void addmonthname(string &s,int month)
{
    int gaps=(28-monthmap[month].length())/2;
    for(int i=0;i<gaps;i++) s.push_back(' ');
    s+=monthmap[month];
    for(int i=0;i<29-(monthmap[month].length()+gaps);i++) s.push_back(' ');
}
void fillfirstrow(string &calender,int j)
{
    for(int i=j;i<j+3;i++)
    {
        calender.push_back(' ');
        pair<int,string> p=monthstartday[i];
        int k=1;
        while(k%7!=p.first)
        {
            calender+="    ";
            k++;
        }
        bool flag=0;
        while(k%7!=1 || flag==0)
        {
            calender+=" ";
            if(monthstartdate[i]<=monthenddate[i])
            {
                if(monthstartdate[i]/10==0)
                    calender+=" ";
                calender+=to_string(monthstartdate[i]);
                monthstartdate[i]++;
            }
            else
                calender+=" ";
            calender+=" ";
            k++;
            flag=1;
        }
        calender+="|";
    }
    calender.pop_back();
    calender.push_back('\n');
}
string printCalender(string startday,int year)
{
    if(year%4==0) monthenddate[1]=29;
    int idx;
    if(startday=="Sun") idx=1;
    else if(startday=="Mon") idx=2;
    else if(startday=="Tue") idx=3;
    else if(startday=="Wed") idx=4;
    else if(startday=="Thu") idx=5;
    else if(startday=="Fri") idx=6;
    else idx=0;
    for(int i=0;i<12;i++)
    {
        monthstartday[i]={idx,weekday[idx]};
        if(i==0 || i==2 || i==4 || i==6 || i==7 || i==9 || i==11)
        {
            idx+=3;
            idx%=7;
        }
        else if(i==1)
        {
            if(year%4==0)
            {
                idx+=1;
                idx%=7;
            }
        }
        else
        {
            idx+=2;
            idx%=7;
        }
    }
    string calender;
    int monthidx=0,rowfill=0;
    for(int i=0;i<4;i++)
    {
        addmonthname(calender,monthidx++);
        calender+='|';
        addmonthname(calender,monthidx++);
        calender+='|';
        addmonthname(calender,monthidx++);
        calender+='\n';
        for(int j=0;j<29.1*3;j++)
            calender.push_back('-');
        calender.push_back('\n');
        for(int j=0;j<3;j++)
        {
            calender+=' ';
            for(int k=1;k<=7;k++)
                calender+=(weekday[k%7]+" ");
            calender+="|";        
        }
        calender.pop_back();
        calender.pop_back();
        calender+="\n";
        
        // fill dates
        fillfirstrow(calender,rowfill);
        for(int j=0;j<5;j++)
        {
            for(int k=rowfill;k<rowfill+3;k++)
            {
                int temp=1;
                bool flag=0;
                calender.push_back(' ');
                while(temp%7!=1 || flag==0)
                {
                    calender+=" ";
                    if(monthstartdate[k]<=monthenddate[k])
                    {
                        if(monthstartdate[k]/10==0)
                            calender+=' ';
                        calender+=(to_string(monthstartdate[k])+" ");
                        monthstartdate[k]++;
                    }
                    else
                        calender+="   ";
                    flag=1;
                    temp++;
                }
                calender.push_back('|');
            }
            calender.pop_back();
            calender.push_back('\n');
        }
        rowfill+=3;
    }
    return calender;
}
void solve()
{
    cout<<"Enter the year: ";
    int year;
    cin>>year;
    string startday=getstartday(year);
    cout<<printCalender(startday,year);
    reset();
}
int main()
{
    int t;
    cin>>t;
    while(t--)
    {
        solve();
        cout<<'\n';
    }
}