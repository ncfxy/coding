import { BinaryTreeNode } from "./TreeNode";

debugger;

function convert(root: BinaryTreeNode | null) {
    if(root == null){
        return null;
    }
    let lastListNode: BinaryTreeNode | null = null;
    let head = convertNode(root, lastListNode);
    while(head && head.left != null) {
        head = head.left;
    }
    return head;
}

function convertNode(root: BinaryTreeNode| null, lastListNode: BinaryTreeNode| null): (BinaryTreeNode| null) {
    if(root == null) {
        return null;
    }
    let currentNode = root;
    if(currentNode.left != null){
        lastListNode = convertNode(currentNode.left, lastListNode);
    }
    currentNode.left = lastListNode;
    if(lastListNode != null) {
        lastListNode.right = currentNode;
    }
    lastListNode = currentNode;
    if(currentNode.right != null) {
        lastListNode = convertNode(currentNode.right, lastListNode);
    }
    return lastListNode;
}

let root: BinaryTreeNode = new BinaryTreeNode(10);
root.left = new BinaryTreeNode(6);
root.right = new BinaryTreeNode(14);
root.left.left = new BinaryTreeNode(4);
root.left.right = new BinaryTreeNode(8);
root.right.left = new BinaryTreeNode(12);
root.right.right = new BinaryTreeNode(16);

let newRoot = convert(root);

let node = newRoot;
while(node != null) {
    console.log(node.val);
    node = node.right;
}
