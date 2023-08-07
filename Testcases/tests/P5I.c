struct tree{
  int val;
  struct tree *left, *right;
};
void inorder(struct tree *root){
  if(!root) ;
  else
  {
  inorder(root->left);
  printf("%d ",root->val);
  inorder(root->right);
  }
}
int main(){
  struct tree r,a1,a2,a3,a4,a5;
  struct tree *rt;
  r.val=0;
  a1.val=1;
  a2.val=2;
  a3.val=3;
  a4.val=4;
  a5.val=5;
  r.left = &a1;  r.right = &a2;
  a1.left = &a3; a1.right = &a4;
  a2.left = 0; a2.right = &a5;
  a3.left = 0; a3.right = 0;
  a4.left = 0; a4.right = 0;
  a5.left = 0; a5.right = 0;
  rt = &r;
  printf("Root pointer: %d\n",rt->val);
  inorder(rt);
  printf("\n");
  return 0;
}
