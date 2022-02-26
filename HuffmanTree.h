//
//  HuffmanTree.h
//  文件压缩
//
//  Created by admin on 18/6/20.
//  Copyright © 2018年 Amon. All rights reserved.
//

#ifndef HuffmanTree_h
#define HuffmanTree_h

#include <queue>

template <class W>
struct HuffmanTreeNode {
    
    HuffmanTreeNode(W w)
        :_w(w)
        ,_left(NULL)
        ,_right(NULL) {}
    
public:
    W _w;
    HuffmanTreeNode<W>* _left;
    HuffmanTreeNode<W>* _right;
};

template <class W>
class HuffmanTree {
    
    typedef HuffmanTreeNode<W> Node;
    struct cmp {
        bool operator() (Node* l, Node* r) {
            return l->_w > r->_w;
        }
    };
    
public:
    HuffmanTree(W* hashInfos, size_t n, const W& invalid) {
        
        priority_queue<Node*, vector<Node*>, cmp> q;
        
        for (int i = 0; i < n; ++i) {
            if (hashInfos[i] != invalid) {
                Node* new_node = new Node(hashInfos[i]);
                q.push(new_node);
            }
        }
        while (q.size() > 1) {
            Node* left = q.top();
            q.pop();
            Node* right = q.top();
            q.pop();
            Node* parent = new Node(left->_w + right->_w);
            parent->_left = left;
            parent->_right = right;
            q.push(parent);
        }
        _root = q.top();
    }
    
    Node* GetRoot() {
        return _root;
    }
    
    ~HuffmanTree() {
        Destroy(_root);
        _root = NULL;
    }
    
    void Destroy(Node* root) {
        if (root == NULL) {
            return;
        }
        Destroy(root->_left);
        Destroy(root->_right);
        
        delete root;
    }
    
private:
    HuffmanTree(const HuffmanTree<W>& h);
    HuffmanTree<W>& operator=(const HuffmanTree<W>& h);
    
protected:
    Node* _root;
};




#endif /* HuffmanTree_h */
