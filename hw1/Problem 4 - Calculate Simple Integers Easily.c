#include<stdio.h>
#include <assert.h>
// ((1+2)*5+(1+7+11))%5-11+
// let '-'=-1, '+'=1 ,'*'=2 ,'/'=-2, '('=-3, ')'=3;
#define int long long
int priority(char a){
    if(a=='+' || a=='-') return -1;
    else return 1;
}
typedef struct element{
    int is_op;
    int num;
    char op;
} math;
char s[1000001];
signed main(){
    scanf("%s",s);
    int len = strlen(s);
    //printf("%d\n",len);
    math *ans;
    ans = malloc(len*sizeof(math));
    char *op;
    op = malloc(len*sizeof(char));
    char cur,top;
    int sum=0,num;
    int opp=-1,k=0;//opp->tail pos
    //printf("%d\n",strlen(s.c));
    int negative=0;
    int is_number=0;
    for(int i=0;i<len-1;i++){
        num = s[i]-'0';
        if(num>=0 && num<=9){
            //printf("haha\n");
            is_number=1;
            sum*=10;
            //if(negative==1) sum-=num;
            sum+=num;
        }
        else{
            if(is_number==1){
                ans[k].is_op=0;
                ans[k].num=sum;
                k++;
                //printf("sum=%d, %c\n",sum,s.c[i]);
                sum=0;
                is_number=0;
            }
            cur = s[i];
            //printf("char=%d\n",cur);
            if(opp==-1){
                opp++;
                op[opp]=cur;
                //printf("opp=%d\n",op[opp]);
            }
            else{
                top = op[opp];
                if(cur==')'){//')'
                    //printf("%c\n",s[i]);
                    while(top!='(' && opp>=0){
                        ans[k].is_op=1;
                        ans[k].op=top;
                        k++;
                        opp--;
                        if(opp==-1) break;
                        top = op[opp];
                    }
                    if(top=='('){
                        opp--;
                    }
                }
                else if(cur=='('){
                    opp++;
                    op[opp]=cur;
                }
                else{
                    while(top!='(' && priority(top)>=priority(cur) && opp>=0){
                        ans[k].is_op=1;
                        ans[k].op=top;
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
        ans[k].is_op=0;
        ans[k].num=sum;
        k++;
        sum=0;
        is_number=0;
    }
    for(int i=opp;i>=0;i--){
        ans[k].is_op=1;
        ans[k].op=op[i];
        k++;
    }
    ans[k].is_op=-1;
    free(op);

    //calculate
    int ptr=-1,a,b;
    char opt;
    int *st;
    st = malloc(len*sizeof(int));
    for(int i=0;i<len;i++){
        if(ans[i].is_op==-1) break;
        if(ans[i].is_op==0){
            ptr++;
            st[ptr] = ans[i].num;
        }
        else{
            b = st[ptr];
            ptr--;
            a = st[ptr];
            //printf("a = %d, b = %d, ans=",a,b);
            opt = ans[i].op;
            if(opt=='+'){
                st[ptr] = a+b;
            }
            else if(opt=='-'){
                st[ptr] = a-b;
            }
            else if(opt=='*'){
                st[ptr] = a*b;
            }
            else if(opt=='/'){
                int c = a/b;
                if(c<=0 && c*b>a){
                    c=c-1;
                }
                st[ptr] = c;
            }
            else if(opt=='%'){
                st[ptr] = a%b;
            }
            //printf("%d\n",st[ptr]);
        }
    }
    printf("Print: %d\n",st[ptr]);
    free(st);
    free(ans);
}
