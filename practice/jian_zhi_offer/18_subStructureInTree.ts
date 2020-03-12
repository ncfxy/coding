import { BinaryTreeNode } from "./TreeNode";

function hasSubtree(root1: BinaryTreeNode | null, root2: BinaryTreeNode | null): boolean {
    let result: boolean = false;
    if (root1 != null && root2 != null) {
        if(root1.val === root2.val) {
            result = doesTree1HaveTree2(root1, root2);
        }
        if(!result) {
            result = hasSubtree(root1.left, root2);
        }
        if(!result) {
            result = hasSubtree(root1.right, root2);
        }
    }
    return result;
}

function doesTree1HaveTree2(root1: BinaryTreeNode | null, root2: BinaryTreeNode | null): boolean {
    if(root2 == null) {
        return true;
    }
    if(root1 == null) {
        return false;
    }
    if(root1.val !== root2.val) {
        return false;
    }
    return doesTree1HaveTree2(root1.left, root2.left) && doesTree1HaveTree2(root1.right, root2.right);
}

let root1 = new BinaryTreeNode(1);
root1.left = new BinaryTreeNode(2);
root1.right = new BinaryTreeNode(3);
root1.left.left = new BinaryTreeNode(4);
root1.left.right = new BinaryTreeNode(5);
let root2 = new BinaryTreeNode(2);
root2.left = new BinaryTreeNode(4);
root2.right = new BinaryTreeNode(5);
console.log(hasSubtree(root1, root2));
console.log(hasSubtree(root1, null));
console.log(hasSubtree(null, root2));
