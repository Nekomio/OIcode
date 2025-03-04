/*
 * @Author: WildRage 
 * @Date: 2017-06-17 10:45:09 
 * @Last Modified by: WildRage
 * @Last Modified time: 2017-06-17 11:09:39
 */
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#include<stack>
using namespace std;
#define ULL unsigned long long
const ULL base=31; 
ULL pw[100005],f[15][15],HASH[100005];
int pos[15],cnt,num[15],s[15][15],n,lenth;
char S[100005],a[100005];
ULL get_hash(int l,int r){
    return HASH[r]-HASH[l-1]*pw[r-l+1];
}
bool OK(int i,int k){
    for(int j=0;j<=num[k];j++){
        if(s[k][j]==0){i++;continue;}
        if(f[k][j]!=get_hash(i,i+s[k][j]-1))return 0;
        i+=s[k][j]+1;
    }
    return 1;
}
bool work(char *b){
    int len=strlen(b+1);
    if(!cnt){
        if(lenth!=len)return 0;
        for(int i=1;i<=lenth;i++)
            if(S[i]!=b[i]&&S[i]!='?')return 0;
        return 1;
    }
    if(len<(pos[1]-1)+(lenth-pos[cnt]))return 0;
    for(int i=1;i<pos[1];i++)if(S[i]!=b[i]&&S[i]!='?')return 0;
    for(int i=lenth,j=len;i>pos[cnt];i--,j--)
        if(S[i]!=b[j]&&S[i]!='?')return 0;
    for(int i=1;i<=len;i++) HASH[i]=HASH[i-1]*base+b[i];
    int MAX=len-(lenth-pos[cnt])+1;
    int i=pos[1];
    for(int k=2;k<=cnt;k++){
        while(i<=MAX){
            if(OK(i,k))break;
            i++;
        }
        i+=pos[k]-pos[k-1]-1;
        if(i>MAX) return 0;
    }
    return 1;
}
int main()
{
    //freopen("match.in","r",stdin);
    //freopen("match.out","w",stdout);
    scanf("%s",S+1);
    lenth=strlen(S+1);
    pw[0]=1;
    cnt=0;
    for(int i=1;i<=100000;i++)pw[i]=pw[i-1]*base;
    for(int i=1;i<=lenth;i++)
        if(S[i]=='*') 
            pos[++cnt]=i;
    for(int i=2;i<=cnt;i++){
        num[i]=0;
        for(int j=pos[i-1]+1;j<pos[i];j++){
            if(S[j]=='?'){
                num[i]++;
                continue;
            }
            s[i][num[i]]++;
            f[i][num[i]]=f[i][num[i]]*base+S[j];
        }
    }
    scanf("%d",&n);
    while(n--){
        scanf("%s",a+1);
        if(work(a))puts("YES");
        else puts("NO");
    }
    //while(1);
}