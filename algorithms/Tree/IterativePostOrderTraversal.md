# Iterative Postorder Traversal
Consider the Below Terminologies:
> 0 (node not developed)
1 (the left node has been put on stack)
2 (the right node has been put on stack)

Take a stack and perform the below operations:
```
1) Insert a pair of the root node as (node, 0)
2) Pop the top element to get the pair
	(let a = node and b be the variable)
	If b is equal to 0:
		Push another pair as (node, 1) and
		Push the left child as (node->left, 0)
		Repeat Step 2
	Else If b is equal to 1:
		Push another pair as (node, 2) and
		Push right child of node as (node->right, 0)
		Repeat Step 2
	Else If b is equal to 2:
		Print(node -> data)
3) Repeat the above steps while stack is not empty
```

For N-ary tree post order traversal, pseudo code:
```
Start from the root.
Repeat all the steps below till either root != null OR stack is not empty.
	If root != null then push root and it’s an index into the stack and continues towards the left node.
	Pop the element from the stack and print it.
	Pop all the elements from stack till stack is not empty && popped node is last children of
	it’s a parent.
	Assign root to the next children of top of stack’s node.
```
