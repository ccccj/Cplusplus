//
//  FileCompress.h
//  文件压缩
//
//  Created by admin on 18/6/20.
//  Copyright © 2018年 Amon. All rights reserved.
//
// 1.将 文件 转化为 哈希表 记录每个字符出现了多少次
// 2.将 哈希表 建立哈夫曼树
// 3.创建 哈夫曼编码 并写入
// 4.写入源文件内容

#ifndef FileCompress_h
#define FileCompress_h

#include <fstream>
#include <string>

#include "HuffmanTree.h"

#define TXT1 "/Users/admin/Desktop/input.txt"
#define TXT2 "/Users/admin/Desktop/inputcopy.txt.Huff"

#define PAGES1 "/Users/admin/Desktop/input.pages"
#define PAGES2 "/Users/admin/Desktop/inputcopy.pages.Huff"

#define PNG1 "/Users/admin/Desktop/input.png"
#define PNG2 "/Users/admin/Desktop/inputcopy.png.Huff"

typedef long long LL;


struct CharInfo {
    
    CharInfo()
        :_count(0)
        ,_code("") {}
    
    CharInfo operator + (const CharInfo& a) {
        CharInfo ret;
        ret._count = _count + a._count;
        return ret;
    }
    
    bool operator > (const CharInfo& a) {
        return _count > a._count;
    }
    
    bool operator != (const CharInfo& a) {
        return _count != a._count;
    }
    
    char _ch;
    LL _count;
    string _code;
};

class FileCompress {
    
    typedef HuffmanTreeNode<CharInfo> Node;
    
public:
    FileCompress() {
        for (size_t i = 0; i < 256; ++i) {
            _hashInfos[i]._ch = i;
            _hashInfos[i]._count = 0;
        }
    }
    
    // 压缩
    void Compress(const char* file) {
        ifstream ifs;
        ifs.open(file);
        
        // 统计个数，创建哈希表
        char ch;
        while (ifs.get(ch)) {
            ++_hashInfos[(unsigned char)ch]._count;
        }
        
        // 创建哈夫曼树
        CharInfo invalid;
        HuffmanTree<CharInfo> h(_hashInfos, 256, invalid);
        
        // 编写哈夫曼编码
        FindHuffCode(h.GetRoot(), "");
        
        // 修改文件名
        string CompressFile = file;
        size_t p = CompressFile.find('.');
        CompressFile.insert(p, "copy");
        CompressFile += ".Huff";
        
        // 写入哈夫曼编码 和 文件内容 到压缩文件
        WriteHuffCodeandFile(file, CompressFile.c_str());
        
    }
    
    void FindHuffCode(Node* root, string now) {
        if (root == NULL) {
            return;
        }
        if (root->_left == NULL && root->_right == NULL) {
            // leaf
            root->_w._code = now;
            _hashInfos[(unsigned char)(root->_w._ch)]._code = now;
            return;
        }
        if (root->_left) {
            FindHuffCode(root->_left, now + '0');
        }
        if (root->_right) {
            FindHuffCode(root->_right, now + '1');
        }
    }
    
    
    void WriteHuffCodeandFile(const char* file, const char* CompressFile) {
        
        // 哈夫曼编码
        ofstream ofs;
        ofs.open(CompressFile);
        
        ////////
        /*
        for (int i = 0; i < 256; ++i) {
            if (_hashInfos[i]._count != 0) {
                ofs << _hashInfos[i]._ch << endl;
                ofs << _hashInfos[i]._count << endl;
            }
        }
        CharInfo info;
        info._count = -1;
        ofs << info._ch << endl;
        ofs << info._count << endl;
        */
        
        for (int i = 0; i < 256; ++i) {
            if (_hashInfos[i]._count != 0) {
                ofs.write((char*)&(_hashInfos[i]), sizeof(CharInfo));
            }
        }
        CharInfo info;
        info._count = -1;
        
        ofs.write((char*)&info, sizeof(CharInfo));
        
        
        // 文件内容
        
        ifstream ifs;
        ifs.open(file);
        
        char ch;
        int value = 0;
        int pos = 0;
        while (ifs.get(ch)) {
            string& code = _hashInfos[(unsigned char)ch]._code;
            for (int i = 0; code[i]; ++i) {
                if (code[i] == '1') {
                    value |= (1 << pos);
                }
                ++pos;
                if (pos == 8) {
                    ofs.put(value);
                    value = 0;
                    pos = 0;
                }
            }
        }
        if (pos > 0) {
            ofs.put(value);
        }
    }
    
    
    
    ///////////////////////////////////////////////////////////////
    
    
    
    void UncompressFile(const char* CompressFile) {
        ifstream ifs;
        ifs.open(CompressFile);
        
        // 修改文件名
        string file(CompressFile);
        size_t p = file.rfind('.');
        file.erase(file.begin() + p, file.end());
        
        ofstream ofs;
        ofs.open(file.c_str());
        
        CharInfo tmp;
        
        // 读入哈夫曼表
        /*
        do {
            ifs >> tmp._ch >> tmp._count;
            if (tmp._count > 0) {
                _hashInfos[tmp._ch]._count = tmp._count;
            }
        } while (tmp._count > 0);
        */
        
        do {
            ifs.read((char*)&tmp, sizeof(CharInfo));
            if (tmp._count > 0) {
                _hashInfos[(unsigned char)tmp._ch]._count = tmp._count;
            }
        } while (tmp._count > 0);
        
        
        // 创建哈弗曼树
        CharInfo InValid;
        HuffmanTree<CharInfo> tree(_hashInfos, 256, InValid);
        Node* root = tree.GetRoot();
        
        // 写入文件内容
        char value;
        long long int count = root->_w._count;
        
        Node* cur = root;
        while (ifs.get(value)) {
            for (int i = 0; i < 8; ++i) {
                if (value & (1 << i)) {
                    cur = cur->_right;
                } else {
                    cur = cur->_left;
                }
                if (cur->_left == NULL && cur->_right == NULL) {
                    // 叶子结点
                    ofs.put(cur->_w._ch);
                    cur = root;
                    if (--count == 0) {
                        return;
                    }
                }
            }
        }
    }
    
    ~FileCompress() {
        
    }
    
protected:
    CharInfo _hashInfos[256];
};

void test1() {
    FileCompress f;
    f.Compress(TXT1);
}

void test2() {
    FileCompress f;
    f.UncompressFile(TXT2);
}
#endif /* FileCompress_h */


