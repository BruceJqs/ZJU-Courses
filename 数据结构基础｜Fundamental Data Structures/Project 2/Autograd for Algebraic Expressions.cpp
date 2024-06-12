#include<iostream>
#include<string>
#include<algorithm>
using namespace std;

struct TreeNode{ 
    string value;
    TreeNode *left;
    TreeNode *right;
};

struct Stack{//define a stack to build the expression tree from inorder expression
    TreeNode *data[100];
    int top;
    
    void push(TreeNode *node){//pushing the node into the stack
        data[++top]=node;
    }

    TreeNode *pop(){//pop and acquire the top element in the stack
        return data[top--];
    }

    TreeNode *visit(){//acquire the top element in the stack
        return data[top];
    }

    bool empty(){//judge whether the stack is empty
        return top==-1;
    }
};

int precedence(char op){//get the precedence of the operator
    switch(op){
        case '^':return 3;break;
        case '*':return 2;break;
        case '/':return 2;break;
        case '+':return 1;break;
        case '-':return 1;break;
        default:return -1;//define the precedence of a number or a variable is the lowest
    }
}

bool cmp(string s1,string s2){//the assisting function for quick_sort algorithm
    return s1<s2;
}

bool isnumber(string s){//determine whether s is a number
    for(int i=0;i<(int)s.length();i++)
        if((s[i]<'0')||(s[i]>'9'))
            return false;
    return true;
}

bool isoperator(string s){//determine whether s is an operator
    return (s[0]=='+')||(s[0]=='-')||(s[0]=='*')||(s[0]=='/')||(s[0]=='^');
}

TreeNode* createnode(string s){//function for creating a new treenode
	TreeNode *temp=new TreeNode;
	temp->value=s;
	temp->left=NULL;temp->right=NULL;
	return temp;
}

TreeNode* buildtree(string expression){//function for building a tree
    Stack nodestack,opstack;//nodestack stores variables,numbers;opstack stores operators
    nodestack.top=opstack.top=-1;//set the two tops
    string var;//collect the variable name/number
    for(int i=0;i<(int)expression.length();i++){
        if(expression[i]=='(')//if we encounter left bracket,push it into opstack for encountering right bracket
            opstack.push(createnode(string(1,expression[i])));
        else if(isalnum(expression[i]))//if expression[i] is a letter or number,collect it into var
            var+=expression[i];
        else if(expression[i]==')'){//if we encounter right bracket,then create expression tree in the brackets
            if(!var.empty())//push the new variable into the stack
            {
                nodestack.push(createnode(var));
                var.clear();//clear the string and start over
            }
            while((!opstack.empty())&&(opstack.visit()->value!="(")){//create until we encounter left bracket
                TreeNode *op=opstack.pop();//get the operator
                TreeNode *rightnode=nodestack.pop();//get the numbers
                TreeNode *leftnode=nodestack.pop();
                op->left=leftnode;op->right=rightnode;//create the tree
                nodestack.push(op);//push the new tree back into the stack
            }
            opstack.pop();//pop the left bracket
        }
        else{//if expression[i] is an operator,then get two numbers from nodestack and create the tree
            if(!var.empty()){
                nodestack.push(createnode(var));
                var.clear();
            }
            while((!opstack.empty())&&(precedence(opstack.visit()->value[0])>=precedence(expression[i]))){//if the precedence of previous operator is greater,handle the operator first
                TreeNode *op=opstack.pop();
                TreeNode *rightnode=nodestack.pop();
                TreeNode *leftnode=nodestack.pop();
                op->left=leftnode;op->right=rightnode;
                nodestack.push(op);
            }
            opstack.push(createnode(string(1,expression[i])));//push the new operator into opstack
        }
    }
    /*there is still a variable in var,a operator in opstack,a variable in nodestack,create the tree*/
    if(!var.empty()){
        nodestack.push(createnode(var));
        var.clear();    
    }
    while(!opstack.empty()){
        TreeNode *op=opstack.pop();
        TreeNode *rightnode=nodestack.pop();
        TreeNode *leftnode=nodestack.pop();
        op->left=leftnode;op->right=rightnode;
        nodestack.push(op);
    }
    return nodestack.pop();//return the headnode
}

TreeNode* addnodes(TreeNode *left,TreeNode *right){//merge leftnode,rightnode and operator "+"
	if(left==NULL)//if left is NULL then there is no need to print "+"(in case "+a")
		return right;
	if(right==NULL)//if right is NULL then there is no need to print "+"(in case "a+")
		return left;
	TreeNode *temp=createnode("+");
	temp->left=left;temp->right=right;
	return temp;
}

TreeNode* subnodes(TreeNode *left,TreeNode *right){//merge leftnode,rightnode and operator "-"
	if(right==NULL)//if right is NULL then there is no need to print "-"(in case "a-")
		return left;
	TreeNode *temp=createnode("-");
	temp->left=left;temp->right=right;
	return temp;
}

TreeNode* mulnodes(TreeNode *left,TreeNode *right){//merge leftnode,rightnode and operator "*"
	if((left==NULL)||(right==NULL))//if right or left is NULL then the whole result is 0
		return NULL;
	TreeNode *temp=createnode("*");
	temp->left=left;temp->right=right;
	return temp;
}

TreeNode* divnodes(TreeNode *left,TreeNode *right){//merge leftnode,rightnode and operator "/"
	if((left==NULL)||(right==NULL))//if right or left is NULL then the whole result is 0
		return NULL;
	TreeNode *temp=createnode("/");
	temp->left=left;temp->right=right;
	return temp;
}

TreeNode* powernodes(TreeNode *left,TreeNode *right){//merge leftnode,rightnode and operator "^"
	TreeNode *temp=createnode("^");
	temp->left=left;temp->right=right;
	return temp;
}

TreeNode* differentiate(TreeNode *root,string var){
    if(root==NULL)
    	return NULL;
    if(isnumber(root->value))//F(x)=c,F'(x)=0
    	return NULL;
    else if(root->value==var)//F(x)=x,F'(x)=1
    	return createnode("1");
    else{//root->value is an operator
    	TreeNode *leftchild=differentiate(root->left,var);//get the derivative of leftchild
    	TreeNode *rightchild=differentiate(root->right,var);//get the derivative of rightchild
    	
    	if(root->value=="+")//F(x)=f(x)+g(x),F'(x)=f'(x)+g'(x)
    		return addnodes(leftchild,rightchild);
    	if(root->value=="-")//F(x)=f(x)-g(x),F'(x)=f'(x)-g'(x)
    		return subnodes(leftchild,rightchild);
    	if(root->value=="*")//F(x)=f(x)*g(x),F'(x)=f'(x)*g(x)+f(x)*g'(x)
    		return addnodes(mulnodes(leftchild,root->right),mulnodes(root->left,rightchild));
    	if(root->value=="/"){//F(x)=f(x)/g(x),F'(x)=[f'(x)*g(x)-f(x)*g'(x)]/g(x)^2
    		TreeNode *term1=mulnodes(leftchild,root->right);
    		TreeNode *term2=mulnodes(root->left,rightchild);
    		TreeNode *term3=powernodes(root->right,createnode("2"));
    		return divnodes(subnodes(term1,term2),term3);
    	}
		if(root->value=="^"){//F(x)=f(x)^[g(x)],F'(x)=[g'(x)*lnf(x)+g(x)*f'(x)/f(x)]*f(x)^g(x)
    		TreeNode *term1=mulnodes(rightchild,createnode("ln("+root->left->value+")"));
    		TreeNode *term2=divnodes(mulnodes(root->right,leftchild),root->left);
    		TreeNode *term3=powernodes(root->left,root->right);
    		return mulnodes(addnodes(term1,term2),term3);
		}
	}
}

void printtree(TreeNode *root){//print the expression tree back to inorder expression
	if(root==NULL)
		return;
	if(root->left!=NULL){
		if(isoperator(root->value)&&isoperator(root->left->value)){
			bool flag=precedence(root->value[0])>precedence(root->left->value[0]);
			if(flag)//if root's operator is higher than root's leftchild's operator,then expression in leftchild need brackets
				cout<<"(";
			printtree(root->left);
			if(flag)
				cout<<")";
		}
		else
			printtree(root->left);
	}
	cout<<root->value;
	if(root->right!=NULL){
		if(isoperator(root->value)&&isoperator(root->right->value)){
			bool flag=precedence(root->value[0])>precedence(root->right->value[0]);
			if(flag)//if root's operator is higher than root's rightchild's operator,then expression in rightchild need brackets
				cout<<"(";
			printtree(root->right);	
			if(flag)
				cout<<")";
		}
		else
			printtree(root->right);
	}
}

int main(){
    string expression;
    cin>>expression;

	/*build the expression tree*/
    TreeNode* root=buildtree(expression);
	
	/*count all the variable names*/
    string variables[100];
    string var;
    int total=0;
    for(int i=0;i<(int)expression.size();i++){
        if(isalnum(expression[i]))
            var+=expression[i];
        else{
            if(!var.empty()){
            	bool flag=true;//flag=true means the new variable name is not in the old set of variable names
            	for(int i=1;i<=total;i++)
            		if(var==variables[i]){
            			flag=false;
            			break;
					}
				if(flag)//add the new variable name
					variables[++total]=var;
                var.clear();
            }
        }
    }
    if(!var.empty()){
        bool flag=true;
        for(int i=1;i<=total;i++)
      		if(var==variables[i]){
			    flag=false;
            	break;
			}
		if(flag)
			variables[++total]=var;
        var.clear();
    }
	/*sort all the variable name in lexicographical order*/
    sort(variables+1,variables+total+1,cmp);
    
    for(int i=1;i<=total;i++)
    	if(!isnumber(variables[i])){
	        cout<<variables[i]<<": ";
	        TreeNode *ans=differentiate(root,variables[i]);//differentiate all variables
	        printtree(ans);
	        cout<<endl;
	    }
    return 0;
}
