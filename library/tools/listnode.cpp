/*
 linked-listを直感的に使えるようにした関数
 push,popはO(1)
 inverseはO(n)
*/


struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};
ListNode* push(int n,ListNode* l){
    ListNode* rtn = new ListNode(n);
    rtn->next=l;
    return rtn;
}
ListNode* pop(ListNode* l){
    if(l!=NULL){
        return l->next;
    }else{
        return l;
    }
}
ListNode* inverse(ListNode* l){
    ListNode* rtn = new ListNode(l->val);
    l=l->next;
    while(l!=NULL){
        rtn = push(l->val,rtn);
        l=l->next;
    }
    return rtn;
}
int main(){
    ListNode l = new ListNode(3);
    l = push(2,l);
}