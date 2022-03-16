#include<stdio.h>
#include <stdlib.h>
//處理動態陣列(malloc)
// ((1+2)*5+(1+7+11))%5-11=
// let '-'=-1, '+'=1 ,'*'=2 ,'/'=-2, '('=-3, ')'=3;
#define int long long int
int char_to_int(char a){
    if(a=='-') return -1;
    else if(a=='+') return 1;
    else if(a=='%') return 2;
    else if(a=='*') return 3;
    else if(a=='/') return -3;
    else if(a=='(') return -4;
    else if(a==')') return 4;
}
char int_to_char(int a){
    if(a==-1) return '-';
    else if(a==1) return '+';
    else if(a==2) return '%';
    else if(a==-3) return '/';
    else if(a==3) return '*';
    else if(a==-4) return '(';
    else if(a==4) return ')';
}
typedef struct str{
    int len;
    char c[100];
} STR;

typedef struct element{
    int is_op;
    int num,op;
} math;
typedef struct a{
    math x[100];
} formula;
formula infix_to_postfix(STR s){
    formula ans;
    int op[100];
    int cur,top,sum=0,num;
    int opp=-1,k=0;//opp->tail pos
    //printf("%d\n",strlen(s.c));
    int negative=0;
    int is_number=0;
    for(int i=0;i<s.len-1;i++){
        if(s.c[i]=='-' && is_number==0){
            negative=1;
            continue;
        }
        num = s.c[i]-'0';
        if(num>=0 && num<=9){
            //printf("haha\n");
            is_number=1;
            sum*=10;
            if(negative==1) sum-=num;
            else sum+=num;
        }
        else{
            if(is_number==1){
                ans.x[k].is_op=0;
                ans.x[k].num=sum;
                k++;
                //printf("sum=%d, %c\n",sum,s.c[i]);
                sum=0;
                is_number=0;
            }
            cur = char_to_int(s.c[i]);
            //printf("char=%d\n",cur);
            if(opp==-1){
                opp++;
                op[opp]=cur;
                //printf("opp=%d\n",op[opp]);
            }
            else{
                top = op[opp];
                if(cur==4){//')'
                    //printf("%c\n",s[i]);
                    while(top!=-4 && opp>=0){
                        ans.x[k].is_op=1;
                        ans.x[k].op=top;
                        k++;
                        opp--;
                        if(opp==-1) break;
                        top = op[opp];
                    }
                    if(top==-4){
                        opp--;
                    }
                }
                else{
                    while(abs(top)>=abs(cur) && opp>=0 && top!=-4){
                        ans.x[k].is_op=1;
                        ans.x[k].op=top;
                        k++;
                        opp--;
                        if(opp==-1) break;
                        top = op[opp];
                    }
                    opp++;
                    op[opp]=cur;
                }

            }
        }


    }
    if(is_number==1){
        ans.x[k].is_op=0;
        ans.x[k].num=sum;
        k++;
        sum=0;
        is_number=0;
    }
    for(int i=opp;i>=0;i--){
        ans.x[k].is_op=1;
        ans.x[k].op=op[i];
        k++;
    }
    ans.x[k].is_op=-1;
    return ans;
}
int cal(formula ans){
    int st[100];
    int ptr=-1,a,b,num;
    char op;
    for(int i=0;i<100;i++){
        if(ans.x[i].is_op==-1) break;
        if(ans.x[i].is_op==0){
            ptr++;
            st[ptr] = ans.x[i].num;
        }
        else{
            b = st[ptr];
            ptr--;
            a = st[ptr];
            //printf("a = %d, b = %d, ans=",a,b);
            op = int_to_char(ans.x[i].op);
            if(op=='+'){
                st[ptr] = a+b;
            }
            else if(op=='-'){
                st[ptr] = a-b;
            }
            else if(op=='*'){
                st[ptr] = a*b;
            }
            else if(op=='/'){
                st[ptr] = a/b;
            }
            else if(op=='%'){
                st[ptr] = a%b;
            }
            //printf("%d\n",st[ptr]);
        }
    }
    //printf("result=%d\n",st[ptr]);
    return st[ptr];
}
int main(){
    STR s;
    formula ans;
    //printf("%d\n",1+6/3%4);
    scanf("%s",s.c);
    s.len = strlen(s.c);
    ans = infix_to_postfix(s);
    printf("Print: %d\n",cal(ans));
}
