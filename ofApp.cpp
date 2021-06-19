#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetFrameRate(10000);

	ofBackground(255, 255, 255);
	ofSetLineWidth(4);
	
	load_flag = 0;
	draw_flag = 0;
	dfs_flag = 0;
	bfs_flag = 0;

}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
	int i, j;
	ofSetColor(0,0,0);
	if (draw_flag == 1)
	{
		for (i = 0; i < height; i++)
		{
			for (j = 0; j < width; j++)
			{
				if (maze[i][j] == '+')
					continue;
				else if (maze[i][j] == '-')
				{
					ofDrawLine(10 + (j - 1) * size, 10 + i * size, 10 + (j + 1) * size, 10 + i * size);
				}
				else if (maze[i][j] == '|')
				{
					ofDrawLine(10 + j * size, 10 + (i - 1) * size, 10 + j * size, 10 + (i + 1) * size);
				}
				else
					continue;
			}
		}
	}
	if (dfs_flag == 1)
	{
		queue1* q = new queue1();
		q->enqueue(head);
		while (!q->isEmpty())
		{
			TreeNode* ptr = q->dequeue();
			
			if (ptr->child1 != NULL)
			{
				q->enqueue(ptr->child1);
			}
			if (ptr->child2 != NULL)
			{
				q->enqueue(ptr->child2);
			}
			if (ptr->child3 != NULL)
			{
				q->enqueue(ptr->child3);
			}

			if (ptr->room == 0)
				continue;
			
			if (ptr->visited == true)	// �湮�� ��� ��� ���
			{
				ofSetColor(0, 255, 0);	// �ʷϻ�
				ofDrawLine(10 + (ptr->x) * size, 10 + (ptr->y) * size, 10 + (ptr->parent->x) * size, 10 + (ptr->parent->y) * size);
			}
			if (ptr->path == true)	// ���� ��� ���
			{
				ofSetColor(255, 0, 0);	// ������
				ofDrawLine(10 + (ptr->x) * size, 10 + (ptr->y) * size, 10 + (ptr->parent->x) * size, 10 + (ptr->parent->y) * size);
			}
		}
	
	}
	if (bfs_flag == 1)
	{
		queue1* q = new queue1();
		q->enqueue(head);
		while (!q->isEmpty())
		{
			TreeNode* ptr = q->dequeue();

			if (ptr->child1 != NULL)
			{
				q->enqueue(ptr->child1);
			}
			if (ptr->child2 != NULL)
			{
				q->enqueue(ptr->child2);
			}
			if (ptr->child3 != NULL)
			{
				q->enqueue(ptr->child3);
			}

			if (ptr->room == 0)
				continue;

			if (ptr->visited == true)	// �湮�� ��� ��� ���
			{
				ofSetColor(0, 255, 0);	// �ʷϻ�
				ofDrawLine(10 + (ptr->x) * size, 10 + (ptr->y) * size, 10 + (ptr->parent->x) * size, 10 + (ptr->parent->y) * size);
			}
		}
		TreeNode* ptr = target;
		ofSetColor(255, 0, 0);	// ������
		while(true)
		{
			if (ptr->x == 1 && ptr->y == 1)
				break;
			ofDrawLine(10 + (ptr->x) * size, 10 + (ptr->y) * size, 10 + (ptr->parent->x) * size, 10 + (ptr->parent->y) * size);
			ptr = ptr->parent;
		}
	}

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
	if (key == 'l')
	{
		if (load_flag == 1)
		{
			freeMemory();
			dfs_flag = 0;
			bfs_flag = 0;
		}
		ofFileDialogResult openFileResult = ofSystemLoadDialog("Select");
		if (openFileResult.bSuccess)
		{
			ofLogVerbose("User selected a file");

			readFile(openFileResult);
			draw_flag = 1;
			load_flag = 1;
		}

	}
	if (key == 'q')
	{
		freeMemory();
		_Exit(0);
	}

	if (key == 'd')
	{
		resetTree();
		bfs_flag = 0;
		dfs_flag = 1;
		DFS();
	}
	if (key == 'b')
	{
		resetTree();
		bfs_flag = 1;
		dfs_flag = 0;
		BFS();
	}
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

bool ofApp::readFile(ofFileDialogResult openFileResult) {

	string fileName = openFileResult.getName();
	ofFile file(fileName);

	ofBuffer buffer(file);
	if (buffer.size() <= 0)
		return false;

	int i,j;
	height = 0;
	width = 0;
	// allocate maze[][]
	for (ofBuffer::Line it = buffer.getLines().begin(), end = buffer.getLines().end(); it != end; ++it) 
	{
		string line = *it;
		width = line.length();
		height++;
	}
	maze = (char**)malloc(sizeof(char*)*height);
	for (i = 0; i < height; i++)
	{
		maze[i] = (char*)malloc(sizeof(char)*width);
	}

	// initialize maze[][]
	int idx = 0;
	for (ofBuffer::Line it = buffer.getLines().begin(), end = buffer.getLines().end(); it != end; ++it)
	{
		string line = *it;
		for (i = 0; i < width; i++)
		{
			maze[idx][i] = line[i];
		}
		idx++;
	}

	// allocate roomNum[][]
	idx = 0;
	room_height = height / 2;
	room_width = width / 2;
	roomNum = (int**)malloc(sizeof(int*)*(room_height));
	for (i = 0; i < room_height; i++)
	{
		roomNum[i] = (int*)malloc(sizeof(int)*room_width);
	}
	// initialize roomNum[][]
	for (i = 0; i < room_height; i++)
	{
		for (j = 0; j < room_width; j++)
		{
			roomNum[i][j] = idx++;
		}
	}

	// �̷� ��� ã�⸦ ���� Tree ���� ����
	head = (TreeNode*)malloc(sizeof(TreeNode));
	head->parent = NULL;
	head->room = roomNum[0][0];
	head->x = 1;
	head->y = 1;
	head->visited = false;
	head->child1 = NULL;
	head->child2 = NULL;
	head->child3 = NULL;
	// head �ʱ�ȭ
	queue1* q = new queue1();
	q->enqueue(head);
	while (!q->isEmpty())
	{
		TreeNode* ptr = q->dequeue();
		if (ptr->room == 0)		// ù ����϶�
		{
			if (maze[ptr->y + 1][ptr->x] == ' ')	//�Ʒ��� �˻�
			{
				
				TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
				newNode->parent = ptr;
				newNode->x = ptr->x;
				newNode->y = ptr->y + 2;
				newNode->room = roomNum[(newNode->y) / 2][(newNode->x) / 2];
				newNode->child1 = NULL;
				newNode->child2 = NULL;
				newNode->child3 = NULL;
				newNode->visited = false;
				newNode->path = false;
				if (ptr->child1 == NULL)
				{
					ptr->child1 = newNode;
				}
				else if (ptr->child2 == NULL)
				{
					ptr->child2 = newNode;
				}
				else
				{
					ptr->child3 = newNode;
				}
				q->enqueue(newNode);
								
			}
			if (maze[ptr->y][ptr->x + 1] == ' ')		// ������ �˻�
			{
				TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
				newNode->parent = ptr;
				newNode->x = ptr->x + 2;
				newNode->y = ptr->y;
				newNode->room = roomNum[(newNode->y) / 2][(newNode->x) / 2];
				newNode->child1 = NULL;
				newNode->child2 = NULL;
				newNode->child3 = NULL;
				newNode->visited = false;
				newNode->path = false;

				if (ptr->child1 == NULL)
				{
					ptr->child1 = newNode;
				}
				else if (ptr->child2 == NULL)
				{
					ptr->child2 = newNode;
				}
				else
				{
					ptr->child3 = newNode;
				}
				q->enqueue(newNode);
			}
			continue;
		}
		if (maze[ptr->y - 1][ptr->x]== ' ')	// ���� �˻�
		{
			if (ptr->parent->room != roomNum[(ptr->y - 2) / 2][(ptr->x)/2])
			{
				TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
				newNode->parent = ptr;
				newNode->x = ptr->x;
				newNode->y = ptr->y - 2;
				newNode->room = roomNum[(newNode->y) / 2][(newNode->x) / 2];
				newNode->child1 = NULL;
				newNode->child2 = NULL;
				newNode->child3 = NULL;
				newNode->visited = false;
				newNode->path = false;

				if (ptr->child1 == NULL)
				{
					ptr->child1 = newNode;
				}
				else if (ptr->child2 == NULL)
				{
					ptr->child2 = newNode;
				}
				else
				{
					ptr->child3 = newNode;
				}
				q->enqueue(newNode);
			}
		}
		if (maze[ptr->y + 1][ptr->x] == ' ')	//�Ʒ��� �˻�
		{
			if (ptr->parent->room != roomNum[(ptr->y + 2) / 2][(ptr->x)/2])
			{
				TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
				newNode->parent = ptr;
				newNode->x = ptr->x;
				newNode->y = ptr->y + 2;
				newNode->room = roomNum[(newNode->y) / 2][(newNode->x) / 2];
				newNode->child1 = NULL;
				newNode->child2 = NULL;
				newNode->child3 = NULL;
				newNode->visited = false;
				newNode->path = false;

				if (ptr->child1 == NULL)
				{
					ptr->child1 = newNode;
				}
				else if (ptr->child2 == NULL)
				{
					ptr->child2 = newNode;
				}
				else
				{
					ptr->child3 = newNode;
				}
				q->enqueue(newNode);

			}
		}
		if (maze[ptr->y][ptr->x - 1] == ' ')	// ���� �˻�
		{
			if (ptr->parent->room != roomNum[(ptr->y) / 2][(ptr->x-2) / 2])
			{
				TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
				newNode->parent = ptr;
				newNode->x = ptr->x-2;
				newNode->y = ptr->y ;
				newNode->room = roomNum[(newNode->y) / 2][(newNode->x) / 2];
				newNode->child1 = NULL;
				newNode->child2 = NULL;
				newNode->child3 = NULL;
				newNode->visited = false;
				newNode->path = false;

				if (ptr->child1 == NULL)
				{
					ptr->child1 = newNode;
				}
				else if (ptr->child2 == NULL)
				{
					ptr->child2 = newNode;
				}
				else
				{
					ptr->child3 = newNode;
				}
				q->enqueue(newNode);

			}
		}
		if (maze[ptr->y][ptr->x + 1] == ' ')		// ������ �˻�
		{
			if (ptr->parent->room != roomNum[(ptr->y) / 2][(ptr->x+2) / 2])
			{
				TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
				newNode->parent = ptr;
				newNode->x = ptr->x+2;
				newNode->y = ptr->y;
				newNode->room = roomNum[(newNode->y) / 2][(newNode->x) / 2];
				newNode->child1 = NULL;
				newNode->child2 = NULL;
				newNode->child3 = NULL;
				newNode->visited = false;
				newNode->path = false;

				if (ptr->child1 == NULL)
				{
					ptr->child1 = newNode;
				}
				else if (ptr->child2 == NULL)
				{
					ptr->child2 = newNode;
				}
				else
				{
					ptr->child3 = newNode;
				}
				q->enqueue(newNode);

			}
		}
	}
	return true;
}

void ofApp::freeMemory() {
	int i, j;

	for (i = 0; i < height; i++)
	{
		free(maze[i]);
	}
	free(maze);

	for (i = 0; i < room_height; i++)
	{
		free(roomNum[i]);
	}
	free(roomNum);

	queue1* q = new queue1();
	q->enqueue(head);
	while (!q->isEmpty())
	{
		TreeNode* ptr = q->dequeue();
		if (ptr->child1 != NULL)
			q->enqueue(ptr->child1);
		if (ptr->child2 != NULL)
			q->enqueue(ptr->child2);
		if (ptr->child3 != NULL)
			q->enqueue(ptr->child3);

		free(ptr);
	}

}

void ofApp::DFS() {
	S = new stack1();	// �ִ� ��� ���� ���� �ʱ�ȭ
	head->visited = true;
	S->push(head);
	while (!S->isEmpty())	// DFS ����
	{
		if (S->Top()->x == width-2 && S->Top()->y == height-2)		// target ��忡 �������� ��� break
			break;

		if ( (S->Top()->child1 != NULL) && (S->Top()->child1->visited == false) )	// child 1�� �湮���� �ʾ��� ��
		{
			S->Top()->child1->visited = true;
			S->push(S->Top()->child1);
			continue;
		}
		else if (S->Top()->child2 != NULL && S->Top()->child2->visited == false)	// child 2�� �湮���� �ʾ��� ��
		{
			S->Top()->child2->visited = true;
			S->push(S->Top()->child2);
			continue;

		}
		else if (S->Top()->child3 != NULL && S->Top()->child3->visited == false)	// child 3�� �湮���� �ʾ��� ��
		{
			S->Top()->child3->visited = true;
			S->push(S->Top()->child3);
			continue;

		}
		else   // �湮���� ���� ��尡 ���� ���(Ȥ�� �ڽ��� ���°��)
		{
			S->pop();
		}
	}
	while (!S->isEmpty())	// ������ ��� ���Ҹ� pop�Ͽ� ���� ��� ���
	{
		S->pop()->path = true;
	}

}

void ofApp::resetTree() {
	queue1* q = new queue1();
	q->enqueue(head);
	while (!q->isEmpty())
	{
		TreeNode* ptr = q->dequeue();
		ptr->visited = false;
		ptr->path = false;
		if (ptr->child1 != NULL)
		{
			q->enqueue(ptr->child1);
		}
		if (ptr->child2 != NULL)
		{
			q->enqueue(ptr->child2);
		}
		if (ptr->child3 != NULL)
		{
			q->enqueue(ptr->child3);
		}
	}
}
void ofApp::BFS() {
	queue1* q = new queue1();	// ť �ʱ�ȭ
	q->enqueue(head);	
	while (!q->isEmpty())	
	{
		TreeNode* ptr = q->dequeue();
		ptr->visited = true;

		if (ptr->x == width - 2 && ptr->y == height - 2)		// ��ǥ��� �湮�� break
		{
			target = ptr;
			break;
		}
		if (ptr->child1 != NULL && ptr->child1->visited == false)
		{
			q->enqueue(ptr->child1);
		}
		if (ptr->child2 != NULL  && ptr->child2->visited == false)
		{
			q->enqueue(ptr->child2);
		}
		if (ptr->child3 != NULL && ptr->child3->visited == false)
		{
			q->enqueue(ptr->child3);
		}


	}

}