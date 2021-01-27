#include <stdlib.h>
#include <list>
#include <set>
#include <iostream>
#include <fstream>
#include <cstdlib>// Header file needed to use rand
#include<cmath>
using  namespace  std;

int main(int argc,char *argv[])
{

     int n,k,f,times,i,j,count;
     n=atoi (argv[1]);
	 k = atoi(argv[2]);     //n=16 k=5;

     times=5;
     list< long > queuePage;
     long trace[n];
     set< long > existqueuePage;
     long maxpagenum=pow(2,k);
     for(i=0;i<n;i++){
         trace[i]=rand()%maxpagenum;
     }
     i=0;
    ofstream out("result.csv");

         for(f=4;f<=pow(2,k);f++){
             cout << "---------------------------------------------"<< endl;
             cout << "f="<< f << endl;
             count=0;
             queuePage.clear();
             existqueuePage.clear();
         for(j=0;j<n;j++){
            long curpagename= trace[j];
            set<long>::iterator iter;
            if((iter=existqueuePage.find(curpagename)) == existqueuePage.end()) {
                count++;
                if (queuePage.size() == f) {
                    long del = queuePage.front();
                    queuePage.pop_front();
                    queuePage.push_back(curpagename);
                    existqueuePage.insert(curpagename);
                    //delete set item
                    existqueuePage.erase(del);
                } else {
                    queuePage.push_back(curpagename);
                    existqueuePage.insert(curpagename);
                }
            }

                cout << j << " round page number is " << curpagename << endl;
                list<long>::iterator it;
                for (it = queuePage.begin(); it != queuePage.end(); it++) {
                    cout << *it << " ";
                }
                cout << endl;
            }
             cout<<"the number of page faults is "<<count<<endl;
             cout<<endl;

             out<<f<<","<<count<<endl;

         }
         out.close();

}
