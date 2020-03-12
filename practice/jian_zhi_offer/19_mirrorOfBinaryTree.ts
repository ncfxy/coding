import { BinaryTreeNode, preTraverse, midTraverse, postTraverse } from "./TreeNode";

debugger;

function mirrorRecursively(node: BinaryTreeNode| null) {
    if(!node) {
        return;
    }
    if(node.left == null && node.right == null) {
        return;
    }
    let temp = node.left;
    node.left = node.right;
    node.right = temp;
    if(node.left){
        mirrorRecursively(node.left);
    }
    if(node.right) {
        mirrorRecursively(node.right);
    }
}

let root: BinaryTreeNode = new BinaryTreeNode(1);
root.left = new BinaryTreeNode(2);
root.right = new BinaryTreeNode(3);
root.left.left = new BinaryTreeNode(4);
root.left.right = new BinaryTreeNode(5);

console.log('preTraverse');
preTraverse(root);
console.log('midTraverse');
midTraverse(root);
console.log('postTraverse');
postTraverse(root);
mirrorRecursively(root);
console.log('preTraverse');
preTraverse(root);
console.log('midTraverse');
midTraverse(root);
console.log('postTraverse');
postTraverse(root);