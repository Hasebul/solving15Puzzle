#include<bits/stdc++.h>
#define NIL 0
#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4
using namespace std;


class Node{

    int currElement[20];
    int curPosition;//current blank position
    int curOpp;
    int misPlaceCost=0;
    int manHattanCost=0;
    int cost=0;

 public:

    //----------------------------setting variable value -----------------------------

    void setcurrElement(int arr[]){
      for(int i=0;i<16;i++) currElement[i]=arr[i];
    }
    void setCurPosition(int i){
      curPosition=i;
    }
    void setCurOpp(int opp){
     curOpp=opp;
    }
    void setMisPlaceCost(int mis){
      misPlaceCost=mis;
    }
    void setManHattanCost(int man){
      manHattanCost=man;
    }
    void setCost(int c){
	  cost=c;
    }





    int countManHattanCost(){
	   int count=0;

	   for(int i=0;i<16;i++){
           if(currElement[i]==0) continue;
           int x1=currElement[i] - ((currElement[i]/4)*4);
           if(x1==0) x1=4;
           int y1=ceil(currElement[i]/4.0);
           int x2=(i+1) - (((i+1)/4)*4);
           if(x2==0) x2=4;
           int y2=ceil((i+1)/4.0);
           int mandis=abs(x1-x2)+abs(y1-y2);
           count+=mandis;
	   }
	   manHattanCost=count;
	   return manHattanCost;
    }

    int countMisPlaceCost(){
         int count=0;

         for(int i=0;i<16;i++){
	     if(currElement[i]==0) continue;
		 if(currElement[i]!=(i+1)) count++;
		 }
         misPlaceCost=count;

         return misPlaceCost;
    }


    int findCurPosition(){
    for(int i=0;i<16;i++) {if(currElement[i]==0) {curPosition=i; return i;}}
    }

   void swapPos(int i,int j){ //swap and update cost
    // ---before changing manHattan and misPlace cost of position i
    	   int x1=currElement[j] - ((currElement[j]/4)*4);
           if(x1==0) x1=4;
           int y1=ceil(currElement[j]/4.0);
           int x2=(j+1) - (((j+1)/4)*4);
           if(x2==0) x2=4;
           int y2=ceil((j+1)/4.0);
           int mandis=abs(x1-x2)+abs(y1-y2);


        int preMan=mandis;
        int preMis=(currElement[j]==(j+1)?0:1);


    //swap operation----------------
		 int a=currElement[i];
		 currElement[i]=currElement[j];
		 currElement[j]=a;
	//---after changing cost of position j

		x2=(i+1) - (((i+1)/4)*4);
		if(x2==0) x2=4;
		y2=ceil((i+1)/4.0);
		mandis=abs(x1-x2)+abs(y1-y2);

        int postMan=mandis;
        int postMis=(currElement[i]==(i+1)?0:1);

        //------update value----------

		 manHattanCost=manHattanCost-preMan+postMan;
		 misPlaceCost=misPlaceCost-preMis+postMis;
		 curPosition=j;

  //
         return;


    }


    void printState(){
      for(int i=0;i<16;i++){

		cout<<currElement[i]<<" ";
		if(i%4==3) cout<<endl;

      }

    }

    bool isSolveAble(){

       int pointer=this->findCurPosition();
       pointer=ceil((pointer+1)/4.0);


       int inv=0;
       for(int i=0;i<16;i++){
		if(currElement[i]==0) continue;
		for(int j=i+1;j<16;j++){
			if(currElement[j]==0) continue;
			if(currElement[i]>currElement[j]) inv++;
		}
       }
       if( (pointer%2==0 && inv%2==0) || (pointer%2==1 && inv%2==1) ) return true;
       else return false;


    }




   //-------------------------getting variable value----------------------------------

    int getCurPosition(){
      return curPosition;
    }
    int getCurOpp(){
     return curOpp;
    }
    int getMisPlaceCost(){
      return misPlaceCost;
    }
    int getManHattanCost(){
      return manHattanCost;
    }
    int getCost(){
       return cost;
	}

};


class CompareManhattan{
public:
	bool operator()(Node a,Node b)
	{
		return a.getManHattanCost()+a.getCost()>b.getManHattanCost()+b.getCost();
	}

};

class CompareMisPlace{
public:
	bool operator()(Node a,Node b){
	return a.getMisPlaceCost()+a.getCost()>b.getMisPlaceCost()+b.getCost();
	}

};






void solvingPuzzle(int arr[]){

	Node initialState;
	initialState.setcurrElement(arr);
	initialState.setCurOpp(NIL);
	initialState.setCost(0);


     if( !initialState.isSolveAble() ){
		cout<<"This puzzle can't be solved "<<endl;
		return ;
     }

	//int method;
	//cout<<"Select method  :\n 1.Manhattan Cost \n 2.Misplacement Cost "<<endl;
	//cin>>method;


	//if(method==1)
		{

		cout<<"---------Working on Manhattan Cost-----------------"<<endl;

		priority_queue <Node,vector<Node>,CompareManhattan> myPq;
		initialState.countManHattanCost();
		initialState.findCurPosition();
		myPq.push(initialState);



     while(true)
      {
		Node currentNode=myPq.top();
		myPq.pop();
		//-----------making children of these node------------------
		//cout<<currentNode.countManHattanCost()<<endl;

		//cout<<"chek:1 "<<currentNode.getCost()<<endl;


		if(currentNode.getManHattanCost()==0) {
			//print the result and break the loop;
			cout<<"Final_STATE_COST:  "<<currentNode.getCost()<<"---------"<<endl;
		    currentNode.printState();
		    cout<<endl;
			break;
		}

		cout<<"STATE_:"<<currentNode.getCost()<<"----Manhattan cost:"<<currentNode.getManHattanCost()<<endl;
		cout<<"total cost: "<<currentNode.getCost()+currentNode.getManHattanCost()<<endl;
		currentNode.printState();
		cout<<endl;


		int curZeroPos=currentNode.getCurPosition();


		if(currentNode.getCurOpp()==NIL){

				//---up--operation--is--not--0<=curZeroPos<=3
				if(!(curZeroPos>=0 && curZeroPos<=3)){

					Node newNode=currentNode;
				    newNode.swapPos(curZeroPos,curZeroPos-4);
				    newNode.setCurOpp(UP);
				    newNode.setCost(currentNode.getCost()+1);
				    myPq.push(newNode);

				}

				//-----down--operation
				if(!(curZeroPos>=12 && curZeroPos<=15)){

					Node newNode=currentNode;
				    newNode.swapPos(curZeroPos,curZeroPos+4);
				    newNode.setCurOpp(DOWN);
				    newNode.setCost(currentNode.getCost()+1);
				    myPq.push(newNode);
				}



				//------left--operation
				if(!(curZeroPos%4==0)){

					Node newNode=currentNode;
				    newNode.swapPos(curZeroPos,curZeroPos-1);
				    newNode.setCurOpp(LEFT);
				    newNode.setCost(currentNode.getCost()+1);
				    myPq.push(newNode);
				}



				//right --operation

				if(!(curZeroPos%4==3)){

					Node newNode=currentNode;
				    newNode.swapPos(curZeroPos,curZeroPos+1);
				    newNode.setCurOpp(RIGHT);
				    newNode.setCost(currentNode.getCost()+1);
				    myPq.push(newNode);
				}


		}



  		else if(currentNode.getCurOpp()==UP){

				//---up--operation--is--not--0<=curZeroPos<=3
				if(!(curZeroPos>=0 && curZeroPos<=3)){

					Node newNode=currentNode;
				    newNode.swapPos(curZeroPos,curZeroPos-4);
				    newNode.setCurOpp(UP);
				    newNode.setCost(currentNode.getCost()+1);
				    myPq.push(newNode);
				}

				//-----down--operation




				//------left--operation
				if(!(curZeroPos%4==0)){

					Node newNode=currentNode;
				    newNode.swapPos(curZeroPos,curZeroPos-1);
				    newNode.setCurOpp(LEFT);
				    newNode.setCost(currentNode.getCost()+1);
				    myPq.push(newNode);
				}



				//right --operation

				if(!(curZeroPos%4==3)){

					Node newNode=currentNode;
				    newNode.swapPos(curZeroPos,curZeroPos+1);
				    newNode.setCurOpp(RIGHT);
				    newNode.setCost(currentNode.getCost()+1);
				    myPq.push(newNode);
				}


		}
		else if(currentNode.getCurOpp()==DOWN){

				//---up--operation--is--not--0<=curZeroPos<=3

				//-----down--operation
				if(!(curZeroPos>=12 && curZeroPos<=15)){

					Node newNode=currentNode;
				    newNode.swapPos(curZeroPos,curZeroPos+4);
				    newNode.setCurOpp(DOWN);
				    newNode.setCost(currentNode.getCost()+1);
				    myPq.push(newNode);
				}



				//------left--operation
				if(!(curZeroPos%4==0)){

					Node newNode=currentNode;
				    newNode.swapPos(curZeroPos,curZeroPos-1);
				    newNode.setCurOpp(LEFT);
				    newNode.setCost(currentNode.getCost()+1);
				    myPq.push(newNode);
				}



				//right --operation

				if(!(curZeroPos%4==3)){

					Node newNode=currentNode;
				    newNode.swapPos(curZeroPos,curZeroPos+1);
				    newNode.setCurOpp(RIGHT);
				    newNode.setCost(currentNode.getCost()+1);
				    myPq.push(newNode);
				}

		}
		else if(currentNode.getCurOpp()==LEFT){
				//---up--operation--is--not--0<=curZeroPos<=3
				if(!(curZeroPos>=0 && curZeroPos<=3)){

					Node newNode=currentNode;
				    newNode.swapPos(curZeroPos,curZeroPos-4);
				    newNode.setCurOpp(UP);
				    newNode.setCost(currentNode.getCost()+1);
				    myPq.push(newNode);
				}

				//-----down--operation
				if(!(curZeroPos>=12 && curZeroPos<=15)){

					Node newNode=currentNode;
				    newNode.swapPos(curZeroPos,curZeroPos+4);
				    newNode.setCurOpp(DOWN);
				    newNode.setCost(currentNode.getCost()+1);
				    myPq.push(newNode);
				}



				//------left--operation
				if(!(curZeroPos%4==0)){

					Node newNode=currentNode;
				    newNode.swapPos(curZeroPos,curZeroPos-1);
				    newNode.setCurOpp(LEFT);
				    newNode.setCost(currentNode.getCost()+1);
				    myPq.push(newNode);
				}



				//right --operation


		}
		else if (currentNode.getCurOpp()==RIGHT){

				//---up--operation--is--not--0<=curZeroPos<=3
				if(!(curZeroPos>=0 && curZeroPos<=3)){

					Node newNode=currentNode;
				    newNode.swapPos(curZeroPos,curZeroPos-4);
				    newNode.setCurOpp(UP);
				    newNode.setCost(currentNode.getCost()+1);
				    myPq.push(newNode);
				}

				//-----down--operation
				if(!(curZeroPos>=12 && curZeroPos<=15)){

					Node newNode=currentNode;
				    newNode.swapPos(curZeroPos,curZeroPos+4);
				    newNode.setCurOpp(DOWN);
				    newNode.setCost(currentNode.getCost()+1);
				    myPq.push(newNode);
				}



				//------left--operation



				//right --operation
				if(!(curZeroPos%4==3)){

					Node newNode=currentNode;
				    newNode.swapPos(curZeroPos,curZeroPos+1);
				    newNode.setCurOpp(RIGHT);
				    newNode.setCost(currentNode.getCost()+1);
				    myPq.push(newNode);
				}

		}






      }



	}
	//else if(method==2)


	 int breakl;
	 cin>>breakl;


	{
		cout<<"--------Working on Misplacement Cost---------------"<<endl;
		priority_queue<Node,vector<Node>,CompareMisPlace> myPq;
		initialState.countMisPlaceCost();
		initialState.findCurPosition();
		myPq.push(initialState);
	while(true)
      {
		Node currentNode=myPq.top();
		myPq.pop();
		//-----------making children of these node------------------
		//cout<<currentNode.countManHattanCost()<<endl;

		//cout<<"chek:1 "<<currentNode.getCost()<<endl;


		if(currentNode.getMisPlaceCost()==0) {//change get 1
			//print the result and break the loop;
			cout<<"Final_STATE_COST:  "<<currentNode.getCost()<<"---------"<<endl;
		    currentNode.printState();
		    cout<<endl;
			break;
		}

		cout<<"STATE_:"<<currentNode.getCost()<<"----MissPlace cost:"<<currentNode.getMisPlaceCost()<<endl;//get 2
		cout<<"total cost: "<<currentNode.getCost()+currentNode.getMisPlaceCost()<<endl;
		currentNode.printState();
		cout<<endl;


		int curZeroPos=currentNode.getCurPosition(); //change


		if(currentNode.getCurOpp()==NIL){

				//---up--operation--is--not--0<=curZeroPos<=3
				if(!(curZeroPos>=0 && curZeroPos<=3)){

					Node newNode=currentNode;
				    newNode.swapPos(curZeroPos,curZeroPos-4);
				    newNode.setCurOpp(UP);
				    newNode.setCost(currentNode.getCost()+1);
				    myPq.push(newNode);

				}

				//-----down--operation
				if(!(curZeroPos>=12 && curZeroPos<=15)){

					Node newNode=currentNode;
				    newNode.swapPos(curZeroPos,curZeroPos+4);
				    newNode.setCurOpp(DOWN);
				    newNode.setCost(currentNode.getCost()+1);
				    myPq.push(newNode);
				}



				//------left--operation
				if(!(curZeroPos%4==0)){

					Node newNode=currentNode;
				    newNode.swapPos(curZeroPos,curZeroPos-1);
				    newNode.setCurOpp(LEFT);
				    newNode.setCost(currentNode.getCost()+1);
				    myPq.push(newNode);
				}



				//right --operation

				if(!(curZeroPos%4==3)){

					Node newNode=currentNode;
				    newNode.swapPos(curZeroPos,curZeroPos+1);
				    newNode.setCurOpp(RIGHT);
				    newNode.setCost(currentNode.getCost()+1);
				    myPq.push(newNode);
				}


		}



  		else if(currentNode.getCurOpp()==UP){

				//---up--operation--is--not--0<=curZeroPos<=3
				if(!(curZeroPos>=0 && curZeroPos<=3)){

					Node newNode=currentNode;
				    newNode.swapPos(curZeroPos,curZeroPos-4);
				    newNode.setCurOpp(UP);
				    newNode.setCost(currentNode.getCost()+1);
				    myPq.push(newNode);
				}

				//-----down--operation




				//------left--operation
				if(!(curZeroPos%4==0)){

					Node newNode=currentNode;
				    newNode.swapPos(curZeroPos,curZeroPos-1);
				    newNode.setCurOpp(LEFT);
				    newNode.setCost(currentNode.getCost()+1);
				    myPq.push(newNode);
				}



				//right --operation

				if(!(curZeroPos%4==3)){

					Node newNode=currentNode;
				    newNode.swapPos(curZeroPos,curZeroPos+1);
				    newNode.setCurOpp(RIGHT);
				    newNode.setCost(currentNode.getCost()+1);
				    myPq.push(newNode);
				}


		}
		else if(currentNode.getCurOpp()==DOWN){

				//---up--operation--is--not--0<=curZeroPos<=3

				//-----down--operation
				if(!(curZeroPos>=12 && curZeroPos<=15)){

					Node newNode=currentNode;
				    newNode.swapPos(curZeroPos,curZeroPos+4);
				    newNode.setCurOpp(DOWN);
				    newNode.setCost(currentNode.getCost()+1);
				    myPq.push(newNode);
				}



				//------left--operation
				if(!(curZeroPos%4==0)){

					Node newNode=currentNode;
				    newNode.swapPos(curZeroPos,curZeroPos-1);
				    newNode.setCurOpp(LEFT);
				    newNode.setCost(currentNode.getCost()+1);
				    myPq.push(newNode);
				}



				//right --operation

				if(!(curZeroPos%4==3)){

					Node newNode=currentNode;
				    newNode.swapPos(curZeroPos,curZeroPos+1);
				    newNode.setCurOpp(RIGHT);
				    newNode.setCost(currentNode.getCost()+1);
				    myPq.push(newNode);
				}

		}
		else if(currentNode.getCurOpp()==LEFT){
				//---up--operation--is--not--0<=curZeroPos<=3
				if(!(curZeroPos>=0 && curZeroPos<=3)){

					Node newNode=currentNode;
				    newNode.swapPos(curZeroPos,curZeroPos-4);
				    newNode.setCurOpp(UP);
				    newNode.setCost(currentNode.getCost()+1);
				    myPq.push(newNode);
				}

				//-----down--operation
				if(!(curZeroPos>=12 && curZeroPos<=15)){

					Node newNode=currentNode;
				    newNode.swapPos(curZeroPos,curZeroPos+4);
				    newNode.setCurOpp(DOWN);
				    newNode.setCost(currentNode.getCost()+1);
				    myPq.push(newNode);
				}



				//------left--operation
				if(!(curZeroPos%4==0)){

					Node newNode=currentNode;
				    newNode.swapPos(curZeroPos,curZeroPos-1);
				    newNode.setCurOpp(LEFT);
				    newNode.setCost(currentNode.getCost()+1);
				    myPq.push(newNode);
				}



				//right --operation


		}
		else if (currentNode.getCurOpp()==RIGHT){

				//---up--operation--is--not--0<=curZeroPos<=3
				if(!(curZeroPos>=0 && curZeroPos<=3)){

					Node newNode=currentNode;
				    newNode.swapPos(curZeroPos,curZeroPos-4);
				    newNode.setCurOpp(UP);
				    newNode.setCost(currentNode.getCost()+1);
				    myPq.push(newNode);
				}

				//-----down--operation
				if(!(curZeroPos>=12 && curZeroPos<=15)){

					Node newNode=currentNode;
				    newNode.swapPos(curZeroPos,curZeroPos+4);
				    newNode.setCurOpp(DOWN);
				    newNode.setCost(currentNode.getCost()+1);
				    myPq.push(newNode);
				}

				//------left--operation

				//right --operation
				if(!(curZeroPos%4==3)){

					Node newNode=currentNode;
				    newNode.swapPos(curZeroPos,curZeroPos+1);
				    newNode.setCurOpp(RIGHT);
				    newNode.setCost(currentNode.getCost()+1);
				    myPq.push(newNode);
				}
		}
      }
	}
}

int main(){
 int n;
 cin>>n;
 int goal_State[20];
 for(int i=0;i<16;i++) cin>>goal_State[i];
 n--;

while(n--)
 {
     int ini_state[20];

     for(int i=0;i<16;i++) cin>>ini_state[i];
     cout<<"-----------------------------------------------------------------------"<<endl;
     solvingPuzzle(ini_state);

 }

return 0;


}

