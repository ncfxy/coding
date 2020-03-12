import { BinaryTreeNode } from "./TreeNode";

function printFromTopToBottom(root: BinaryTreeNode | null) {
    if(root == null) {
        return;
    }
    const queue: BinaryTreeNode[] = [];
    queue.push(root);
    while(queue.length > 0) {
        const top = queue.shift();
        top && console.log(top.val);
        top && top.left && queue.push(top.left);
        top && top.right && queue.push(top.right);
    }
}

const root: BinaryTreeNode = new BinaryTreeNode(1);
root.left = new BinaryTreeNode(2);
root.right = new BinaryTreeNode(3);
root.left.left = new BinaryTreeNode(4);
root.left.right = new BinaryTreeNode(5);

printFromTopToBottom(root);