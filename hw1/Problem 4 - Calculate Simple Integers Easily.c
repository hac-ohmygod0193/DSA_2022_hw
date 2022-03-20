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
    char opt;
} math;
void inToPostfix(char* s,math* ans,int len,int k){
    char *op;
    op = malloc(len*sizeof(char));
    char cur,top;
    int sum=0,num;
    int opp=-1;
    int negative=0;
    int is_number=0;

    for(int i=0;i<len;i++){
        num = s[i]-'0';
        if(num>=0 && num<=9){
            is_number=1;
            sum*=10;
            if(negative==1) sum-=num;
            else sum+=num;
        }
        else{
            if(is_number==1){
                ans[k].is_op=0;
                ans[k].num=sum;
                k++;
                sum=0;
                is_number=0;
            }
            cur = s[i];
            if(opp==-1){
                opp++;
                op[opp]=cur;
            }
            else{
                top = op[opp];
                if(cur==')'){//')'
                    while(top!='(' && opp>=0){
                        ans[k].is_op=1;
                        ans[k].opt=top;
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
                    while(priority(top)>=priority(cur) && opp>=0 && top!='('){
                        ans[k].is_op=1;
                        ans[k].opt=top;
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
        ans[k].opt=op[i];
        k++;
    }
    ans[k].is_op=-1;
    free(op);
}
int cal(math* ans,int len){
    int *st;
    st = malloc(len*sizeof(int));
    int ptr=-1,a,b;
    char opt;
    for(int i=0;i<len+1;i++){
        if(ans[i].is_op==-1) break;
        if(ans[i].is_op==0){
            ptr++;
            st[ptr] = ans[i].num;
        }
        else{
            b = st[ptr];
            ptr--;
            a = st[ptr];
            opt = ans[i].opt;
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
                if(!(a>0 && b>0) && a%b){
                    c=c-1;
                }
                st[ptr] = c;
            }
            else if(opt=='%'){
                st[ptr] = a%b;
            }

        }
    }
    return st[0];
    free(st);
}

char s[1000001];
char c[1000001];
signed main(){
    scanf("%s",c);
    int len;
    int p=0,result=0;
    int first=0;
    //printf("%d\n",len);
    for(int j=0;j<strlen(c);j++){
        if(c[j]!='='){
            s[p]=c[j];p++;
            continue;
        }
        else{
            s[p]='\0';
            len = p;
            p=0;
        }
        math *ans;
        ans = malloc((len+1)*sizeof(math));
        int k=0;
        if(first==1){
            ans[k].is_op=0;
            ans[k].num=result;
            k++;
        }
        inToPostfix(s,ans,len,k);
        result = cal(ans,len);
        printf("Print: %d\n",result);
        free(ans);
        first=1;
    }
}
