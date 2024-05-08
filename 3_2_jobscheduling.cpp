#include<iostream>
using namespace std;

struct Job{
    int jobId;
    int profit;
    int deadline;
};

class JobScheduling{

    struct Job jobs[10];
    int n;
    public:
        JobScheduling()
        {
            cout<<"Enter number of jobs: ";
            cin>>n;
            for(int i=0;i<n;i++){
                struct Job job;
                job.jobId=i+1;
                cout<<"Enter job profit: ";
                cin>>job.profit;
                cout<<"Enter job deadline: ";
                cin>>job.deadline;
                jobs[i]=job;
            }

        }

        int findMaxDeadline(){
            int max_deadline=0;

            for(int i=0;i<n;i++){
                if(jobs[i].deadline >max_deadline){
                    max_deadline=jobs[i].deadline;
                }
            }
            return max_deadline;
        }

        void findMaxProfitSchedule(){
            
             int max_profit=0;
            for(int i=0;i<n;i++){
                max_profit=i;
                for(int j=i;j<n;j++){
                    if(jobs[i].profit>max_profit){
                        max_profit=i;
                    }
                }
                Job temp=jobs[i];
                jobs[i]=jobs[max_profit];
                jobs[max_profit]=temp;
                
            }

            int max_deadline=findMaxDeadline();

            int schedule[max_deadline];

            for(int i=0;i<max_deadline;i++){
                schedule[i]=-1;
            }

            int total_profit=0;
            for(int i=0;i<n;i++){
                for(int j=min(max_deadline,jobs[i].deadline)-1;j>=0;j--){
                    if(schedule[j]==-1){
                        schedule[j]=jobs[i].jobId;
                        total_profit+=jobs[i].profit;
                        break;
                    }

                }
            }

cout<<"Scheduled jobs: ";
            for(int i=0;i<max_deadline;i++){
                if(schedule[i]!=-1){
                    cout<<"job "<<schedule[i]<<"\t";
                }
            }
            cout<<"\nTotal profit: "<<total_profit;
          
        }

};

int main(){

    JobScheduling j;
    j.findMaxProfitSchedule();
    return 0;
}
