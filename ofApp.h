#pragma once

#include "ofMain.h"

typedef struct _TreeNode {
	struct _TreeNode* parent;
	int room;
	int x;
	int y;
	bool visited;
	bool path;
	struct _TreeNode* child1;
	struct _TreeNode* child2;
	struct _TreeNode* child3;
	struct _TreeNode* next;
	struct _TreeNode* prev;
}TreeNode;


class stack1 {
	TreeNode* top;
	public:
		stack1() {
			top = NULL;
		}
		void push(TreeNode* T)
		{
			if (top == NULL)
			{
				top = T;
				top->next = NULL;
			}
			else
			{
				T->next = top;
				top = T;
			}
		}
		TreeNode* Top()
		{
			if (top == NULL)
			{
				return NULL;
			}
			else
				return top;
		}
		TreeNode* pop()
		{
			TreeNode* cur;
			if (top == NULL)
			{
				return NULL;
			}
			else
			{
				cur = top;
				top = top->next;
				return cur;
			}
		}
		bool isEmpty() {
			if (top == NULL)
			{
				return true;
			}
			else
				return false;
		}
};


class queue1 {
		
	public:
		TreeNode* front;
		TreeNode* rear;
		queue1() {
			front = rear = NULL;
		}
		
		void enqueue(TreeNode* T)
		{
			if (front == NULL)
			{
				front = rear = T;
			}
			else
			{
				rear->prev = T;
				T->next = rear;
				rear = T;
			}
		}
		TreeNode* dequeue()
		{
			TreeNode* ptr;
			if (front == NULL)
				return NULL;
			
			if (front == rear)
			{
				ptr = front;
				front = rear = NULL;
				return ptr;
			}
			else
			{
				ptr = front;
				front = front->prev;
				return ptr;
			}
		}
		bool isEmpty() {
			if (front == NULL)
				return true;
			else
				return false;
		}
};

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

		// user function
		bool readFile(ofFileDialogResult openFileResult);
		void freeMemory();
		void DFS();
		void resetTree();
		void BFS();

		//flag variables
		int draw_flag;
		int load_flag;
		int dfs_flag;
		int bfs_flag;
	
		// other variables
		char** maze;
		int height;
		int width;
		int size = 10;	// 미로를 화면상에 나타낼 크기, 화면에 미로가 전부 안 보일 경우, 이 변수만 수정하면 된다.
		int** roomNum;
		int room_height;
		int room_width;
		TreeNode* head = NULL;
		TreeNode* target = NULL;
		stack1* S;

		
};
